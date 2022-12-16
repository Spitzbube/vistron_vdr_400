
#include "main.h"


//_sdata: 20000000 - 200000c8 -> 080193f8 - 80194C0

lcdPropertiesTypeDef lcdProperties = //20000024 (801941C)
{
   320, 240
};
//20000028 (8019420)
lcdFontPropTypeDef lcdFont = //2000002c (8019424)
{
   COLOR_YELLOW,
   COLOR_BLACK,
   &Data_2000003c, //0x2000003c,
   1 //TextWrap
};
sFONT Data_2000003c = //2000003c (8019434)
{
   0, //0x08012f90/TODO*/,
   7,
   12
};
#if 0 //->font2.c
sFONT Data_20000044 = //20000044 (801943c)
{
   0, //8013404
   11,
   16
};
#endif
#if 0 //->font1.c
sFONT Data_2000004c = //2000004c (8019444)
{
   0, //8014ec4
   17,
   24
};
#endif
uint8_t bData_20000054 = 1; //20000054 (801944C)
uint8_t bData_20000055 = 0xff; //20000055 (801944D)
uint8_t bData_20000056 = 4; //20000056 (801944E)
uint8_t bCurrentVolume = 31; //20000057 (801944F)
//uint32_t SystemCoreClock; //20000058 (8019450)
//uint32_t uwTickPrio; //2000005C (8019454)
//HAL_TickFreqTypeDef uwTickFreq; //20000060 (8019458)
//_impure_ptr; //?? //20000064 (801945C)
//impure_data; //?? //20000068 (8019460 -> 80194C0?)

lcdCursorPosTypeDef cursorXY; //200000e4
uint8_t lcdPortraitConfig; //200000e8
uint8_t lcdLandscapeConfig; //200000e9
uint8_t lcdPortraitMirrorConfig; //200000ea
uint8_t lcdLandscapeMirrorConfig; //200000eb
char Data_200000ec[256]; //200000ec, size?
uint16_t g_wTouchX; //200001ec
uint16_t g_wTouchY; //200001ee

uint8_t si46xx_buffer[2048]; //200001f0
uint8_t g_bGroup2AMaxAddress; //200009f0
uint32_t g_dwGroup2AFlagsLow; //200009f4
uint32_t g_dwGroup2AFlagsHigh; //200009f8
uint8_t g_bGroup0AFlags; //200009fc
uint8_t g_bGroup0ABuffer[8]; //20000a00
uint8_t g_bGroup2ABuffer[64]; //20000a08

Struct_20000a48 IrEvent;
Struct_20000a48 KeyEvent; //20000a48
Alarm_Time currentAlarmTime; //20000a4c
User_Settings UserSettings; //20000a50
uint8_t bBackgroundSearchRetry; //20000a54
uint8_t bBackgroundChannelNr; //20000a55
uint16_t wMainloopEvents; //20000a56
uint8_t bCurrentChannelNumber; //20000a58
uint8_t bData_20000a59; //20000a59
int8_t Data_20000a5a; //20000a5a
Tuner_Values Data_20000a5c; //20000a5c
uint8_t bMainIrCode;
uint8_t bMainTouchCode; //20000a6c
uint8_t bMainKeyCode; //20000a6d
RTC_TimeTypeDef rtcTime; //20000a70
RTC_DateTypeDef rtcDate; //20000a74
Radio_Text radioText; //20000a78
//int Data_20000af8; //20000af8
Radio_Text radioTextOld; //20000afc
uint8_t sleepTimerCount; //20000b7d
Touch_Data g_stTouchData; //20000b90
Struct_20000bc0 TouchEvent;
char** CurrentTextTable; //20000bc8
char strFMVersion[12]; //20000bcc
char strDABVersion[12]; //20000bd8
uint8_t bFavouriteCount; //20000be4
Tuner_Channel FavouriteList[8]; //20000be8 +224
Tuner_Channel ChannelList[200]; //20000cc8 +5600
uint8_t bChannelCount; //200022a8
Tuner_Channel* Data_200023e0; //200023e0

RC5_Data rc5Data;
