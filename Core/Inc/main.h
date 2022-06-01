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

} Screen_Resolution;

typedef struct
{
   uint8_t* Data_0; //0
   uint16_t width; //4
   uint16_t height; //6

} Struct_2000002c_Inner8;


typedef struct
{
   int fg_color; //0
   int bg_color; //4
   Struct_2000002c_Inner8* pFont; //8;
   uint8_t bData_12; //12

} Text_Attributes;

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
   int Data_0; //0
   uint16_t wData_4; //4
   uint16_t wData_6; //6
   uint16_t wData_8; //8
   uint16_t wData_10; //19
   int Data_12; //12
   int Data_16; //16
   int Data_20; //20
   int Data_24; //24
   int Data_28; //28
   int Data_32; //32
   uint16_t wData_36; //36
   uint16_t wData_38; //38
   uint16_t wData_40; //40
   uint16_t wData_42; //42
   uint16_t wData_44; //44
   uint16_t wData_46; //46

} Struct_20000b90;


typedef struct
{
	uint8_t bData_0; //0
	uint16_t wData_2; //2
	uint16_t wData_4; //4

} Struct_20000bc0;


typedef struct
{
   uint8_t bData_0; //0
   uint8_t bData_1; //1

} Struct_20000a48;


typedef struct
{
   int8_t rssi; //0
   int8_t snr; //1
   uint16_t fib_error_count; //2
   uint8_t freq_index; //4
   uint32_t frequency; //8
   uint8_t multipath; //12
   uint8_t freq_offset; //13
   //16
} Tuner_Values;


typedef struct
{
   uint8_t arData_0[128]; //0
   uint8_t bData_0x80; //0x80
   //129
} Struct_20000a78;

typedef void (*Func_20000000)(uint16_t, uint16_t, int, uint16_t);


extern const char* Data_8012cdc[]; //8012cdc

extern Func_20000000 Funcs_20000000[]; //0x20000000
extern Screen_Resolution ScreenResolution; //20000024 (801941C)
extern Text_Attributes TextAttributes; //2000002c
extern Struct_2000002c_Inner8 Data_2000003c; //2000003c
extern Struct_2000002c_Inner8 Data_20000044; //20000044
extern Struct_2000002c_Inner8 Data_2000004c; //2000004c
extern uint8_t bData_20000054; //20000054 (801944C)
extern uint8_t bData_20000055; //20000055 (801944D)
extern uint8_t bData_20000056; //20000056 (801944E)
extern uint8_t bData_20000057; //20000057 (801944F)
extern uint32_t SystemCoreClock; //20000058
extern uint32_t uwTickPrio; //2000005C
extern HAL_TickFreqTypeDef uwTickFreq; //20000060
extern Struct_200000e4 TextCursor; //200000e4
extern uint8_t bData_200000e8; //200000e8
extern uint8_t bData_200000e9; //200000e9
extern uint8_t bData_200000ea; //200000ea
extern uint8_t bData_200000eb; //200000eb
extern char Data_200000ec[]; //200000ec
extern uint16_t wData_200001ec; //200001ec
extern uint16_t wData_200001ee; //200001ee
extern uint8_t si46xx_buffer[]; //200001f0
extern uint8_t bData_200009f0; //200009f0
extern int Data_200009f4; //200009f4
extern int Data_200009f8; //200009f8
extern uint8_t bData_200009fc; //200009fc
extern uint8_t Data_20000a00[]; //20000a00
extern uint8_t Data_20000a08[]; //20000a08
extern Struct_20000a48 Data_20000a48; //20000a48
//extern int Data_20000a4c; //20000a4c
extern Struct_20000a4c Data_20000a4c; //20000a4c
extern Struct_20000a50 Data_20000a50; //20000a50
extern uint8_t bData_20000a54; //20000a54
extern uint8_t bData_20000a55; //20000a55
extern uint16_t wData_20000a56; //20000a56
extern uint8_t bCurrentChannelNumber; //20000a58
extern uint8_t bData_20000a59; //20000a59
extern int8_t Data_20000a5a; //20000a5a
extern Tuner_Values Data_20000a5c; //20000a5c
extern uint8_t bData_20000a6c; //20000a6c
extern uint8_t bData_20000a6d; //20000a6d
extern RTC_TimeTypeDef Data_20000a70; //20000a70
extern RTC_DateTypeDef Data_20000a74; //20000a74
extern Struct_20000a78 Data_20000a78; //20000a78
//extern int Data_20000af8; //20000af8
extern Struct_20000a78 Data_20000afc; //20000afc
extern uint8_t bData_20000b7d; //20000b7d
extern Struct_20000b90 Data_20000b90; //20000b90
extern Struct_20000bc0 Data_20000bc0;
extern char** CurrentTextTable; //20000bc8
extern char strFMVersion[]; //20000bcc
extern char strDABVersion[]; //20000bd8
extern uint8_t bData_20000be4; //20000be4
extern struct_8008d84 Data_20000be8[]; //20000be8 +224
extern struct_8008d84 Data_20000cc8[]; //20000cc8 +5600

