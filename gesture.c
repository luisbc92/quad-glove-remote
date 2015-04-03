/*
 * gesture.c
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#include "gesture.h"

void GestureUpdate(ImuFiltered *hand, ImuFiltered *finger, GloveState *glove) {
	// Fist
	static int fist_timer;
	if ((hand->inv == 0 && finger->inv == 1) || (hand->inv == 1 && finger->inv == 0)) {
		if (fist_timer > 25) glove->fist = 1;
		fist_timer++;
	} else {
		glove->fist = 0;
		fist_timer = 0;
	}

	// Inverted
	static int inv_timer;
	if (hand->inv == 1) {
		if (inv_timer > 25) glove->inverted = 1;
		inv_timer++;
	} else {
		glove->inverted = 0;
		inv_timer = 0;
	}

	// Left
	if (hand->x < -GEST_LOW) {
		glove->left = 1;
	} else {
		glove->left = 0;
	}

	// Right
	if (hand->x > GEST_LOW) {
		glove->right = 1;
	} else {
		glove->right = 0;
	}

	// Up
	if (hand->y > GEST_LOW) {
		glove->up = 1;
	} else {
		glove->up = 0;
	}

	// Down
	if (hand->y < -GEST_LOW) {
		glove->down = 1;
	} else {
		glove->down = 0;
	}
}
