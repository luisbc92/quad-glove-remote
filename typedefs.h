/*
 * typedefs.h
 *
 *  Created on: Mar 16, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_TYPEDEFS_H_
#define QUADGLOVEREMOTE_TYPEDEFS_H_

#include <stdint.h>
#include <stdbool.h>

// Structure with calibration offsets for an IMU
typedef struct ImuOffset {
	// Accelerometer
	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;
	// Gyroscope
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
} ImuOffset;

// Structure with raw input from an IMU
typedef struct ImuRaw {
	// Accelerometer
	int16_t acc_x;	// -512 <-> +512
	int16_t acc_y;
	int16_t acc_z;
	// Gyroscope
	int16_t gyro_x;	// -32,768 <-> +32,768
	int16_t gyro_y;
	int16_t gyro_z;
	// Compass
	int16_t mag_x;	// -4096 <-> +4096
	int16_t mag_y;
	int16_t mag_z;
} ImuRaw;

// Structure with filtered input from and IMU
typedef struct ImuFiltered {
	// Rotation
	float x;	// -90 <-> 90
	float y;
	float z;
	// Inverted
	bool inv;
} ImuFiltered;

// Structure with control values for quadcopter
typedef struct QuadControl {
	// Derivative values
	int16_t pitch;		// 1100 <-> 1900
	int16_t roll;		// 1100 <-> 1900
	int16_t yaw;		//    0 <->  360
	int16_t throttle;	// 1100 <-> 1900
	int16_t arm;		// 1100 (disarm) 1900 (arm)
	//int16_t hold;		// 1100 (no hold) 1900 (gps hold)
} QuadControl;

// Glove State
typedef struct GloveState {
	bool	fist;		// Making a fist
	bool	inverted;	// Glove upside-down
	bool	left;		//
	bool	right;		//
	bool	up;			//
	bool	down;		//
} GloveState;

// Main State
typedef enum MainState {
	INIT,
	LAND,
	ARM,
	SAFE,
	FLY,
	HOLD
} MainState;

// RGB LED
typedef struct LedState {
	enum	color {OFF, BLUE, GREEN, AQUA,
		RED, PURPLE, YELLOW, WHITE} color;
	int16_t	rate;
} LedState;

#endif /* QUADGLOVEREMOTE_TYPEDEFS_H_ */











