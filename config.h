/*
 * config.h
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_CONFIG_H_
#define QUADGLOVEREMOTE_CONFIG_H_

// IMU Parameters
#define GYRO_SENSITIVITY	14.375

// Scheduler
#define SCHED_FREQ		1000

// Processing Loop
#define LOOP_FREQ		100
#define LOOP_DT			(1 / (float)LOOP_FREQ)

// IMU Identifier
#define IMU_HAND		0
#define IMU_FINGER		1
#define IMU_HAND_I2C	I2C1_BASE
#define IMU_FINGER_I2C	I2C3_BASE

// Gestures
#define GEST_LOW		10		// Minimum value for gesture
#define GEST_HIGH		75		// Maximum value for gesture
#define GEST_ALTRATE	1		// Rate in ms for inc/dec altitutde

// Direction Control
#define DIR_MIN			15.0
#define DIR_MAX			60.0

// Timing
#define TIME_ARM		300
#define TIME_DISARM		100
#define TIME_HOLD		300

// LED Rates
#define FAST			250
#define NORMAL			500
#define SLOW			1000

// Console
#define CON_RATE		115200

// Link
#define LINK_ID			"1234"	// Xbee PAN ID
#define LINK_MY			"0"		// Xbee Local Address
#define LINK_DL			"1"		// Xbee Remote Address
#define LINK_BD			"7"		// Xbee Baud Rate










#endif /* QUADGLOVEREMOTE_CONFIG_H_ */
