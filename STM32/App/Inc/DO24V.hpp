/*
 * DO24V.h
 *
 *  Created on: Oct 25, 2023
 *      Author: burge
 */

#ifndef SRC_DO24V_HPP_
#define SRC_DO24V_HPP_

#include "stdint.h"
#include "PLC.hpp"

#define DO1 1
#define DO2 2
#define DO3 3
#define DO4 4
#define DO5 5
#define DO6 6
#define DO7 7
#define DO8 8

class DO_24V {
private:
	PLC &plc;
	bool inverted;
	uint8_t doNr;
public:
	DO_24V(PLC &plc, uint8_t doNr);
	DO_24V(PLC &plc, uint8_t doNr, bool inverted);
	void setOn();
	void setOff();
	void set(bool state);
	void setInverted(bool inverted);
};

#endif /* SRC_DO24V_HPP_ */
