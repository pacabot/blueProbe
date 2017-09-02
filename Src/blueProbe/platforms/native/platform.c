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

static void adc_init(void);
static void setup_vbus_irq(void);
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

    DEBUG("PLF\n");

    /* Setup GPIO ports */
    //    gpio_clear(USB_PU_PORT, USB_PU_PIN);
    //    gpio_set_mode(USB_PU_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
    //            USB_PU_PIN);

    //    gpio_set_mode(JTAG_PORT, GPIO_MODE_OUTPUT_50_MHZ,
    //            GPIO_CNF_OUTPUT_PUSHPULL,
    //            TMS_DIR_PIN | TMS_PIN | TCK_PIN | TDI_PIN);

    /* This needs some fixing... */
    /* Toggle required to sort out line drivers... */
    //    gpio_port_write(GPIOA, 0x8102);
    //    gpio_port_write(GPIOB, 0x2000);
    //
    //    gpio_port_write(GPIOA, 0x8182);
    //    gpio_port_write(GPIOB, 0x2002);
    //
    //    gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_2_MHZ,
    //            GPIO_CNF_OUTPUT_PUSHPULL,
    //            LED_UART | LED_IDLE_RUN | LED_ERROR);

    /* FIXME: This pin in intended to be input, but the TXS0108 fails
     * to release the device from reset if this floats. */
    //    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ,
    //            GPIO_CNF_OUTPUT_PUSHPULL, GPIO7);
    /* Enable SRST output. Original uses a NPN to pull down, so setting the
     * output HIGH asserts. Mini is directly connected so use open drain output
     * and set LOW to assert.
     */
    platform_srst_set_val(false);
    //    gpio_set_mode(SRST_PORT, GPIO_MODE_OUTPUT_50_MHZ,
    //            (((platform_hwversion() == 0) ||
    //              (platform_hwversion() >= 3))
    //             ? GPIO_CNF_OUTPUT_PUSHPULL
    //             : GPIO_CNF_OUTPUT_OPENDRAIN),
    //            SRST_PIN);

    /* Enable internal pull-up on PWR_BR so that we don't drive
       TPWR locally or inadvertently supply power to the target. */
    //    if (platform_hwversion () == 1) {
    //        gpio_set(PWR_BR_PORT, PWR_BR_PIN);
    //        gpio_set_mode(PWR_BR_PORT, GPIO_MODE_INPUT,
    //                      GPIO_CNF_INPUT_PULL_UPDOWN, PWR_BR_PIN);
    //    } else if (platform_hwversion() > 1) {
    //        gpio_set(PWR_BR_PORT, PWR_BR_PIN);
    //        gpio_set_mode(PWR_BR_PORT, GPIO_MODE_OUTPUT_50_MHZ,
    //                      GPIO_CNF_OUTPUT_OPENDRAIN, PWR_BR_PIN);
    //    }
    //
    //    if (platform_hwversion() > 0) {
    //        adc_init();
    //    } else {
    //        gpio_clear(GPIOB, GPIO0);
    //        gpio_set_mode(GPIOB, GPIO_MODE_INPUT,
    //                GPIO_CNF_INPUT_PULL_UPDOWN, GPIO0);
    //    }
    /* Relocate interrupt vector table here */
    //    extern int vector_table;
    //    SCB_VTOR = (uint32_t)&vector_table;

    //cdcacm_init();

    /* On mini hardware, UART and SWD share connector pins.
     * Don't enable UART if we're being debugged. */
    //    if ((platform_hwversion() == 0) || !(SCS_DEMCR & SCS_DEMCR_TRCENA))
    //        usbuart_init();

    //    setup_vbus_irq();

    bluetoothInit(460800);
    printf("Start BlueProbe \n");
}

void platform_srst_set_val(bool assert)
{
    //    gpio_set_val(TMS_PORT, TMS_PIN, 1);
    //    if ((platform_hwversion() == 0) ||
    //        (platform_hwversion() >= 3)) {
    //        gpio_set_val(SRST_PORT, SRST_PIN, assert);
    //    } else {
    //        gpio_set_val(SRST_PORT, SRST_PIN, !assert);
    //    }
    //    if (assert) {
    //        for(int i = 0; i < 10000; i++) asm("nop");
    //    }
    HAL_GPIO_WritePin(SWDIO_GPIO_Port, SWDIO_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SRST_GPIO_Port, SRST_Pin, !assert);
    if (assert)
    {
        for(int i = 0; i < 10000; i++) asm("nop");
    }
}

bool platform_srst_get_val(void)
{
    //    if (platform_hwversion() == 0) {
    //        return gpio_get(SRST_SENSE_PORT, SRST_SENSE_PIN) == 0;
    //    } else if (platform_hwversion() >= 3) {
    //        return gpio_get(SRST_SENSE_PORT, SRST_SENSE_PIN) != 0;
    //    } else {
    //        return gpio_get(SRST_PORT, SRST_PIN) == 0;
    //    }
    return HAL_GPIO_ReadPin(SRST_SENSE_GPIO_Port, SRST_SENSE_Pin);
}

