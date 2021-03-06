
#include <string.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"

extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi2;

extern void Error_Handler(void);
int sub_800b2ac(void* a, void* b);


//_sdata: 20000000 - 200000c8 -> 080193f8 - 80194C0

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

extern int sub_800bc04(struct_8008d84* a, struct_8008d84* b, void* c, void* d);


/* 800173c - todo */
void draw_main_screen(RTC_TimeTypeDef r7_c, void* r7_8, uint8_t r7_7, void* r7, uint8_t r7_18, uint8_t channel_nr, Tuner_Values* g, uint16_t h)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);

   draw_channel_name(r7_8);
   draw_radio_text(r7, r7_18);
   draw_channel_number_box(12, 6, channel_nr, h & 4);
   draw_signal_strength_bars(142, 42, &g->rssi);

   draw_volume_bar(r7_7);

   sub_8001ae8(r7_c); //Clock display

   draw_on_off_icon(291, 214); //On-Off icon display (low right corner - red)

   sub_8005198(8, 196, 0x1f, 1); //blue touch area, 1 = black arrow down
   sub_8005198(61, 196, 0x7e0, 0); //x+53 green touch area, 0 = black arrow up
   sub_8005198(114, 196, 0xf800, 2); //red touch area, 2 = black arrow left
   sub_8005198(167, 196, 0xffe0, 3); //yellow touch area, 3 = black arrow right
   sub_8005198(79, 6, 0xfd20, 4); //orange touch area, 4 = three horizontal lines
}


/* 8001224 - todo */
int sub_8001224(char* a)
{
   char* b;
   for (b = a; *b != 0; b++) {}
   return b-a-1;
}


/* 8001a14 - todo */
void draw_channel_name(void* a)
{
   uint16_t len;

   if (bChannelCount != 0)
   {
      ili9341_set_font(&Data_2000004c);
      ili9341_draw_box(0, 63, 320, 24, 0xffff);
      ili9341_set_text_color(0, 0xffff);
      len = sub_800c88c(a, 16);
      ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 63);
      ili9341_draw_string(a, len);
   }
   else
   {
      len = sub_8001224(CurrentTextTable[TEXT_ID_NO_CHANNEL]);
      ili9341_set_font(&Data_2000004c);
      ili9341_set_text_color(0, 0xffff);
      ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 63);
      ili9341_draw_format_string(CurrentTextTable[TEXT_ID_NO_CHANNEL]);
   }
}


/* 8002cac - todo */
void sub_8002cac(uint16_t firstTextId, uint8_t lines, uint8_t focus)
{
   uint8_t i;
   uint8_t r7_e = (focus > 5)? focus - 2: 0;
   uint8_t r7_d = (lines < 5)? lines + 1: 5;

   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);

   for (i = 0; (i < r7_d) && ((r7_e + i) < lines); )
   {
      //loc_8002cf4
      if ((r7_e + i) == focus)
      {
         ili9341_set_text_color(0xffff, 0);
      }
      else
      {
         ili9341_set_text_color(0, 0xffff);
      }

      ili9341_set_cursor(0, 72 + 24 * i);
      ili9341_draw_format_string(CurrentTextTable[firstTextId + i]);
      i++;
   }
}


/* 8002d70 - todo */
void sub_8002d70(uint16_t textId, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   sub_8003038(textId, &Data_2000004c);
   sub_8002cac(r7_4, r7_3, r7_2);
   sub_8005198(8, 196, 0x1f, 1); //blue box / down arrow
   sub_8005198(61, 196, 0x7e0, 0); // green box / up arrow
   sub_8005198(167, 196, 0xffe0, 6); //yellow box
   sub_8005198(273, 196, 0xffff, 7); //white box / back arrow
}


