/*
 * adxl345.c
 *
 *  Created on: Mar 14, 2014
 *      Author: Luiz
 */

/*
 * Includes
 */
#define PART_TM4C123GH6PM
#include "adxl345.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/i2c.h"
#include "drivers/i2c.h"

/*
 * Variables
 */

/*
 * Functions
 */
uint8_t ADXL345GetDeviceID(uint32_t i2c_base) {
	return I2CReadSingle(i2c_base, ADXL345_ADDRESS, ADXL345_REG_DEVID);
}

int16_t ADXL345GetX(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, ADXL345_ADDRESS, ADXL345_REG_DATAX0, data, 2);
	return (uint16_t)(data[0] | data[1] << 8);
}

int16_t ADXL345GetY(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, ADXL345_ADDRESS, ADXL345_REG_DATAY0, data, 2);
	return (uint16_t)(data[0] | data[1] << 8);
}

int16_t ADXL345GetZ(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, ADXL345_ADDRESS, ADXL345_REG_DATAZ0, data, 2);
	return (uint16_t)(data[0] | data[1] << 8);
}

bool ADXL345Init(uint32_t i2c_base) {
	return I2CWriteSingle(i2c_base, ADXL345_ADDRESS, ADXL345_REG_POWER_CTL, 0x08);
}

void ADXL345SetRange(uint32_t i2c_base, Range range) {
	// Read the data format register to preserve bits
	uint8_t format = I2CReadSingle(i2c_base, ADXL345_ADDRESS, ADXL345_REG_DATA_FORMAT);

	// Update the data rate
	format &= ~0x0F;
	format |= range;

	// Make sure that the FULL_RES bit is enabled for range scaling
	format |= 0x08;

	// Write the register back
	I2CWriteSingle(i2c_base, ADXL345_ADDRESS, ADXL345_REG_DATA_FORMAT, format);
}

Range ADXL345GetRange(uint32_t i2c_base) {
	return (Range)(I2CReadSingle(i2c_base, ADXL345_ADDRESS, ADXL345_REG_DATA_FORMAT) & 0x03);
}

void ADXL345SetDataRate(uint32_t i2c_base, DataRate data_rate) {
	I2CWriteSingle(i2c_base, ADXL345_ADDRESS, ADXL345_REG_BW_RATE, data_rate);
}

DataRate ADXL345GetDataRate(uint32_t i2c_base) {
	return (DataRate)(I2CReadSingle(i2c_base, ADXL345_ADDRESS, ADXL345_REG_BW_RATE) & 0x0F);
}


