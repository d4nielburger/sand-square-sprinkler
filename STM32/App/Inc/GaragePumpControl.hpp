/*
 * GaragePumpControl.hpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#ifndef SRC_GARAGEPUMPCONTROL_HPP_
#define SRC_GARAGEPUMPCONTROL_HPP_

#include "FreeRTOS.h"
#include "queue.h"
#include "DO24V.hpp"
#include "commands.h"

class GaragePumpControl {
private:
	typedef enum {
		INIT, ON, OFF
	} FsmStates_t;

	FsmStates_t state;
	QueueHandle_t commandQueue;
	DO_24V &pump;

public:
	GaragePumpControl(QueueHandle_t commandQueue, DO_24V &pump);
	void run();
};

#endif /* SRC_GARAGEPUMPCONTROL_HPP_ */