/* 8002e98 - todo */
uint8_t sub_8002e98(uint16_t a, uint16_t b)
{
   if ((a > 7) && (a < 45) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(8, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(8, 196, 0x1f, 1);
      return 3;
   }

   if ((a > 60) && (a < 98) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(61, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(61, 196, 0x7e0, 0);
      return 2;
   }

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(167, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(167, 196, 0xffe0, 6);
      return 4;
   }

   if ((a > 272) && (a < 311) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(273, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(273, 196, 0xffff, 7);
      return 5;
   }

   if ((a < 320) && (b > 71) && (b < 97))
   {
      return 25;
   }

   if ((a < 320) && (b > 95) && (b < 121))
   {
      return 26;
   }

   if ((a < 320) && (b > 119) && (b < 145))
   {
      return 27;
   }

   if ((a < 320) && (b > 143) && (b < 169))
   {
      return 28;
   }

   if ((a < 320) && (b > 167) && (b < 193))
   {
      return 29;
   }

   return 0;
}


/* 8003038 - todo */
void sub_8003038(uint16_t textId, Struct_2000002c_Inner8* font)
{
   uint16_t len;

   ili9341_set_font(font);
   ili9341_draw_box(0, 23, 320, 24, 0xffff);
   ili9341_set_text_color(0, 0xffff);
   len = sub_8001224(CurrentTextTable[textId]);
   ili9341_set_cursor(160 - (len * font->width) / 2, 24);
   ili9341_draw_format_string(CurrentTextTable[textId]);
}


/* 80039b0 - todo */
void draw_signal_information_screen(struct_8008d84* r7_c, uint8_t r7_b, Tuner_Values* r7_4)
{
   extern const char* Data_8012cdc[];

   uint8_t r7_17;

   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   sub_8003038(TEXT_ID_SIGNAL_INFORMATION, &Data_2000004c);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 72);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_CHANNEL]);
   ili9341_set_cursor(140, 72);
   if (bChannelCount == 0)
   {
      ili9341_draw_string(CurrentTextTable[TEXT_ID_NO_CHANNEL], sub_8001224(CurrentTextTable[TEXT_ID_NO_CHANNEL]));
   }
   else
   {
      //loc_8003a46
      r7_17 = sub_800c88c(&r7_c[r7_b].Data_8, 16);
      ili9341_draw_string(&r7_c[r7_b].Data_8, r7_17);
   }
   //loc_8003a80
   draw_signal_level_line(r7_4);
   draw_signal_quality_line(r7_4);

   if (r7_4->frequency > 15000)
   {
      ili9341_set_font(&Data_20000044);
      ili9341_set_text_color(0, 0xffff);
      ili9341_set_cursor(0, 96);
      ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_MULTIPLEX]);
      ili9341_set_cursor(140, 96);
      ili9341_draw_format_string("%s/%u.%03u MHz", Data_8012cdc[10 + r7_4->freq_index],
    		  r7_4->frequency / 1000, r7_4->frequency % 1000);

      draw_signal_error_rate_line(r7_4);
   }
   else
   {
      //loc_8003b08
      ili9341_set_font(&Data_20000044);
      ili9341_set_cursor(0, 96);
      ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_FREQUENCY]);
      ili9341_set_cursor(140, 96);
      ili9341_draw_format_string("%u.%02uMHz",
    		  r7_4->frequency / 100, r7_4->frequency % 100);

      draw_signal_multipath_line(r7_4);
   }
   //loc_8003b5e
   sub_8005198(8, 196, 0x1f, 1); //blue touch area, 1 = black arrow down
   sub_8005198(61, 196, 0x7e0, 0); //x+53 green touch area, 0 = black arrow up
   sub_8005198(114, 196, 0xf800, 2); //red touch area, 2 = black arrow left
   sub_8005198(167, 196, 0xffe0, 3); //yellow touch area, 3 = black arrow right
   sub_8005198(273, 196, 0xffff, 7); //
}


/* 8003bd4 - todo */
void draw_signal_level_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->frequency > 15000)
   {
      if (r7_4->rssi < 20)
      {
         color = 0xf800;
      }
      else if (r7_4->rssi < 30)
      {
         color = 0xffe0;
      }
      else
      {
         color = 0x7e0;
      }
   }
   else
   {
      //loc_8003c14
      if (r7_4->rssi < 25)
      {
         color = 0xf800;
      }
      else if (r7_4->rssi < 35)
      {
         color = 0xffe0;
      }
      else
      {
         color = 0x7e0;
      }
   }
   //loc_8003c3e
   ili9341_draw_box(140, 120, 115, 23, 0xffff);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 120);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_LEVEL]);
   ili9341_set_cursor(140, 120);
   ili9341_draw_format_string("%d dBuV", r7_4->rssi);
   ili9341_draw_box(280, 122, 20, 20, color);
   sub_800581e(280, 122, 20, 20, 0);
}


