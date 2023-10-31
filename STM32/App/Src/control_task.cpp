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
#include "TankFillControl.hpp"
#include "PressurizedWaterControl.hpp"

QueueHandle_t commandQueue;
QueueHandle_t garagePumpCmds;
QueueHandle_t tankFillCmds;
QueueHandle_t pressWaterCmds;

// =================== Static object declarations =============================
// IO
static PLC plc01;

static DO_24V garagePump(plc01, DO1);
static DO_24V pressurePump(plc01,DO2);
static DO_24V valveSmallTankInlet(plc01, DO3);
static DO_24V valveLargeTankInlet(plc01, DO4);
static DO_24V valveSprinkler(plc01, DO5);
static DO_24V valveHose(plc01, DO6);

static DI_24V switchSmallTankFull(plc01, DI1);
static DI_24V switchSmallTankEmpty(plc01, DI2);
static DI_24V switchLargeTankFull(plc01, DI3);
static DI_24V switchLargeTankEmpty(plc01, DI2);

// Controllers
static GaragePumpControl garagePumpControl(commandQueue, garagePump);
static TankFillControl tankFillControl(commandQueue,
										valveSmallTankInlet,
										valveLargeTankInlet,
										switchSmallTankFull,
										switchLargeTankFull);
static PressurizedWaterControl pressWaterControl(commandQueue,
										pressurePump,
										valveHose,
										valveSprinkler,
										switchSmallTankEmpty);

// ========================= control task =====================================

void controlTask(void *argument) {
	// Get command queue from task argument
	commandQueue = static_cast<QueueHandle_t>(argument);

	// For periodical task execution
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = CONTROL_TASK_PERIOD / portTICK_PERIOD_MS;

	plc01.init();

	// Infinite Loop
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		garagePumpControl.run();
		tankFillControl.run();
		pressWaterControl.run();

		plc01.run();
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
}
