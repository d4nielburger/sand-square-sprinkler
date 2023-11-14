/*
 * GaragePumpControl.hpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#ifndef SRC_GARAGEPUMPCONTROL_HPP_
#define SRC_GARAGEPUMPCONTROL_HPP_

#include "DO24V.hpp"
#include "CommandQueue.hpp"
#include "StatusQueue.hpp"

class GaragePumpControl {
private:
	typedef enum {
		INIT, ON, OFF
	} FsmStates_t;

	FsmStates_t state;
	CommandQueue &commandQueue;
	StatusQueue &statusQueue;
	DO_24V &pump;

public:
	GaragePumpControl(CommandQueue &commandQueue, StatusQueue &statQueue, DO_24V &pump);
	void run();
	void sendStatus();
};

#endif /* SRC_GARAGEPUMPCONTROL_HPP_ */
