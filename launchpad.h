/*
 * launchpad.h
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_LAUNCHPAD_H_
#define QUADGLOVEREMOTE_LAUNCHPAD_H_

// Includes
#define PART_TM4C123GH6PM
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

// Launchpad I/O
#define LP_PORT			GPIO_PORTF_BASE
#define LP_LED_RED		GPIO_PIN_1
#define LP_LED_BLUE		GPIO_PIN_2
#define LP_LED_GREEN	GPIO_PIN_3
#define LP_SW_1			GPIO_PIN_4
#define LP_SW_2			GPIO_PIN_0
#define LP_LEDS			(LP_LED_RED|LP_LED_BLUE|LP_LED_GREEN)
#define LP_SWS			(LP_SW_1|LP_SW_2)

void LaunchPadInit();
void LedWrite(uint8_t rgb);

#endif /* QUADGLOVEREMOTE_LAUNCHPAD_H_ */
