/*
 * CommandDirector.cpp
 *
 *  Created on: Oct 31, 2023
 *      Author: burge
 */

#include "CommandDirector.hpp"

void CommandDirector::directControlCommand(QueueHandle_t command,
		QueueHandle_t garagePumpCmd, QueueHandle_t tankFillCmd,
		QueueHandle_t pressWaterCmd) {

	// Get command
	Commands_t command = NONE;
	xQueueReceive(commandQueue, &command, (TickType_t) 0);

	switch (command) {
	case GARAGE_PUMP_START:
		break;
	case GARAGE_PUMP_STOP:
		break;
	case FILL_LARGE_TANK:
		break;
	case FILL_SMALL_TANK:
		break;
	case FILL_NO_TANK:
		break;
	case SPRINKLER_START:
		break;
	case SPRINKLER_STOP:
		break;
	case HOSE_START:
		break;
	case HOSE_STOP:
		break;
	case PRESSURE_PUMP_START:
		break;
	case PRESSURE_PUMP_STOP:
		break;
	case NONE:
		break;
	default:
		break;
	}
}
