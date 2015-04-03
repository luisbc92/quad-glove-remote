/*
 * button.c
 *
 *  Created on: Oct 26, 2014
 *      Author: Luiz
 */

#include "button.h"

int8_t ButtonRead(uint32_t port, uint8_t pin) {
	return !GPIOPinRead(port, pin);
}

