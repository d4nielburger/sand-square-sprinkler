/*
 * Queues.hpp
 *
 *  Created on: Nov 14, 2023
 *      Author: burge
 */

#ifndef INC_QUEUES_HPP_
#define INC_QUEUES_HPP_

#include "CommandQueue.hpp"
#include "StatusQueue.hpp"

class Queues {
public:
	CommandQueue *commandQueue;
	StatusQueue *statusQueue;
};

#endif /* INC_QUEUES_HPP_ */
