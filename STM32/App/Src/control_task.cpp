/*
 * motorControltask.cpp
 *
 *  Created on: Oct 23, 2023
 *      Author: burge
 */

// Module include
#include <control_task.hpp>

// System includes
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Project includes
#include "PLC.hpp"
#include "DO24V.hpp"
#include "DI24V.hpp"
#include "GaragePumpControl.hpp"

// =================== Static object declarations =============================
// IO
static PLC plc01;
static DO_24V garagePump(plc01, DO1);

// Controllers
static GaragePumpControl garagePumpControl(commandQueue, garagePump);


// ========================= control task =====================================

void controlTask(void *argument) {
	QueueHandle_t commandQueue = static_cast<QueueHandle_t>(argument);

	// For periodical task execution
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = CONTROL_TASK_PERIOD / portTICK_PERIOD_MS;

	plc01.init();

	// Infinite Loop
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		garagePumpControl.run();

		plc01.run();
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
}

