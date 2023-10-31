/*
 * TankFillControl.cpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#include "TankFillControl.hpp"

TankFillControl::TankFillControl(QueueHandle_t cmdQueue,
		DO_24V &vSmallTankInlet,
		DO_24V &vLargeTankInlet,
		DI_24V &swSmallTankFull,
		DI_24V &swLargeTankFull) :
		commandQueue(cmdQueue),
		valveSmallTankInlet(vSmallTankInlet),
		valveLargeTankInlet(vLargeTankInlet),
		switchSmallTankFull(swSmallTankFull),
		switchLargeTankFull(swLargeTankFull) {
	state = INIT;
}

void TankFillControl::run() {
	// Get command received from high level controller
	Commands_t command = NONE;
	xQueueReceive(commandQueue, &command, (TickType_t) 0);

	// FSM
	switch (state) {
	case INIT:
		valveLargeTankInlet.setOff();
		valveSmallTankInlet.setOff();

		if (command == FILL_LARGE_TANK) {
			state = FILL_LARGE;
		} else if (command == FILL_NO_TANK) {
			state = DRAIN;
		} else {
			state = FILL_SMALL;
		}
		break;
	case FILL_SMALL:
		if (switchSmallTankFull.read()) {
			valveSmallTankInlet.setOff();
		} else {
			valveSmallTankInlet.setOn();
		}

		if (command == FILL_LARGE_TANK) {
			state = FILL_LARGE;
		} else if (command == FILL_NO_TANK) {
			state = DRAIN;
		}
		break;
	case FILL_LARGE:
		if (switchLargeTankFull.read()) {
			valveLargeTankInlet.setOff();
		} else {
			valveLargeTankInlet.setOn();
		}

		if (command == FILL_SMALL_TANK) {
			state = FILL_SMALL;
		} else if (command == FILL_NO_TANK) {
			state = DRAIN;
		}
		break;
	case DRAIN:
		valveLargeTankInlet.setOff();
		valveSmallTankInlet.setOff();

		if (command == FILL_SMALL_TANK) {
			state = FILL_SMALL;
		} else if (command == FILL_LARGE_TANK) {
			state = FILL_LARGE;
		}
		break;
	default:
		state = INIT;
		break;
	}
}
