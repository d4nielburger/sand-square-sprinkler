/*
 * TankFillControl.hpp
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#ifndef SRC_TANKFILLCONTROL_HPP_
#define SRC_TANKFILLCONTROL_HPP_

#include "FreeRTOS.h"
#include "queue.h"
#include "DO24V.hpp"
#include "DI24V.hpp"
#include "commands.h"

class TankFillControl {
private:
	typedef enum {
		INIT, FILL_SMALL, FILL_LARGE, DRAIN
	} FsmStates_t;

	FsmStates_t state;
	QueueHandle_t commandQueue;
	DO_24V &valveSmallTankInlet;
	DO_24V &valveDrain;
	DI_24V &switchSmallTankFull;

public:
	TankFillControl(QueueHandle_t cmdQueue, DO_24V &vSmallTankInlet,
			DO_24V &vDrain, DI_24V &swSmallTankFull);

	void run();
};

#endif /* SRC_TANKFILLCONTROL_HPP_ */
