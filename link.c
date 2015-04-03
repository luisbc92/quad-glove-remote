#include "link.h"

extern QuadControl	quad;

void UARTStringPut(uint32_t ui32Base, char * string) {
	unsigned int ptr = 0;
	while (*(string+ptr) != '\0') {
		UARTCharPut(ui32Base, *(string+ptr));
		ptr++;
	}
}

void LinkInit() {
	char receive;

	// Configure UART1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	GPIOPinConfigure(GPIO_PC4_U1RX);
	GPIOPinConfigure(GPIO_PC5_U1TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
	UARTFIFODisable(UART1_BASE);

	/*
	 * Configure Xbee Baud Rate at 9600
	 */
	UARTConfigSetExpClk(UART1_BASE, 16000000, 9600, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
	UARTEnable(UART1_BASE);

	// Enter AT Mode
	UARTStringPut(UART1_BASE, "+++");
	SysCtlDelay((SysCtlClockGet() / 3000) * 2000);
	UARTStringPut(UART1_BASE, "ATBD ");
	UARTStringPut(UART1_BASE, LINK_BD);
	UARTStringPut(UART1_BASE, "\r");
	SysCtlDelay((SysCtlClockGet() / 3000) * 1000);
	UARTStringPut(UART1_BASE, "ATWR\r");
	SysCtlDelay((SysCtlClockGet() / 3000) * 1000);
	UARTStringPut(UART1_BASE, "ATCN\r");
	SysCtlDelay((SysCtlClockGet() / 3000) * 1000);


	/*
	 * Configure Link at target baud rate
	 */
	UARTDisable(UART1_BASE);
	UARTConfigSetExpClk(UART1_BASE, 16000000, 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
	UARTEnable(UART1_BASE);

	// Clear Buffer
	while (UARTCharsAvail(UART1_BASE) == true) {
		UARTCharGet(UART1_BASE);
	}
	// Enter AT Mode
	do {
		UARTStringPut(UART1_BASE, "+++");
		SysCtlDelay((SysCtlClockGet() / 3000) * 2000);
		receive = UARTCharGet(UART1_BASE);
	} while (receive != 'O');
	UARTCharGet(UART1_BASE);	// Drop the K
	UARTCharGet(UART1_BASE);	// Drop the CR
	// Set PAN ID
	do {
		UARTStringPut(UART1_BASE, "ATID ");
		UARTStringPut(UART1_BASE, LINK_ID);
		UARTStringPut(UART1_BASE, "\r");
		receive = UARTCharGet(UART1_BASE);
	} while (receive != 'O');
	UARTCharGet(UART1_BASE);	// Drop the K
	UARTCharGet(UART1_BASE);	// Drop the CR
	// Set Local Address
	do {
		UARTStringPut(UART1_BASE, "ATMY ");
		UARTStringPut(UART1_BASE, LINK_MY);
		UARTStringPut(UART1_BASE, "\r");
		receive = UARTCharGet(UART1_BASE);
	} while (receive != 'O');
	UARTCharGet(UART1_BASE);	// Drop the K
	UARTCharGet(UART1_BASE);	// Drop the CR
	// Set Remote Address
	do {
		UARTStringPut(UART1_BASE, "ATDL ");
		UARTStringPut(UART1_BASE, LINK_DL);
		UARTStringPut(UART1_BASE, "\r");
		receive = UARTCharGet(UART1_BASE);
	} while (receive != 'O');
	UARTCharGet(UART1_BASE);	// Drop the K
	UARTCharGet(UART1_BASE);	// Drop the CR
	// Write Configuration
	do {
		UARTStringPut(UART1_BASE, "ATWR\r");
		receive = UARTCharGet(UART1_BASE);
	} while (receive != 'O');
	UARTCharGet(UART1_BASE);	// Drop the K
	UARTCharGet(UART1_BASE);	// Drop the CR
	// Close
	do {
		UARTStringPut(UART1_BASE, "ATCN\r");
		receive = UARTCharGet(UART1_BASE);
	} while (receive != 'O');
	UARTCharGet(UART1_BASE);	// Drop the K
	UARTCharGet(UART1_BASE);	// Drop the CR
}

void LinkSend() {
	// Signature
	UARTCharPut(UART1_BASE, 0xF0);
	// Send Data
	int i;
	for (i = 0; i < sizeof(QuadControl); i++) {
		UARTCharPut(UART1_BASE, *((unsigned char *) &quad + i));
	}
}















