/*
 * linmath.c
 *
 *  Created on: Apr 17, 2017
 *      Author: dizcza
 */


#include "linmath.h"

void math_sinf_cosf(float *sf, float *cf, float theta_rads) {
    *sf = sinf(theta_rads);
    *cf = cosf(theta_rads);
}
