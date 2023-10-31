/*
 * PressurizedWaterControl.cpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#include "PressurizedWaterControl.hpp"

PressurizedWaterControl::PressurizedWaterControl(QueueHandle_t cmdQueue,
		DO_24V &pump, DO_24V &vHose, DO_24V &vSprinkler,
		DI_24V &swSmallTankEmpty) :
		commandQueue(cmdQueue), pump(pump), valveHose(vHose), valveSprinkler(
				vSprinkler), switchSmallTankEmpty(swSmallTankEmpty) {
	state = INIT;
}

void PressurizedWaterControl::run() {
	// Get command received from high level controller
	Commands_t command;
	if (xQueueReceive(commandQueue, &command, (TickType_t) 0) != pdPASS) {
		command = NONE;
	}

	// FSM
	switch (state) {
	case INIT:
		pump.setOff();
		valveSprinkler.setOff();
		valveHose.setOff();

		if (command == SPRINKLER_START) {
			state = SPRINKLER;
		} else if (command == HOSE_START) {
			state = HOSE;
		} else {
			state = OFF;
		}
		break;
	case OFF:
		pump.setOff();
		valveSprinkler.setOff();
		valveHose.setOff();

		if (command == SPRINKLER_START) {
			state = SPRINKLER;
		} else if (command == HOSE_START) {
			state = HOSE;
		}
		break;
	case SPRINKLER:
		if (switchSmallTankEmpty.read()) {
			pump.setOff();
		} else {
			pump.setOn();
		}

		valveSprinkler.setOn();
		valveHose.setOff();

		if (command == SPRINKLER_STOP) {
			state = OFF;
		} else if (command == HOSE_START) {
			state = HOSE;
		}
		break;
	case HOSE:
		if (switchSmallTankEmpty.read()) {
			pump.setOff();
		} else {
			pump.setOn();
		}

		valveSprinkler.setOff();
		valveHose.setOn();

		if (command == HOSE_STOP) {
			state = OFF;
		} else if (command == SPRINKLER_START) {
			state = SPRINKLER;
		}
		break;
	default:
		state = INIT;
		break;
	}
}