bool platform_target_get_power(void)
{
    //    if (platform_hwversion() > 0) {
    //        return !gpio_get(PWR_BR_PORT, PWR_BR_PIN);
    //    }
    return !HAL_GPIO_ReadPin(PWR_BR_GPIO_Port, PWR_BR_Pin);
}

void platform_target_set_power(bool power)
{
    //    if (platform_hwversion() > 0) {
    //        gpio_set_val(PWR_BR_PORT, PWR_BR_PIN, !power);
    //    }
    HAL_GPIO_WritePin(PWR_BR_GPIO_Port, PWR_BR_Pin, !power);
}

const char *platform_target_voltage(void)
{
    //    if (platform_hwversion() == 0)
    //        return gpio_get(GPIOB, GPIO0) ? "OK" : "ABSENT!";

    static char ret[] = "0.0V";
    const uint8_t channel = 8;
    //    adc_set_regular_sequence(ADC1, 1, (uint8_t*)&channel);
    HAL_ADC_PollForConversion(&hadc1  , 1);

    //    adc_start_conversion_direct(ADC1);
    HAL_ADC_Start(&hadc1);

    /* Wait for end of conversion. */
    //    while (!adc_eoc(ADC1));
    while (!HAL_ADC_STATE_REG_EOC);

    //    uint32_t val = adc_read_regular(ADC1) * 99; /* 0-4095 */
    uint32_t val = HAL_ADC_GetValue(&hadc1) * 99; /* 0-4095 */
    ret[0] = '0' + val / 81910;
    ret[2] = '0' + (val / 8191) % 10;

    return ret;
}

void platform_request_boot(void)
{
    //    /* Disconnect USB cable */
    //    gpio_set_mode(USB_PU_PORT, GPIO_MODE_INPUT, 0, USB_PU_PIN);
    //
    //    /* Drive boot request pin */
    //    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
    //            GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
    //    gpio_clear(GPIOB, GPIO12);
}

char *bluetoothCmd(const char *cmd)
{
    HAL_StatusTypeDef rv;
    static char response[255];
    char command[50];
    char *p_response = response;

    memset(response, 0, sizeof(response));

    strcpy(command, cmd);
    strcat(command, "\r\n");

    HAL_UART_Transmit(&GDB_UART, (uint8_t *)command, strlen(command), 1000);

    // Wait until end of reception
    do
    {
        rv = HAL_UART_Receive(&GDB_UART, (uint8_t *)p_response++, 1, 200);
    }
    while (rv != HAL_TIMEOUT);

    // Put a NULL character at the end of the response string
    *p_response = '\0';

    return response;
}

void bluetoothInit(int baudrate)
{
    char cmd[40];

    // Allow Remote Escape Sequence
    bluetoothCmd("AT+AB Config RmtEscapeSequence = true");

    // Reset the bluetooth peripheral
    bluetoothCmd("AT+AB Reset");

    // Send command to Bluetooth module
    sprintf(cmd, "AT+AB ChangeBaud %i", baudrate);
    bluetoothCmd(cmd);

    // Set baudrate of CPU USART
    __HAL_UART_DISABLE(&GDB_UART);

    GDB_UART.Init.BaudRate = baudrate;
    if (HAL_UART_Init(&GDB_UART) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_UART_ENABLE(&GDB_UART);
}

void exti15_10_isr(void)
{
    //    if (gpio_get(USB_VBUS_PORT, USB_VBUS_PIN)) {
    //        /* Drive pull-up high if VBUS connected */
    //        gpio_set_mode(USB_PU_PORT, GPIO_MODE_OUTPUT_10_MHZ,
    //                GPIO_CNF_OUTPUT_PUSHPULL, USB_PU_PIN);
    //    } else {
    //        /* Allow pull-up to float if VBUS disconnected */
    //        gpio_set_mode(USB_PU_PORT, GPIO_MODE_INPUT,
    //                GPIO_CNF_INPUT_FLOAT, USB_PU_PIN);
    //    }
    //
    //    exti_reset_request(USB_VBUS_PIN);
}

static void setup_vbus_irq(void)
{
    //    nvic_set_priority(USB_VBUS_IRQ, IRQ_PRI_USB_VBUS);
    //    nvic_enable_irq(USB_VBUS_IRQ);
    //
    //    gpio_set(USB_VBUS_PORT, USB_VBUS_PIN);
    //    gpio_set(USB_PU_PORT, USB_PU_PIN);
    //
    //    gpio_set_mode(USB_VBUS_PORT, GPIO_MODE_INPUT,
    //            GPIO_CNF_INPUT_PULL_UPDOWN, USB_VBUS_PIN);
    //
    //    /* Configure EXTI for USB VBUS monitor */
    //    exti_select_source(USB_VBUS_PIN, USB_VBUS_PORT);
    //    exti_set_trigger(USB_VBUS_PIN, EXTI_TRIGGER_BOTH);
    //    exti_enable_request(USB_VBUS_PIN);
    //
    //    exti15_10_isr();
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

    switch (sp->syscall) {
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