extern uint8_t bChannelCount; //200022a8
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

#define TOUCH_CMD_RDX                       0xD0
#define TOUCH_CMD_RDY                       0x90

#define TEXT_ID_NO_CHANNEL                  8
#define TEXT_ID_MAIN_MENU                   13
#define TEXT_ID_CHANNEL_LIST                18
#define TEXT_ID_SETTINGS                    19
#define TEXT_ID_ALARM                       21
#define TEXT_ID_AUTOMATIC_SEARCH            23
#define TEXT_ID_LANGUAGE                    28
#define TEXT_ID_GERMAN                      34

#define TEXT_ID_MAIN_MENU_FIRST             TEXT_ID_CHANNEL_LIST
#define TEXT_ID_MAIN_MENU_ITEMS             5
#define TEXT_ID_SETTINGS_FIRST              TEXT_ID_LANGUAGE
#define TEXT_ID_SETTINGS_ITEMS              3
#define TEXT_ID_LANGUAGE_FIRST              TEXT_ID_GERMAN
#define TEXT_ID_LANGUAGE_ITEMS              2
#define TEXT_ID_CHANNEL_LIST_FIRST          TEXT_ID_AUTOMATIC_SEARCH
#define TEXT_ID_CHANNEL_LIST_ITEMS          3

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

