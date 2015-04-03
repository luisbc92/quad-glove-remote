/*
 * launchpad.c
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */
#include "launchpad.h"

void LaunchPadInit() {
	// Setup the clock at 80Mhz from PLL with crystal
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	// Enable FPU
	FPUEnable();
	FPULazyStackingEnable();
	//Configure GPIO port for LEDs and PBs
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LP_LEDS);
	/* Unlock F0 */
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	/* Unlock F0 */
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, LP_SWS);
	GPIOPadConfigSet(GPIO_PORTF_BASE, LP_SWS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

void LedWrite(uint8_t rgb) {
	uint8_t led_write = 0;

	if (rgb & 0x01)
		led_write |= LP_LED_BLUE;
	if (rgb & 0x02)
		led_write |= LP_LED_GREEN;
	if (rgb & 0x04)
		led_write |= LP_LED_RED;

	GPIOPinWrite(LP_PORT, LP_LEDS, led_write);
}
