
#include "main.h"

//_sdata: 20000000 - 200000c8 -> 080193f8 - 80194C0

#if 0
Func_20000000 Funcs_20000000[] = //20000000 (80193f8)
{
   sub_8004be8, //arrow up
   sub_8004c4c, //arrow down
   sub_8004cb0, //arrow left
   sub_8004d14, //arrow right
   sub_8004d78, //three horizontal lines
   sub_8004e74,
   sub_8004f24,
   sub_8004fc4,
   sub_8005074
};
#endif
Screen_Resolution ScreenResolution = //20000024 (801941C)
{
   320, 240
};
//20000028 (8019420)
Text_Attributes TextAttributes = //2000002c (8019424)
{
   0xffe0,
   0,
   &Data_2000003c, //0x2000003c,
   1
};
Struct_2000002c_Inner8 Data_2000003c = //2000003c (8019434)
{
   0, //0x08012f90/TODO*/,
   7,
   12
};
#if 0 //->font2.c
Struct_2000002c_Inner8 Data_20000044 = //20000044 (801943c)
{
   0, //8013404
   11,
   16
};
#endif
#if 0 //->font1.c
Struct_2000002c_Inner8 Data_2000004c = //2000004c (8019444)
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
Struct_200000e4 TextCursor; //200000e4
uint8_t bData_200000e8; //200000e8
uint8_t bData_200000e9; //200000e9
uint8_t bData_200000ea; //200000ea
uint8_t bData_200000eb; //200000eb
char Data_200000ec[256]; //200000ec, size?
uint16_t wData_200001ec; //200001ec
uint16_t wData_200001ee; //200001ee
uint8_t si46xx_buffer[2048]; //200001f0 size?
uint8_t bData_200009f0; //200009f0
int Data_200009f4; //200009f4
int Data_200009f8; //200009f8
uint8_t bData_200009fc; //200009fc
uint8_t Data_20000a00[8]; //20000a00, size?
uint8_t Data_20000a08[0x40]; //20000a08, size?
Struct_20000a48 KeyEvent; //20000a48
Alarm_Time currentAlarmTime; //20000a4c
Struct_20000a50 Data_20000a50; //20000a50
uint8_t bData_20000a54; //20000a54
uint8_t bData_20000a55; //20000a55
uint16_t wMainloopEvents; //20000a56
uint8_t bCurrentChannelNumber; //20000a58
uint8_t bData_20000a59; //20000a59
int8_t Data_20000a5a; //20000a5a
Tuner_Values Data_20000a5c; //20000a5c
uint8_t bData_20000a6c; //20000a6c
uint8_t bData_20000a6d; //20000a6d
RTC_TimeTypeDef Data_20000a70; //20000a70
RTC_DateTypeDef Data_20000a74; //20000a74
Struct_20000a78 Data_20000a78; //20000a78
//int Data_20000af8; //20000af8
Struct_20000a78 Data_20000afc; //20000afc
uint8_t sleepTimerCount; //20000b7d
Struct_20000b90 Data_20000b90; //20000b90
Struct_20000bc0 TouchEvent;
char** CurrentTextTable; //20000bc8
char strFMVersion[12]; //20000bcc
char strDABVersion[12]; //20000bd8
uint8_t bFavouriteCount; //20000be4
struct_8008d84 FavouriteList[8]; //20000be8 +224
struct_8008d84 ChannelList[200]; //20000cc8 +5600
uint8_t bChannelCount; //200022a8
struct_8008d84* Data_200023e0; //200023e0

