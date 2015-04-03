/*
 * i2c.c
 *
 *  Created on: Mar 16, 2014
 *      Author: Luiz
 */

#define PART_TM4C123GH6PM
#include <stdbool.h>
#include <stdint.h>
#include "i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/i2c.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

/*
 * Functions
 */
void I2CInit(uint32_t i2c_base, uint32_t i2c_speed) {

	// Initialize GPIO and I2C depending on chosen port
	switch (i2c_base) {

	case I2C0_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
		GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
		GPIOPinConfigure(GPIO_PB2_I2C0SCL);
		GPIOPinConfigure(GPIO_PB3_I2C0SDA);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
		I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), i2c_speed);
		break;

	case I2C1_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
		GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
		GPIOPinConfigure(GPIO_PA6_I2C1SCL);
		GPIOPinConfigure(GPIO_PA7_I2C1SDA);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
		I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), i2c_speed);
		break;

	case I2C2_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
		GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);
		GPIOPinConfigure(GPIO_PE4_I2C2SCL);
		GPIOPinConfigure(GPIO_PE5_I2C2SDA);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
		I2CMasterInitExpClk(I2C2_BASE, SysCtlClockGet(), i2c_speed);
		break;

	case I2C3_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
		GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
		GPIOPinConfigure(GPIO_PD0_I2C3SCL);
		GPIOPinConfigure(GPIO_PD1_I2C3SDA);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
		I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), i2c_speed);
		break;

	}
}

uint32_t I2CReadSingle(uint32_t i2c_base, uint8_t address, uint8_t reg) {
	uint32_t data = 0;

	// Set slave register to be read
	while(I2CMasterBusy(i2c_base));
	I2CMasterSlaveAddrSet(i2c_base, address, 0);
	I2CMasterDataPut(i2c_base, reg);
	I2CMasterControl(i2c_base, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(i2c_base));

	// Check for errors
	if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

	// Request for register data
	I2CMasterSlaveAddrSet(i2c_base, address, 1);
	I2CMasterControl(i2c_base, I2C_MASTER_CMD_SINGLE_RECEIVE);
	while(I2CMasterBusy(i2c_base));

	// Check for errors
	if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

	// Read received data
	data = I2CMasterDataGet(i2c_base);

	return data;
}

uint32_t I2CWriteSingle(uint32_t i2c_base, uint8_t address, uint8_t reg, uint8_t data) {

	// Set slave register to be written
	while(I2CMasterBusy(i2c_base));
	I2CMasterSlaveAddrSet(i2c_base, address, 0);
	I2CMasterDataPut(i2c_base, reg);
	I2CMasterControl(i2c_base, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(i2c_base));

	// Check for errors
	if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

	// Write data
	I2CMasterDataPut(i2c_base, data);
	I2CMasterControl(i2c_base, I2C_MASTER_CMD_BURST_SEND_CONT);
	while(I2CMasterBusy(i2c_base));

	// Check for errors
	if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

	// End transmission
	I2CMasterControl(i2c_base, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(i2c_base));

	// Check for errors
	if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

	return 1;
}

uint32_t I2CReadMultiple(uint32_t i2c_base, uint8_t address, uint8_t reg, uint8_t *data, uint32_t size) {
	uint32_t byte_count;
	uint32_t master_command;

	// Set slave register to be read
	while(I2CMasterBusy(i2c_base));
	I2CMasterSlaveAddrSet(i2c_base, address, 0);
	I2CMasterDataPut(i2c_base, reg);
	I2CMasterControl(i2c_base, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(i2c_base));

	// Check for errors
	if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

	// Start burst read
	I2CMasterSlaveAddrSet(i2c_base, address, 1);
	master_command = I2C_MASTER_CMD_BURST_RECEIVE_START;

	for (byte_count = 0; byte_count < size; byte_count++) {

		// The second byte has to be read with CONT
		if (byte_count == 1) master_command = I2C_MASTER_CMD_BURST_RECEIVE_CONT;

		// The last byte has to be read with FINISH
		if (byte_count == size - 1) master_command = I2C_MASTER_CMD_BURST_RECEIVE_FINISH;

		// If only one byte, reconfigure to SINGLE
		if (size == 1) master_command = I2C_MASTER_CMD_SINGLE_RECEIVE;

		// Initiate read
		I2CMasterControl(i2c_base, master_command);

		// Wait for master operation
		while(I2CMasterBusy(i2c_base));

		// Check for errors
		if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

		// Put data into array
		data[byte_count] = I2CMasterDataGet(i2c_base);
	}

	return byte_count;
}

uint32_t I2CWriteMultiple(uint32_t i2c_base, uint8_t address, uint8_t reg, uint8_t *data, uint32_t size) {
	uint32_t byte_count;
	uint32_t master_command;

	// Set slave register to be written
	while(I2CMasterBusy(i2c_base));
	I2CMasterSlaveAddrSet(i2c_base, address, 0);
	I2CMasterDataPut(i2c_base, reg);
	I2CMasterControl(i2c_base, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(i2c_base));

	// Check for errors
	if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;

	// Start burst write
	master_command = I2C_MASTER_CMD_BURST_SEND_CONT;

	for (byte_count = 0; byte_count < size; byte_count++) {

		// The second byte has to be sent with CONT
		if (byte_count == 1) master_command = I2C_MASTER_CMD_BURST_SEND_CONT;

		// The last byte has to be sent with FINISH
		if (byte_count == size - 1) master_command = I2C_MASTER_CMD_BURST_SEND_FINISH;

		// If only one byte, reconfigure to SINGLE
		if (size == 1) master_command = I2C_MASTER_CMD_SINGLE_SEND;

		// Write byte
		I2CMasterDataPut(i2c_base, data[byte_count]);
		I2CMasterControl(i2c_base, master_command);

		// Wait for master operation
		while(I2CMasterBusy(i2c_base));

		// Check for errors
		if (I2CMasterErr(i2c_base) != I2C_MASTER_ERR_NONE) return 0;
	}

	return 1;
}








