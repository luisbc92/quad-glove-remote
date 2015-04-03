/*
 * gesture.h
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_GESTURE_H_
#define QUADGLOVEREMOTE_GESTURE_H_

#include "typedefs.h"
#include "config.h"

void GestureUpdate(ImuFiltered *hand, ImuFiltered *finger, GloveState *glove);

#endif /* QUADGLOVEREMOTE_GESTURE_H_ */
