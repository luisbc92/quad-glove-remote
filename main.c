/*********************************************************
 * quadGloveRemote
 *
 *********************************************************/

/*
 * Includes
 */
#define PART_TM4C123GH6PM
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "drivers/i2c.h"
#include "drivers/lcd.h"
#include "drivers/color.h"
#include "drivers/adxl345.h"
#include "drivers/itg3200.h"
#include "drivers/hmc5883l.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "utils/random.h"
#include "utils/scheduler.h"
#include "gesture.h"
#include "config.h"
#include "typedefs.h"
#include "launchpad.h"
#include "imufilter.h"
#include "console.h"
#include "button.h"
#include "link.h"

/*
 * Global Variables
 */

ImuOffset		imu_offset[2];
ImuRaw			imu_raw[2];
ImuFiltered		imu_filtered[2];
QuadControl		quad;
GloveState		glove;
MainState		main_state;
LedState		led_state;
long			timer;

/*
 * Functions
 */
void ImuCalibrate() {
	imu_offset[0].gyro_x = ITG3200GetX(IMU_HAND_I2C);
	imu_offset[0].gyro_y = ITG3200GetY(IMU_HAND_I2C);
	imu_offset[0].gyro_z = ITG3200GetZ(IMU_HAND_I2C);
	imu_offset[1].gyro_x = ITG3200GetX(IMU_FINGER_I2C);
	imu_offset[1].gyro_y = ITG3200GetY(IMU_FINGER_I2C);
	imu_offset[1].gyro_z = ITG3200GetZ(IMU_FINGER_I2C);
}

void ImuUpdate(void *pvParam) {
	imu_raw[0].acc_x = ADXL345GetX(IMU_HAND_I2C);
	imu_raw[0].acc_y = ADXL345GetY(IMU_HAND_I2C);
	imu_raw[0].acc_z = ADXL345GetZ(IMU_HAND_I2C);
	imu_raw[0].gyro_x = ITG3200GetX(IMU_HAND_I2C) - imu_offset[0].gyro_x;
	imu_raw[0].gyro_y = ITG3200GetY(IMU_HAND_I2C) - imu_offset[0].gyro_y;
	imu_raw[0].gyro_z = ITG3200GetZ(IMU_HAND_I2C) - imu_offset[0].gyro_z;
	imu_raw[0].mag_x = HMC5883LGetX(IMU_HAND_I2C);
	imu_raw[0].mag_y = HMC5883LGetY(IMU_HAND_I2C);
	imu_raw[0].mag_z = HMC5883LGetZ(IMU_HAND_I2C);

	imu_raw[1].acc_x = ADXL345GetX(IMU_FINGER_I2C);
	imu_raw[1].acc_y = ADXL345GetY(IMU_FINGER_I2C);
	imu_raw[1].acc_z = ADXL345GetZ(IMU_FINGER_I2C);
	imu_raw[1].gyro_x = ITG3200GetX(IMU_FINGER_I2C) - imu_offset[1].gyro_x;
	imu_raw[1].gyro_y = ITG3200GetY(IMU_FINGER_I2C) - imu_offset[1].gyro_y;
	imu_raw[1].gyro_z = ITG3200GetZ(IMU_FINGER_I2C) - imu_offset[1].gyro_z;
	imu_raw[1].mag_x = HMC5883LGetX(IMU_FINGER_I2C);
	imu_raw[1].mag_y = HMC5883LGetY(IMU_FINGER_I2C);
	imu_raw[1].mag_z = HMC5883LGetZ(IMU_FINGER_I2C);

	ImuFilter(&imu_raw[0], &imu_filtered[0]);
	ImuFilter(&imu_raw[1], &imu_filtered[1]);

	GestureUpdate(&imu_filtered[0], &imu_filtered[1], &glove);
}

void TimerUpdate(void *pvParam) {
	timer++;
}

// LED
void LedUpdate(void *pvParam) {
	static uint16_t timer = 0;		// Increment by 100ms
	static bool toggle = 0;			// Invert bit for flashing

	timer += 100;

	if (led_state.rate > 0) {
		if (timer > led_state.rate/2) {
			toggle = ~toggle;
			LedWrite(toggle ? led_state.color : 0);
			timer = 0;
		}
	} else {
		LedWrite(led_state.color);
	}

}

