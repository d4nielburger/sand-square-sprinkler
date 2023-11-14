/*
 * StatusQueue.cpp
 *
 *  Created on: Nov 14, 2023
 *      Author: burge
 */

#include "StatusQueue.hpp"

StatusQueue::StatusQueue(size_t queueLength) :
		queueLength(queueLength) {
	xStatusQueue = xQueueCreate(queueLength, sizeof(Status_t));
	if (xStatusQueue == nullptr) {
		// Handle queue creation failure
	}
}

StatusQueueStatus StatusQueue::send(const Status_t &status) {
	BaseType_t result = xQueueSend(xCommandQueue, &status, ticksToWait);
	if (result == pdPASS) {
		return StatusQueueStatus::Success;
	} else if (result == errQUEUE_FULL) {
		return StatusQueueStatus::Timeout;
	} else {
		return StatusQueueStatus::Failure;
	}
}

StatusQueueStatus StatusQueue::receive(Status_t &status) {
	BaseType_t result = xQueueReceive(xStatusQueue, &status, ticksToWait);
	if (result == pdPASS) {
		return StatusQueueStatus::Success;
	} else if (result == errQUEUE_EMPTY) {
		return StatusQueueStatus::Timeout;
	} else {
		return StatusQueueStatus::Failure;
	}
}
