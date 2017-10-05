/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_dma.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define TARGET_VOLTAGE_Pin LL_GPIO_PIN_0
#define TARGET_VOLTAGE_GPIO_Port GPIOA
#define SWDIO_TMS_Pin LL_GPIO_PIN_1
#define SWDIO_TMS_GPIO_Port GPIOA
#define UART_TX_STLINK_Pin LL_GPIO_PIN_2
#define UART_TX_STLINK_GPIO_Port GPIOA
#define SWCLK_TCK_Pin LL_GPIO_PIN_3
#define SWCLK_TCK_GPIO_Port GPIOA
#define LED_1_Pin LL_GPIO_PIN_4
#define LED_1_GPIO_Port GPIOA
#define LED_0_Pin LL_GPIO_PIN_5
#define LED_0_GPIO_Port GPIOA
#define LED_2_Pin LL_GPIO_PIN_6
#define LED_2_GPIO_Port GPIOA
#define GPIO7_BT_Pin LL_GPIO_PIN_7
#define GPIO7_BT_GPIO_Port GPIOA
#define BT_PWR_Pin LL_GPIO_PIN_0
#define BT_PWR_GPIO_Port GPIOB
#define SWO_Pin LL_GPIO_PIN_1
#define SWO_GPIO_Port GPIOB
#define UART_TX_BT_Pin LL_GPIO_PIN_9
#define UART_TX_BT_GPIO_Port GPIOA
#define UART_RX_BT_Pin LL_GPIO_PIN_10
#define UART_RX_BT_GPIO_Port GPIOA
#define UART_CTS_BT_Pin LL_GPIO_PIN_11
#define UART_CTS_BT_GPIO_Port GPIOA
#define UART_RTS_BT_Pin LL_GPIO_PIN_12
#define UART_RTS_BT_GPIO_Port GPIOA
#define UART_RX_STLINK_Pin LL_GPIO_PIN_15
#define UART_RX_STLINK_GPIO_Port GPIOA
#define SRST_Pin LL_GPIO_PIN_4
#define SRST_GPIO_Port GPIOB
#define TARGET_PWR_Pin LL_GPIO_PIN_5
#define TARGET_PWR_GPIO_Port GPIOB
#define TDO_Pin LL_GPIO_PIN_6
#define TDO_GPIO_Port GPIOB
#define TDI_Pin LL_GPIO_PIN_7
#define TDI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
