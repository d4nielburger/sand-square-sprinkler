/*
 * PressurizedWaterControl.hpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#ifndef SRC_PRESSURIZEDWATERCONTROL_HPP_
#define SRC_PRESSURIZEDWATERCONTROL_HPP_

#include "FreeRTOS.h"
#include "queue.h"
#include "DO24V.hpp"
#include "DI24V.hpp"
#include "commands.h"

typedef enum {
	INIT, OFF, SPRINKLER, HOSE
} FsmStates_t;

class PressurizedWaterControl {
private:
	FsmStates_t state;
	QueueHandle_t commandQueue;
	DO_24V &pump;
	DO_24V &valveHose;
	DO_24V &valveSprinkler;
	DI_24V &switchSmallTankEmpty;

public:
	PressurizedWaterControl(QueueHandle_t cmdQueue, DO_24V &pump, DO_24V &vHose,
			DO_24V &vSprinkler, DI_24V &swSmallTankEmpty);
	void run();
};

#endif /* SRC_PRESSURIZEDWATERCONTROL_HPP_ */
