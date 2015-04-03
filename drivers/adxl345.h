/*
 * ADX345.h
 *
 *  Created on: Mar 14, 2014
 *      Author: Luiz
 */

#ifndef ADX345_H_
#define ADX345_H_

/*
 * Includes
 */
#include <stdint.h>
#include <stdbool.h>

/*
 * Definitions
 */

// I2C Address
#define ADXL345_ADDRESS                 (0x53)    // Assumes ALT address pin low

// Registers
#define ADXL345_REG_DEVID               (0x00)    // Device ID
#define ADXL345_REG_THRESH_TAP          (0x1D)    // Tap threshold
#define ADXL345_REG_OFSX                (0x1E)    // X-axis offset
#define ADXL345_REG_OFSY                (0x1F)    // Y-axis offset
#define ADXL345_REG_OFSZ                (0x20)    // Z-axis offset
#define ADXL345_REG_DUR                 (0x21)    // Tap duration
#define ADXL345_REG_LATENT              (0x22)    // Tap latency
#define ADXL345_REG_WINDOW              (0x23)    // Tap window
#define ADXL345_REG_THRESH_ACT          (0x24)    // Activity threshold
#define ADXL345_REG_THRESH_INACT        (0x25)    // Inactivity threshold
#define ADXL345_REG_TIME_INACT          (0x26)    // Inactivity time
#define ADXL345_REG_ACT_INACT_CTL       (0x27)    // Axis enable control for activity and inactivity detection
#define ADXL345_REG_THRESH_FF           (0x28)    // Free-fall threshold
#define ADXL345_REG_TIME_FF             (0x29)    // Free-fall time
#define ADXL345_REG_TAP_AXES            (0x2A)    // Axis control for single/double tap
#define ADXL345_REG_ACT_TAP_STATUS      (0x2B)    // Source for single/double tap
#define ADXL345_REG_BW_RATE             (0x2C)    // Data rate and power mode control
#define ADXL345_REG_POWER_CTL           (0x2D)    // Power-saving features control
#define ADXL345_REG_INT_ENABLE          (0x2E)    // Interrupt enable control
#define ADXL345_REG_INT_MAP             (0x2F)    // Interrupt mapping control
#define ADXL345_REG_INT_SOURCE          (0x30)    // Source of interrupts
#define ADXL345_REG_DATA_FORMAT         (0x31)    // Data format control
#define ADXL345_REG_DATAX0              (0x32)    // X-axis data 0
#define ADXL345_REG_DATAX1              (0x33)    // X-axis data 1
#define ADXL345_REG_DATAY0              (0x34)    // Y-axis data 0
#define ADXL345_REG_DATAY1              (0x35)    // Y-axis data 1
#define ADXL345_REG_DATAZ0              (0x36)    // Z-axis data 0
#define ADXL345_REG_DATAZ1              (0x37)    // Z-axis data 1
#define ADXL345_REG_FIFO_CTL            (0x38)    // FIFO control
#define ADXL345_REG_FIFO_STATUS         (0x39)    // FIFO status
#define ADXL345_MG2G_MULTIPLIER 		(0.004)   // 4mg per lsb

/* Used with register 0x2C (ADXL345_REG_BW_RATE) to set bandwidth */
typedef enum {
	ADXL345_DATARATE_3200_HZ    = 0x0F, // 1600Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_1600_HZ    = 0x0E, //  800Hz Bandwidth    90µA IDD
	ADXL345_DATARATE_800_HZ     = 0x0D, //  400Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_400_HZ     = 0x0C, //  200Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_200_HZ     = 0x0B, //  100Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_100_HZ     = 0x0A, //   50Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_50_HZ      = 0x09, //   25Hz Bandwidth    90µA IDD
	ADXL345_DATARATE_25_HZ      = 0x08, // 12.5Hz Bandwidth    60µA IDD
	ADXL345_DATARATE_12_5_HZ    = 0x07, // 6.25Hz Bandwidth    50µA IDD
	ADXL345_DATARATE_6_25HZ     = 0x06, // 3.13Hz Bandwidth    45µA IDD
	ADXL345_DATARATE_3_13_HZ    = 0x05, // 1.56Hz Bandwidth    40µA IDD
	ADXL345_DATARATE_1_56_HZ    = 0x04, // 0.78Hz Bandwidth    34µA IDD
	ADXL345_DATARATE_0_78_HZ    = 0x03, // 0.39Hz Bandwidth    23µA IDD
	ADXL345_DATARATE_0_39_HZ    = 0x02, // 0.20Hz Bandwidth    23µA IDD
	ADXL345_DATARATE_0_20_HZ    = 0x01, // 0.10Hz Bandwidth    23µA IDD
	ADXL345_DATARATE_0_10_HZ    = 0x00  // 0.05Hz Bandwidth    23µA IDD (default value)
} DataRate;

/* Used with register 0x31 (ADXL345_REG_DATA_FORMAT) to set g range */
typedef enum {
  ADXL345_RANGE_16_G          = 0x03,   // +/- 16g
  ADXL345_RANGE_8_G           = 0x02,   // +/- 8g
  ADXL345_RANGE_4_G           = 0x01,   // +/- 4g
  ADXL345_RANGE_2_G           = 0x00    // +/- 2g (default value)
} Range;

/*
 * Functions
 */
uint8_t ADXL345GetDeviceID(uint32_t i2c_base);
int16_t ADXL345GetX(uint32_t i2c_base);
int16_t ADXL345GetY(uint32_t i2c_base);
int16_t ADXL345GetZ(uint32_t i2c_base);
bool ADXL345Init(uint32_t i2c_base);
void ADXL345SetRange(uint32_t i2c_base, Range range);
Range ADXL345GetRange(uint32_t i2c_base);
void ADXL345SetDataRate(uint32_t i2c_base, DataRate data_rate);
DataRate ADXL345GetDataRate(uint32_t i2c_base);


#endif /* ADX345_H_ */
