/*
 * DI24V.hpp
 *
 *  Created on: Oct 25, 2023
 *      Author: burge
 */

#ifndef SRC_DI24V_HPP_
#define SRC_DI24V_HPP_

#include "stdint.h"
#include "PLC.hpp"

class DI_24V {
private:
	PLC &plc;
	bool inverted;
	uint8_t diNr;
public:
	DI_24V(PLC &plc, uint8_t diNr);
	DI_24V(PLC &plc, uint8_t diNr, bool inverted);
	bool read();
	void setInverted(bool inverted);
};

#endif /* SRC_DI24V_HPP_ */
