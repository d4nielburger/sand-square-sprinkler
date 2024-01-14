const serialPort = require('serialport');
const readline = require('@serialport/parser-readline');
const { SERIAL_PORT, SERIAL_BAUD } = require('./config');
const { SERIAL_UPDATE_INTERV, SERIAL_RECON_INTERV } = require('./config');
let serialEventCallback;

const port = new serialPort.SerialPort({
    path: SERIAL_PORT,
    baudRate: SERIAL_BAUD
});

const parser = port.pipe(new readline.ReadlineParser({ delimiter: '\n\r' }));

const status = {
    garagePump: '',
    tankSelect: '',
    sprinkler: '',
    hose: '',
};

port.on('open', () => {
    console.log('Serial Port Open');
});

port.on('error', (err) => {
    console.error('***Serial Port Error:', err.message);
});

port.on('close', () => {
    console.log('Serial Port Disconnected');
    reconnectSerialPort();
});

parser.on('data', (data) => {
    console.log('Data from STM32:', data);
    updateStatusFromSerial(data);
    if (serialEventCallback) {
        serialEventCallback();
    }
});

function reconnectSerialPort() {
    console.log('Attempting to reconnect to the serial port...');

    setTimeout(() => {
        if (! port.isOpen){
            port.open((err) => {
                if (err) {
                    console.error('Failed to reopen the serial port:', err.message);
                    reconnectSerialPort();
                } else {
                    console.log('Serial port reconnected.');
                }
            });
        }
    }, SERIAL_RECON_INTERV);
}

function setSerialEventCallback(callback) {
    serialEventCallback = callback;
}

function sendSerialCommand(command) {
    if (port.isOpen) {
        port.write(command, (err) => {
            if (err) {
                console.error('***ERROR writing to serial:', err.message);
            }
        });
    } else {
        console.error('Serial port not open. Cannot send command:', command);
    }
}

function updateStatusFromSerial(data) {
    switch (data.trim()) {
        case 'GARAGE_PUMP_RUNNING':
            status.garagePump = 'on';
            break;
        case 'GARAGE_PUMP_STOPPED':
            status.garagePump = 'off';
            break;
        case 'LARGE_TANK_SELECTED':
            status.tankSelect = 'large';
            break;
        case 'SMALL_TANK_SELECTED':
            status.tankSelect = 'small';
            break;
        case 'NO_TANK_SELECTED':
            status.tankSelect = 'none';
            break;
        case 'SPRINKLER_RUNNING':
            status.sprinkler = 'on';
            break;
        case 'SPRINKLER_STOPPED':
            status.sprinkler = 'off';
            break;
        case 'HOSE_RUNNING':
            status.hose = 'on';
            break;
        case 'HOSE_STOPPED':
            status.hose = 'off';
            break;
        case 'ERROR_UNKNOWN_CMD':
            console.error(`***ERROR received from STM: ${data}`);
            break;
        default:
            console.error(`Unknown status received: ${data}`);
            break;
    }
}

function getStatusUpdate() {
    sendSerialCommand('GET_STATUS_ALL\r');
}

setInterval(getStatusUpdate, SERIAL_RECON_INTERV);

module.exports = { sendSerialCommand, setSerialEventCallback, status };