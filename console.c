/*
 * console.c
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#include "console.h"

extern ImuFiltered	imu_filtered[2];
extern ImuRaw		imu_raw[2];
extern GloveState	glove;
extern MainState	main_state;
extern QuadControl	quad;

enum StreamState {
	NO_STREAM,
	SENSORS_FILTERED,
	SENSORS_RAW,
	GESTURES,
	STATUS
} stream_state;

// Initialisation
void ConsoleInit() {
	// Configure UART0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
	UARTStdioConfig(0, CON_RATE, 16000000);
}

void cmdStreamStatus(int argc, char *argv[]) {
	stream_state = STATUS;
}

// Read Sensor Data
void cmdStreamFiltered(int argc, char *argv[]) {
	stream_state = SENSORS_FILTERED;
}

// Read Sensor Data
void cmdStreamRaw(int argc, char *argv[]) {
	stream_state = SENSORS_RAW;
}

// Read Gestures
void cmdStreamGlove(int argc, char *argv[]) {
	stream_state = GESTURES;
}

// Disable Stream
void cmdStreamEnd(int argc, char *argv[]) {
	stream_state = NO_STREAM;
}

// Commands List
tCmdLineEntry g_psCmdTable[] = {
	{"streamFiltered", (pfnCmdLine) cmdStreamFiltered, "Sensor Stream"},
	{"streamRaw", (pfnCmdLine) cmdStreamRaw, "Raw Stream"},
	{"streamGlove", (pfnCmdLine) cmdStreamGlove, "Glove Stream"},
	{"streamEnd", (pfnCmdLine) cmdStreamEnd, "End Stream"},
	{"streamStatus", (pfnCmdLine) cmdStreamStatus, "End Stream"},
	{0, 0, 0}
};

// UART Handler
void ConsoleRun(void *pvParam) {
	// Read incoming chars into a buffer and process commands
	static char buffer[128];
	static int  ptr;

	while (UARTCharsAvail(UART0_BASE)) {
		buffer[ptr] = UARTCharGet(UART0_BASE);

		if (buffer[ptr] == '\n') {
			buffer[ptr] = '\0';
			buffer[ptr-1] = '\0';
			CmdLineProcess(buffer);
			ptr = 0;
		} else {
			ptr++;
			if (ptr >= 128) ptr = 0;
		}
	}

	// Stream Commands
	switch (stream_state) {
	case NO_STREAM:
		break;

	case SENSORS_FILTERED:
		UARTprintf("[HAND]   X=%3d Y=%3d Z=%3d INV=%3d\n", (int)imu_filtered[0].x, (int)imu_filtered[0].y, (int)imu_filtered[0].z, (int)imu_filtered[0].inv);
		UARTprintf("[FINGER] X=%3d Y=%3d Z=%3d INV=%3d\n", (int)imu_filtered[1].x, (int)imu_filtered[1].y, (int)imu_filtered[1].z, (int)imu_filtered[1].inv);
		UARTprintf("\n");
		break;

	case SENSORS_RAW:
		UARTprintf("[HAND]\n");
		UARTprintf("ACC>  X=%3d Y=%3d Z=%3d\n", (int)imu_raw[0].acc_x, (int)imu_raw[0].acc_y, (int)imu_raw[0].acc_z);
		UARTprintf("GYRO> X=%3d Y=%3d Z=%3d\n", (int)imu_raw[0].gyro_x, (int)imu_raw[0].gyro_y, (int)imu_raw[0].gyro_z);
		UARTprintf("MAG>  X=%3d Y=%3d Z=%3d\n", (int)imu_raw[0].mag_x, (int)imu_raw[0].mag_y, (int)imu_raw[0].mag_z);
		UARTprintf("[FINGER]\n");
		UARTprintf("ACC>  X=%3d Y=%3d Z=%3d\n", (int)imu_raw[1].acc_x, (int)imu_raw[1].acc_y, (int)imu_raw[1].acc_z);
		UARTprintf("GYRO> X=%3d Y=%3d Z=%3d\n", (int)imu_raw[1].gyro_x, (int)imu_raw[1].gyro_y, (int)imu_raw[1].gyro_z);
		UARTprintf("MAG>  X=%3d Y=%3d Z=%3d\n", (int)imu_raw[1].mag_x, (int)imu_raw[1].mag_y, (int)imu_raw[1].mag_z);
		UARTprintf("\n");
		break;

	case GESTURES:
		UARTprintf("[FIST]  %d\n", glove.fist);
		UARTprintf("[INV]   %d\n", glove.inverted);
		UARTprintf("[LEFT]  %d\n", glove.left);
		UARTprintf("[RIGHT] %d\n", glove.right);
		UARTprintf("[UP]    %d\n", glove.up);
		UARTprintf("[DOWN]  %d\n", glove.down);
		UARTprintf("\n");

	case STATUS:
		UARTprintf("----- Status\n");
		UARTprintf("| State:     %d\n", main_state);
		UARTprintf("| Pitch:     %d\n", quad.pitch);
		UARTprintf("| Roll:      %d\n", quad.roll);
		UARTprintf("| Yaw:       %d\n", quad.yaw);
		UARTprintf("| Throttle:  %d\n", quad.throttle);
		UARTprintf("| Arm:       %d\n", quad.arm);
		//UARTprintf("| Hold:      %d\n", quad.hold);
	}
}







