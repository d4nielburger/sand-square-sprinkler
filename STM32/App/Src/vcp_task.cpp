/*
 * vcp_task.cpp
 *
 *  Created on: Nov 15, 2023
 *      Author: burge
 */

#include "vcp_task.hpp"

#include "FreeRTOS.h"
#include "Queues.hpp"
#include "uart.h"
#include <string.h>
#include <stdint.h>

static CommandQueue *commandQueue;
static StatusQueue *statusQueue;

void handleCommand(void);
void handleStatus(void);
void processCommand(const char *buf);
void sendStatus(Status_t status);

void vcpTask(void *arguments) {
	// Get queues from task argument
	Queues *queues = static_cast<Queues*>(arguments);
	commandQueue = queues->commandQueue;
	statusQueue = queues->statusQueue;

	uart_init();
	for (uint8_t i = 0; i < 10; i++) {
		uart_send_nl();
		uart_send_cr();
	}

	commandQueue->send(GET_STATUS_ALL);

	for (;;) {
		handleCommand();
		handleStatus();
	}
}

void handleCommand(void) {
	char buf[UART_BUF_LEN];
	strcpy(buf, "");
	uart_read(buf, sizeof(buf));
	if (strlen(buf) > 0) {
		uart_send_nl();
		uart_send_cr();
		processCommand(buf);
	}
}

void handleStatus(void) {
	Status_t status = NO_STATUS;
	statusQueue->receive(status);
	if (NO_STATUS != status) {
		sendStatus(status);
		uart_send_nl();
		uart_send_cr();
	}
}

void processCommand(const char *buf) {
	for (uint8_t i = 0; commandMap[i].cmdString != NULL; ++i) {
		if (!strcmp(buf, commandMap[i].cmdString)) {
			commandQueue->send(commandMap[i].cmdEnum);
			return;
		}
	}

	statusQueue->send(ERROR_UNKNOWN_CMD);
}

void sendStatus(Status_t status) {
	for (uint8_t i = 0; statusMap[i].statusString != NULL; i++) {
		if (statusMap[i].statusEnum == status) {
			uart_send(statusMap[i].statusString,
					strlen(statusMap[i].statusString));
			return;
		}
	}
}
