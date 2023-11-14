/*
 * PressurizedWaterControl.cpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#include "PressurizedWaterControl.hpp"

PressurizedWaterControl::PressurizedWaterControl(CommandQueue &cmdQueue,
		StatusQueue &statQueue, DO_24V &pump, DO_24V &vHose, DO_24V &vSprinkler,
		DI_24V &swSmallTankEmpty) :
		commandQueue(cmdQueue), statusQueue(statQueue), pump(pump), valveHose(
				vHose), valveSprinkler(vSprinkler), switchSmallTankEmpty(
				swSmallTankEmpty) {
	state = INIT;
}

void PressurizedWaterControl::run() {
	// Get command
	Commands_t command;
	if (commandQueue.receive(command) != CommandQueueStatus::Success) {
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
			sendStatus();
		} else if (command == HOSE_START) {
			state = HOSE;
			sendStatus();
		} else {
			state = OFF;
			sendStatus();
		}
		break;
	case OFF:
		pump.setOff();
		valveSprinkler.setOff();
		valveHose.setOff();

		if (command == SPRINKLER_START) {
			state = SPRINKLER;
			sendStatus();
		} else if (command == HOSE_START) {
			state = HOSE;
			sendStatus();
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
			sendStatus();
		} else if (command == HOSE_START) {
			state = HOSE;
			sendStatus();
		}
		break;
	case HOSE:
		if (switchSmallTankEmpty.read()) {
			pump.setOff();
			sendStatus();
		} else {
			pump.setOn();
			sendStatus();
		}

		valveSprinkler.setOff();
		valveHose.setOn();

		if (command == HOSE_STOP) {
			state = OFF;
			sendStatus();
		} else if (command == SPRINKLER_START) {
			state = SPRINKLER;
			sendStatus();
		}
		break;
	default:
		state = INIT;
		break;
	}
}

void PressurizedWaterControl::sendStatus() {
	switch (state) {
	case INIT:
		// no status
		break;
	case OFF:
		statusQueue.send(SPRINKLER_STOPPED);
		statusQueue.send(HOSE_STOPPED);
		break;
	case SPRINKLER:
		statusQueue.send(SPRINKLER_RUNNING);
		statusQueue.send(HOSE_STOPPED);
		break;
	case HOSE:
		statusQueue.send(SPRINKLER_STOPPED);
		statusQueue.send(HOSE_RUNNING);
		break;
	default:
		// no status
		break;
	}
}
