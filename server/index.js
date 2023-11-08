const express = require("express");
const bodyParser = require('body-parser');
const fs = require('fs').promises;

// Config
const PORT = 3000;
const API_URI = '/sss/api'

const app = express();
app.use(bodyParser.json());

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

app.post(`${API_URI}/control/garage-pump`, (req, res) => {
    const { state } = req.body;
    console.log(`Garage pump control was triggered. New state: ${state}`);
    // handle the garage pump control
    res.status(200).json({ message: "Request successful" });
});

app.post(`${API_URI}/control/tank`, (req, res) => {
    const { select } = req.body;
    console.log(`Tank fill control was triggered. Option selected: ${select}`);
    // handle the tank control
    res.status(200).json({ message: "Request successful" });
});

app.post(`${API_URI}/control/hose`, (req, res) => {
    const { state } = req.body;
    console.log(`Hose control was triggered. New state: ${state}`);
    // logic to handle the hose control
    res.status(200).json({ message: "Request successful" });
});

app.post(`${API_URI}/control/sprinkler`, (req, res) => {
    const { state } = req.body;
    console.log(`Sprinkler control was triggered. New state: ${state}`);
    // handle the sprinkler control
    res.status(200).json({ message: "Request successful" });
});


app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});