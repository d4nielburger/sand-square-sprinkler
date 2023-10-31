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
#include "queue.h"

// Project includes
#include "control_task.hpp"
#include "commands.h"

void app_main() {
	// Setup command queue
	QueueHandle_t commandQueue = NULL;
	commandQueue = xQueueCreate(5, sizeof(Commands_t));

	TaskHandle_t controlTaskHandle = NULL;

	// generate the control task
	xTaskCreate(controlTask, 			// Function that implements the task.
			"control", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 20, 	// Stack size in words, not bytes.
			static_cast<void*>(commandQueue),		// Parameter passed into the task.
			tskIDLE_PRIORITY + 10, 	// Priority at which the task is created.
			&controlTaskHandle); // Used to pass out the created task's handle.

	// start the RTOS scheduler
	vTaskStartScheduler();
	for (;;) {
	}
}
