# sand-square-sprinkler
System to control water sprinklers and manage the water reservoir.
![Artwork](overview-dalle.png)

## Table of Contents
- [sand-square-sprinkler](#sand-square-sprinkler)
  - [Table of Contents](#table-of-contents)
  - [System Overview](#system-overview)
  - [Controller Block Diagram](#controller-block-diagram)
  - [Responsibilities](#responsibilities)
  - [ToDo](#todo)
    - [STM](#stm)
    - [Raspi - Server](#raspi---server)
    - [Webclient](#webclient)
  - [Requirements](#requirements)
    - [GUI](#gui)

## System Overview
![System](SA-SD/overview-1.png)
## Controller Block Diagram
![Block Diagram](SA-SD/overview-2.png)

## Responsibilities
**Bachmann**
- Server/Client?
  
**Burger**
- STM32

## ToDo
- Discuss block diagram with MDC
### STM
- VirtualComPort Handler
- Status Signals

### Raspi - Server
- Com Port interface
- High level controller
- Database
- Webserver

### Webclient
- GUI Mainpage

## Requirements
### GUI
**Controls**
- Garage Pump On/Off
- Fill tank: Small/Large/none
- Sprinkler On/Off
- Hose On/Off
- Sprinkler On [for x Minutes]

**Status**
- Garage pump status
- Fill tank status
- Sprinkler status
- Hose status

**Visual System Overview**
- Optional: Display a visual overview of the System with all pumps, valves and level switches

**Diverse**
- Alive signal