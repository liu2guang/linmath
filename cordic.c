/*
 * cordic.c
 *
 *  Created on: Apr 17, 2017
 *      Author: dizcza
 */

#include "linmath.h"
#include "stdint.h"

#define cordic_1K    0x26DD3B6A
#define half_pi      0x6487ED51
#define MUL          1073741824.0f
#define CORDIC_NTAB  16

int32_t cordic_ctab [] = {
    0x3243F6A8, 0x1DAC6705, 0x0FADBAFC, 0x07F56EA6, 0x03FEAB76, 0x01FFD55B,
    0x00FFFAAA, 0x007FFF55, 0x003FFFEA, 0x001FFFFD, 0x000FFFFF, 0x0007FFFF, 0x0003FFFF,
    0x0001FFFF, 0x0000FFFF, 0x00007FFF, 0x00003FFF, 0x00001FFF, 0x00000FFF, 0x000007FF,
    0x000003FF, 0x000001FF, 0x000000FF, 0x0000007F, 0x0000003F, 0x0000001F, 0x0000000F,
    0x00000008, 0x00000004, 0x00000002, 0x00000001, 0x00000000,
};

void cordic_sinf_cosf(float *sf, float *cf, float theta_rads)
{
    int32_t k, d, tx, ty, tz;
    int32_t x = cordic_1K, y = 0, z = (int32_t)(theta_rads * MUL);
    for (k = 0; k < CORDIC_NTAB; ++k)
    {
        d = z >> 31;
        //get sign. for other architectures, you might want to use the more portable version
        //d = z>=0 ? 0 : -1;
        tx = x - (((y >> k) ^ d) - d);
        ty = y + (((x >> k) ^ d) - d);
        tz = z - ((cordic_ctab[k] ^ d) - d);
        x = tx;
        y = ty;
        z = tz;
    }
    *cf = x / MUL;
    *sf = y / MUL;
}