/* 8003ccc - todo */
void draw_signal_quality_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->frequency > 15000)
   {
	  if (r7_4->snr <= 0)
	  {
		 color = 0xf800;
	  }
	  else if (r7_4->snr < 4)
	  {
		 color = 0xffe0;
	  }
	  else
	  {
		 color = 0x7e0;
	  }
   }
   else
   {
	  //loc_8003d0c
	  if (r7_4->snr < 15)
	  {
		 color = 0xf800;
	  }
	  else if (r7_4->snr < 25)
	  {
		 color = 0xffe0;
	  }
	  else
	  {
		 color = 0x7e0;
	  }
   }
   //loc_8003d36
   ili9341_draw_box(140, 144, 115, 23, 0xffff);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 144);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_SNR]);
   ili9341_set_cursor(140, 144);
   ili9341_draw_format_string("%d dB", r7_4->snr);
   ili9341_draw_box(280, 145, 20, 20, color);
   sub_800581e(280, 145, 20, 20, 0);
}


/* 8003dc4 - todo */
void draw_signal_error_rate_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->fib_error_count < 50)
   {
      color = 0x7e0;
   }
   else if (r7_4->fib_error_count < 1000)
   {
      color = 0xffe0;
   }
   else
   {
      color = 0xf800;
   }

   ili9341_draw_box(140, 168, 115, 23, 0xffff);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 168);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_ERROR_RATE]);
   ili9341_set_cursor(140, 168);
   ili9341_draw_format_string("%u", r7_4->fib_error_count);
   ili9341_draw_box(280, 168, 20, 20, color);
   sub_800581e(280, 168, 20, 20, 0);
}


/* 8003e80 - todo */
void draw_signal_multipath_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->multipath < 5)
   {
	  color = 0x7e0;
   }
   else if (r7_4->multipath < 10)
   {
	  color = 0xffe0;
   }
   else
   {
	  color = 0xf800;
   }

   ili9341_draw_box(140, 168, 115, 23, 0xffff);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 168);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_MULTIPATH]);
   ili9341_set_cursor(140, 168);
   ili9341_draw_format_string("%u", r7_4->multipath);
   ili9341_draw_box(280, 168, 20, 20, color);
   sub_800581e(280, 168, 20, 20, 0);
}


/* 8003f38 - todo */
int signal_information_screen_check_touch_fields(uint16_t a, uint16_t b)
{
   if ((a > 7) && (a < 45) && (b > 195) && (b < 233))
   {
	  ili9341_draw_box(8, 196, 36, 36, 0xce59);
	  sub_800c7e0(100);
	  sub_8005198(8, 196, 0x1f, 1);
	  return 3;
   }

   if ((a > 60) && (a < 98) && (b > 195) && (b < 233))
   {
	  ili9341_draw_box(61, 196, 36, 36, 0xce59);
	  sub_800c7e0(100);
	  sub_8005198(61, 196, 0x7e0, 0);
	  return 2;
   }

   if ((a > 113) && (a < 151) && (b > 195) && (b < 233))
   {
	  ili9341_draw_box(114, 196, 36, 36, 0xce59);
	  sub_800c7e0(100);
	  sub_8005198(114, 196, 0xf800, 2);
	  return 1;
   }

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
	  ili9341_draw_box(167, 196, 36, 36, 0xce59);
	  sub_800c7e0(100);
	  sub_8005198(167, 196, 0xffe0, 3);
	  return 4;
   }

   if ((a > 272) && (a < 311) && (b > 195) && (b < 233))
   {
	  ili9341_draw_box(273, 196, 36, 36, 0xce59);
	  sub_800c7e0(100);
	  sub_8005198(273, 196, 0xffff, 7);
	  return 5;
   }

   return 0;
}


/* 80040a4 - todo */
void draw_sw_information_screen(char* dab, char* fm)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   sub_8003038(TEXT_ID_INFORMATION, &Data_2000004c);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 72);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_PRODUCT]);
   ili9341_set_cursor(140, 72);
   ili9341_draw_format_string("DAB-Radio");
   ili9341_set_cursor(0, 96);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_HARDWARE]);
   ili9341_set_cursor(140, 96);
   ili9341_draw_format_string("L3-02 Rev.1.2");
   ili9341_set_cursor(0, 120);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_SOFTWARE]);
   ili9341_set_cursor(140, 120);
   ili9341_draw_format_string("4.0");
   ili9341_set_cursor(0, 144);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_DAB_FIRMWARE]);
   ili9341_set_cursor(140, 144);
   ili9341_draw_format_string("%s", dab);
   ili9341_set_cursor(0, 168);
   ili9341_draw_format_string("%s", CurrentTextTable[TEXT_ID_FM_FIRMWARE]);
   ili9341_set_cursor(140, 168);
   ili9341_draw_format_string("%s", fm);

   sub_8005198(273, 196, 0xffff, 7);
}


