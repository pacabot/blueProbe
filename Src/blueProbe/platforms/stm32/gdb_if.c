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

/* This file implements a transparent channel over which the GDB Remote
 * Serial Debugging protocol is implemented.  This implementation for STM32
 * uses the UART.
 */
#include "usart.h"
#include "general.h"
#include "gdb_if.h"


void gdb_if_putchar(unsigned char c, int flush)
{
    if(HAL_UART_Transmit(&GDB_UART, (uint8_t*)&c, 1, 10)!= HAL_OK)
    {
      Error_Handler();
    }
}

unsigned char gdb_if_getchar(void)
{
    unsigned char c = 0;
    HAL_UART_Receive(&GDB_UART , (uint8_t *)&c, 1, 10);
	return c;
}

unsigned char gdb_if_getchar_to(int timeout)
{
    return gdb_if_getchar();
}

