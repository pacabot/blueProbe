/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2015  Black Sphere Technologies Ltd.
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

#include "stub.h"
#include <stdint.h>

#define MMIO32(addr)                (*(volatile uint32_t *)(addr))
#define PERIPH_BASE                 (0x40000000U)
#define PERIPH_BASE_AHB             (PERIPH_BASE + 0x18000)
#define FLASH_MEM_INTERFACE_BASE    (PERIPH_BASE_AHB + 0x0a000)
#define FLASH_CR                    MMIO32(FLASH_MEM_INTERFACE_BASE + 0x10)
#define FLASH_CR_PG                 (1 << 0)
#define FLASH_SR                    MMIO32(FLASH_MEM_INTERFACE_BASE + 0x0C)
#define FLASH_SR_BSY                (1 << 0)

#define SR_ERROR_MASK 0x14

void __attribute__((naked))
stm32f1_flash_write_stub(unsigned int *dest, unsigned int *src, unsigned int size)
{
	for (int i = 0; i < size; i += 2) {
		FLASH_CR = FLASH_CR_PG;
		*dest++ = *src++;
		while (FLASH_SR & FLASH_SR_BSY)
			;
	}

	if (FLASH_SR & SR_ERROR_MASK)
		stub_exit(1);

	stub_exit(0);
}

