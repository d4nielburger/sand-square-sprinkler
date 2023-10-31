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

#define DI1 1
#define DI2 2
#define DI3 3
#define DI4 4
#define DI5 5
#define DI6 6
#define DI7 7
#define DI8 8

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
