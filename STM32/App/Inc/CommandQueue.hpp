/*
 * CommandQue.hpp
 *
 *  Created on: Oct 31, 2023
 *      Author: burge
 */

#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "commands.h"

enum class CommandQueueStatus {
	Success, Failure, Timeout
};

class CommandQueue {
private:
	size_t queueLength;
	QueueHandle_t xCommandQueue;
	static const TickType_t ticksToWait = (TickType_t) 0;

public:
	CommandQueue(size_t queueLength);
	CommandQueueStatus send(const Commands_t &command);
	CommandQueueStatus receive(Commands_t &command);

};

#endif // COMMAND_QUEUE_H
