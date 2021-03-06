/*
 * color.h
 *
 *  Created on: Mar 5, 2014
 *      Author: Luiz
 */

#ifndef COLOR_H_
#define COLOR_H_

#define COLOR_NO			0x0001
#define COLOR_BLACK   		0x0000
#define COLOR_BLUE    		0x001F
#define COLOR_RED     		0xF800
#define COLOR_GREEN  		0x07E0
#define COLOR_CYAN    		0x07FF
#define COLOR_MAGENTA 		0xF81F
#define COLOR_YELLOW  		0xFFE0
#define COLOR_WHITE   		0xFFFF
#define COLOR_ORANGE		0xFD20
#define COLOR_ORANGE_RED	0xFA20
#define COLOR_DARK_ORANGE	0xFC60
#define COLOR_GRAY			0xBDF7
#define COLOR_NAVY			0x0010
#define COLOR_ROYAL_BLUE	0x435C
#define COLOR_SKY_BLUE		0x867D
#define COLOR_TURQUOISE		0x471A
#define COLOR_STEEL_BLUE	0x4416
#define COLOR_LIGHT_BLUE	0xAEDC
#define COLOR_AQUAMARINE	0x7FFA
#define COLOR_DARK_GREEN	0x0320
#define COLOR_DARK_OLIVE_GREEN	0x5345
#define COLOR_SEA_GREEN		0x2C4A
#define COLOR_SPRING_GREEN	0x07EF
#define COLOR_PALE_GREEN	0x9FD3
#define COLOR_GREEN_YELLOW	0xAFE5
#define COLOR_LIME_GREEN	0x3666
#define COLOR_FOREST_GREEN	0x2444
#define COLOR_KHAKI			0xF731
#define COLOR_GOLD			0xFEA0
#define COLOR_GOLDENROD		0xDD24
#define COLOR_SIENNA		0xA285
#define COLOR_BEIGE			0xF7BB
#define COLOR_TAN			0xD5B1
#define COLOR_BROWN			0xA145
#define COLOR_CHOCOLATE		0xD343
#define COLOR_FIREBRICK		0xB104
#define COLOR_HOT_PINK		0xFB56
#define COLOR_PINK			0xFE19
#define COLOR_DEEP			0xF8B2
#define COLOR_VIOLET		0xEC1D
#define COLOR_DARK_VIOLET	0x901A
#define COLOR_PURPLE		0xA11E
#define COLOR_MEDIUM_PURPLE	0x939B

const unsigned int color[] = { COLOR_BLACK, COLOR_WHITE, COLOR_YELLOW,
		COLOR_RED, COLOR_MAGENTA, COLOR_BLUE, COLOR_CYAN,
		COLOR_GREEN, COLOR_ORANGE, COLOR_ORANGE_RED,
		COLOR_DARK_ORANGE, COLOR_GRAY, COLOR_NAVY, COLOR_ROYAL_BLUE,
		COLOR_SKY_BLUE, COLOR_TURQUOISE, COLOR_STEEL_BLUE,
		COLOR_LIGHT_BLUE, COLOR_AQUAMARINE, COLOR_DARK_GREEN,
		COLOR_DARK_OLIVE_GREEN, COLOR_SEA_GREEN, COLOR_SPRING_GREEN,
		COLOR_PALE_GREEN, COLOR_GREEN_YELLOW, COLOR_LIME_GREEN,
		COLOR_FOREST_GREEN, COLOR_KHAKI, COLOR_GOLD,
		COLOR_GOLDENROD, COLOR_SIENNA, COLOR_BEIGE, COLOR_TAN,
		COLOR_BROWN, COLOR_CHOCOLATE, COLOR_FIREBRICK,
		COLOR_HOT_PINK, COLOR_PINK, COLOR_DEEP, COLOR_VIOLET,
		COLOR_DARK_VIOLET, COLOR_PURPLE, COLOR_MEDIUM_PURPLE, 0 }; //43

#endif /* COLOR_H_ */
