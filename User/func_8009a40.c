
#include <string.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"

extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi2;

extern void Error_Handler(void);
int sub_800b2ac(void* a, void* b);

Draw_Icon g_arIcons[] = //20000000 (80193f8)
{
   draw_arrow_up, //ICON_UP
   draw_arrow_down, //ICON_DOWN
   draw_arrow_left, //ICON_LEFT
   draw_arrow_right, //ICON_RIGHT
   draw_icon_menu, //ICON_MENU
   sub_8004e74,
   sub_8004f24,
   draw_icon_back, //ICON_BACK
   sub_8005074
};


/* 800173c - todo */
void draw_main_screen(RTC_TimeTypeDef r7_c, void* r7_8, uint8_t r7_7, void* r7, uint8_t r7_18, uint8_t channel_nr, Tuner_Values* g, uint16_t h)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);

   draw_channel_name(r7_8);
   draw_radio_text(r7, r7_18);
   draw_channel_number_box(12, 6, channel_nr, h & MAIN_LOOP_EVENT_FAV_ACTIVE);
   draw_signal_strength_bars(142, 42, &g->rssi);

   draw_volume_bar(r7_7);

   draw_foreground_clock(r7_c);

   draw_on_off_icon(291, 214);

   draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
   draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
   draw_36x36(114, 196, COLOR_RED, ICON_LEFT);
   draw_36x36(167, 196, COLOR_YELLOW, ICON_RIGHT);
   draw_36x36(79, 6, COLOR_ORANGE, ICON_MENU);
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
      lcdSetTextFont(&Data_2000004c);
      lcdFillRect(0, 63, 320, 24, COLOR_WHITE);
      lcdSetTextColor(0, COLOR_WHITE);
      len = sub_800c88c(a, 16);
      lcdSetCursor(160 - (len * Data_2000004c.Width) / 2, 63);
      ili9341_draw_string(a, len);
   }
   else
   {
      len = sub_8001224(CurrentTextTable[TEXT_ID_NO_CHANNEL]);
      lcdSetTextFont(&Data_2000004c);
      lcdSetTextColor(0, COLOR_WHITE);
      lcdSetCursor(160 - (len * Data_2000004c.Width) / 2, 63);
      lcdPrintf(CurrentTextTable[TEXT_ID_NO_CHANNEL]);
   }
}


/* 8002cac - todo */
void sub_8002cac(uint16_t firstTextId, uint8_t lines, uint8_t focus)
{
   uint8_t i;
   uint8_t r7_e = (focus > 5)? focus - 2: 0;
   uint8_t r7_d = (lines < 5)? lines + 1: 5;

   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);

   for (i = 0; (i < r7_d) && ((r7_e + i) < lines); )
   {
      //loc_8002cf4
      if ((r7_e + i) == focus)
      {
         lcdSetTextColor(COLOR_WHITE, COLOR_BLACK);
      }
      else
      {
         lcdSetTextColor(0, COLOR_WHITE);
      }

      lcdSetCursor(0, 72 + 24 * i);
      lcdPrintf(CurrentTextTable[firstTextId + i]);
      i++;
   }
}


/* 8002d70 - todo */
void sub_8002d70(uint16_t textId, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_screen_caption(textId, &Data_2000004c);
   sub_8002cac(r7_4, r7_3, r7_2);
   draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
   draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
   draw_36x36(167, 196, COLOR_YELLOW, 6);
   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
}