/* 80041e0 - todo */
int sub_80041e0(uint16_t r7_6, uint16_t r7_4)
{
   if ((r7_6 > 272) && (r7_6 < 310) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(273, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(273, 196, 0xffff, 7);
      return 5;
   }

   return 0;
}


/* 8004244 - todo */
void draw_alarm_screen(Alarm_Time* r7_4, uint8_t offOn, uint8_t editFocus)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   sub_8003038(TEXT_ID_ALARM, &Data_2000004c);
   draw_alarm_time_edit(r7_4, offOn, editFocus);
   sub_8005198(8, 196, 0x1f, 1);
   sub_8005198(61, 196, 0x7e0, 0);
   sub_8005198(167, 196, 0xffe0, 6);
   sub_8005198(273, 196, 0xffff, 7);
}


/* 80042d0 - todo */
void draw_alarm_time_edit(Alarm_Time* r7_4, uint8_t offOn, uint8_t editFocus)
{
   uint8_t len;
   char str[20];

   len = sprintf(str, "%2d:%02d %s", r7_4->hours, r7_4->minutes, CurrentTextTable[TEXT_ID_OFF + offOn]);

   ili9341_draw_box(0, 96, 320, 25, 0xffff);
   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0, 0xffff);

   switch (editFocus)
   {
      case 0:
         //loc_8004342
         ili9341_set_cursor(160 - len * Data_2000004c.width / 2, 97);
         ili9341_draw_format_string("__");
         //->loc_80043dc
         break;

      case 1:
         //loc_800436a
         ili9341_set_cursor(160 - len * Data_2000004c.width / 2 + 3 * Data_2000004c.width, 97);
         ili9341_draw_format_string("__");
         //->loc_80043dc
         break;

      case 2:
         //loc_80043a2
         ili9341_set_cursor(160 - len * Data_2000004c.width / 2 + 6 * Data_2000004c.width, 97);
         ili9341_draw_format_string("___");
         //->loc_80043dc
         break;
#if 0
      default:
    	  break;
#endif
   }
   //loc_80043dc
   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(160 - len * Data_2000004c.width / 2, 96);
   ili9341_draw_string(str, len);
}


/* 8004438 - todo */
int alarm_screen_check_touch_fields(uint16_t r7_6, uint16_t r7_4)
{
   if ((r7_6 > 7) && (r7_6 < 45) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(8, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(8, 196, 0x1f, 1);
      return 3;
   }

   if ((r7_6 > 60) && (r7_6 < 98) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(61, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(61, 196, 0x7e0, 0);
      return 2;
   }

   if ((r7_6 > 166) && (r7_6 < 204) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(167, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(167, 196, 0xffe0, 6);
      return 4;
   }

   if ((r7_6 > 272) && (r7_6 < 310) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(273, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(273, 196, 0xffff, 7);
      return 5;
   }

   return 0;
}


/* 8004560 - todo */
void draw_on_off_icon(uint16_t a, uint16_t b)
{
   ili9341_draw_box(a - 16, b - 11, 32, 40, 0xffff);
   ili9341_draw_circle(a, b, 13, 0xf800);
   ili9341_draw_circle(a, b, 9, 0xffff);
   ili9341_draw_box(a - 4, b - 20, 9, 16, 0xffff);
   ili9341_draw_box(a - 1, b - 15, 3, 12, 0xf800);
}


/* 80045f8 - todo */
void draw_standby_screen(RTC_TimeTypeDef r7_c, RTC_DateTypeDef r7_8, Alarm_Time* r7_4, uint8_t r7_3)
{
   // Display Backlight Off
   HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_SET);

   ili9341_fill_screen(0);
   ili9341_draw_hor_line(0, 320, 48, 0xffff);
   ili9341_draw_hor_line(0, 320, 192, 0xffff);
   sub_8001b60(r7_c);
   sub_800465c(r7_8);

   if (r7_3 != 0)
   {
	   draw_alarm_time(r7_4);
   }
}


/* 800465c - todo */
void sub_800465c(RTC_DateTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%d.%d.%d", a.Date, a.Month, a.Year + 2000);

   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0xffff, 0);

   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 72);
   ili9341_draw_string(buf, len);
}


/* 80046d8 - todo */
void draw_alarm_time(Alarm_Time* a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%s %d:%02d", CurrentTextTable[TEXT_ID_ALARM], a->hours, a->minutes);

   ili9341_draw_box(0, 120, 320, 23, 0);
   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0xffff, 0);
   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 120);
   ili9341_draw_string(buf, len);
}


