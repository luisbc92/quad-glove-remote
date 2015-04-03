/*
 * lcd.c
 *
 *  Created on: Mar 4, 2014
 *      Author: Luiz
 */

#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>
#include "fonts.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"

/*
 * Variables
 */
uint16_t color_low_ = 0;
uint16_t color_high_ = 0;
uint16_t colors_low_ = 0;
uint16_t colors_high_ = 0;
uint16_t colorbg_low_ = 0;
uint16_t colorbg_high_ = 0;

uint16_t graph_x_ = 0;
uint16_t graph_y_ = 0;
uint16_t graph_sizex_ = 0;
uint16_t graph_sizey_ = 0;
uint16_t graph_curx_ = 0;
uint16_t graph_cury_ = 0;


/*
 * Driver
 */

void LCDWrite(uint16_t dc, uint16_t data) {
	GPIOPinWrite(LCD_CS_PORT, LCD_CS_PIN, 0x00);
	if (dc == 1) GPIOPinWrite(LCD_DC_PORT, LCD_DC_PIN, 0xFF);
	else GPIOPinWrite(LCD_DC_PORT, LCD_DC_PIN, 0x00);
	SSIDataPut(SSI2_BASE, data);
	while(SSIBusy(SSI2_BASE));;
	//SysCtlDelay((SysCtlClockGet() / 3000000));
	GPIOPinWrite(LCD_CS_PORT, LCD_CS_PIN, 0xFF);
}

void LCDSetArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	LCDWrite(LCD_CMD, LCD_CASETP);
	LCDWrite(LCD_DATA, x1 >> 8);
	LCDWrite(LCD_DATA, x1);
	LCDWrite(LCD_DATA, x2 >> 8);
	LCDWrite(LCD_DATA, x2);

	LCDWrite(LCD_CMD, LCD_PASETP);
	LCDWrite(LCD_DATA, y1 >> 8);
	LCDWrite(LCD_DATA, y1);
	LCDWrite(LCD_DATA, y2 >> 8);
	LCDWrite(LCD_DATA, y2);

	LCDWrite(LCD_CMD, LCD_RAMWRP);
}

void LCDInit() {
	GPIOPinWrite(LCD_RST_PORT, LCD_RST_PIN, 0x00);
	SysCtlDelay((SysCtlClockGet() / 3000) * 10);
	GPIOPinWrite(LCD_RST_PORT, LCD_RST_PIN, 0xFF);

	LCDWrite(LCD_CMD, 0xCB);
	LCDWrite(LCD_DATA, 0x39);
	LCDWrite(LCD_DATA, 0x2C);
	LCDWrite(LCD_DATA, 0x00);
	LCDWrite(LCD_DATA, 0x34);
	LCDWrite(LCD_DATA, 0x02);

	LCDWrite(LCD_CMD, 0xCF);
	LCDWrite(LCD_DATA, 0x00);
	LCDWrite(LCD_DATA, 0xC1);
	LCDWrite(LCD_DATA, 0x30);

	LCDWrite(LCD_CMD, 0xE8);
	LCDWrite(LCD_DATA, 0x85);
	LCDWrite(LCD_DATA, 0x00);
	LCDWrite(LCD_DATA, 0x78);

	LCDWrite(LCD_CMD, 0xEA);
	LCDWrite(LCD_DATA, 0x00);
	LCDWrite(LCD_DATA, 0x00);

	LCDWrite(LCD_CMD, 0xED);
	LCDWrite(LCD_DATA, 0x64);
	LCDWrite(LCD_DATA, 0x03);
	LCDWrite(LCD_DATA, 0x12);
	LCDWrite(LCD_DATA, 0x81);

	LCDWrite(LCD_CMD, 0x7F);
	LCDWrite(LCD_DATA, 0x20);

	LCDWrite(LCD_CMD, LCD_ILIPC1);
	LCDWrite(LCD_DATA, 0x23);
	LCDWrite(LCD_CMD, LCD_ILIPC2);
	LCDWrite(LCD_DATA, 0x10);
	LCDWrite(LCD_CMD, LCD_ILIVC1);
	LCDWrite(LCD_DATA, 0x3e);
	LCDWrite(LCD_DATA, 0x28);
	LCDWrite(LCD_CMD, LCD_ILIVC2);
	LCDWrite(LCD_DATA, 0x86);

	LCDWrite(LCD_CMD, LCD_ILIPFS);
	LCDWrite(LCD_DATA, 0x55);

	LCDWrite(LCD_CMD, LCD_ILIFCNM);
	LCDWrite(LCD_DATA, 0x00);
	LCDWrite(LCD_DATA, 0x18);

	LCDWrite(LCD_CMD, LCD_ILIDFC);
	LCDWrite(LCD_DATA, 0x08);
	LCDWrite(LCD_DATA, 0x82);
	LCDWrite(LCD_DATA, 0x27);

	LCDWrite(LCD_CMD, LCD_ILIGFD);
	LCDWrite(LCD_DATA, 0x00);
	LCDWrite(LCD_CMD, LCD_ILIGS);
	LCDWrite(LCD_DATA, 0x01);

	LCDWrite(LCD_CMD, LCD_ILIPGC);
	uint16_t gamma1[] = { 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1,
			0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00 };
	uint16_t c = 0;
	while (c < 16) {
		LCDWrite(LCD_DATA, gamma1[c]);
		c++;
	}

	LCDWrite(LCD_CMD, LCD_ILINGC);
	uint16_t gamma2[] = { 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1,
			0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F };
	c = 0;
	while (c < 16) {
		LCDWrite(LCD_DATA, gamma2[c]);
		c++;
	}

	LCDWrite(LCD_CMD, LCD_SLEEPOUT);
	SysCtlDelay((SysCtlClockGet() / 3000) * 12);
	LCDWrite(LCD_CMD, LCD_DISPON);
	LCDWrite(LCD_CMD, LCD_RAMWRP);

	// Orientation
	LCDWrite(LCD_CMD, LCD_ILIMAC);
	LCDWrite(LCD_DATA, 0xE8);
}

