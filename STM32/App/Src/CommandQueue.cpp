/*
 * CommandQue.cpp
 *
 *  Created on: Oct 31, 2023
 *      Author: burge
 */

#include "CommandQueue.hpp"

CommandQueue::CommandQueue(size_t queueLength) :
		queueLength(queueLength) {
	xCommandQueue = xQueueCreate(queueLength, sizeof(Commands_t));
	if (xCommandQueue == nullptr) {
		// Handle queue creation failure
	}
}

CommandQueueStatus CommandQueue::send(const Commands_t &command) {
	BaseType_t result = xQueueSend(xCommandQueue, &command, ticksToWait);
	if (result == pdPASS) {
		return CommandQueueStatus::Success;
	} else if (result == errQUEUE_FULL) {
		return CommandQueueStatus::Timeout;
	} else {
		return CommandQueueStatus::Failure;
	}
}

CommandQueueStatus CommandQueue::receive(Commands_t &command) {
	BaseType_t result = xQueueReceive(xCommandQueue, &command, ticksToWait);
	if (result == pdPASS) {
		return CommandQueueStatus::Success;
	} else if (result == errQUEUE_EMPTY) {
		return CommandQueueStatus::Timeout;
	} else {
		return CommandQueueStatus::Failure;
	}
}
