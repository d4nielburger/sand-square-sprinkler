const express = require('express');
const router = express.Router();
const { sendSerialCommand } = require('../serialManager');

router.post('/garage-pump', async (req, res) => {
    const { state } = req.body;
    let command;
    switch (state) {
        case 'on':
            command = 'GARAGE_PUMP_START\r';
            break;
        case 'off':
            command = 'GARAGE_PUMP_STOP\r';
            break;
        default:
            break;
    }
    if (command) {
        sendSerialCommand(command);
        res.status(200).json({ message: "Command sent successfully" });
    } else {
        console.error("Unkown request value:", req.body);
        res.status(500).send('Unkown value');
    }
});

router.post('/tank', async (req, res) => {
    const { select } = req.body;
    let command;
    switch (select) {
        case 'small':
            command = 'FILL_SMALL_TANK\r';
            break;
        case 'large':
            command = 'FILL_LARGE_TANK\r';
            break;
        case 'none':
            command = 'FILL_NO_TANK\r';
            break;
        default:
            break;
    }
    if (command) {
        sendSerialCommand(command);
        res.status(200).json({ message: "Command sent successfully" });
    } else {
        console.error("Unkown request value:", req.body);
        res.status(500).send('Unkown value');
    }
});

router.post('/hose', async (req, res) => {
    const { state } = req.body;
    let command;
    switch (state) {
        case 'on':
            command = 'HOSE_START\r';
            break;
        case 'off':
            command = 'HOSE_STOP\r';
            break;
        default:
            break;
    }
    if (command) {
        sendSerialCommand(command);
        res.status(200).json({ message: "Command sent successfully" });
    } else {
        console.error("Unkown request value:", req.body);
        res.status(500).send('Unkown value');
    }
});

router.post('/sprinkler', async (req, res) => {
    const { state } = req.body;
    let command;
    switch (state) {
        case 'on':
            command = 'SPRINKLER_START\r';
            break;
        case 'off':
            command = 'SPRINKLER_STOP\r';
            break;
        default:
            break;
    }
    if (command) {
        sendSerialCommand(command);
        res.status(200).json({ message: "Command sent successfully" });
    } else {
        console.error("Unkown request value:", req.body);
        res.status(500).send('Unkown value');
    }
});

module.exports = router;
