/*
 * uart.c
 *
 *  Created on: Oct 28, 2023
 *      Author: zihlmalb
 */

#include "stm32f4xx_hal.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <string.h>

extern UART_HandleTypeDef huart2;

// /*
// Queue Variant
#define QUEUE_LEN (2)
#define BUF_LEN (128)

static char buffer[BUF_LEN];
static uint8_t idx = 0;
QueueHandle_t myQueue;

static void uart_syncinit(void) {
	myQueue = xQueueCreate(QUEUE_LEN, BUF_LEN);
}

size_t uart_read(char *const buf, size_t n) {
	if (n < BUF_LEN) {
		return 0;
	}

	xQueueReceive(myQueue, (void*) buf, ( TickType_t ) 0);
	return n;
}

static void putChar(char c) {
	BaseType_t xTaskWokenByReceive = pdFALSE;
	buffer[idx] = c;
	idx++;
	if (idx >= (sizeof(buffer) - 1)) {
		idx = 0;
	}
	if ('\n' == c || '\r' == c) {
		buffer[idx] = '\0'; // Add null-termination
		idx = 0;
		xQueueSendFromISR(myQueue, (void* )&buffer, &xTaskWokenByReceive);

		if (xTaskWokenByReceive != pdFALSE) {
			// We should switch context so the ISR returns to a different task.
			// NOTE:  How this is done depends on the port you are using.  Check
			// the documentation and examples for your port.
			taskYIELD();
		}
	}
}
// */

void uart_init(void) {
	uart_syncinit();
	/* Enable RX not empty interrupt */
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	/*Configure the USART1 IRQ priority */
	HAL_NVIC_SetPriority(USART2_IRQn,
	configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY, 0U);
	/* Enable the USART1 global Interrupt */
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void uart_send(const char* buf, size_t n) {
	HAL_UART_Transmit(&huart2, buf, n, portMAX_DELAY);
}

void uart_send_cr(){
	char cr = '\r';
	uart_send(&cr,1);
}

void uart_send_nl(){
	char cr = '\n';
	uart_send(&cr,1);
}

void USART2_IRQHandler(void) {
	if (huart2.Instance->SR & USART_SR_RXNE) {
		/* get the character received */
		char ch = (uint8_t) (huart2.Instance->DR);
		/*/ echo ch via TxD */
		huart2.Instance->DR = ch;
		putChar(ch);
	}
}
