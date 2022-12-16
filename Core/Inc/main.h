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
#include "colors.h"
#include "fonts.h"
#include "ili9341.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


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
   uint16_t frequency; //24
   //28
} Tuner_Channel;

typedef struct
{
	int b0: 1;
	uint8_t b1: 1;
	uint8_t b2: 1;
	int a: 5;
	uint8_t b: 6;
} User_Settings;


typedef struct
{
   uint32_t timerCount; //0
   uint16_t raw_x; //4
   uint16_t raw_y; //6
   uint16_t x; //8
   uint16_t y; //19
   float Data_12; //12
   float Data_16; //16
   float Data_20; //20
   float Data_24; //24
   float Data_28; //28
   float Data_32; //32
#if 0
   uint16_t wData_36; //36
   uint16_t wData_38; //38
   uint16_t wData_40; //40
   uint16_t wData_42; //42
   uint16_t wData_44; //44
   uint16_t wData_46; //46
#endif

} Touch_Data;


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
   uint8_t str[128]; //0
   uint8_t bLength; //0x80
   //129
} Radio_Text;

typedef struct
{
   uint16_t hours; //0
   uint16_t minutes; //2
} Alarm_Time;

typedef void (*Draw_Icon)(uint16_t, uint16_t, int, uint16_t);


extern const char* Data_8012cdc[]; //8012cdc

extern Draw_Icon g_arIcons[]; //0x20000000
extern lcdPropertiesTypeDef lcdProperties; //20000024 (801941C)
extern lcdFontPropTypeDef lcdFont; //2000002c
extern sFONT Data_2000003c; //2000003c
extern sFONT Data_20000044; //20000044
extern sFONT Data_2000004c; //2000004c
extern uint8_t bData_20000054; //20000054 (801944C)
extern uint8_t bData_20000055; //20000055 (801944D)
extern uint8_t bData_20000056; //20000056 (801944E)
extern uint8_t bCurrentVolume; //20000057 (801944F)
extern uint32_t SystemCoreClock; //20000058
extern uint32_t uwTickPrio; //2000005C
extern HAL_TickFreqTypeDef uwTickFreq; //20000060

extern lcdCursorPosTypeDef cursorXY; //200000e4
extern uint8_t lcdPortraitConfig; //200000e8
extern uint8_t lcdLandscapeConfig; //200000e9
extern uint8_t lcdPortraitMirrorConfig; //200000ea
extern uint8_t lcdLandscapeMirrorConfig; //200000eb
extern char Data_200000ec[]; //200000ec
extern uint16_t g_wTouchX; //200001ec
extern uint16_t g_wTouchY; //200001ee

extern uint8_t si46xx_buffer[]; //200001f0
extern uint8_t g_bGroup2AMaxAddress; //200009f0
extern uint32_t g_dwGroup2AFlagsLow; //200009f4
extern uint32_t g_dwGroup2AFlagsHigh; //200009f8
extern uint8_t g_bGroup0AFlags; //200009fc
extern uint8_t g_bGroup0ABuffer[]; //20000a00
extern uint8_t g_bGroup2ABuffer[]; //20000a08

extern Struct_20000a48 KeyEvent; //20000a48
extern Alarm_Time currentAlarmTime; //20000a4c
extern User_Settings UserSettings; //20000a50
extern uint8_t bBackgroundSearchRetry; //20000a54
extern uint8_t bBackgroundChannelNr; //20000a55
extern uint16_t wMainloopEvents; //20000a56
extern uint8_t bCurrentChannelNumber; //20000a58
extern uint8_t bData_20000a59; //20000a59
extern int8_t Data_20000a5a; //20000a5a
extern Tuner_Values Data_20000a5c; //20000a5c
extern uint8_t bMainTouchCode; //20000a6c
extern uint8_t bMainKeyCode; //20000a6d
extern RTC_TimeTypeDef rtcTime; //20000a70
extern RTC_DateTypeDef rtcDate; //20000a74
extern Radio_Text radioText; //20000a78
//extern int Data_20000af8; //20000af8
extern Radio_Text radioTextOld; //20000afc
extern uint8_t sleepTimerCount; //20000b7d
extern Touch_Data g_stTouchData; //20000b90
extern Struct_20000bc0 TouchEvent;
extern char** CurrentTextTable; //20000bc8
extern char strFMVersion[]; //20000bcc
extern char strDABVersion[]; //20000bd8
extern uint8_t bFavouriteCount; //20000be4
extern Tuner_Channel FavouriteList[]; //20000be8 +224
extern Tuner_Channel ChannelList[]; //20000cc8 +5600

