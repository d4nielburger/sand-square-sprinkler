/*
 * CommandDirector.hpp
 *
 *  Created on: Oct 31, 2023
 *      Author: burge
 */

#ifndef SRC_COMMANDDIRECTOR_HPP_
#define SRC_COMMANDDIRECTOR_HPP_

#include "FreeRTOS.h"
#include "queue.h"
#include "commands.h"

class CommandDirector {
private:
	CommandDirector();
public:
	static void directControlCommand(QueueHandle_t command,
			QueueHandle_t garagePumpCmd, QueueHandle_t tankFillCmd,
			QueueHandle_t pressWaterCmd);
};

#endif /* SRC_COMMANDDIRECTOR_HPP_ */
