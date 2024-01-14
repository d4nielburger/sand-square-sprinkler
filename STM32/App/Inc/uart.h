/*
 * uart.h
 *
 *  Created on: Oct 28, 2023
 *      Author: zihlmalb
 */

#ifndef APP_INC_UART_H_
#define APP_INC_UART_H_

#define UART_BUF_LEN 128

#include "stddef.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Initializes the UART
 */
void uart_init(void);

/**
 * Read max n Bytes from UART
 */
size_t uart_read(char * const buf, size_t n);

void uart_send(const char* buf, size_t n);
void uart_send_cr();
void uart_send_nl();

#ifdef __cplusplus
}
#endif
#endif /* APP_INC_UART_H_ */
