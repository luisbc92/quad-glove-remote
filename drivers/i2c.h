/*
 * i2c.h
 *
 *  Created on: Mar 16, 2014
 *      Author: Luiz
 */

#ifndef I2C_H_
#define I2C_H_

/*
 * Port Location
 *
 * I2C0 - SCL<PB2> / SDA<PB3>
 * I2C1 - SCL<PA6> / SDA<PA7>
 * I2C2 - SCL<PE4> / SDA<PE5>
 * I2C3 - SCL<PD0> / SDA<PD1>
 *
 */

/*
 * Functions
 */

// Configure I2C port
void I2CInit(uint32_t i2c_base,
				   uint32_t i2c_speed);

// Reading/Writing single bytes of data
uint32_t I2CReadSingle(uint32_t i2c_base,
					   uint8_t address,
					   uint8_t reg);
uint32_t I2CWriteSingle(uint32_t i2c_base,
					    uint8_t address,
					    uint8_t reg,
					    uint8_t data);

// Reading/Writing multiple bytes of data
uint32_t I2CReadMultiple(uint32_t i2c_base,
					  	 uint8_t address,
					  	 uint8_t reg,
					  	 uint8_t *data,
					  	 uint32_t size);
uint32_t I2CWriteMultiple(uint32_t i2c_base,
						  uint8_t address,
						  uint8_t reg,
						  uint8_t *data,
						  uint32_t size);


#endif /* I2C_H_ */
