/*
 * CommandDirector.hpp
 *
 *  Created on: Oct 31, 2023
 *      Author: burge
 */

#ifndef SRC_COMMANDDIRECTOR_HPP_
#define SRC_COMMANDDIRECTOR_HPP_

#include "FreeRTOS.h"
#include "CommandQueue.hpp"
#include "commands.h"

class CommandDirector {
private:

public:
	CommandDirector();
	static void directControlCommand(CommandQueue &commandQueue,
			CommandQueue &garagePumpCmd, CommandQueue &tankFillCmd,
			CommandQueue &pressWaterCmd);
};

#endif /* SRC_COMMANDDIRECTOR_HPP_ */