/* 8002e98 - todo */
uint8_t sub_8002e98(uint16_t a, uint16_t b)
{
   if ((a > 7) && (a < 45) && (b > 195) && (b < 233))
   {
      lcdFillRect(8, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
      return 3;
   }

   if ((a > 60) && (a < 98) && (b > 195) && (b < 233))
   {
      lcdFillRect(61, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
      return 2;
   }

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
      lcdFillRect(167, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(167, 196, COLOR_YELLOW, 6);
      return 4;
   }

   if ((a > 272) && (a < 311) && (b > 195) && (b < 233))
   {
      lcdFillRect(273, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
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
void draw_screen_caption(uint16_t textId, sFONT* font)
{
   uint16_t len;

   lcdSetTextFont(font);
   lcdFillRect(0, 23, 320, 24, COLOR_WHITE);
   lcdSetTextColor(0, COLOR_WHITE);
   len = sub_8001224(CurrentTextTable[textId]);
   lcdSetCursor(160 - (len * font->Width) / 2, 24);
   lcdPrintf(CurrentTextTable[textId]);
}


/* 80039b0 - todo */
void draw_signal_information_screen(Tuner_Channel* r7_c, uint8_t r7_b, Tuner_Values* r7_4)
{
   extern const char* Data_8012cdc[];

   uint8_t r7_17;

   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_screen_caption(TEXT_ID_SIGNAL_INFORMATION, &Data_2000004c);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 72);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_CHANNEL]);
   lcdSetCursor(140, 72);
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
      lcdSetTextFont(&Data_20000044);
      lcdSetTextColor(0, COLOR_WHITE);
      lcdSetCursor(0, 96);
      lcdPrintf("%s", CurrentTextTable[TEXT_ID_MULTIPLEX]);
      lcdSetCursor(140, 96);
      lcdPrintf("%s/%u.%03u MHz", Data_8012cdc[10 + r7_4->freq_index],
    		  r7_4->frequency / 1000, r7_4->frequency % 1000);

      draw_signal_error_rate_line(r7_4);
   }
   else
   {
      //loc_8003b08
      lcdSetTextFont(&Data_20000044);
      lcdSetCursor(0, 96);
      lcdPrintf("%s", CurrentTextTable[TEXT_ID_FREQUENCY]);
      lcdSetCursor(140, 96);
      lcdPrintf("%u.%02uMHz",
    		  r7_4->frequency / 100, r7_4->frequency % 100);

      draw_signal_multipath_line(r7_4);
   }
   //loc_8003b5e
   draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN); //blue touch area, 1 = black arrow down
   draw_36x36(61, 196, COLOR_GREEN, ICON_UP); //x+53 green touch area, 0 = black arrow up
   draw_36x36(114, 196, COLOR_RED, ICON_LEFT); //red touch area, 2 = black arrow left
   draw_36x36(167, 196, COLOR_YELLOW, ICON_RIGHT); //yellow touch area, 3 = black arrow right
   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
}


/* 8003bd4 - todo */
void draw_signal_level_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->frequency > 15000)
   {
      if (r7_4->rssi < 20)
      {
         color = COLOR_RED;
      }
      else if (r7_4->rssi < 30)
      {
         color = COLOR_YELLOW;
      }
      else
      {
         color = COLOR_GREEN;
      }
   }
   else
   {
      //loc_8003c14
      if (r7_4->rssi < 25)
      {
         color = COLOR_RED;
      }
      else if (r7_4->rssi < 35)
      {
         color = COLOR_YELLOW;
      }
      else
      {
         color = COLOR_GREEN;
      }
   }
   //loc_8003c3e
   lcdFillRect(140, 120, 115, 23, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 120);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_LEVEL]);
   lcdSetCursor(140, 120);
   lcdPrintf("%d dBuV", r7_4->rssi);
   lcdFillRect(280, 122, 20, 20, color);
   lcdDrawRect(280, 122, 20, 20, COLOR_BLACK);
}


