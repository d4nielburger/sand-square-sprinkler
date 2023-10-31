/*
 * appmain.cpp
 *
 *  Created on: Oct 7, 2023
 *      Author: Daniel
 */

// Module include
#include "app_main.hpp"

// System includes
#include <stdint.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"

// Project includes
#include "control_task.hpp"
#include "commands.h"
#include "CommandQueue.hpp"

#define COMMAND_QUEUE_LENGTH 10

static CommandQueue commandQueue(COMMAND_QUEUE_LENGTH);

void testTask(void *arguments) {
	// Get command queue from task argument
	CommandQueue *commandQueue = static_cast<CommandQueue*>(arguments);
	Commands_t commands[] = { SPRINKLER_START, SPRINKLER_STOP, GARAGE_PUMP_STOP,
			GARAGE_PUMP_START };

	for (;;) {
		for (Commands_t command : commands) {
			vTaskDelay(1000);
			commandQueue->send(command);
		}
	}
}

void app_main() {
	TaskHandle_t controlTaskHandle = NULL;
	TaskHandle_t testTaskHandle = NULL;

	// generate the control task
	xTaskCreate(controlTask, 			// Function that implements the task.
			"control", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 50, 	// Stack size in words, not bytes.
			static_cast<void*>(&commandQueue), // Parameter passed into the task.
			tskIDLE_PRIORITY + 10, 	// Priority at which the task is created.
			&controlTaskHandle); // Used to pass out the created task's handle.

	// test
	xTaskCreate(testTask, 			// Function that implements the task.
			"test", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 20, 	// Stack size in words, not bytes.
			static_cast<void*>(&commandQueue), // Parameter passed into the task.
			tskIDLE_PRIORITY + 5, 	// Priority at which the task is created.
			&testTaskHandle); // Used to pass out the created task's handle.

	// start the RTOS scheduler
	vTaskStartScheduler();
	for (;;) {
	}
}