int sub_8001224(char* a);
void draw_main_screen(RTC_TimeTypeDef r7_c, void* r7_8, uint8_t r7_7, void* r7, uint8_t r7_18, uint8_t f, Tuner_Values* g, uint16_t h);
void sub_8001eb6(uint8_t r7_7);
void draw_channel_name(void* a);
void draw_radio_text(void* r7_4, uint8_t r7_3);
void draw_channel_number_box(uint16_t r7_6, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2);
void draw_signal_strength_bars(uint16_t r7_6, uint16_t r7_4, int8_t* r7);
void sub_8002054(struct_8008d84* r7_c, uint8_t r7_b, uint8_t r7_a, void* r7_4, uint8_t r7_18);
int menu_channel_select_check_touch_fields(uint16_t a, uint16_t b);
void draw_on_off_icon(uint16_t a, uint16_t b);
void draw_scroll_bar(uint8_t r7_7, uint8_t r7_6);
void draw_snr_indicator(uint16_t r7_e, uint16_t r7_c, Tuner_Values* r7_8, uint8_t r7_7);
void draw_channel_freq_mux_label(struct_8008d84* r7_4, uint8_t r7_3);
void sub_80028b8(struct_8008d84* r7_4, uint8_t r7_3, uint8_t r7_2);
void draw_automatic_search_screen(struct_8008d84* r7_4, uint8_t r7_3, uint8_t r7_2, uint16_t r7, uint16_t r7_10, void* r7_14, uint16_t r7_18);
int menu_automatic_search_check_touch_fields(uint16_t a, uint16_t b);
void draw_progress_bar(uint16_t r7_6, uint16_t r7_4, uint16_t r7_2, uint16_t r7);
void draw_channel_list(struct_8008d84* r7_4, uint8_t r7_3);
void draw_freq_mux_label(uint16_t a);
void sub_8002d70(uint16_t textId, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2);
void sub_8003038(uint16_t textId, Struct_2000002c_Inner8* font);
void draw_standby_screen(RTC_TimeTypeDef r7_c, RTC_DateTypeDef r7_8, Struct_20000a4c* r7_4, uint8_t r7_3);
void sub_80046d8(Struct_20000a4c* a);
void sub_8004be8(uint16_t, uint16_t, uint16_t, uint16_t);
void sub_8004c4c(uint16_t, uint16_t, int, uint16_t);
void sub_8004cb0(uint16_t, uint16_t, int, uint16_t);
void sub_8004d14(uint16_t, uint16_t, int, uint16_t);
void sub_8004d78(uint16_t, uint16_t, uint16_t, uint16_t);
void sub_8004e74(uint16_t, uint16_t, int, uint16_t);
void sub_8004f24(uint16_t, uint16_t, int, uint16_t);
void sub_8004fc4(uint16_t, uint16_t, int, uint16_t);
void sub_8005074(uint16_t, uint16_t, int, uint16_t);
void sub_8005198(uint16_t a, uint16_t b, uint16_t c, uint8_t d);
void menu_set_language(uint8_t a);
void ili9341_init(void);
void ili9341_fill_screen(uint16_t a);
void ili9341_draw_vert_line(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color);
void ili9341_draw_hor_line(uint16_t a, uint16_t b, uint16_t c, uint16_t e);
void ili9341_draw_format_string(const char * format, ...);
void ili9341_draw_string(char* a, uint8_t len);
void ili9341_draw_box(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void ili9341_draw_rect(int16_t a, int16_t b, int16_t c, int16_t d, uint16_t color);
void ili9341_draw_circle(int16_t a, int16_t b, uint16_t c, uint16_t d);
void sub_800581e(int16_t a, int16_t b, int16_t c, int16_t d, uint16_t e);
void sub_80058f0(int16_t a, int16_t b, int16_t c, uint8_t d, int16_t e, uint16_t color);
void sub_8005af0(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, uint16_t g);
void ili9341_set_font(Struct_2000002c_Inner8* a);
void ili9341_set_text_color(uint16_t fg, uint16_t bg);
void ili9341_set_cursor(uint16_t x, uint16_t y);
void ili9341_set_address(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
void ili9341_setup_interface(void);
void ili9341_write_command(uint8_t a);
void ili9341_write_data(uint16_t a);
uint8_t sub_8006254(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f);
void touch_toggle_clk_line(uint8_t a);
void touch_toggle_cs_line(uint8_t a);
void touch_toggle_mosi_line(uint8_t a);
int touch_read_miso_line(void);
int touch_read_irq(void);
uint16_t touch_spi_transfer(int cmd);
void ili9341_configure_gpio(void);
void ili9341_configure_fsmc(void);
int touch_init(void);
void touch_configure_gpio(void);
void sub_8006618(void);
void sub_8006624(void);
void touch_read_xy(uint8_t a);
void sub_8006730(void);
uint8_t sub_8006838(void);
void sub_80068e4(uint8_t a);
void sub_800691c(uint8_t a);
void sub_8006950(uint8_t a);
uint16_t sub_80069b4(int a);
void sub_8006a70(int a);
int sub_8006a8e(uint32_t addr, uint16_t data[], uint16_t r7_6);
int sub_8006af4(uint32_t addr);
void menu_main(void);
int menu_channel_list(void);
int menu_settings(void);
int sub_8007114(void);
int sub_80073c0(void);
int sub_8007415(void);
int sub_80075e9(void);
int menu_language(void);
int sub_8008200(void);
int sub_800837c(void);
int sub_80088cc(void);

int si46xx_send_command(uint16_t numTxBytes, uint16_t b, uint16_t c);
int si46xx_read_stc_reply(uint16_t a, uint16_t b);
uint8_t si46xx_read_reply(uint16_t a, uint16_t numRxBytes);
int si46xx_load_and_boot(uint8_t a);
int si46xx_get_dab_status(void);
int si46xx_set_dab_config(void);
int si46xx_set_config(void);
int si46xx_set_audio_output(uint8_t a);
int si46xx_set_property(uint16_t name, uint16_t value);
int si46xx_dab_tune_freq(uint8_t index);
int si46xx_fm_tune_freq(uint16_t khz);
int si46xx_dab_search(uint8_t* r7_4);
int si46xx_fm_search(uint8_t* r7_4);
int si46xx_dab_get_time_date(RTC_TimeTypeDef* r7_4, RTC_DateTypeDef* r7);
int si46xx_fm_get_rds_data(void* r7_c, uint8_t* r7_8, void* r7_4, void* r7, uint16_t* r7_30, uint8_t* r7_34);
int sub_8009868(uint8_t r7_4[]);
int sub_8009f1c(uint8_t a);
int sub_8009f70(uint8_t* a);
int si46xx_get_digital_service_list(uint8_t r7_7, uint16_t* r7);
int sub_800a174(void);
int sub_800a1a4(uint8_t r7_7, uint8_t r7_6);
int si46xx_start_fm_seek(void);
void si46xx_get_rds_time(RTC_TimeTypeDef* a, RTC_DateTypeDef* b);
int si46xx_get_fm_values(Tuner_Values* r7_4);
int si46xx_get_dab_values(Tuner_Values* a);
int si46xx_get_digital_service_data(uint8_t r7_4[], uint8_t* r7);
void channel_next(void);
void channel_previous(void);
void channel_set(struct_8008d84* a);
void sub_800ad68(void);
void sub_800adb8(void);
void button_gpio_check(void);
int sub_800b398(uint16_t a, void* b);
int sub_800b43c(uint16_t a);
void sub_800b610(uint8_t a);
int sub_800b8d4(uint8_t r7_f, uint32_t r7_8, uint32_t r7_4, uint8_t* r7);
int sub_800ba74(struct_8008d84* r7_c, struct_8008d84* r7_8, void* r7_4, void* r7);
int sub_800bbbc(void);
void menu_channel_select(void);
int menu_automatic_search(void);
void sub_800c460(void);
void sub_800c7e0(uint16_t a);
uint32_t calculate_crc(uint32_t r7_c, void* r7_8, uint32_t r7_4);
uint16_t sub_800c88c(uint8_t r7_4[], uint16_t r7_2);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Button_Blue_Pin GPIO_PIN_4
#define Button_Blue_GPIO_Port GPIOA
#define Display_Backlight_Pin GPIO_PIN_5
#define Display_Backlight_GPIO_Port GPIOA
#define Touch_SPI_MISO_Pin GPIO_PIN_6
#define Touch_SPI_MISO_GPIO_Port GPIOA
#define Touch_SPI_MOSI_Pin GPIO_PIN_7
#define Touch_SPI_MOSI_GPIO_Port GPIOA
#define Button_Yellow_Pin GPIO_PIN_5
#define Button_Yellow_GPIO_Port GPIOC
#define Button_Red_Pin GPIO_PIN_0
#define Button_Red_GPIO_Port GPIOB
#define Button_Green_Pin GPIO_PIN_1
#define Button_Green_GPIO_Port GPIOB
#define SPI2_CS_SI46xx_Pin GPIO_PIN_12
#define SPI2_CS_SI46xx_GPIO_Port GPIOB
#define Touch_SPI_CLK_Pin GPIO_PIN_12
#define Touch_SPI_CLK_GPIO_Port GPIOD
#define Touch_SPI_IRQ_Pin GPIO_PIN_6
#define Touch_SPI_IRQ_GPIO_Port GPIOB
#define Touch_SPI_CS_Pin GPIO_PIN_7
#define Touch_SPI_CS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
