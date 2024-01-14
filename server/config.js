// Server config
const BASE_URI = "/sss";
const SERVER_PORT = "3000";
const CLIENT_PATH = "../dist"

// Serial config
const SERIAL_PORT = "/dev/ttyACM0";
const SERIAL_BAUD = 115200;
const SERIAL_RECON_INTERV = 5000;
const SERIAL_UPDATE_INTERV = 1500;

module.exports = { BASE_URI, SERVER_PORT, CLIENT_PATH, SERIAL_PORT, SERIAL_BAUD, SERIAL_RECON_INTERV, SERIAL_UPDATE_INTERV };