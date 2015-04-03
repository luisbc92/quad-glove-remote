/*
 * console.h
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_CONSOLE_H_
#define QUADGLOVEREMOTE_CONSOLE_H_

#define PART_TM4C123GH6PM
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "utils/cmdline.h"
#include "utils/uartstdio.h"
#include "typedefs.h"
#include "config.h"

void ConsoleInit();
void ConsoleRun(void *pvParam);

#endif /* QUADGLOVEREMOTE_CONSOLE_H_ */
