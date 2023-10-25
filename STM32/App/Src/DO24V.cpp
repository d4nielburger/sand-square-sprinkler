/*
 * DO24V.cpp
 *
 *  Created on: Oct 25, 2023
 *      Author: burge
 */

#include "DO24V.hpp"

DO_24V::DO_24V(PLC &plc, uint8_t doNr) : plc(plc), doNr(doNr), inverted(false) {}

DO_24V::DO_24V(PLC &plc, uint8_t doNr, bool inverted) : plc(plc), doNr(doNr), inverted(inverted) {}

void DO_24V::setOn() {
	DO_24V::set(true);
}

void DO_24V::setOff() {
	DO_24V::set(false);
}

void DO_24V::set(bool state) {
	plc.setOutput(doNr, state ^ inverted);
}

void DO_24V::setInverted(bool inverted) {
	this->inverted = inverted;
}