// Link
void LinkSendWrapper(void *pvParam) {
	LinkSend();
}

/*
 * Functions to take out
 */
// Delay Milliseconds
#define DelayMs(time)	(SysCtlDelay((SysCtlClockGet() / 3000) * time))


/*
 * Scheduler
 */

tSchedulerTask g_psSchedulerTable[] = {
	{ImuUpdate, (void*)0, (SCHED_FREQ/LOOP_FREQ), 0, true},
	{ConsoleRun, (void*)0, 200, 0, true},
	{TimerUpdate, (void*)0, 10, 0, true},
	{LinkSend, (void*)0, 20, 0, true},
	{LedUpdate, (void*)0, 100, 0, true}
};
uint32_t g_ui32SchedulerNumTasks = (sizeof(g_psSchedulerTable) / sizeof(tSchedulerTask));

/*
 * Main Loop
 */
void main() {

	// Initialize Peripherals
	LaunchPadInit();

	// Initialize IMU
	I2CInit(IMU_HAND_I2C, false);
	ADXL345Init(IMU_HAND_I2C);
	ADXL345SetRange(IMU_HAND_I2C, ADXL345_RANGE_2_G);
	ADXL345SetDataRate(IMU_HAND_I2C, ADXL345_DATARATE_400_HZ);
	ITG3200Init(IMU_HAND_I2C);
	HMC5883LInit(IMU_HAND_I2C);

	I2CInit(IMU_FINGER_I2C, false);
	ADXL345Init(IMU_FINGER_I2C);
	ADXL345SetRange(IMU_FINGER_I2C, ADXL345_RANGE_2_G);
	ADXL345SetDataRate(IMU_FINGER_I2C, ADXL345_DATARATE_400_HZ);
	ITG3200Init(IMU_FINGER_I2C);
	HMC5883LInit(IMU_FINGER_I2C);

	ImuCalibrate();

	// Initialize Console
	ConsoleInit();

	// Initialize Link
	LinkInit();

	// Initialize Scheduler
	SchedulerInit(SCHED_FREQ);
	IntMasterEnable();

	// Main Loop
	while (1) {

		// Parallel Tasks
		SchedulerRun();

		// Main State Machine
		switch (main_state) {
		case INIT:
			// Quadcopter is disarmed, motors off.
			quad.throttle = 1100;
			quad.arm = 1100;
			quad.pitch = 1500;
			quad.roll = 1500;
			main_state = LAND;
			break;

		case LAND:
			// LED
			led_state.color = GREEN;
			// Quadcopter is disarmed, motors off.
			quad.throttle = 1100;
			quad.arm = 1100;
			// Wait for glove to be inverted and with a fist,
			// then wait 3 seconds and arm quadcopter.
			if (glove.inverted && glove.fist) {
				if (timer > TIME_ARM) main_state = ARM;
				led_state.rate = FAST;
			} else {
				timer = 0;
				led_state.rate = 0;
			}
			break;

		case ARM:
			// LED
			led_state.color = YELLOW;
			led_state.rate = NORMAL;
			// Quadcopter is armed, motors on.
			quad.throttle = 1100;
			quad.arm = 1900;
			// Wait for glove to not be inverted and with a fist,
			// then wait 1 second and switch to safe mode.
			if (!glove.inverted && glove.fist) {
				if (timer > 100) {
					main_state = SAFE;
				}
			} else {
				timer = 0;
			}
			break;

		case SAFE:
			// Active while glove is in a fist, switches to FLY when not.
			// Quadcopter is armed, motors on.
			// No pitch and roll is sent to quadcopter.
			// Up and down movements control altitude.
			if (glove.fist) {
				// Block pitch and roll
				quad.pitch = 1500;
				quad.roll = 1500;
				// Disable GPS hold
				//quad.hold = 1100;

				// Landing
				if (ButtonRead(BTN_DISARM)) {
					if (timer > TIME_DISARM) {
						main_state = LAND;
						led_state.color = WHITE;
						led_state.rate = 0;
						LedUpdate((void*)0);
					}
					led_state.color = GREEN;
					led_state.rate = FAST;
				} else
				// Holding
				if (ButtonRead(BTN_HOLD)) {
					if (timer > TIME_HOLD) {
						main_state = HOLD;
						led_state.color = WHITE;
						led_state.rate = 0;
						LedUpdate((void*)0);
						while (ButtonRead(BTN_HOLD));
					}
					led_state.color = BLUE;
					led_state.rate = FAST;
				} else
				// Altitude control
				if (glove.up && (quad.throttle < 1900)) {
					if (timer > GEST_ALTRATE) {
						quad.throttle++;
						timer = 0;
					}
					led_state.color = RED;
					led_state.rate = NORMAL;
				} else
				if (glove.down && (quad.throttle > 1100)) {
					if (timer > GEST_ALTRATE) {
						quad.throttle--;
						timer = 0;
					}
					led_state.color = RED;
					led_state.rate = NORMAL;
				} else {
					timer = 0;
					led_state.color = RED;
					led_state.rate = SLOW;
				}
			} else {
				main_state = FLY;
			}
			break;

		case FLY:
			// Active while glove is open, switches to SAFE when not.
			// Quadcopter is armed, motors on.
			// Pitch and roll is sent to quadcopter.
			// Throttle/Altitude is fixed.
			if (!glove.fist) {
				// LED
				led_state.color = RED;
				led_state.rate = FAST;
				// Disable GPS hold
				//quad.hold = 1100;

				// Calculate pitch
				if (abs(imu_filtered[IMU_HAND].y) > DIR_MAX) {
					if (imu_filtered[IMU_HAND].y > 0) quad.pitch = 1900;
					if (imu_filtered[IMU_HAND].y < 0) quad.pitch = 1100;
				}
				else if (abs(imu_filtered[IMU_HAND].y) > DIR_MIN) {
					if (imu_filtered[IMU_HAND].y > 0)
						quad.pitch = (int16_t)(1500.0 + ((imu_filtered[IMU_HAND].y - DIR_MIN) * (400.0/DIR_MAX-DIR_MIN)));	// Chicanada
					if (imu_filtered[IMU_HAND].y < 0)
						quad.pitch = (int16_t)(1500.0 + ((imu_filtered[IMU_HAND].y + DIR_MIN) * (400.0/DIR_MAX-DIR_MIN)));	// Chicanada
				}
				else {
					quad.pitch = 1500;
				}

				// Calculate roll
				if (abs(imu_filtered[IMU_HAND].x) > DIR_MAX) {
					if (imu_filtered[IMU_HAND].x > 0) quad.roll = 1900;
					if (imu_filtered[IMU_HAND].x < 0) quad.roll = 1100;
				}
				else if (abs(imu_filtered[IMU_HAND].x) > DIR_MIN) {
					if (imu_filtered[IMU_HAND].x > 0)
						quad.roll = (int16_t)(1500.0 + (-(imu_filtered[IMU_HAND].x - DIR_MIN) * (400.0/DIR_MAX-DIR_MIN)));	// Chicanada
					if (imu_filtered[IMU_HAND].x < 0)
						quad.roll = (int16_t)(1500.0 + (-(imu_filtered[IMU_HAND].x + DIR_MIN) * (400.0/DIR_MAX-DIR_MIN)));	// Chicanada
				}
				else {
					quad.roll = 1500;
				}

			} else {
				main_state = SAFE;
			}
			break;

		case HOLD:
			// Enable GPS hold
			//quad.hold = 1900;

			led_state.color = BLUE;
			led_state.rate = SLOW;

			// Block pitch and roll
			quad.pitch = 1500;
			quad.roll = 1500;

			if (ButtonRead(BTN_HOLD)) {
				if (timer > TIME_HOLD) {
					main_state = SAFE;
					led_state.color = WHITE;
					led_state.rate = 0;
					LedUpdate((void*)0);
					while (ButtonRead(BTN_HOLD));
				}
				led_state.color = RED;
				led_state.rate = FAST;
			} else {
				timer = 0;
			}
			break;

		}

		// Safety Landing
		if ((main_state == SAFE || main_state == FLY || main_state == HOLD) &&
				ButtonRead(BTN_DISARM) && ButtonRead(BTN_HOLD)) {
			timer = 0;
			quad.throttle = 1250;
		}
	}
}

























