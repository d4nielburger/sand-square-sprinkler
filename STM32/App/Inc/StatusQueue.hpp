/*
 * StatusQueue.hpp
 *
 *  Created on: Nov 14, 2023
 *      Author: burge
 */

#ifndef SRC_STATUSQUEUE_HPP_
#define SRC_STATUSQUEUE_HPP_

#include "FreeRTOS.h"
#include "queue.h"
#include "status.h"

enum class StatusQueueStatus {
	Success, Failure, Timeout
};

class StatusQueue {
private:
	size_t queueLength;
	QueueHandle_t xStatusQueue;
	static const TickType_t ticksToWait = (TickType_t) 0;

public:
	StatusQueue(size_t queueLength);
	StatusQueueStatus send(const Status_t &status);
	StatusQueueStatus receive(Status_t &status);

};
#endif /* SRC_STATUSQUEUE_HPP_ */