/* 8003ccc - todo */
void draw_signal_quality_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->frequency > 15000)
   {
	  if (r7_4->snr <= 0)
	  {
		 color = COLOR_RED;
	  }
	  else if (r7_4->snr < 4)
	  {
		 color = COLOR_YELLOW;
	  }
	  else
	  {
		 color = COLOR_GREEN;
	  }
   }
   else
   {
	  //loc_8003d0c
	  if (r7_4->snr < 15)
	  {
		 color = COLOR_RED;
	  }
	  else if (r7_4->snr < 25)
	  {
		 color = COLOR_YELLOW;
	  }
	  else
	  {
		 color = COLOR_GREEN;
	  }
   }
   //loc_8003d36
   lcdFillRect(140, 144, 115, 23, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 144);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_SNR]);
   lcdSetCursor(140, 144);
   lcdPrintf("%d dB", r7_4->snr);
   lcdFillRect(280, 145, 20, 20, color);
   lcdDrawRect(280, 145, 20, 20, COLOR_BLACK);
}


/* 8003dc4 - todo */
void draw_signal_error_rate_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->fib_error_count < 50)
   {
      color = COLOR_GREEN;
   }
   else if (r7_4->fib_error_count < 1000)
   {
      color = COLOR_YELLOW;
   }
   else
   {
      color = COLOR_RED;
   }

   lcdFillRect(140, 168, 115, 23, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 168);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_ERROR_RATE]);
   lcdSetCursor(140, 168);
   lcdPrintf("%u", r7_4->fib_error_count);
   lcdFillRect(280, 168, 20, 20, color);
   lcdDrawRect(280, 168, 20, 20, COLOR_BLACK);
}


/* 8003e80 - todo */
void draw_signal_multipath_line(Tuner_Values* r7_4)
{
   uint16_t color;

   if (r7_4->multipath < 5)
   {
	  color = COLOR_GREEN;
   }
   else if (r7_4->multipath < 10)
   {
	  color = COLOR_YELLOW;
   }
   else
   {
	  color = COLOR_RED;
   }

   lcdFillRect(140, 168, 115, 23, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 168);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_MULTIPATH]);
   lcdSetCursor(140, 168);
   lcdPrintf("%u", r7_4->multipath);
   lcdFillRect(280, 168, 20, 20, color);
   lcdDrawRect(280, 168, 20, 20, COLOR_BLACK);
}


/* 8003f38 - todo */
int signal_information_screen_check_touch_fields(uint16_t a, uint16_t b)
{
   if ((a > 7) && (a < 45) && (b > 195) && (b < 233))
   {
	  lcdFillRect(8, 196, 36, 36, COLOR_GRAY_200);
	  main_delay(100);
	  draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
	  return 3;
   }

   if ((a > 60) && (a < 98) && (b > 195) && (b < 233))
   {
	  lcdFillRect(61, 196, 36, 36, COLOR_GRAY_200);
	  main_delay(100);
	  draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
	  return 2;
   }

   if ((a > 113) && (a < 151) && (b > 195) && (b < 233))
   {
	  lcdFillRect(114, 196, 36, 36, COLOR_GRAY_200);
	  main_delay(100);
	  draw_36x36(114, 196, COLOR_RED, ICON_LEFT);
	  return 1;
   }

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
	  lcdFillRect(167, 196, 36, 36, COLOR_GRAY_200);
	  main_delay(100);
	  draw_36x36(167, 196, COLOR_YELLOW, ICON_RIGHT);
	  return 4;
   }

   if ((a > 272) && (a < 311) && (b > 195) && (b < 233))
   {
	  lcdFillRect(273, 196, 36, 36, COLOR_GRAY_200);
	  main_delay(100);
	  draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
	  return 5;
   }

   return 0;
}


/* 80040a4 - todo */
void draw_sw_information_screen(char* dab, char* fm)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_screen_caption(TEXT_ID_INFORMATION, &Data_2000004c);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 72);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_PRODUCT]);
   lcdSetCursor(140, 72);
   lcdPrintf("DAB-Radio");
   lcdSetCursor(0, 96);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_HARDWARE]);
   lcdSetCursor(140, 96);
   lcdPrintf("L3-02 Rev.1.2");
   lcdSetCursor(0, 120);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_SOFTWARE]);
   lcdSetCursor(140, 120);
   lcdPrintf("4.0");
   lcdSetCursor(0, 144);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_DAB_FIRMWARE]);
   lcdSetCursor(140, 144);
   lcdPrintf("%s", dab);
   lcdSetCursor(0, 168);
   lcdPrintf("%s", CurrentTextTable[TEXT_ID_FM_FIRMWARE]);
   lcdSetCursor(140, 168);
   lcdPrintf("%s", fm);

   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
}


