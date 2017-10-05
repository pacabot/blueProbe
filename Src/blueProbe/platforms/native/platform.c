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

#include "general.h"
#include "morse.h"
#include "adc.h"
#include "gdb_if.h"

static void bluetoothInit(int baudrate);

/* Pins PB[7:5] are used to detect hardware revision.
 * 000 - Original production build.
 * 001 - Mini production build.
 * 010 - Mini V2.0e and later.
 */
int platform_hwversion(void)
{
    return 2;
}

void platform_init(void)
{
#ifdef ENABLE_DEBUG
    void initialise_monitor_handles(void);
    initialise_monitor_handles();
#endif

    DEBUG("Start BlueProbe\n");

    platform_srst_set_val(false);
    gdb_if_init();
    //    bluetoothInit(921600);
}

void platform_srst_set_val(bool assert)
{
    LL_GPIO_SetOutputPin(SWDIO_TMS_GPIO_Port, SWDIO_TMS_Pin);

    if (assert)
    {
        LL_GPIO_ResetOutputPin(SRST_GPIO_Port, SRST_Pin);
        for(int i = 0; i < 10000; i++) asm("nop");
    }
    else
    {
        LL_GPIO_SetOutputPin(SRST_GPIO_Port, SRST_Pin); //todo check hard reset function
    }
}

bool platform_srst_get_val(void)
{
    return 0; //HAL_GPIO_ReadPin(SRST_SENSE_GPIO_Port, SRST_SENSE_Pin);
}

bool platform_target_get_power(void)
{
    return !LL_GPIO_IsInputPinSet(TARGET_PWR_GPIO_Port, TARGET_PWR_Pin);
}

void platform_target_set_power(bool power)
{
    if (!power)
        LL_GPIO_SetOutputPin(TARGET_PWR_GPIO_Port, TARGET_PWR_Pin);
    else
        LL_GPIO_ResetOutputPin(TARGET_PWR_GPIO_Port, TARGET_PWR_Pin);
}

const char *platform_target_voltage(void)
{
    static char ret[] = "0.0V";
    const uint8_t channel = 8;
    HAL_ADC_PollForConversion(&hadc1, 1);

    HAL_ADC_Start(&hadc1);

    while (!HAL_ADC_STATE_REG_EOC);

    uint32_t val = HAL_ADC_GetValue(&hadc1) * 99; /* 0-4095 */
    ret[0] = '0' + val / 81910;
    ret[2] = '0' + (val / 8191) % 10;

    return ret;
}

void platform_request_boot(void)
{
}

char *bluetoothCmd(const char *cmd)
{
    HAL_StatusTypeDef rv;
    static char response[255];
    int i = 0;

    memset(response, 0, sizeof(response));

    gdb_if_putstr(cmd);

    while (((response[i++] = gdb_if_getchar_to(2000)) != '\n') && (i < sizeof(response)));     // Wait until end of reception

    DEBUG("%s \n", response);

    return response;
}

void bluetoothInit(int baudrate)
{
    char cmd[40];

    //    LL_GPIO_ResetOutputPin(BT_PWR_GPIO_Port, BT_PWR_Pin);
    LL_GPIO_SetOutputPin(BT_PWR_GPIO_Port, BT_PWR_Pin);
    HAL_Delay(100);

    //    bluetoothCmd("AT+AB Bypass\n\r");
    bluetoothCmd("AT+AB Config RmtEscapeSequence = false\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB Config ATReply = AT-AB\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB Config StreamingSerial = False\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB Config QoS_Latency = 3\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB Config UartTimeout = 8\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB Config CpuMHz = 64\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB Config COD = 10050C\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB Config HciBaudrate = 2000000\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    bluetoothCmd("AT+AB DefaultLocalName blueProbe\n\r");
    bluetoothCmd("AT+AB Reset\n\r");

    sprintf(cmd, "AT+AB ChangeDefaultBaud %d\n\r", baudrate);
    bluetoothCmd("AT+AB ChangeDefaultBaud 921600\n\r");
    bluetoothCmd("AT+AB Reset\n\r");
}

#ifdef ENABLE_DEBUG
enum {
    RDI_SYS_OPEN = 0x01,
    RDI_SYS_WRITE = 0x05,
    RDI_SYS_ISTTY = 0x09,
};

int rdi_write(int fn, const char *buf, size_t len)
{
    (void)fn;
    if (debug_bmp)
        return len - usbuart_debug_write(buf, len);

    return 0;
}

struct ex_frame {
    union {
        int syscall;
        int retval;
    };
    const int *params;
    uint32_t r2, r3, r12, lr, pc;
};

void debug_monitor_handler_c(struct ex_frame *sp)
{
    /* Return to after breakpoint instruction */
    sp->pc += 2;

    switch (sp->syscall)
    {
        case RDI_SYS_OPEN:
            sp->retval = 1;
            break;
        case RDI_SYS_WRITE:
            sp->retval = rdi_write(sp->params[0], (void*)sp->params[1], sp->params[2]);
            break;
        case RDI_SYS_ISTTY:
            sp->retval = 1;
            break;
        default:
            sp->retval = -1;
    }

}

asm(".globl debug_monitor_handler\n"
        ".thumb_func\n"
        "debug_monitor_handler: \n"
        "    mov r0, sp\n"
        "    b debug_monitor_handler_c\n");

#endif
