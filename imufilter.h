/*
 * imufilter.h
 *
 *  Created on: Oct 19, 2014
 *      Author: Luiz
 */

#ifndef QUADGLOVEREMOTE_IMUFILTER_H_
#define QUADGLOVEREMOTE_IMUFILTER_H_

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "typedefs.h"
#include "config.h"

#define PI 					3.14159265359

void ImuFilter(ImuRaw *raw, ImuFiltered *filtered);


#endif /* QUADGLOVEREMOTE_IMUFILTER_H_ */
