/*
 * itg3200.h
 *
 *  Created on: Mar 16, 2014
 *      Author: Luiz
 */

#ifndef ITG3200_H_
#define ITG3200_H_

/*
 * Includes
 */
#include <stdint.h>
#include <stdbool.h>

/*
 * Definitions
 */

// I2C Port
#define ITG3200_I2C_BASE				I2C3_BASE

// I2C Address
#define ITG3200_ADDRESS					(0x68)		// Assumes AD0 low

// Registers
#define ITG3200_REG_WHO_AM_I			(0x00)		// Device ID
#define ITG3200_REG_SMPLRT_DIV			(0x15)		// Sample Rate Divider
#define ITG3200_REG_DLPF_FS				(0x16)		// Sensor Acquisition Configuration
#define ITG3200_REG_INT_CONFIG			(0x17)		// Interrupt Configuration
#define ITG3200_REG_INT_STATUS			(0x18)		// Interrupt Status
#define ITG3200_REG_TEMP				(0x1B)		// Temperature (2 Bytes)
#define ITG3200_REG_X					(0x1D)		// X axis (2 Bytes)
#define ITG3200_REG_Y					(0x1F)		// Y axis (2 Bytes)
#define ITG3200_REG_Z					(0x21)		// Z axis (2 Bytes)
#define ITG3200_REG_PWR_MGM				(0x3E)		// Power Management

/*
 * Functions
 */
bool ITG3200Init(uint32_t i2c_base);
int16_t ITG3200GetX(uint32_t i2c_base);
int16_t ITG3200GetY(uint32_t i2c_base);
int16_t ITG3200GetZ(uint32_t i2c_base);
int16_t ITG3200GetTemp(uint32_t i2c_base);


#endif /* ITG3200_H_ */




















