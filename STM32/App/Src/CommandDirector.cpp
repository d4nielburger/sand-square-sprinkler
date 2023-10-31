/*
 * CommandDirector.cpp
 *
 *  Created on: Oct 31, 2023
 *      Author: burge
 */

#include "CommandDirector.hpp"

CommandDirector::CommandDirector() {
}

void CommandDirector::directControlCommand(QueueHandle_t commandQueue,
		QueueHandle_t garagePumpCmd, QueueHandle_t tankFillCmd,
		QueueHandle_t pressWaterCmd) {

	// Get command
	Commands_t command = NONE;
	xQueueReceive(commandQueue, &command, (TickType_t) 0);

	// garage pump commands
	if (command == GARAGE_PUMP_START ||
		command == GARAGE_PUMP_STOP)
	{
		xQueueSend(garagePumpCmd, static_cast<void*>(&command), (TickType_t ) 0);
	}

	// tank fill commands
	if (command == FILL_LARGE_TANK ||
		command == FILL_SMALL_TANK ||
		command == FILL_NO_TANK)
	{
		xQueueSend(tankFillCmd, static_cast<void*>(&command), (TickType_t ) 0);
	}

	// pressure water commands
	if (command == SPRINKLER_START ||
		command == SPRINKLER_STOP ||
		command == HOSE_START ||
		command == HOSE_STOP ||
		command == PRESSURE_PUMP_START ||
		command == PRESSURE_PUMP_STOP ||
		command == NONE)
	{
		xQueueSend(pressWaterCmd, static_cast<void*>(&command), (TickType_t ) 0);
	}
}
