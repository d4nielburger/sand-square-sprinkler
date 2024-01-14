/*
 * PLC.hpp
 *
 *  Created on: Oct 25, 2023
 *      Author: burge
 */

#ifndef SRC_PLC_HPP_
#define SRC_PLC_HPP_

#define USE_STM32F4XX_NUCLEO

#include "stdint.h"

class PLC {
private:
	const uint8_t numberOfDo = 8;
	const uint8_t numberOfDi = 8;
	uint8_t doData;
	uint8_t diData;

public:
	PLC();
	void init();
	void run();
	void setOutputOn(uint8_t doNr);
	void setOutputOff(uint8_t doNr);
	void setOutput(uint8_t doNr, bool state);
	bool readInput(uint8_t diNr);
};

#endif /* SRC_PLC_HPP_ */
