/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


typedef struct
{
   uint16_t wData_0; //0
   uint16_t wData_2; //2

} Struct_20000024;

typedef struct
{
   char* Data_0; //0
   uint16_t wData_4; //4
   uint16_t wData_6; //6

} Struct_2000002c_Inner8;


typedef struct
{
   int Data_0; //0
   int Data_4; //4
   Struct_2000002c_Inner8* Data_8; //8;
   uint8_t bData_12; //12

} Struct_2000002c;

typedef void (*Func_20000000)(uint16_t, uint16_t, int, uint16_t);


extern Func_20000000 Funcs_20000000[]; //0x20000000
extern Struct_2000002c Data_2000002c; //2000002c
extern Struct_2000002c_Inner8 Data_2000003c; //2000003c
extern Struct_2000002c_Inner8 Data_2000004c; //2000004c
extern uint32_t SystemCoreClock; //20000058
extern uint32_t uwTickPrio; //2000005C
extern HAL_TickFreqTypeDef uwTickFreq; //20000060

extern SPI_HandleTypeDef hspi2; //200022ac
extern I2C_HandleTypeDef hi2c2; //20002304
extern TIM_HandleTypeDef htim5; //20002358
extern SRAM_HandleTypeDef hsram1; //20002398
extern RTC_HandleTypeDef hrtc; //200023e4
extern TIM_HandleTypeDef htim6; //200023f8
extern UART_HandleTypeDef huart2; //20002438

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void sub_8004be8(uint16_t, uint16_t, int, uint16_t);
void sub_8004c4c(uint16_t, uint16_t, int, uint16_t);
void sub_8004cb0(uint16_t, uint16_t, int, uint16_t);
void sub_8004d14(uint16_t, uint16_t, int, uint16_t);
void sub_8004d78(uint16_t, uint16_t, int, uint16_t);
void sub_8004e74(uint16_t, uint16_t, int, uint16_t);
void sub_8004f24(uint16_t, uint16_t, int, uint16_t);
void sub_8004fc4(uint16_t, uint16_t, int, uint16_t);
void sub_8005074(uint16_t, uint16_t, int, uint16_t);
void sub_8005198(uint16_t a, uint16_t b, uint16_t c, uint8_t d);
void sub_80060ac(Struct_2000002c_Inner8* a);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Display_Backlight_Pin GPIO_PIN_5
#define Display_Backlight_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
