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

static unsigned int read_idx = DMA_RX_BUF_SIZE;
static unsigned int write_idx = 0;
volatile static uint8_t dma_rx_buf[DMA_RX_BUF_SIZE]  = {'\0'};   /* Circular buffer for DMA */
volatile static uint8_t dma_tx_buf[DMA_TX_BUF_SIZE]   = {'\0'};

__IO ITStatus UartReady = RESET;

void gdb_if_init(void)
{
    /* Start DMA */
    if(HAL_UART_Receive_DMA(&GDB_UART, (uint8_t*)dma_rx_buf, sizeof(dma_rx_buf)) != HAL_OK)
    {
        Error_Handler();
    }

    /* Disable Half Transfer Interrupt */
    __HAL_DMA_DISABLE_IT(GDB_UART.hdmarx, DMA_IT_HT);
}

void gdb_if_putstr(const char *str)
{
    if (HAL_UART_Transmit_DMA(&GDB_UART, (uint8_t*)str, strlen(str)) != HAL_OK)
    {
        /* Transfer error in transmission process */
        Error_Handler();
    }

    /* Wait for the end of the transfer ###################################*/
    while (UartReady != SET);
    /* Reset transmission flag */
    UartReady = RESET;
}

void gdb_if_putchar(unsigned char c, int flush)
{
    dma_tx_buf[write_idx++] = c;
    if(flush || (write_idx == DMA_TX_BUF_SIZE))
    {
        if (HAL_UART_Transmit_DMA(&GDB_UART, (uint8_t*)dma_tx_buf, write_idx) != HAL_OK)
        {
            /* Transfer error in transmission process */
            Error_Handler();
        }

        /* Wait for the end of the transfer ###################################*/
        while (UartReady != SET);
        /* Reset transmission flag */
        UartReady = RESET;

        write_idx = 0;
    }
}

unsigned char gdb_if_getchar(void)
{
    unsigned char c = '\0';

    while ((read_idx == __HAL_DMA_GET_COUNTER(GDB_UART.hdmarx)) || (__HAL_DMA_GET_COUNTER(GDB_UART.hdmarx) == 0));

    c = dma_rx_buf[DMA_RX_BUF_SIZE - read_idx];
    dma_rx_buf[DMA_RX_BUF_SIZE - read_idx] = '\0';

    read_idx--;

    if (read_idx == 0)
        read_idx = (DMA_RX_BUF_SIZE);

    return c;
}

unsigned char gdb_if_getchar_to(int timeout)
{
    platform_timeout t;
    platform_timeout_set(&t, timeout);

    while ((!platform_timeout_is_expired(&t)) && (read_idx == __HAL_DMA_GET_COUNTER(GDB_UART.hdmarx)));

    if (read_idx > __HAL_DMA_GET_COUNTER(GDB_UART.hdmarx))
        return gdb_if_getchar();

    return -1;
}

/**
 * @brief  Tx Transfer completed callback
 * @param  UartHandle: UART handle.
 * @note   This example shows a simple way to report end of DMA Tx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if (UartHandle == &GDB_UART)
    {
        /* Set transmission flag: trasfer complete*/
        UartReady = SET;
    }
}

/**
 * @brief  UART error callbacks
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report transfer error, and you can
 *         add your own implementation.
 * @retval None
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
    if (UartHandle == &GDB_UART)
    {
        Error_Handler();
    }
    else
    {
        Error_Handler();
    }
}
