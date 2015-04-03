/*
 * lcd.h
 *
 *  Created on: Mar 4, 2014
 *      Author: Luiz
 */

#ifndef LCD_H_
#define LCD_H_

/*
 * Includes
 */
#include <stdint.h>
#include <stdbool.h>

/*
 * Definitions
 */
// LCD Pins
#define LCD_RST_PIN		GPIO_PIN_2
#define LCD_RST_PORT	GPIO_PORTA_BASE
#define LCD_CS_PIN		GPIO_PIN_5
#define LCD_CS_PORT		GPIO_PORTB_BASE
#define LCD_DC_PIN		GPIO_PIN_5
#define LCD_DC_PORT		GPIO_PORTE_BASE
// LCD Size
#define LCD_WIDTH	 	320
#define LCD_HEIGHT	 	240
// LCD Control Constants
#define LCD_CMD			0x00
#define LCD_DATA		0x01
// Driver specific
#define LCD_SWRESET		0x01
#define	LCD_BSTRON		0x03
#define LCD_RDDIDIF		0x04
#define LCD_RDDST		0x09
#define LCD_SLEEPIN     0x10
#define	LCD_SLEEPOUT	0x11
#define	LCD_NORON		0x13
#define	LCD_INVOFF		0x20
#define LCD_INVON      	0x21
#define	LCD_SETCON		0x25
#define LCD_DISPOFF     0x28
#define LCD_DISPON      0x29
#define LCD_CASETP      0x2A
#define LCD_PASETP      0x2B
#define LCD_RAMWRP      0x2C
#define LCD_RGBSET	    0x2D
#define	LCD_MADCTL		0x36
#define LCD_SEP			0x37
#define	LCD_COLMOD		0x3A
#define LCD_DISCTR      0xB9
#define LCD_DOR			0xBA
#define	LCD_EC			0xC0
#define LCD_RDID1		0xDA
#define LCD_RDID2		0xDB
#define LCD_RDID3		0xDC
#define LCD_SETOSC		0xB0
#define LCD_SETPWCTR4	0xB4
#define LCD_SETPWCTR5	0xB5
#define LCD_SETEXTCMD	0xC1
#define LCD_SETGAMMAP	0xC2
#define LCD_SETGAMMAN	0xC3
#define LCD_ILIGS		0x26
#define LCD_ILIMAC		0x36
#define LCD_ILIPFS		0x3A
#define LCD_ILIFCNM		0xB1
#define LCD_ILIFCIM		0xB2
#define LCD_ILIFCPM		0xB3
#define LCD_ILIDFC		0xB6
#define LCD_ILIPC1		0xC0
#define LCD_ILIPC2		0xC1
#define LCD_ILIVC1		0xC5
#define LCD_ILIVC2		0xC7
#define LCD_ILIPGC		0xE0
#define LCD_ILINGC		0xE1
#define LCD_ILIGFD		0xF2
// Graphics
#define FONT_SM			0
#define FONT_MD			1
#define FONT_LG			2
#define FONT_SM_BG		3
#define FONT_MD_BG		4
#define FONT_LG_BG		5

/*
 * Driver Functions
 */
void LCDWrite(uint16_t dc, uint16_t data);
void LCDSetArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCDClear();
void LCDInit();

/*
 * Graphics Functions
 */
void LCDSetColor(uint16_t color);
void LCDSetColorSlider(uint16_t color);
void LCDSetColorBg(uint16_t color);
void LCDClearScreen(uint16_t color);
void LCDDrawPixel(uint16_t x, uint16_t y);
void LCDDrawString(uint16_t x, uint16_t y, uint16_t scale, char *string);
void LCDDrawStringCentered(uint16_t y, uint16_t scale, char *string);
void LCDDrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void LCDDrawFastVLine(int16_t x, int16_t y, int16_t h);
void LCDDrawFastHLine(int16_t x, int16_t y, int16_t w);
void LCDDrawRectangle(int16_t x, int16_t y, int16_t w, int16_t h);
void LCDDrawRectangleFilled(int16_t x, int16_t y, int16_t w, int16_t h);
void LCDDrawHSlider(int16_t x, int16_t y, int16_t w, int16_t h, float min, float max, float val);
uint16_t LCDDrawChar(uint16_t x, uint16_t y, uint16_t scale, char c);


#endif /* LCD_H_ */
