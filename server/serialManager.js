const serialPort = require('serialport');
const readline = require('@serialport/parser-readline');
let serialEventCallback;

const port = new serialPort.SerialPort({
    path: '/dev/ttyACM0',
    baudRate: 115200
});

const parser = port.pipe(new readline.ReadlineParser({ delimiter: '\n\r' }));

const status = {
    garagePump: '',
    tank: '',
    sprinkler: '',
    hose: '',
};

port.on('open', () => {
    console.log('Serial Port Open');
});

parser.on('data', (data) => {
    console.log('Data from STM32:', data);
    updateStatusFromSerial(data);
    if (serialEventCallback) {
        serialEventCallback();
    }
});

function setSerialEventCallback(callback) {
    serialEventCallback = callback;
}

function sendSerialCommand(command) {
    port.write(command, (err) => {
        if (err) {
            console.log('Error writing to serial:', err.message);
        }
    });
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
            status.tank = 'large';
            break;
        case 'SMALL_TANK_SELECTED':
            status.tank = 'small';
            break;
        case 'NO_TANK_SELECTED':
            status.tank = 'drain';
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
        default:
            console.log(`Unknown status received: ${data}`);
    }
}

function getStatusUpdate() {
    sendSerialCommand('GET_STATUS_ALL\r');
}

setInterval(getStatusUpdate, 1000);

module.exports = { sendSerialCommand, setSerialEventCallback, status };