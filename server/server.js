const express = require('express');
const http = require('http')
const bodyParser = require('body-parser');
const socketIO = require('socket.io');
const path = require('path')
const { BASE_URI, SERVER_PORT, CLIENT_PATH} = require('./config');
const API_URI = `${BASE_URI}/api`;

const app = express();

// Static hosting of client page
app.use(express.static(CLIENT_PATH));

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

function emitStatusUpdate() {
  io.emit('status_update_available');
}

const { setSerialEventCallback , status} = require('./serialManager');

setSerialEventCallback(emitStatusUpdate);

app.use((_, res, next) => {
  res.setHeader('access-control-allow-origin', '*');
  res.setHeader('access-control-allow-headers',
    'Origin, X-Requested-With, Content-Type, Accept');
  return next();
});

app.get(`${API_URI}/status`, async (req, res) => {
   res.status(200).json(status);
});

const controlRoutes = require('./routes/controlRoutes');
app.use(`${API_URI}/control`, controlRoutes);

server.listen(SERVER_PORT, () => {
  console.log(`Server listening on port ${SERVER_PORT}`);
});

module.exports = io;