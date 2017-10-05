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

#ifndef __GDB_IF_H
#define __GDB_IF_H

/* Configuration **************************************************************/
#define DMA_TX_BUF_SIZE     64      /* DMA circular buffer size in bytes */
#define DMA_RX_BUF_SIZE     512     /* DMA circular buffer size in bytes */
#define DMA_TIMEOUT_MS      10      /* DMA Timeout duration in msec */
#define BUFF_OUT_SIZE       (DMA_BUF_SIZE * 16)
/******************************************************************************/

/* Type definitions ----------------------------------------------------------*/
typedef struct
{
    volatile uint8_t  flag;     /* Timeout event flag */
    uint16_t timer;             /* Timeout duration in msec */
    uint16_t prevCNDTR;         /* Holds previous value of DMA_CNDTR */
} DMA_Event_t;

void gdb_if_init(void);
unsigned char gdb_if_getchar(void);
unsigned char gdb_if_getchar_to(int timeout);
void gdb_if_putchar(unsigned char c, int flush);
void gdb_if_putstr(const char* str);

#endif

