/*
 * motorControltask.cpp
 *
 *  Created on: Oct 23, 2023
 *      Author: burge
 */

#include <control_task.hpp>
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "PLC.hpp"
#include "DO24V.hpp"
#include "DI24V.hpp"

void controlTask(void *argument) {
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = CONTROL_TASK_PERIOD / portTICK_PERIOD_MS;

	static PLC plc1;
	plc1.init();

	// test
	static DO_24V do1(plc1, 1, false);
	static DO_24V do2(plc1, 2, true);
	static DO_24V do3(plc1, 3);
	static DO_24V do4(plc1, 4, true);
	static DO_24V do5(plc1, 5);
	static DO_24V do6(plc1, 6);
	static DO_24V do7(plc1, 7);
	static DO_24V do8(plc1, 8);

	static DI_24V di1(plc1, 1);
	static DI_24V di2(plc1, 2);
	static DI_24V di3(plc1, 3);
	static DI_24V di4(plc1, 4);
	static DI_24V di5(plc1, 5);
	static DI_24V di6(plc1, 6, true);
	static DI_24V di7(plc1, 7, false);
	static DI_24V di8(plc1, 8, true);

	// Infinite Loop
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		// test
		do1.set(di1.read());
		do2.set(di2.read());
		do3.set(di3.read());
		do4.set(di4.read());
		do5.set(di5.read());
		do6.set(di6.read());
		do7.set(di7.read());
		do8.set(di8.read());

		plc1.run();
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
}