/* 800476c - todo */
void draw_sleep_timer_screen(uint8_t r7_7)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   sub_8003038(TEXT_ID_SLEEP_TIMER, &Data_2000004c);
   draw_sleep_timer_value(r7_7);
   sub_8005198(8, 196, 0x1f, 1);
   sub_8005198(61, 196, 0x7e0, 0);
   sub_8005198(167, 196, 0xffe0, 6);
   sub_8005198(273, 196, 0xffff, 7);
}


/* 80047f0 - todo */
void draw_sleep_timer_value(uint8_t r7_7)
{
   uint8_t r7_17 = (r7_7 != 0)? 1: 0;
   uint8_t len = 0;
   char buf[12];

   len = sprintf(buf, "%2d min %s", r7_7, CurrentTextTable[TEXT_ID_OFF + r7_17]);

   ili9341_draw_box(0, 96, 320, 25, 0xffff);
   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 96);
   ili9341_draw_string(buf, len);
}


/* 8004894 - todo */
int sub_8004894(uint16_t r7_6, uint16_t r7_4)
{
   if ((r7_6 > 7) && (r7_6 < 45) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(8, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(8, 196, 0x1f, 1);
      return 3;
   }

   if ((r7_6 > 60) && (r7_6 < 98) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(61, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(61, 196, 0x7e0, 0);
      return 2;
   }

   if ((r7_6 > 166) && (r7_6 < 204) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(167, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(167, 196, 0xffe0, 6);
      return 4;
   }

   if ((r7_6 > 272) && (r7_6 < 310) && (r7_4 > 195) && (r7_4 < 233))
   {
      ili9341_draw_box(273, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(273, 196, 0xffff, 7);
      return 5;
   }

   return 0;
}


/* 8004be8 - todo */
void sub_8004be8(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
   sub_8005af0(a - 9, b + 9, a + 9, b + 9, a, b - 9, c);
}


/* 8004c4c - todo */
void sub_8004c4c(uint16_t a, uint16_t b, int c, uint16_t d)
{
   sub_8005af0(a - 9, b - 9, a + 9, b - 9, a, b + 9, c);
}


/* 8004cb0 - todo */
void sub_8004cb0(uint16_t a, uint16_t b, int c, uint16_t d)
{
   sub_8005af0(a - 9, b, a + 9, b - 9, a + 9, b + 9, c);
}


/* 8004d14 - todo */
void sub_8004d14(uint16_t a, uint16_t b, int c, uint16_t d)
{
   sub_8005af0(a - 9, b - 9, a - 9, b + 9, a + 9, b, c);
}


/* 8004d78 - todo */
void sub_8004d78(uint16_t r7_6, uint16_t r7_4, uint16_t color, uint16_t d)
{
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 9, color); //      *--------+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 10, color); //    *---------+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 8, color); //       *-------+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4, color); //                   *
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 1, color); //              *+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 1, color); //               +*
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 9, color); //               +--------*
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 8, color); //               +-------*
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 10, color); //              +---------*
}


/* 8004e74 - todo */
void sub_8004e74(uint16_t r7_6, uint16_t r7_4, int r7_2, uint16_t r7)
{
   uint16_t r7_e;
   char r7_8[] = "FAV"; //0x564146;

   ili9341_set_text_color(r7_2, r7);
   ili9341_set_font(&Data_20000044);
   r7_e = sub_8001224(r7_8);
   ili9341_set_cursor(r7_6 - (r7_e * Data_20000044.width) / 2/*??*/, r7_4 - Data_20000044.height / 2);
   ili9341_draw_string(r7_8, r7_e);
   ili9341_draw_box(r7_6 + 18, r7_4 - 18, 4, 36, 0xffff);
}


void sub_8004f24(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


/* 8004fc4 - todo */
void sub_8004fc4(uint16_t r7_6, uint16_t r7_4, int r7_2, uint16_t r7)
{
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 9, r7_2);
   ili9341_draw_vert_line(r7_6 + 9, r7_4 - 9, r7_4 + 9, r7_2);
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 9, r7_2);
   sub_8005af0(r7_6 - 9, r7_4 - 9, r7_6 - 5, r7_4 - 11, r7_6 - 5, r7_4 - 7, r7_2);
}


