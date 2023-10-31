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

typedef enum {
	INIT, FILL_SMALL, FILL_LARGE, DRAIN
} FsmStates_t;

class TankFillControl {
private:
	FsmStates_t state;
	QueueHandle_t commandQueue;
	DO_24V &valveSmallTankInlet;
	DO_24V &valveLargeTankInlet;
	DI_24V &switchSmallTankFull;
	DI_24V &switchLargeTankFull;

public:
	TankFillControl(QueueHandle_t cmdQueue, DO_24V &vSmallTankInlet,
			DO_24V &vLargeTankInlet, DI_24V &swSmallTankFull,
			DI_24V &swLargeTankFull);

	void run();
};

#endif /* SRC_TANKFILLCONTROL_HPP_ */
