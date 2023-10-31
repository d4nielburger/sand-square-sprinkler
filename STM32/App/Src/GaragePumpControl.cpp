/*
 * GaragePumpControl.cpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#include "GaragePumpControl.hpp"

GaragePumpControl::GaragePumpControl(CommandQueue &commandQueue, DO_24V &pump) :
		commandQueue(commandQueue), pump(pump) {
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
		} else {
			state = ON;
		}
		break;
	case ON:
		pump.setOn();

		if (command == GARAGE_PUMP_STOP) {
			state = OFF;
		}
		break;
	case OFF:
		pump.setOff();

		if (command == GARAGE_PUMP_STOP) {
			state = ON;
		}
		break;
	default:
		state = INIT;
		break;
	}

}
