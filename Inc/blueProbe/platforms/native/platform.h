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

/* This file implements the platform specific functions for the STM32
 * implementation.
 */
#ifndef __PLATFORM_H
#define __PLATFORM_H

#include "main.h"

#include "timing.h"
#include "timing_stm32.h"

#include "usart.h"

//#define PLATFORM_HAS_TRACESWO
//#define PLATFORM_HAS_POWER_SWITCH
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define PLATFORM_HAS_DEBUG
#define USBUART_DEBUG
#endif
#define BOARD_IDENT             "Black Magic Probe"
#define BOARD_IDENT_DFU	        "Black Magic Probe (Upgrade)"
#define BOARD_IDENT_UPD	        "Black Magic Probe (DFU Upgrade)"
#define DFU_IDENT               "Black Magic Firmware Upgrade"
#define UPD_IFACE_STRING        "@Internal Flash   /0x08000000/8*001Kg"

/* Important pin mappings for STM32 implementation:
 *
 * LED0 = 	PA4	(Yellow LED : Running)
 * LED1 = 	PA5	(Yellow LED : Idle)
 * LED2 = 	PA6	(Red LED    : Error)
 *
 * TPWR = 	RB0 (input) -- analogue on mini design ADC1, ch8
 * nTRST = 	PB1 (output) [blackmagic]
 * PWR_BR = 	PB1 (output) [blackmagic_mini] -- supply power to the target, active low
 * TMS_DIR =    PA1 (output) [blackmagic_mini v2.1] -- choose direction of the TCK pin, input low, output high
 * SRST_OUT = 	PA2 (output)
 * TDI = 	PA10 (output)
 * TMS = 	PA8 (input/output for SWDIO)
 * TCK = 	PA9 (output SWCLK)
 * TDO = 	PA12 (input)
 * nSRST = 	PA7 (input)
 *
 * USB cable pull-up: PA8
 * USB VBUS detect:  PB13 -- New on mini design.
 *                           Enable pull up for compatibility.
 * Force DFU mode button: PB12
 */

#include "stm32f1xx_ll_gpio.h"

//#define TRACE_TIM TIM3
//#define TRACE_TIM_CLK_EN() rcc_periph_clock_enable(RCC_TIM3)
//#define TRACE_IRQ   NVIC_TIM3_IRQ
//#define TRACE_ISR   tim3_isr

#ifdef ENABLE_DEBUG
extern bool debug_bmp;
int usbuart_debug_write(const char *buf, size_t len);

#define DEBUG printf
#else
#define DEBUG(...)
#endif

#define GDB_UART            huart3

#define LED_UART            LED_0_Pin
#define LED_UART_PORT       LED_0_GPIO_Port
#define LED_IDLE_RUN        LED_1_Pin
#define LED_IDLE_RUN_PORT   LED_1_GPIO_Port
#define LED_ERROR           LED_2_Pin
#define LED_ERROR_PORT      LED_2_GPIO_Port

#define SET_RUN_STATE(state)    {running_status = (state);}
#define SET_IDLE_STATE(state)   {HAL_GPIO_WritePin(LED_IDLE_RUN_PORT, LED_IDLE_RUN, state);}
#define SET_ERROR_STATE(state)  {HAL_GPIO_WritePin(LED_ERROR_PORT, LED_ERROR, state);}


//#define TMS_SET_MODE() do { \                             //Native TMS (use 2 GPIOs)
//    gpio_set(TMS_DIR_PORT, TMS_DIR_PIN); \
//    gpio_set_mode(TMS_PORT, GPIO_MODE_OUTPUT_50_MHZ, \
//                  GPIO_CNF_OUTPUT_PUSHPULL, TMS_PIN); \
//} while(0)

//#define TMS_SET_MODE() \
//    gpio_set_mode(TMS_PORT, GPIO_MODE_OUTPUT_50_MHZ, \
//                  GPIO_CNF_OUTPUT_PUSHPULL, TMS_PIN);


//#define SWDIO_MODE_FLOAT() \
//    gpio_set_mode(SWDIO_PORT, GPIO_MODE_INPUT, \
//                  GPIO_CNF_INPUT_FLOAT, SWDIO_PIN);

#define SWDIO_MODE_FLOAT() \
        LL_GPIO_SetPinMode(SWDIO_GPIO_Port, SWDIO_Pin_LL, LL_GPIO_MODE_FLOATING);

#define SWDIO_MODE_DRIVE() \
        LL_GPIO_SetPinMode(SWDIO_GPIO_Port, SWDIO_Pin_LL, LL_GPIO_MODE_OUTPUT); \
        LL_GPIO_SetPinSpeed(SWDIO_GPIO_Port, SWDIO_Pin_LL, LL_GPIO_SPEED_FREQ_HIGH); \
        LL_GPIO_SetPinOutputType(SWCLK_GPIO_Port, SWCLK_Pin_LL, LL_GPIO_OUTPUT_PUSHPULL);


//#define UART_PIN_SETUP() \
//    gpio_set_mode(USBUSART_PORT, GPIO_MODE_OUTPUT_2_MHZ, \
//                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, USBUSART_TX_PIN);


/* Use newlib provided integer only stdio functions */
#define sscanf siscanf
#define sprintf siprintf
#define snprintf sniprintf
#define vasprintf vasiprintf

#endif
