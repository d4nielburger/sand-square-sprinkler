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

server.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});

module.exports = io;