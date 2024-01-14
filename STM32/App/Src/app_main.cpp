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
#include "Queues.hpp"
#include "vcp_task.hpp"

#define COMMAND_QUEUE_LENGTH 10
#define STATUS_QUEUE_LENGTH 10

static CommandQueue commandQueue(COMMAND_QUEUE_LENGTH);
static StatusQueue statusQueue(STATUS_QUEUE_LENGTH);
static Queues queues = { &commandQueue, &statusQueue };

void app_main() {
	TaskHandle_t controlTaskHandle = NULL;
	TaskHandle_t vcpTaskHandle = NULL;

// generate the control task
	xTaskCreate(controlTask, 			// Function that implements the task.
			"control", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 100, // Stack size in words, not bytes.
			static_cast<void*>(&queues), // Parameter passed into the task.
			tskIDLE_PRIORITY + 10, 	// Priority at which the task is created.
			&controlTaskHandle); // Used to pass out the created task's handle.

// test
	xTaskCreate(vcpTask, 			// Function that implements the task.
			"vcp", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 200, // Stack size in words, not bytes.
			static_cast<void*>(&queues), // Parameter passed into the task.
			tskIDLE_PRIORITY + 5, 	// Priority at which the task is created.
			&vcpTaskHandle); // Used to pass out the created task's handle.

// start the RTOS scheduler
	vTaskStartScheduler();
	for (;;) {
	}
}
