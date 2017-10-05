/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2017  Black Sphere Technologies Ltd.
 * Written by Gordon Smith <gordonhj.smith@gmail.com>
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

#include "stub.h"
#include <stdint.h>

#define FPEC_BASE                   0x40023C00
#define MMIO32(addr)                (*(volatile uint32_t *)(addr))
#define PERIPH_BASE                 (0x40000000U)
#define PERIPH_BASE_AHB1            (PERIPH_BASE + 0x20000)
#define FLASH_MEM_INTERFACE_BASE    (PERIPH_BASE_AHB1 + 0x3C00)
#define FLASH_CR                    MMIO32(FLASH_MEM_INTERFACE_BASE + 0x10)
#define FLASH_CR_PG                 (1 << 0)
#define FLASH_CR_PROGRAM_X8         (0x00 << 8)
#define FLASH_SR                    MMIO32(FLASH_MEM_INTERFACE_BASE + 0x0C)
//#define FLASH_SR_BSY                (1 << 16)
#define FLASH_SR_BSY                (1 << 0)

#define SR_ERROR_MASK 0xF2

void __attribute__((naked))
stm32f4_flash_write_x8_stub(unsigned int *dest, unsigned int *src, unsigned int size)
{
	unsigned char *b_dest, *b_src;
	b_dest = (void *)dest;
	b_src = (void *)src;
	for (int i = 0; i < size; i += 1)
	{
		FLASH_CR = FLASH_CR_PROGRAM_X8 | FLASH_CR_PG;
		*b_dest++ = *b_src++;
		__asm("dsb");
		while (FLASH_SR & FLASH_SR_BSY);
	}

	if (FLASH_SR & SR_ERROR_MASK)
		stub_exit(1);

	stub_exit(0);
}

