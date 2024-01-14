/*
 * PressurizedWaterControl.hpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#ifndef SRC_PRESSURIZEDWATERCONTROL_HPP_
#define SRC_PRESSURIZEDWATERCONTROL_HPP_

#include "DO24V.hpp"
#include "DI24V.hpp"
#include "commands.h"
#include "CommandQueue.hpp"

class PressurizedWaterControl {
private:
	typedef enum {
		INIT, OFF, SPRINKLER, HOSE
	} FsmStates_t;

	FsmStates_t state;
	CommandQueue &commandQueue;
	DO_24V &pump;
	DO_24V &valveHose;
	DO_24V &valveSprinkler;
	DI_24V &switchSmallTankEmpty;

public:
	PressurizedWaterControl(CommandQueue &cmdQueue, DO_24V &pump, DO_24V &vHose,
			DO_24V &vSprinkler, DI_24V &swSmallTankEmpty);
	void run();
};

#endif /* SRC_PRESSURIZEDWATERCONTROL_HPP_ */
