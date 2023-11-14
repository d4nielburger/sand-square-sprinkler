/*
 * GaragePumpControl.cpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#include "GaragePumpControl.hpp"

GaragePumpControl::GaragePumpControl(CommandQueue &commandQueue, StatusQueue &statQueue, DO_24V &pump) :
		commandQueue(commandQueue), statusQueue(statQueue), pump(pump) {
	state = INIT;
}

void GaragePumpControl::run() {
	// Get command
	Commands_t command;
	if (commandQueue.receive(command) != CommandQueueStatus::Success) {
		command = NONE;
	}

	switch (state) {
	case INIT:
		if (command == GARAGE_PUMP_STOP) {
			state = OFF;
			sendStatus();
		} else {
			state = ON;
			sendStatus();
		}
		break;
	case ON:
		pump.setOn();

		if (command == GARAGE_PUMP_STOP) {
			state = OFF;
			sendStatus();
		}
		break;
	case OFF:
		pump.setOff();

		if (command == GARAGE_PUMP_STOP) {
			state = ON;
			sendStatus();
		}
		break;
	default:
		state = INIT;
		break;
	}

}

void GaragePumpControl::sendStatus() {
	switch (state) {
		case INIT:
			// No status
			break;
		case ON:
			statusQueue.send(GARAGE_PUMP_RUNNING);
			break;
		case OFF:
			statusQueue.send(GARAGE_PUMP_STOPPED);
			break;
		default:
			// No status
			break;
		}
}
