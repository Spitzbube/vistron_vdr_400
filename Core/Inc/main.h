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
   uint16_t width; //0
   uint16_t height; //2

} Struct_20000024;

typedef struct
{
   uint8_t* Data_0; //0
   uint16_t width; //4
   uint16_t height; //6

} Struct_2000002c_Inner8;


typedef struct
{
   int Data_0; //0
   int Data_4; //4
   Struct_2000002c_Inner8* pFont; //8;
   uint8_t bData_12; //12

} Struct_2000002c;

typedef struct
{
   uint16_t x; //0
   uint16_t y; //2

} Struct_200000e4;

typedef struct
{
   int a;
   int b;

} struct_8008d84_Inner8;

typedef struct
{
   uint32_t service_id; //0
   uint32_t component_id; //4
   struct_8008d84_Inner8 Data_8; //8
   int fill_16[2]; //16
   uint16_t wData_24; //24
   //28
} struct_8008d84;

typedef struct
{
	uint16_t a;
	uint16_t b;
} Struct_20000a4c;

typedef struct
{
	int b0: 1;
	uint8_t b1: 1;
	uint8_t b2: 1;
	int a: 5;
	uint8_t b: 6;
} Struct_20000a50;

typedef struct
{
	uint8_t bData_0; //0
	uint16_t wData_2; //2
	uint16_t wData_4; //4

} Struct_20000bc0;


typedef void (*Func_20000000)(uint16_t, uint16_t, int, uint16_t);


extern Func_20000000 Funcs_20000000[]; //0x20000000
extern Struct_20000024 Data_20000024; //20000024 (801941C)
extern Struct_2000002c Data_2000002c; //2000002c
extern Struct_2000002c_Inner8 Data_2000003c; //2000003c
extern Struct_2000002c_Inner8 Data_2000004c; //2000004c
extern uint8_t bData_20000054; //20000054 (801944C)
extern uint8_t bData_20000055; //20000055 (801944D)
extern uint8_t bData_20000056; //20000056 (801944E)
extern uint8_t bData_20000057; //20000057 (801944F)
extern uint32_t SystemCoreClock; //20000058
extern uint32_t uwTickPrio; //2000005C
extern HAL_TickFreqTypeDef uwTickFreq; //20000060
extern Struct_200000e4 Data_200000e4; //200000e4
extern uint8_t bData_200000e8; //200000e8
extern uint8_t bData_200000e9; //200000e9
extern uint8_t bData_200000ea; //200000ea
extern uint8_t bData_200000eb; //200000eb

extern uint8_t Data_200001f0[]; //200001f0

//extern uint8_t bData_20000a48; //20000a48
extern uint8_t bData_20000a48[]; //20000a48, size?
//extern int Data_20000a4c; //20000a4c
extern Struct_20000a4c Data_20000a4c; //20000a4c
extern Struct_20000a50 Data_20000a50; //20000a50
extern uint16_t wData_20000a56; //20000a56
extern uint8_t bData_20000a58; //20000a58
extern uint8_t bData_20000a59; //20000a59
extern uint8_t bData_20000a6c; //20000a6c
extern uint8_t bData_20000a6d; //20000a6d
extern RTC_TimeTypeDef Data_20000a70; //20000a70
extern RTC_DateTypeDef Data_20000a74; //20000a74
extern uint8_t bData_20000b7d; //20000b7d
extern Struct_20000bc0 Data_20000bc0;
extern char strFMVersion[]; //20000bcc
extern char strDABVersion[]; //20000bd8
extern uint8_t bData_20000be4; //20000be4
extern struct_8008d84 Data_20000be8[]; //20000be8 +224
extern struct_8008d84 Data_20000cc8[]; //20000cc8 +5600

extern uint8_t bData_200022a8; //200022a8
extern SPI_HandleTypeDef hspi2; //200022ac
extern I2C_HandleTypeDef hi2c2; //20002304
extern TIM_HandleTypeDef htim5; //20002358
extern SRAM_HandleTypeDef hsram1; //20002398
extern struct_8008d84* Data_200023e0; //200023e0
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
void ili9341_init(void);
void ili9341_fill_screen(uint16_t a);
void ili9341_draw_vert_line(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color);
void ili9341_draw_hor_line(uint16_t a, uint16_t b, uint16_t c, uint16_t e);
void ili9341_draw_string(char* a, uint8_t len);
void ili9341_draw_box(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void ili9341_draw_rect(int16_t a, int16_t b, int16_t c, int16_t d, uint16_t color);
void ili9341_set_font(Struct_2000002c_Inner8* a);
void sub_80060c8(uint16_t a, uint16_t b);
void ili9341_set_cursor(uint16_t x, uint16_t y);
void ili9341_set_address(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
void ili9341_setup_interface(void);
void ili9341_write_command(uint8_t a);
void ili9341_write_data(uint16_t a);
uint8_t sub_8006254(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f);
void sub_80062d8(void);
void sub_80063a4(void);
void sub_800651c(void);
void sub_8006618(void);
void sub_8006624(void);
void sub_8006694(uint8_t a);
void sub_80068e4(uint8_t a);
void sub_800691c(uint8_t a);
void sub_8006950(uint8_t a);
uint16_t sub_80069b4(int a);
void sub_8006a70(int a);

int si46xx_send_command(uint16_t numTxBytes, uint16_t b, uint16_t c);
int si46xx_read_stc_reply(uint16_t a, uint16_t b);
uint8_t si46xx_read_reply(uint16_t a, uint16_t numRxBytes);
int si46xx_load_and_boot(uint8_t a);
int si46xx_set_dab_config(void);
int si46xx_set_config(void);
int si46xx_set_audio_output(uint8_t a);
int si46xx_set_property(uint16_t name, uint16_t value);

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