/* 80041e0 - todo */
int sub_80041e0(uint16_t r7_6, uint16_t r7_4)
{
   if ((r7_6 > 272) && (r7_6 < 310) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(273, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
      return 5;
   }

   return 0;
}


/* 8004244 - todo */
void draw_alarm_screen(Alarm_Time* r7_4, uint8_t offOn, uint8_t editFocus)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_screen_caption(TEXT_ID_ALARM, &Data_2000004c);
   draw_alarm_time_edit(r7_4, offOn, editFocus);
   draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
   draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
   draw_36x36(167, 196, COLOR_YELLOW, 6);
   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
}


/* 80042d0 - todo */
void draw_alarm_time_edit(Alarm_Time* r7_4, uint8_t offOn, uint8_t editFocus)
{
   uint8_t len;
   char str[20];

   len = sprintf(str, "%2d:%02d %s", r7_4->hours, r7_4->minutes, CurrentTextTable[TEXT_ID_OFF + offOn]);

   lcdFillRect(0, 96, 320, 25, COLOR_WHITE);
   lcdSetTextFont(&Data_2000004c);
   lcdSetTextColor(0, COLOR_WHITE);

   switch (editFocus)
   {
      case 0:
         //loc_8004342
         lcdSetCursor(160 - len * Data_2000004c.Width / 2, 97);
         lcdPrintf("__");
         //->loc_80043dc
         break;

      case 1:
         //loc_800436a
         lcdSetCursor(160 - len * Data_2000004c.Width / 2 + 3 * Data_2000004c.Width, 97);
         lcdPrintf("__");
         //->loc_80043dc
         break;

      case 2:
         //loc_80043a2
         lcdSetCursor(160 - len * Data_2000004c.Width / 2 + 6 * Data_2000004c.Width, 97);
         lcdPrintf("___");
         //->loc_80043dc
         break;
#if 0
      default:
    	  break;
#endif
   }
   //loc_80043dc
   lcdSetTextFont(&Data_2000004c);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(160 - len * Data_2000004c.Width / 2, 96);
   ili9341_draw_string(str, len);
}


