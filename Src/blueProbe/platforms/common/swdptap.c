/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2011  Black Sphere Technologies Ltd.
 * Written by Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* This file implements the low-level SW-DP interface. */

#include "general.h"
#include "swdptap.h"

int swdptap_init(void)
{
    return 0;
}

static void swdptap_turnaround(uint8_t dir)
{
    static uint8_t olddir = 0;

    /* Don't turnaround if direction not changing */
    if(dir == olddir) return;
    olddir = dir;

#ifdef DEBUG_SWD_BITS
    DEBUG("%s", dir ? "\n-> ":"\n<- ");
#endif

    if(dir)
        SWDIO_MODE_FLOAT();
    LL_GPIO_SetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);
    LL_GPIO_ResetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);
    if(!dir)
        SWDIO_MODE_DRIVE();
}

bool swdptap_bit_in(void)
{
    uint16_t ret;

    swdptap_turnaround(1);

    ret = LL_GPIO_IsInputPinSet(SWDIO_TMS_GPIO_Port, SWDIO_TMS_Pin);
    LL_GPIO_SetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);
    LL_GPIO_ResetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);

#ifdef DEBUG_SWD_BITS
    DEBUG("%d", ret?1:0);
#endif

    return ret != 0;
}

void swdptap_bit_out(bool val)
{
#ifdef DEBUG_SWD_BITS
    DEBUG("%d", val);
#endif

    swdptap_turnaround(0);

    if (val > 0)
        LL_GPIO_SetOutputPin(SWDIO_TMS_GPIO_Port, SWDIO_TMS_Pin);
    else
        LL_GPIO_ResetOutputPin(SWDIO_TMS_GPIO_Port, SWDIO_TMS_Pin);

    LL_GPIO_SetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);
    LL_GPIO_ResetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);
}
