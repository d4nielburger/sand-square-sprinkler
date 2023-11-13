const express = require('express');
const http = require('http')
const bodyParser = require('body-parser');
const fs = require('fs').promises;
const socketIO = require('socket.io');

// Config
const PORT = 3000;
const API_URI = '/sss/api'

const app = express();
app.use(bodyParser.json());
const server = http.createServer(app);
const io = socketIO(server, {
  cors: {
    origin: "*", // Allow all origins
    methods: ["GET", "POST"],
    allowedHeaders: ["Origin", "X-Requested-With", "Content-Type", "Accept"],
    credentials: true,
  },
});

app.use((_, res, next) => {
  res.setHeader('access-control-allow-origin', '*');
  res.setHeader('access-control-allow-headers',
    'Origin, X-Requested-With, Content-Type, Accept');
  return next();
});

app.get(`${API_URI}/status`, async (req, res) => {
  try {
    const data = await fs.readFile('status.json', 'utf8');
    const status = JSON.parse(data);
    res.status(200).json(status);
  } catch (error) {
    console.error("Error reading status.json:", error);
    res.status(500).send('Server error');
  }
});

app.post(`${API_URI}/control/garage-pump`, async (req, res) => {
  const { state } = req.body;
  const success = await updateStatus('garagePump',state);
  sendGenericResponse(res,success);
});

app.post(`${API_URI}/control/tank`, async (req, res) => {
  const { select } = req.body;
  const success = await updateStatus('tankSelect',select);
  sendGenericResponse(res,success);
});

app.post(`${API_URI}/control/hose`, async (req, res) => {
  const { state } = req.body;
  const success = await updateStatus('hose',state);
  sendGenericResponse(res,success);
});

app.post(`${API_URI}/control/sprinkler`, async (req, res) => {
  const { state } = req.body;
  const success = await updateStatus('sprinkler',state);
  sendGenericResponse(res,success);
});

server.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});

// For testing
async function updateStatus(key, newState) {
  try {
    const data = await fs.readFile('status.json', 'utf8');
    const statuses = JSON.parse(data);

    statuses[key] = newState;

    await fs.writeFile('status.json', JSON.stringify(statuses, null, 2), 'utf8');
    console.log(`Status updated for ${key}`);

    io.emit('status_update_available');

    return true; // success
  } catch (error) {
    console.error(`Error updating the status for ${key}:`, error);
    return false; // failure
  }
}

function sendGenericResponse(res,success) {
  if (success) {
    res.status(200).json({ message: "Request successful" });
  } else {
    res.status(500).send('Server error');
  }  
}