/* 8004438 - todo */
int alarm_screen_check_touch_fields(uint16_t r7_6, uint16_t r7_4)
{
   if ((r7_6 > 7) && (r7_6 < 45) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(8, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
      return 3;
   }

   if ((r7_6 > 60) && (r7_6 < 98) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(61, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
      return 2;
   }

   if ((r7_6 > 166) && (r7_6 < 204) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(167, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(167, 196, COLOR_YELLOW, 6);
      return 4;
   }

   if ((r7_6 > 272) && (r7_6 < 310) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(273, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
      return 5;
   }

   return 0;
}


/* 8004560 - todo */
void draw_on_off_icon(uint16_t a, uint16_t b)
{
   lcdFillRect(a - 16, b - 11, 32, 40, COLOR_WHITE);
   lcdFillCircle(a, b, 13, COLOR_RED);
   lcdFillCircle(a, b, 9, COLOR_WHITE);
   lcdFillRect(a - 4, b - 20, 9, 16, COLOR_WHITE);
   lcdFillRect(a - 1, b - 15, 3, 12, COLOR_RED);
}


/* 80045f8 - todo */
void draw_standby_screen(RTC_TimeTypeDef r7_c, RTC_DateTypeDef r7_8, Alarm_Time* r7_4, uint8_t r7_3)
{
   // Display Backlight Off
   HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_SET);

   lcdFillRGB(0);
   lcdDrawHLine(0, 320, 48, COLOR_WHITE);
   lcdDrawHLine(0, 320, 192, COLOR_WHITE);
   draw_background_clock(r7_c);
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

   lcdSetTextFont(&Data_2000004c);
   lcdSetTextColor(COLOR_WHITE, COLOR_BLACK);

   lcdSetCursor(160 - (len * Data_2000004c.Width) / 2, 72);
   ili9341_draw_string(buf, len);
}


/* 80046d8 - todo */
void draw_alarm_time(Alarm_Time* a)
{
   char buf[15];
   uint8_t len = 0;

   len = sprintf(buf, "%s %d:%02d", CurrentTextTable[TEXT_ID_ALARM], a->hours, a->minutes);

   lcdFillRect(0, 120, 320, 23, COLOR_BLACK);
   lcdSetTextFont(&Data_2000004c);
   lcdSetTextColor(COLOR_WHITE, COLOR_BLACK);
   lcdSetCursor(160 - (len * Data_2000004c.Width) / 2, 120);
   ili9341_draw_string(buf, len);
}


/* 800476c - todo */
void draw_sleep_timer_screen(uint8_t r7_7)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_screen_caption(TEXT_ID_SLEEP_TIMER, &Data_2000004c);
   draw_sleep_timer_value(r7_7);
   draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
   draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
   draw_36x36(167, 196, COLOR_YELLOW, 6);
   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
}


/* 80047f0 - todo */
void draw_sleep_timer_value(uint8_t r7_7)
{
   uint8_t r7_17 = (r7_7 != 0)? 1: 0;
   uint8_t len = 0;
   char buf[12];

   len = sprintf(buf, "%2d min %s", r7_7, CurrentTextTable[TEXT_ID_OFF + r7_17]);

   lcdFillRect(0, 96, 320, 25, COLOR_WHITE);
   lcdSetTextFont(&Data_2000004c);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(160 - (len * Data_2000004c.Width) / 2, 96);
   ili9341_draw_string(buf, len);
}


/* 8004894 - todo */
int sub_8004894(uint16_t r7_6, uint16_t r7_4)
{
   if ((r7_6 > 7) && (r7_6 < 45) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(8, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
      return 3;
   }

   if ((r7_6 > 60) && (r7_6 < 98) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(61, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
      return 2;
   }

   if ((r7_6 > 166) && (r7_6 < 204) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(167, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(167, 196, COLOR_YELLOW, 6);
      return 4;
   }

   if ((r7_6 > 272) && (r7_6 < 310) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(273, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
      return 5;
   }

   return 0;
}


/* 8004be8 - todo */
void draw_arrow_up(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
   lcdFillTriangle(a - 9, b + 9, a + 9, b + 9, a, b - 9, c);
}


/* 8004c4c - todo */
void draw_arrow_down(uint16_t a, uint16_t b, int c, uint16_t d)
{
   lcdFillTriangle(a - 9, b - 9, a + 9, b - 9, a, b + 9, c);
}


/* 8004cb0 - todo */
void draw_arrow_left(uint16_t a, uint16_t b, int c, uint16_t d)
{
   lcdFillTriangle(a - 9, b, a + 9, b - 9, a + 9, b + 9, c);
}


/* 8004d14 - todo */
void draw_arrow_right(uint16_t a, uint16_t b, int c, uint16_t d)
{
   lcdFillTriangle(a - 9, b - 9, a - 9, b + 9, a + 9, b, c);
}


/* 8004d78 - todo */
void draw_icon_menu(uint16_t r7_6, uint16_t r7_4, uint16_t color, uint16_t d)
{
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 - 9, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 - 10, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 - 8, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 - 1, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 + 1, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 + 9, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 + 8, color);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 + 10, color);
}


/* 8004e74 - todo */
void sub_8004e74(uint16_t r7_6, uint16_t r7_4, int r7_2, uint16_t r7)
{
   uint16_t r7_e;
   char r7_8[] = "FAV"; //0x564146;

   lcdSetTextColor(r7_2, r7);
   lcdSetTextFont(&Data_20000044);
   r7_e = sub_8001224(r7_8);
   lcdSetCursor(r7_6 - (r7_e * Data_20000044.Width) / 2/*??*/, r7_4 - Data_20000044.Height / 2);
   ili9341_draw_string(r7_8, r7_e);
   lcdFillRect(r7_6 + 18, r7_4 - 18, 4, 36, COLOR_WHITE);
}


void sub_8004f24(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


/* 8004fc4 - todo */
void draw_icon_back(uint16_t r7_6, uint16_t r7_4, int r7_2, uint16_t r7)
{
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 + 9, r7_2);
   lcdDrawVLine(r7_6 + 9, r7_4 - 9, r7_4 + 9, r7_2);
   lcdDrawHLine(r7_6 - 9, r7_6 + 9, r7_4 - 9, r7_2);
   lcdFillTriangle(r7_6 - 9, r7_4 - 9, r7_6 - 5, r7_4 - 11, r7_6 - 5, r7_4 - 7, r7_2);
}


void sub_8005074(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


/* 8005198 - todo */
void draw_36x36(uint16_t x, uint16_t y, uint16_t color, uint8_t r7_1)
{
   lcdFillRect(x, y, 36, 36, color);

   (g_arIcons)[r7_1](x + 18, y + 18, 0, color);

   lcdDrawRect(x, y, 36, 36, COLOR_BLACK);
}


/* 8007414 - todo */
int sub_8007414(void)
{
   typedef int (*funcs)(void);
   funcs r7[] = //8012c80
   {
	  sub_80078c4, //
	  sub_8007b48, //
   };

   uint8_t r7_9;
   uint8_t r7_a;

   uint8_t r7_f = 0;
   uint8_t r7_e = 1;
   uint8_t r7_d = 0;
   uint8_t r7_c = 0;
   uint8_t r7_b = 0;

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   sub_8002d70(24, 26, 2, r7_c);

   //->loc_80075c6
   while (r7_e != 0)
   {
	   //loc_8007454
	   r7_a = 0;
	   if (KeyEvent.bData_0 == 0)
	   {
		   r7_a = KeyEvent.bData_1;
		   KeyEvent.bData_0 = 1;
	   }
	   //loc_800746c
	   r7_9 = 0;
	   if (TouchEvent.bData_0 == 0)
	   {
		   r7_9 = sub_8002e98(TouchEvent.wData_2, TouchEvent.wData_4);
	   }
	   //loc_800748c
	   if ((r7_9 | r7_a) != 0)
	   {
		   switch (r7_9 | r7_a)
		   {
		   default:
			   //loc_8007554
			   break;
		   }
		   //loc_800755e
		   TouchEvent.bData_0 = 1;
		   KeyEvent.bData_0 = 1;
	   }
	   //loc_800756a
	   if (r7_d != 0)
	   {
		   r7_d = 0;

	       if (0 != r7[r7_c]())
	       {
	            wMainloopEvents |= 0x02;
	            r7_e = 0;
	            r7_f = 1;
	            //->loc_80075ae
	       }
	       else
	       {
	    	   //loc_80075a2
	    	   sub_8002d70(24, 26, 2, r7_c);
	       }
	   }
	   //loc_80075ae
	   if (r7_c != r7_b)
	   {
		   r7_b = r7_c;

		   sub_8002cac(26, 2, r7_c);
	   }
	   //loc_80075c6
   }
   //80075ce
   return r7_f;
}


/* 80075e9 - todo */
int sub_80075e9(void)
{

}


/* 80078c4 - todo */
int sub_80078c4(void)
{

}


/* 8007b48 - todo */
int sub_8007b48(void)
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

   channel_list_clear();

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
      persist_write(ChannelList, FavouriteList, &currentAlarmTime, &UserSettings);
   }
   else
   {
      //loc_800c426
      sub_800b2ac(&currentAlarmTime, &UserSettings);
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


