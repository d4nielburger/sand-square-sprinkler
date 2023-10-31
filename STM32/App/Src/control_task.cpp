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

// Project includes
#include "PLC.hpp"
#include "DO24V.hpp"
#include "DI24V.hpp"
#include "GaragePumpControl.hpp"
#include "TankFillControl.hpp"
#include "PressurizedWaterControl.hpp"
#include "CommandDirector.hpp"
#include "CommandQueue.hpp"
#include "commands.h" //Test

#define LOCAL_COMMAND_QUEUE_LENGTH 5


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

// Helper
static CommandDirector commandDirector;

// ========================= control task =====================================

void controlTask(void *argument) {
	// Get command queue from task argument
	CommandQueue* commandQueue = static_cast<CommandQueue*>(argument);

	// Initialize local command queues
	CommandQueue garagePumpCmds(LOCAL_COMMAND_QUEUE_LENGTH);
	CommandQueue tankFillCmds(LOCAL_COMMAND_QUEUE_LENGTH);
	CommandQueue pressWaterCmds(LOCAL_COMMAND_QUEUE_LENGTH);

	// Initialize controllers
	GaragePumpControl garagePumpControl(garagePumpCmds, garagePump);
	TankFillControl tankFillControl(tankFillCmds, valveSmallTankInlet,
			valveDrain, switchSmallTankFull);
	PressurizedWaterControl pressWaterControl(pressWaterCmds, pressurePump,
			valveHose, valveSprinkler, switchSmallTankEmpty);

	// For periodical task execution
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = CONTROL_TASK_PERIOD / portTICK_PERIOD_MS;

	plc01.init();

	// Infinite Loop
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		// Direct the incoming commands
		commandDirector.directControlCommand(*commandQueue, garagePumpCmds,
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
