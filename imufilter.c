/*
 * imufilter.c
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#include "imufilter.h"

void ImuFilter(ImuRaw *raw, ImuFiltered *filtered) {
	float pitch_acc, roll_acc;

	// Integrate gyroscope data
	filtered->x += ((float)raw->gyro_x / GYRO_SENSITIVITY) * LOOP_DT;
	filtered->y -= ((float)raw->gyro_y / GYRO_SENSITIVITY) * LOOP_DT;

	// Compensate for drift with accelerometer data if within reasonable forces
	// Sensitivity = -2 to 2 G at 10bit -> 2G = 512 && 0.5G = 256
	int force_magnitude = abs(raw->acc_x) + abs(raw->acc_y) + abs(raw->acc_z);
	if (force_magnitude > 256 && force_magnitude < 512) {

		// If accelerometer is upside down flip rotation and mark inv flag
		if (raw->acc_z < 0) {
			// Invert
			raw->acc_x = -raw->acc_x;
			raw->acc_y = -raw->acc_y;
			raw->acc_z = -raw->acc_z;
			// Mark flag
			filtered->inv = true;
		} else {
			filtered->inv = false;
		}

		pitch_acc = atan2f((float)(raw->acc_y), (float)(raw->acc_z)) * 180 / PI;
		roll_acc = atan2f((float)(raw->acc_x), (float)(raw->acc_z)) * 180 / PI;

		// If values obtained from the accelerometer differ much from the gyroscope
		// we assume that a flip occurred so we reset to accelerometer data
		if ((abs(pitch_acc - filtered->x) > 90) || (abs(roll_acc - filtered->y) > 90)) {
			filtered->x = pitch_acc;
			filtered->y = roll_acc;
		} else {
			filtered->x = filtered->x * 0.98 + pitch_acc * 0.02;
			filtered->y = filtered->y * 0.98 + roll_acc * 0.02;
		}

	}

	filtered->z = atan2f((float)(raw->mag_x), (float)(raw->mag_y)) * 180 / PI;
}


