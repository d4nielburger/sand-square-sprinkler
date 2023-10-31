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
#include "CommandDirector.hpp"
#include "commands.h" //Test

QueueHandle_t commandQueue;
QueueHandle_t garagePumpCmds;
QueueHandle_t tankFillCmds;
QueueHandle_t pressWaterCmds;

// =================== Static object declarations =============================
// IO
static PLC plc01;

static DO_24V garagePump(plc01, DO1);
static DO_24V pressurePump(plc01, DO2);
static DO_24V valveSmallTankInlet(plc01, DO3);
static DO_24V valveDrain(plc01, DO4);
static DO_24V valveSprinkler(plc01, DO5);
static DO_24V valveHose(plc01, DO6);

static DI_24V switchSmallTankFull(plc01, DI1);
static DI_24V switchSmallTankEmpty(plc01, DI2);

//// Controllers
//static GaragePumpControl garagePumpControl(commandQueue, garagePump);
//static TankFillControl tankFillControl(commandQueue, valveSmallTankInlet,
//		valveDrain, switchSmallTankFull);
//static PressurizedWaterControl pressWaterControl(commandQueue, pressurePump,
//		valveHose, valveSprinkler, switchSmallTankEmpty);

// Helper
static CommandDirector commandDirector;

// ========================= control task =====================================

void controlTask(void *argument) {
	// Get command queue from task argument
	commandQueue = static_cast<QueueHandle_t>(argument);

	// test
	garagePumpCmds = xQueueCreate(5, sizeof(Commands_t));
	tankFillCmds = xQueueCreate(5, sizeof(Commands_t));
	pressWaterCmds = xQueueCreate(5, sizeof(Commands_t));

	// test Controllers
	GaragePumpControl garagePumpControl(garagePumpCmds, garagePump);
	TankFillControl tankFillControl(tankFillCmds, valveSmallTankInlet,
			valveDrain, switchSmallTankFull);
	PressurizedWaterControl pressWaterControl(pressWaterCmds, pressurePump,
			valveHose, valveSprinkler, switchSmallTankEmpty);

	// For periodical task execution
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = CONTROL_TASK_PERIOD / portTICK_PERIOD_MS;

	// test
	uint32_t testCnt = 0;
	uint8_t cmdCnt = 6;
	uint8_t cmdCounter = 0;
	Commands_t commands[cmdCnt] = { FILL_LARGE_TANK, FILL_SMALL_TANK, FILL_NO_TANK, FILL_LARGE_TANK, FILL_NO_TANK, FILL_SMALL_TANK};

	plc01.init();

	// Infinite Loop
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		// Create test commands
		testCnt++;
		if (testCnt >= (100 * 3)) {
			testCnt = 0;

			xQueueSend(commandQueue,
					static_cast<void*>(&(commands[cmdCounter])),
					(TickType_t ) 0);

			cmdCounter++;
			if (cmdCounter >= cmdCnt) {
				cmdCounter = 0;
			}
		}

		// Direct the incoming commands
		commandDirector.directControlCommand(commandQueue, garagePumpCmds,
				tankFillCmds, pressWaterCmds);

		// Run controls
		garagePumpControl.run();
		tankFillControl.run();
		pressWaterControl.run();

		// Run plc module
		plc01.run();

		// Wait for next task period
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
}
