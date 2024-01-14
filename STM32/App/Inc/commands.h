/*
 * commands.h
 *
 *  Created on: Oct 30, 2023
 *      Author: dburger
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#define GARAGE_PUMP_START_STR "GARAGE_PUMP_START"
#define GARAGE_PUMP_STOP_STR "GARAGE_PUMP_STOP"
#define FILL_LARGE_TANK_STR "FILL_LARGE_TANK"
#define FILL_SMALL_TANK_STR "FILL_SMALL_TANK"
#define FILL_NO_TANK_STR "FILL_NO_TANK"
#define SPRINKLER_START_STR "SPRINKLER_START"
#define SPRINKLER_STOP_STR "SPRINKLER_STOP"
#define HOSE_START_STR "HOSE_START"
#define HOSE_STOP_STR "HOSE_STOP"
#define PRESSURE_PUMP_START_STR "PRESSURE_PUMP_START"
#define PRESSURE_PUMP_STOP_STR "PRESSURE_PUMP_STOP"

typedef enum {
	GARAGE_PUMP_START,
	GARAGE_PUMP_STOP,
	FILL_LARGE_TANK,
	FILL_SMALL_TANK,
	FILL_NO_TANK,
	SPRINKLER_START,
	SPRINKLER_STOP,
	HOSE_START,
	HOSE_STOP,
	PRESSURE_PUMP_START,
	PRESSURE_PUMP_STOP,
	NONE
}Commands_t;

#endif /* INC_COMMANDS_H_ */