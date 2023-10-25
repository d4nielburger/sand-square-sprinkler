/*
 * DI24V.cpp
 *
 *  Created on: Oct 25, 2023
 *      Author: burge
 */

#include "DI24V.hpp"

DI_24V::DI_24V(PLC &plc, uint8_t diNr) :
		plc(plc), diNr(diNr), inverted(false) {
}

DI_24V::DI_24V(PLC &plc, uint8_t diNr, bool inverted) :
		plc(plc), diNr(diNr), inverted(inverted) {
}

bool DI_24V::read() {
	return plc.readInput(diNr) ^ inverted;
}

void DI_24V::setInverted(bool inverted) {
	this->inverted = inverted;
}