extern uint8_t bChannelCount; //200022a8
extern SPI_HandleTypeDef hspi2; //200022ac
extern I2C_HandleTypeDef hi2c2; //20002304
extern TIM_HandleTypeDef htim5; //20002358
extern SRAM_HandleTypeDef hsram1; //20002398
extern Tuner_Channel* Data_200023e0; //200023e0
extern RTC_HandleTypeDef hrtc; //200023e4
extern TIM_HandleTypeDef htim6; //200023f8
extern UART_HandleTypeDef huart2; //20002438

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define TOUCH_CMD_RDX                       0xD0
#define TOUCH_CMD_RDY                       0x90

#define ICON_UP								0
#define ICON_DOWN							1
#define ICON_LEFT							2
#define ICON_RIGHT							3
#define ICON_MENU							4
#define ICON_BACK							7

#define MAIN_LOOP_EVENT_DAB_ACTIVE          (1 << 0)
#define MAIN_LOOP_EVENT_FAV_ACTIVE          (1 << 2)
#define MAIN_LOOP_EVENT_ALARM               (1 << 3)
#define MAIN_LOOP_EVENT_RTC                 (1 << 4)
#define MAIN_LOOP_EVENT_BACKGROUND_TIME     (1 << 7)
#define MAIN_LOOP_EVENT_FOREGROUND          (1 << 8)
#define MAIN_LOOP_EVENT_SLEEP_TIMER         (1 << 9)
#define MAIN_LOOP_EVENT_AUTO_STANDBY        (1 << 10)

