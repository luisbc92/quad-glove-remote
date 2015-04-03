/*
 * itg3200.c
 *
 *  Created on: Mar 16, 2014
 *      Author: Luiz
 */

/*
 * Includes
 */
#define PART_TM4C123GH6PM
#include "itg3200.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/i2c.h"
#include "drivers/i2c.h"

bool ITG3200Init(uint32_t i2c_base) {
	/*
	 * Configures
	 * 	- Sample Rate = 500 Hz
	 * 	- Parameter = +/- 2000 deg/s
	 * 	- Low Pass Filter = 5 Hz
	 * 	- No interrupt
	 */
	I2CWriteSingle(i2c_base, ITG3200_ADDRESS, ITG3200_REG_PWR_MGM, 0x00);
	I2CWriteSingle(i2c_base, ITG3200_ADDRESS, ITG3200_REG_SMPLRT_DIV, 0x02);
	I2CWriteSingle(i2c_base, ITG3200_ADDRESS, ITG3200_REG_DLPF_FS, 0x1E);
	I2CWriteSingle(i2c_base, ITG3200_ADDRESS, ITG3200_REG_INT_CONFIG, 0x00);
	return 1;
}

int16_t ITG3200GetX(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, ITG3200_ADDRESS, ITG3200_REG_X, data, 2);
	return (uint16_t)(data[0] << 8 | data[1]);
}

int16_t ITG3200GetY(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, ITG3200_ADDRESS, ITG3200_REG_Y, data, 2);
	return (uint16_t)(data[0] << 8 | data[1]);
}

int16_t ITG3200GetZ(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, ITG3200_ADDRESS, ITG3200_REG_Z, data, 2);
	return (uint16_t)(data[0] << 8 | data[1]);
}

int16_t ITG3200GetTemp(uint32_t i2c_base) {
	uint8_t data[2];
	I2CReadMultiple(i2c_base, ITG3200_ADDRESS, ITG3200_REG_TEMP, data, 2);
	return (uint16_t)(data[0] << 8 | data[1]);
}

