/*
 * HMC5883L.h
 *
 *  Created on: Mar 17, 2014
 *      Author: Luiz
 */

#ifndef HMC5883L_H_
#define HMC5883L_H_

/*
 * Includes
 */
#include <stdint.h>
#include <stdbool.h>

/*
 * Definitions
 */

// I2C Address
#define HMC5883L_ADDRESS				(0x1E)		// I2C Address

// Registers
#define HMC5883L_REG_CONFIGA			(0x00)		// Configuration Register A
#define HMC5883L_REG_CONFIGB			(0x01)		// Configuration Register B
#define HMC5883L_REG_MODE				(0x02)		// Mode Register
#define HMC5883L_REG_X					(0x03)		// X axis (2 Bytes)
#define HMC5883L_REG_Z					(0x05)		// Z axis (2 Bytes)
#define HMC5883L_REG_Y					(0x07)		// Y axis (2 Bytes)
#define HMC5883L_REG_STATUS				(0x09)		// Status Register
#define HMC5883L_REG_IDA				(0x10)		// Identification A
#define HMC5883L_REG_IDB				(0x11)		// Identification B
#define HMC5883L_REG_IDC				(0x12)		// Identification C

// Settings
#define HMC5883L_CONTINUOUS				(0x00)		// Continuous Mode
#define HMC5883L_SINGLE					(0x01)		// Single Mode
#define HMC5883L_IDLE					(0x03)		// Idle Mode

/*
 * Functions
 */

bool HMC5883LInit(uint32_t i2c_base);
int16_t HMC5883LGetX(uint32_t i2c_base);
int16_t HMC5883LGetY(uint32_t i2c_base);
int16_t HMC5883LGetZ(uint32_t i2c_base);

#endif /* HMC5883L_H_ */














