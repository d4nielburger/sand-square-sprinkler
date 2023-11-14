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
#include "CommandQueue.hpp"
#include "StatusQueue.hpp"
#include "Queues.hpp"
#include "uart.h"

#define COMMAND_QUEUE_LENGTH 10
#define STATUS_QUEUE_LENGTH 10

static CommandQueue commandQueue(COMMAND_QUEUE_LENGTH);
static StatusQueue statusQueue(STATUS_QUEUE_LENGTH);
static Queues queues = { &commandQueue, &statusQueue };

void testTask(void *arguments) {
	// Get queues from task argument
	Queues *queues = static_cast<Queues*>(arguments);
	CommandQueue *commandQueue = queues->commandQueue;
	StatusQueue *statusQueue = queues->statusQueue;

	uart_init();

	for (;;) {
		char buf[128];
		uart_read(buf, sizeof(buf));

		if (!strcmp(buf, SPRINKLER_START_STR)) {
			commandQueue->send(SPRINKLER_START);
		} else if (!strcmp(buf, SPRINKLER_STOP_STR)) {
			commandQueue->send(SPRINKLER_STOP);
		}

		Status_t status = NO_STATUS;
		statusQueue->receive(status);
		if (NO_STATUS != status) {
			if (status == SPRINKLER_RUNNING) {
				char buf2[] = SPRINKLER_RUNNING_STR;
				uart_send(buf2, sizeof(buf2));
				uart_send_nl();
				uart_send_cr();
			} else if (status == SPRINKLER_STOPPED) {
				char buf2[] = SPRINKLER_STOPPED_STR;
				uart_send(buf2, sizeof(buf2));
				uart_send_nl();
				uart_send_cr();
			}

		}
	}
}

void app_main() {
	TaskHandle_t controlTaskHandle = NULL;
	TaskHandle_t testTaskHandle = NULL;

// generate the control task
	xTaskCreate(controlTask, 			// Function that implements the task.
			"control", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 100, // Stack size in words, not bytes.
			static_cast<void*>(&queues), // Parameter passed into the task.
			tskIDLE_PRIORITY + 10, 	// Priority at which the task is created.
			&controlTaskHandle); // Used to pass out the created task's handle.

// test
	xTaskCreate(testTask, 			// Function that implements the task.
			"test", 						// Text name for the task.
			configMINIMAL_STACK_SIZE + 150, // Stack size in words, not bytes.
			static_cast<void*>(&queues), // Parameter passed into the task.
			tskIDLE_PRIORITY + 5, 	// Priority at which the task is created.
			&testTaskHandle); // Used to pass out the created task's handle.

// start the RTOS scheduler
	vTaskStartScheduler();
	for (;;) {
	}
}
