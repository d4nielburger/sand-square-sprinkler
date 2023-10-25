/*
 * appmain.cpp
 *
 *  Created on: Oct 7, 2023
 *      Author: Daniel
 */

#include "app_main.hpp"
#include <stdint.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "control_task.hpp"

void app_main() {
	TaskHandle_t controlTaskHandle = NULL;

	// generate the control task
	xTaskCreate(controlTask, 				// Function that implements the task.
			"control", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 20, 	// Stack size in words, not bytes.
			(void*) 1, 						// Parameter passed into the task.
			tskIDLE_PRIORITY + 10, 			// Priority at which the task is created.
			&controlTaskHandle); 			// Used to pass out the created task's handle.

	// start the RTOS scheduler
	vTaskStartScheduler();
	for (;;) {
	}
}