void sub_8005074(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


/* 8005198 - todo */
void sub_8005198(uint16_t x, uint16_t y, uint16_t color, uint8_t r7_1)
{
   ili9341_draw_box(x, y, 36, 36, color);

   (Funcs_20000000)[r7_1](x + 18, y + 18, 0, color);

   ili9341_draw_rect(x, y, 36, 36, 0);
}


/* 8006254 - todo */
uint8_t sub_8006254(uint8_t r7_7, uint8_t r7_6, uint8_t r7_5, uint8_t r7_4, uint8_t r7_18, uint8_t r7_1c)
{
   uint8_t r7_f = 0;

   if (r7_1c != 0)
   {
      r7_f |= 0x04;
   }

   if (r7_18 != 0)
   {
      r7_f |= 0x08;
   }

   if (r7_4 != 0)
   {
      r7_f |= 0x10;
   }

   if (r7_5 != 0)
   {
      r7_f |= 0x20;
   }

   if (r7_6 != 0)
   {
      r7_f |= 0x40;
   }

   if (r7_7 != 0)
   {
      r7_f |= 0x80;
   }

   return r7_f;
}


/* 80062d8 - todo */
void ili9341_configure_gpio(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_GPIOE_CLK_ENABLE();

   GPIO_InitStruct.Pin = 0xcfb3; //1100 1111 1011 0011 = FSMC_D1, FSMC_D0, FSMC_A16, FSMC_D15 ... FSMC_D13, FSMC_D3, FSMC_D2
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = 0xff80; //1111 1111 1000 0000 = FSMC_D12 ... FSMC_D4
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = GPIO_PIN_1;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


/* 80063a4 - todo */
void ili9341_configure_fsmc(void)
{
   SRAM_HandleTypeDef hsram;
   FSMC_NORSRAM_TimingTypeDef Timing = {0};

   hsram.Instance = FSMC_NORSRAM_DEVICE;
   hsram.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

   hsram.Init.NSBank = FSMC_NORSRAM_BANK1;
   hsram.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
   hsram.Init.MemoryType = FSMC_MEMORY_TYPE_NOR;
   hsram.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
   hsram.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
   hsram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
   hsram.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
   hsram.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
   hsram.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
   hsram.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
   hsram.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
   hsram.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
   hsram.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;

   Timing.AddressSetupTime = 3;
   Timing.AddressHoldTime = 0;
   Timing.DataSetupTime = 6;
   Timing.BusTurnAroundDuration = 0;
   Timing.CLKDivision = 1;
   Timing.DataLatency = 0;
   Timing.AccessMode = FSMC_ACCESS_MODE_B;

   HAL_SRAM_Init(&hsram, &Timing, NULL);
}


/* 8006434 - todo */
int touch_init(void)
{
   uint8_t r7_7 = 1;

   TouchEvent.bData_0 = 1;
   TouchEvent.wData_2 = 0;
   TouchEvent.wData_4 = 0;

   Data_20000b90.Data_0 = 0;
   Data_20000b90.wData_4 = 0x8000;
   Data_20000b90.wData_6 = 0x8000;
   Data_20000b90.wData_8 = 0;
   Data_20000b90.wData_10 = 0;
   Data_20000b90.Data_12 = 0x3db50005;
   Data_20000b90.Data_16 = 0x3ada36b7;
   Data_20000b90.Data_20 = 0xc1f9d490;
   Data_20000b90.Data_24 = 0xba638759;
   Data_20000b90.Data_28 = 0xbd878821;
   Data_20000b90.Data_32 = 0x437f9706;
   Data_20000b90.wData_36 = 0x869;
   Data_20000b90.wData_38 = 0x23a;
   Data_20000b90.wData_40 = 0x2a5;
   Data_20000b90.wData_42 = 0x7f8;
   Data_20000b90.wData_44 = 0xddb;
   Data_20000b90.wData_46 = 0xd7d;

   touch_configure_gpio();
   touch_read_xy(1);

   if ((Data_20000b90.wData_4 < 0x1000) &&
		   (Data_20000b90.wData_6 < 0x1000))
   {
      r7_7 = 0;

      sub_8006618();
      sub_8006624();
   }

   return r7_7;
}


/* 800651c - todo */
void touch_configure_gpio(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();

   // CLK
   GPIO_InitStruct.Pin = GPIO_PIN_12;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   // MOSI
   GPIO_InitStruct.Pin = GPIO_PIN_7;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   // MISO
   GPIO_InitStruct.Pin = GPIO_PIN_6;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   // CS
   GPIO_InitStruct.Pin = GPIO_PIN_7;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   // IRQ
   GPIO_InitStruct.Pin = GPIO_PIN_6;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   touch_toggle_cs_line(1);
   touch_toggle_clk_line(0);
   touch_toggle_mosi_line(0);
}


/* 8006618 - complete */
void sub_8006618(void)
{
   /* empty */
}


/* 8006624 - complete */
void sub_8006624(void)
{
   /* empty */
}


/* 8006630 - todo */
void touch_poll(void)
{
   uint8_t r7_7 = 1;

   if (0 == touch_read_irq())
   {
      r7_7 = 0;
   }
   else
   {
      r7_7 = 1;
   }

   if (r7_7 == 0)
   {
      touch_read_xy(1);
      sub_8006730();
      if ((0 == sub_8006838()) && (TouchEvent.bData_0 != 0))
      {
         TouchEvent.bData_0 = 0;
      }
   }
   else if (TouchEvent.bData_0 != 0)
   {
      TouchEvent.bData_0 = 1;
   }
}


/* 8006694 - todo */
void touch_read_xy(uint8_t a)
{
   uint16_t i;
   uint32_t x = 0;
   uint32_t y = 0;
   uint16_t data;

   if (a == 0)
   {
      Data_20000b90.wData_4 = touch_spi_transfer(0x900000);
      Data_20000b90.wData_6 = touch_spi_transfer(0xd00000);
   }
   else
   {
      touch_spi_transfer(0x900000);

      for (i = 0; i < 4; i++)
      {
         //loc_80066dc
         data = touch_spi_transfer(0x900000);
         x += data;

         data = touch_spi_transfer(0xd00000);
         y += data;
      }

      Data_20000b90.wData_4 = x / 4;
      Data_20000b90.wData_6 = y / 4;
   }
}


/* 8006730 - todo */
void sub_8006730(void)
{
   int r7_24;
   int r7_20;
   int r7_1c = sub_80013a0(Data_20000b90.wData_4);
   int r7_18 = sub_80013a0(Data_20000b90.wData_6);
   int r7_14 = sub_8001450(r7_1c, Data_20000b90.Data_12);
   int r7_10 = sub_80016f0(r7_14);
   int r7_c = sub_8001450(r7_18, Data_20000b90.Data_16);
   int r7_8 = sub_80016f0(r7_c);
   int r7_4 = sub_80016f0(Data_20000b90.Data_20);
   r7_24 = r7_10 + r7_8 + r7_4;

   r7_14 = sub_8001450(r7_1c, Data_20000b90.Data_24);
   r7_10 = sub_80016f0(r7_14);
   r7_c = sub_8001450(r7_18, Data_20000b90.Data_28);
   r7_8 = sub_80016f0(r7_c);
   r7_4 = sub_80016f0(Data_20000b90.Data_32);
   r7_20 = r7_10 + r7_8 + r7_4;

   if (r7_24 >= 320)
   {
      r7_24 = 319;
   }

   if (r7_24 < 0)
   {
      r7_24 = 0;
   }

   if (r7_20 > 239)
   {
      r7_20 = 239;
   }

   if (r7_20 < 0)
   {
      r7_20 = 0;
   }

   Data_20000b90.wData_8 = r7_24;
   Data_20000b90.wData_10 = r7_20;
}


/* 8006838 - todo */
uint8_t sub_8006838(void)
{
   uint8_t r7_7 = 0;
   uint16_t r7_4;

   if (Data_20000b90.wData_8 >= wData_200001ec)
   {
      r7_4 = Data_20000b90.wData_8 - wData_200001ec;
   }
   else
   {
      r7_4 = wData_200001ec - Data_20000b90.wData_8;
   }

   if (r7_4 > 30)
   {
      r7_7 = 1;
   }

   if (Data_20000b90.wData_10 >= wData_200001ee)
   {
      r7_4 = Data_20000b90.wData_10 - wData_200001ee;
   }
   else
   {
      r7_4 = wData_200001ee - Data_20000b90.wData_10;
   }

   if (r7_4 > 30)
   {
      r7_7 = 1;
   }

   wData_200001ec = Data_20000b90.wData_8;
   wData_200001ee = Data_20000b90.wData_10;

   if (r7_7 == 0)
   {
      TouchEvent.wData_2 = Data_20000b90.wData_8;
      TouchEvent.wData_4 = Data_20000b90.wData_10;
   }

   return r7_7;
}


/* 80068e4 - todo */
void touch_toggle_clk_line(uint8_t a)
{
   if (a == 1)
   {
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
   }
   else
   {
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
   }
}


/* 800691c - todo */
void touch_toggle_cs_line(uint8_t a)
{
   if (a == 1)
   {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
   }
   else
   {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
   }
}


/* 8006950 - todo */
void touch_toggle_mosi_line(uint8_t a)
{
   if (a == 1)
   {
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
   }
   else
   {
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
   }
}


/* 8006984 - todo */
int touch_read_miso_line(void)
{
   return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
}


/* 800699c - todo */
int touch_read_irq(void)
{
   return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
}


/* 80069b4 - todo */
uint16_t touch_spi_transfer(int cmd)
{
   uint16_t i;
   uint32_t mosi_bits = 0x800000;
   uint16_t miso_bits = 0x800;
   uint16_t data = 0;

   sub_8006a70(100);
   touch_toggle_cs_line(0);
   sub_8006a70(500);

   for (i = 0; i < 24; i++)
   {
      if ((cmd & mosi_bits) == 0)
      {
         touch_toggle_mosi_line(0);
      }
      else
      {
         touch_toggle_mosi_line(1);
      }

      touch_toggle_clk_line(1);

      if ((i > 8) && (i < 21))
      {
         if (0 != touch_read_miso_line())
         {
            data |= miso_bits;
         }

         miso_bits >>= 1;
      }

      sub_8006a70(500);
      touch_toggle_clk_line(0);
      sub_8006a70(500);

      mosi_bits >>= 1;
   }

   sub_8006a70(500);
   touch_toggle_cs_line(1);
   sub_8006a70(500);

   return data;
}


/* 8006a70 - todo */
void sub_8006a70(int a)
{
	while (a-- != 0)
	{
		/* delay */
	}
}


/* 8007415 - todo */
int sub_8007415(void)
{

}


/* 80075e9 - todo */
int sub_80075e9(void)
{

}


/* 80088cc - todo */
int sub_80088cc(void)
{

}


/* 800c33c - todo */
int menu_automatic_search(void)
{
   uint8_t r7_17;
   uint8_t r7_16;
   uint8_t r7_15 = 1;
   uint8_t r7_14 = 0;
   struct
   {
	   int fill[4];
   } r7_4;

   r7_17 = 0;
   r7_16 = 0;

   TouchEvent.bData_0 = 1;

   sub_800b5e0();

   draw_automatic_search_screen(ChannelList, 0, bChannelCount, 0, 41, &r7_4, 0);

   si46xx_mute(1);

   si46xx_start_dab(bCurrentVolume);

   if (0 != si46xx_dab_search(&r7_14))
   {
      r7_16 &= ~1;
   }
   else
   {
      //loc_800c3a0
      r7_16 |= 1;
      r7_17 += r7_14;
   }
   //loc_800c3b0
   draw_automatic_search_screen(ChannelList, 0, bChannelCount, 0, 2040/*10790-8750*/, &r7_4, 8750);

   si46xx_start_fm(bCurrentVolume);

   si46xx_mute(1);

   if (0 != si46xx_fm_search(&r7_14))
   {
      r7_16 &= ~2;
   }
   else
   {
      //loc_800c3f8
      r7_16 |= 2;
      r7_17 += r7_14;
   }
   //loc_800c408
   si46xx_mute(0);

   if (r7_16 != 0)
   {
      sub_800c460();
      persist_write(ChannelList, FavouriteList, &currentAlarmTime, &Data_20000a50);
   }
   else
   {
      //loc_800c426
      sub_800b2ac(&currentAlarmTime, &Data_20000a50);
   }
   //loc_800c42e
   bCurrentChannelNumber = 0;

   return r7_15;
}


/* 800c460 - todo */
void sub_800c460(void)
{
   uint8_t r7_7 = 0;
   uint8_t r7_6 = bFavouriteCount;

   for (r7_7 = 0; r7_7 < r7_6; r7_7++)
   {
      if (0xff == sub_800b494(&FavouriteList[r7_7]))
      {
         sub_800b53c(r7_7);
      }
   }
}


