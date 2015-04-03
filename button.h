/*
 * button.h
 *
 *  Created on: Oct 26, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_BUTTON_H_
#define QUADGLOVEREMOTE_BUTTON_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

// Connected buttons
#define BTN_HOLD		GPIO_PORTF_BASE,0x10
#define BTN_DISARM		GPIO_PORTF_BASE,0x01

int8_t ButtonRead(uint32_t port, uint8_t pin);

#endif /* QUADGLOVEREMOTE_BUTTON_H_ */
