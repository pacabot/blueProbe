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

/* This file implements the low-level JTAG TAP interface.  */

#include <stdio.h>

#include "general.h"
#include "jtagtap.h"
#include "gdb_packet.h"

int jtagtap_init(void)
{
    TMS_SET_MODE();

	/* Go to JTAG mode for SWJ-DP */
	for(int i = 0; i <= 50; i++) jtagtap_next(1, 0); /* Reset SW-DP */
	jtagtap_tms_seq(0xE73C, 16);		/* SWD to JTAG sequence */
	jtagtap_soft_reset();

	return 0;
}

void jtagtap_reset(void)
{
#ifdef TRST_PORT
	if (platform_hwversion() == 0) {
		volatile int i;
		gpio_clear(TRST_PORT, TRST_PIN);
		for(i = 0; i < 10000; i++) asm("nop");
		gpio_set(TRST_PORT, TRST_PIN);
	}
#endif
	jtagtap_soft_reset();
}

inline uint8_t jtagtap_next(uint8_t dTMS, uint8_t dTDI)
{
	uint16_t ret;

	if (dTMS == 0)
	    LL_GPIO_ResetOutputPin(SWDIO_TMS_GPIO_Port, SWDIO_TMS_Pin);
	else
	    LL_GPIO_SetOutputPin(SWDIO_TMS_GPIO_Port, SWDIO_TMS_Pin);
    if (dTDI == 0)
        LL_GPIO_ResetOutputPin(TDI_GPIO_Port, TDI_Pin);
    else
        LL_GPIO_SetOutputPin(TDI_GPIO_Port, TDI_Pin);
    LL_GPIO_SetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);
    ret = LL_GPIO_IsInputPinSet(TDO_GPIO_Port, TDO_Pin);
    LL_GPIO_ResetOutputPin(SWCLK_TCK_GPIO_Port, SWCLK_TCK_Pin);

	DEBUG("jtagtap_next(TMS = %d, TDI = %d) = %d\n", dTMS, dTDI, ret);

	return ret != 0;
}