/*
 * Graphics
 */

void LCDSetColor(uint16_t color) {
	color_low_ = color;
	color_high_ = color >> 8;
}

void LCDSetColorBg(uint16_t color) {
	colorbg_low_ = color;
	colorbg_high_ = color >> 8;
}

void LCDSetColorSlider(uint16_t color) {
	colors_low_ = color;
	colors_high_ = color >> 8;
}

void LCDClearScreen(uint16_t color) {
	LCDSetArea(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
	LCDSetColorBg(color);
	uint32_t pixels = LCD_WIDTH * LCD_HEIGHT;
	while (pixels--) {
		LCDWrite(LCD_DATA, colorbg_high_);
		LCDWrite(LCD_DATA, colorbg_low_);
	}
}

void LCDDrawPixel(uint16_t x, uint16_t y) {
	LCDSetArea(x, y, x, y);
	LCDWrite(LCD_DATA, color_high_);
	LCDWrite(LCD_DATA, color_low_);
}

void LCDDrawString(uint16_t x, uint16_t y, uint16_t scale, char *string) {
	while (*string) {
		x += LCDDrawChar(x, y, scale, *string++) + 1;
	}
}

void LCDDrawStringCentered(uint16_t y, uint16_t scale, char *string) {
	char *ptr = string;
	uint16_t count = 0;
	while (*ptr++) count++;
	uint16_t x = (LCD_WIDTH - (5*scale*count)) / 2;
	LCDDrawString(x, y, scale, string);
}

uint16_t LCDDrawChar(uint16_t x, uint16_t y, uint16_t scale, char c) {
	uint16_t col = 0;
	uint16_t row = 0;
	uint16_t bit = 1;
	uint16_t scale_x, scale_y;

	LCDSetArea(x, y, x + (5*scale) - 1, y + (7*scale) - 1);

	for (row = 0; row < 7; row++) {
		for (scale_y = 0; scale_y < scale; scale_y++) {
			for (col = 0; col < 5; col++) {
				for (scale_x = 0; scale_x < scale; scale_x++) {
					if (font_5x7[c - 0x20][col] & bit) {
						//foreground
						LCDWrite(LCD_DATA, color_high_);
						LCDWrite(LCD_DATA, color_low_);
					} else {
						//background
						LCDWrite(LCD_DATA, colorbg_high_);
						LCDWrite(LCD_DATA, colorbg_low_);
					}
				}
			}
		}
		bit <<= 1;
	}

	return (5*scale);
}

void LCDDrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		uint16_t temp;
		temp = x0;
		x0 = y0;
		y0 = temp;
		temp = x1;
		x1 = y1;
		y1 = temp;
	}

	if (x0 > x1) {
		uint16_t temp;
		temp = x0;
		x0 = x1;
		x1 = temp;
		temp = y0;
		y0 = y1;
		y1 = temp;
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			LCDDrawPixel(y0, x0);
		} else {
			LCDDrawPixel(x0, y0);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void LCDDrawFastVLine(int16_t x, int16_t y, int16_t h) {
	LCDSetArea(x, y, x, y+h-1);
	while (h--) {
		LCDWrite(LCD_DATA, color_high_);
		LCDWrite(LCD_DATA, color_low_);
	}
}

void LCDDrawFastHLine(int16_t x, int16_t y, int16_t w) {
	LCDSetArea(x, y, x+w-1, y);
	while (w--) {
		LCDWrite(LCD_DATA, color_high_);
		LCDWrite(LCD_DATA, color_low_);
	}
}

void LCDDrawRectangle(int16_t x, int16_t y, int16_t w, int16_t h) {
	LCDDrawFastHLine(x, y, w);
	LCDDrawFastHLine(x, y+h-1, w);
	LCDDrawFastVLine(x, y, h);
	LCDDrawFastVLine(x+w-1, y, h);
}

void LCDDrawRectangleFilled(int16_t x, int16_t y, int16_t w, int16_t h) {
	LCDDrawRectangle(x, y, w, h);
	LCDSetArea(x+1, y+1, x+w-2, y+h-2);
	int16_t size = (w-2) * (h-2);
	while (size--) {
		LCDWrite(LCD_DATA, colorbg_high_);
		LCDWrite(LCD_DATA, colorbg_low_);
	}
}

void LCDDrawHSlider(int16_t x, int16_t y, int16_t w, int16_t h, float min, float max, float val) {
	LCDDrawRectangleFilled(x, y, w, h);
	float val_pos = (val - min) / (max - min);
	if (val_pos > 1.00) val_pos = 1.00;
	if (val_pos < 0.00) val_pos = 0.00;

	int16_t slider_pos = (int16_t)((float)w * val_pos);
	if (slider_pos < 2) slider_pos = 2;
	if (slider_pos > w-3) slider_pos = w-3;

	LCDSetArea(x+slider_pos-1, y+1, x+slider_pos+1, y+h-1);
	h -= 1;
	h *= 3;
	while (h--) {
		LCDWrite(LCD_DATA, colors_high_);
		LCDWrite(LCD_DATA, colors_low_);
	}
}














