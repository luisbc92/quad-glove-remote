/*
 * link.h
 *
 *  Created on: Nov 23, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_LINK_H_
#define QUADGLOVEREMOTE_LINK_H_

#define PART_TM4C123GH6PM
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "typedefs.h"
#include "config.h"

void UARTStringPut(uint32_t ui32Base, char * string);
void LinkInit();
void LinkSend();


#endif /* QUADGLOVEREMOTE_LINK_H_ */
