/*
 * TankFillControl.cpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#include "TankFillControl.hpp"

TankFillControl::TankFillControl(CommandQueue &cmdQueue, StatusQueue &statQueue,
		DO_24V &vSmallTankInlet, DO_24V &vDrain, DI_24V &swSmallTankFull) :
		commandQueue(cmdQueue), statusQueue(statQueue), valveSmallTankInlet(
				vSmallTankInlet), valveDrain(vDrain), switchSmallTankFull(
				swSmallTankFull) {
	state = INIT;
}

void TankFillControl::run() {
	// Get command
	Commands_t command;
	if (commandQueue.receive(command) != CommandQueueStatus::Success) {
		command = NONE;
	}

	FsmStates_t oldState = state;

	// FSM
	switch (state) {
	case INIT:
		valveDrain.setOn();
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

		valveDrain.setOff();

		if (command == FILL_LARGE_TANK) {
			state = FILL_LARGE;
		} else if (command == FILL_NO_TANK) {
			state = DRAIN;
		}
		break;
	case FILL_LARGE:
		valveDrain.setOff();
		valveSmallTankInlet.setOff();

		if (command == FILL_SMALL_TANK) {
			state = FILL_SMALL;
		} else if (command == FILL_NO_TANK) {
			state = DRAIN;
		}
		break;
	case DRAIN:
		valveDrain.setOn();
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

	if (command != NONE) {
		sendStatus();
	}
}

void TankFillControl::sendStatus() {
	switch (state) {
		case INIT:
			// no status
			break;
		case FILL_SMALL:
			statusQueue.send(SMALL_TANK_SELECTED);
			break;
		case FILL_LARGE:
			statusQueue.send(LARGE_TANK_SELECTED);
			break;
		case DRAIN:
			statusQueue.send(NO_TANK_SELECTED);
			break;
		default:
			// no status
			break;
		}
}
