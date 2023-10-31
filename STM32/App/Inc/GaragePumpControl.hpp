/*
 * GaragePumpControl.hpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#ifndef SRC_GARAGEPUMPCONTROL_HPP_
#define SRC_GARAGEPUMPCONTROL_HPP_

#include "DO24V.hpp"
#include "commands.h"
#include "CommandQueue.hpp"

class GaragePumpControl {
private:
	typedef enum {
		INIT, ON, OFF
	} FsmStates_t;

	FsmStates_t state;
	CommandQueue &commandQueue;
	DO_24V &pump;

public:
	GaragePumpControl(CommandQueue &commandQueue, DO_24V &pump);
	void run();
};

#endif /* SRC_GARAGEPUMPCONTROL_HPP_ */
