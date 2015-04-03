/*
 * hmc5883l.c
 *
 *  Created on: Mar 17, 2014
 *      Author: Luiz
 */

/*
 * Includes
 */
#define PART_TM4C123GH6PM
#include "hmc5883l.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/i2c.h"
#include "drivers/i2c.h"

/*
 * Functions
 */
bool HMC5883LInit(uint32_t i2c_base) {
	I2CWriteSingle(i2c_base, HMC5883L_ADDRESS, HMC5883L_REG_CONFIGB, 0x02);
	I2CWriteSingle(i2c_base, HMC5883L_ADDRESS, HMC5883L_REG_MODE, HMC5883L_CONTINUOUS);
	return 1;
}

int16_t HMC5883LGetX(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, HMC5883L_ADDRESS, HMC5883L_REG_X, data, 2);
	return (uint16_t)(data[0] << 8 | data[1]);
}

int16_t HMC5883LGetY(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, HMC5883L_ADDRESS, HMC5883L_REG_Y, data, 2);
	return (uint16_t)(data[0] << 8 | data[1]);
}

int16_t HMC5883LGetZ(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, HMC5883L_ADDRESS, HMC5883L_REG_Z, data, 2);
	return (uint16_t)(data[0] << 8 | data[1]);
}