#define TEXT_ID_NO_CHANNEL                  8
#define TEXT_ID_FAV_LIST_FULL               9
#define TEXT_ID_MAIN_MENU                   13
#define TEXT_ID_CHANNEL_LIST                18
#define TEXT_ID_SETTINGS                    19
#define TEXT_ID_ALARM                       21
#define TEXT_ID_INFORMATION                 22
#define TEXT_ID_AUTOMATIC_SEARCH            23
#define TEXT_ID_LANGUAGE                    28
#define TEXT_ID_SLEEP_TIMER                 29
#define TEXT_ID_AUTO_STANDBY                30
#define TEXT_ID_GERMAN                      34
#define TEXT_ID_OFF                         37
#define TEXT_ID_SIGNAL_INFORMATION          39
#define TEXT_ID_CHANNEL                     40
#define TEXT_ID_MULTIPLEX                   41
#define TEXT_ID_FREQUENCY                   42
#define TEXT_ID_LEVEL                       43
#define TEXT_ID_SNR                         44
#define TEXT_ID_ERROR_RATE                  45
#define TEXT_ID_MULTIPATH                   46
#define TEXT_ID_PRODUCT                     53
#define TEXT_ID_HARDWARE                    54
#define TEXT_ID_SOFTWARE                    55
#define TEXT_ID_DAB_FIRMWARE                56
#define TEXT_ID_FM_FIRMWARE                 57

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
uint8_t main_screen_check_touch_fields(uint16_t a, uint16_t b);
void draw_volume_bar(uint8_t r7_7);
void draw_channel_name(void* a);
void draw_foreground_clock(RTC_TimeTypeDef);
void draw_background_clock(RTC_TimeTypeDef);
void draw_channel_number_box(uint16_t r7_6, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2);
void draw_signal_strength_bars(uint16_t r7_6, uint16_t r7_4, int8_t* r7);
void draw_radio_text(void* r7_4, uint8_t r7_3);
void sub_8002054(Tuner_Channel* r7_c, uint8_t r7_b, uint8_t r7_a, void* r7_4, uint8_t r7_18);
int menu_channel_select_check_touch_fields(uint16_t a, uint16_t b);
void draw_on_off_icon(uint16_t a, uint16_t b);
void sub_80023d0(Tuner_Channel* r7_4, uint8_t r7_3, uint8_t r7_2);
void draw_scroll_bar(uint8_t r7_7, uint8_t r7_6);
void draw_snr_indicator(uint16_t r7_e, uint16_t r7_c, Tuner_Values* r7_8, uint8_t r7_7);
void draw_channel_freq_mux_label(Tuner_Channel* r7_4, uint8_t r7_3);
void sub_80028b8(Tuner_Channel* r7_4, uint8_t r7_3, uint8_t r7_2);
void draw_automatic_search_screen(Tuner_Channel* r7_4, uint8_t r7_3, uint8_t r7_2, uint16_t r7, uint16_t r7_10, void* r7_14, uint16_t r7_18);
int menu_automatic_search_check_touch_fields(uint16_t a, uint16_t b);
void draw_progress_bar(uint16_t r7_6, uint16_t r7_4, uint16_t r7_2, uint16_t r7);
void draw_channel_list(Tuner_Channel* r7_4, uint8_t r7_3);
void draw_freq_mux_label(uint16_t a);
void sub_8002cac(uint16_t firstTextId, uint8_t lines, uint8_t focus);
void sub_8002d70(uint16_t textId, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2);
void sub_8002e0c(uint16_t r7_6, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2);
uint8_t sub_8002e98(uint16_t a, uint16_t b);
void draw_screen_caption(uint16_t textId, sFONT* font);
void draw_signal_information_screen(Tuner_Channel* a, uint8_t b, Tuner_Values* c);
void draw_signal_level_line(Tuner_Values* a);
void draw_signal_quality_line(Tuner_Values* a);
void draw_signal_error_rate_line(Tuner_Values* a);
void draw_signal_multipath_line(Tuner_Values* a);
int signal_information_screen_check_touch_fields(uint16_t a, uint16_t b);
void draw_sw_information_screen(char* r7_4, char* r7);
int sub_80041e0(uint16_t r7_6, uint16_t r7_4);
void draw_alarm_screen(Alarm_Time* r7_4, uint8_t r7_3, uint8_t r7_2);
void draw_alarm_time_edit(Alarm_Time* r7_4, uint8_t r7_3, uint8_t r7_2);
int alarm_screen_check_touch_fields(uint16_t r7_6, uint16_t r7_4);
void draw_standby_screen(RTC_TimeTypeDef r7_c, RTC_DateTypeDef r7_8, Alarm_Time* r7_4, uint8_t r7_3);
void draw_alarm_time(Alarm_Time* a);
void draw_sleep_timer_screen(uint8_t a);
void draw_sleep_timer_value(uint8_t r7_7);
int sub_8004894(uint16_t a, uint16_t b);
void draw_volume_change_screen(uint8_t a);
void draw_volume_change_bar(uint8_t a);
int volume_change_screen_check_touch_fields(uint16_t a, uint16_t b);
void sub_8004b74(int a, int b, char* c);
void draw_arrow_up(uint16_t, uint16_t, uint16_t, uint16_t);
void draw_arrow_down(uint16_t, uint16_t, int, uint16_t);
void draw_arrow_left(uint16_t, uint16_t, int, uint16_t);
void draw_arrow_right(uint16_t, uint16_t, int, uint16_t);
void draw_icon_menu(uint16_t, uint16_t, uint16_t, uint16_t);
void sub_8004e74(uint16_t, uint16_t, int, uint16_t);
void sub_8004f24(uint16_t, uint16_t, int, uint16_t);
void draw_icon_back(uint16_t, uint16_t, int, uint16_t);
void sub_8005074(uint16_t, uint16_t, int, uint16_t);
void draw_36x36(uint16_t a, uint16_t b, uint16_t c, uint8_t d);
void menu_set_language(uint8_t a);
void lcdInit(void);
void lcdFillRGB(uint16_t color);
void lcdDrawPixel(uint16_t a, uint16_t b, uint16_t color);
void lcdDrawHLine(uint16_t a, uint16_t b, uint16_t c, uint16_t color);
void lcdDrawVLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color);
void lcdPrintf(const char * format, ...);
void ili9341_draw_string(char* a, uint8_t len);
void lcdFillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void lcdDrawRect(int16_t a, int16_t b, int16_t c, int16_t d, uint16_t color);
void lcdFillCircle(int16_t a, int16_t b, uint16_t c, uint16_t d);
void lcdFillCircleHelper(int16_t a, int16_t b, int16_t c, uint8_t d, int16_t e, uint16_t color);
void lcdFillTriangle(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, uint16_t g);
void lcdDrawChar(int16_t x, int16_t y, char c, uint16_t fg, uint16_t bg);
void lcdSetTextFont(sFONT* a);
void lcdSetTextColor(uint16_t fg, uint16_t bg);
void lcdSetCursor(uint16_t x, uint16_t y);
void lcdSetWindow(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
void ili9341_setup_interface(void);
void lcdWriteCommand(uint8_t a);
void lcdWriteData(uint16_t a);
uint8_t lcdBuildMemoryAccessControlConfig(uint8_t my, uint8_t mx, uint8_t mv, uint8_t ml, uint8_t bgr, uint8_t mh);
void touch_poll(void);
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
void touch_convert_values(void);
uint8_t touch_detect_move(void);
void touch_toggle_clk_line(uint8_t a);
void touch_toggle_cs_line(uint8_t a);
void touch_toggle_mosi_line(uint8_t a);
uint16_t sub_touch_spi_transfer(int a);
void touch_spi_delay(int a);
int flash_write(uint32_t addr, uint16_t data[], uint16_t r7_6);
int flash_erase(uint32_t addr);
void menu_main(void);
int menu_channel_list(void);
int menu_settings(void);
int menu_alarm(void);
int menu_sw_information(void);
int sub_8007414(void);
int sub_80075e9(void);
int sub_80078c4(void);
int sub_8007b48(void);
int menu_language(void);
int menu_sleep_timer(void);
int menu_auto_standby(void);
int menu_volume_change(void);
int sub_80088cc(void);

int si46xx_set_volume(uint8_t a);
int si46xx_mute(uint8_t bMute);
int si46xx_start_dab(uint8_t a);
int si46xx_start_fm(uint8_t a);
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
int si46xx_fm_get_rds_data(void* pStationName, uint8_t* pRadioText, RTC_TimeTypeDef*, RTC_DateTypeDef*, uint16_t* pwMainloopEvents, uint8_t* pbRadioTextLength);
int si46xx_get_fm_station_name(uint8_t[]);
int si46xx_is_dab_service_list_avail(uint8_t);
int sub_8009f70(uint8_t* a);
int si46xx_get_digital_service_list(uint8_t r7_7, uint16_t* r7);
int si46xx_get_fm_received_signal_quality(void);
int si46xx_get_fm_rds_status(uint8_t ackBits, uint8_t numRetry);
int si46xx_start_fm_seek(void);
void si46xx_get_rds_time(RTC_TimeTypeDef* a, RTC_DateTypeDef* b);
int si46xx_get_fm_values(Tuner_Values* r7_4);
int si46xx_get_dab_values(Tuner_Values* a);
int si46xx_get_digital_service_data(uint8_t r7_4[], uint8_t* r7);
int sub_800a9a8(void);
void channel_next(void);
void channel_previous(void);
void channel_set(Tuner_Channel* a);
void volume_up(void);
void volume_down(void);
void channel_start_current(void);
void channel_stop_playing(void);
int channel_search_time(void);
void button_poll(void);
int sub_800b270(void);
int sub_800b2ac(void* a, void* b);
int sub_800b398(uint16_t a, void* b);
int sub_800b43c(uint16_t a);
int sub_800b4ec(Tuner_Channel* a);
uint8_t channel_list_clear(void);
void sub_800b610(uint8_t a);
int sub_800b6f0(Tuner_Channel a);
int sub_800b7f8(Tuner_Channel a);
int persist_add_dab_station(uint8_t r7_f, uint32_t r7_8, uint32_t r7_4, uint8_t* r7);
int persist_write(Tuner_Channel* r7_c, Tuner_Channel* r7_8, void* r7_4, void* r7);
int persist_clear(void);
int persist_read(Tuner_Channel* r7_c, Tuner_Channel* r7_8, void* r7_4, void* r7);
void menu_channel_select(void);
int menu_automatic_search(void);
void sub_800c460(void);
void menu_signal_information(void);
void main_delay(uint16_t);
uint32_t calculate_crc(uint32_t r7_c, void* r7_8, uint32_t r7_4);
uint16_t sub_800c88c(uint8_t r7_4[], uint16_t r7_2);
//800c8f4: main

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SI46xx_Interrupt_Pin GPIO_PIN_0
#define SI46xx_Interrupt_GPIO_Port GPIOC
#define ILI9341_Reset_Pin GPIO_PIN_1
#define ILI9341_Reset_GPIO_Port GPIOC
#define SI46xx_Reset_Pin GPIO_PIN_2
#define SI46xx_Reset_GPIO_Port GPIOC
#define Amp_Mute_Pin GPIO_PIN_3
#define Amp_Mute_GPIO_Port GPIOC
#define Amp_Shutdown_Pin GPIO_PIN_1
#define Amp_Shutdown_GPIO_Port GPIOA
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
