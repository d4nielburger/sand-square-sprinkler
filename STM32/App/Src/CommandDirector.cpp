/*
 * CommandDirector.cpp
 *
 *  Created on: Oct 31, 2023
 *      Author: burge
 */

#include "CommandDirector.hpp"

CommandDirector::CommandDirector() {
}

void CommandDirector::directControlCommand(CommandQueue &commandQueue,
		CommandQueue &garagePumpCmd, CommandQueue &tankFillCmd,
		CommandQueue &pressWaterCmd) {

	// Get command
	Commands_t command;
	if (commandQueue.receive(command) != CommandQueueStatus::Success) {
		command = NONE;
	}

	// Update all statuses
	if (command == GET_STATUS_ALL) {
		garagePumpCmd.send(command);
		tankFillCmd.send(command);
		pressWaterCmd.send(command);
	}

	// garage pump commands
	if (command == GARAGE_PUMP_START || command == GARAGE_PUMP_STOP) {
		garagePumpCmd.send(command);
	}

	// tank fill commands
	if (command == FILL_LARGE_TANK || command == FILL_SMALL_TANK
			|| command == FILL_NO_TANK) {
		tankFillCmd.send(command);
	}

	// pressure water commands
	if (command == SPRINKLER_START || command == SPRINKLER_STOP
			|| command == HOSE_START || command == HOSE_STOP
			//|| command == PRESSURE_PUMP_START
			//|| command == PRESSURE_PUMP_STOP
			) {
		pressWaterCmd.send(command);
	}
}
