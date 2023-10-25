/*
 * PLC.cpp
 *
 *  Created on: Oct 25, 2023
 *      Author: burge
 */

#include "PLC.hpp"

#include "FreeRTOS.h"
#include "task.h"

#include "x_nucleo_plc01a1.h"

PLC::PLC() {
}

void PLC::init() {
	BSP_Relay_Init();
	BSP_CurrentLimiter_Init();

	/* Reset relay at startup to avoid FAULT */
	BSP_RELAY_Reset();

	/* wait for 100 ms at startup */
	vTaskDelay(100 / portTICK_PERIOD_MS);

	/* Enable Relay Outputs */
	BSP_RELAY_EN_Out();
}

/*
 * @brief run at least every 30ms
 */
void PLC::run() {

	static uint8_t *clData = NULL;

	clData = BSP_CURRENT_LIMITER_Read();

	uint8_t *Current_Limiter_Status = clData;

	if (BSP_GetCurrentLimiterStatus(Current_Limiter_Status)
			!= CURRENT_LIMITER_OK) {
		/* Set input error code here */
	}

	diData = *(clData + 1);

	uint8_t *Relay_Status = BSP_RELAY_SetOutputs(&doData);

	if (BSP_GetRelayStatus(Relay_Status) != RELAY_OK) {
		/* Set output error code here */
	}
}

void PLC::setOutputOn(uint8_t doNr) {
	PLC::setOutput(doNr, true);
}

void PLC::setOutputOff(uint8_t doNr) {
	PLC::setOutput(doNr, false);
}

void PLC::setOutput(uint8_t doNr, bool state) {
	if (doNr > 0 && doNr <= numberOfDo) {
		if (state) {
			doData = doData | (1 << (doNr - 1));
		} else {
			doData = doData & ~(1 << (doNr - 1));
		}

	}
}

bool PLC::readInput(uint8_t diNr) {
	if (diNr > 0 && diNr <= numberOfDi) {
		return diData & (1 << (diNr - 1));
	}

	return false;
}
