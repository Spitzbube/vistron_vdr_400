
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"


/* 8001802 - todo */
uint8_t main_screen_check_touch_fields(uint16_t a, uint16_t b)
{
   if ((a > 7) && (a < 45) && (b > 195) && (b < 233))
   {
      //blue
      lcdFillRect(8, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
      return 3;
   }
   //loc_8001852
   if ((a > 60) && (a < 98) && (b > 195) && (b < 233))
   {
      //green
      lcdFillRect(61, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
      return 2;
   }
   //loc_8001894
   if ((a > 113) && (a < 151) && (b > 195) && (b < 233))
   {
      //red
      lcdFillRect(114, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(114, 196, COLOR_RED, ICON_LEFT);
      return 1;
   }
   //loc_80018d6
   if ((a > 166) && (a < 203) && (b > 195) && (b < 233))
   {
      //yellow
      lcdFillRect(167, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(167, 196, COLOR_YELLOW, ICON_RIGHT);
      return 4;
   }
   //loc_8001918
   if ((a > 78) && (a < 116) && (b > 5) && (b < 43))
   {
      //orange
      lcdFillRect(79, 6, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(79, 6, COLOR_ORANGE, ICON_MENU);
      return 21;
   }
   //loc_800195a
   if ((a < 320) && (b > 47) && (b < 97))
   {
      return 6;
   }
   //loc_8001972
   if ((a > 274) && (a < 308) && (b > 197) && (b < 231))
   {
      //On-Off
      lcdFillCircle(291, 214, 16, COLOR_GRAY_200);
      main_delay(200);
      draw_on_off_icon(291, 214);
      return 14;
   }
   //loc_80019b2
   if ((a > 11) && (a < 63) && (b > 5) && (b < 43))
   {
      return 20; //Channel number box
   }
   //loc_80019ce
   if ((a > 141) && (a < 213) && (b > 6) && (b < 78))
   {
      return 22; //Signal strength bar
   }
   //loc_80019ea
   if ((a > 241) && (a < 307) && (b > 5) && (b < 43))
   {
      return 23; //Volume bar?
   }

   return 0;
}


/* 8001ae8 - todo */
void draw_foreground_clock(RTC_TimeTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   lcdSetTextFont(&Data_2000004c);
   lcdSetTextColor(0, COLOR_WHITE);

   lcdSetCursor(160 - (len * Data_2000004c.Width) / 2, 93);
   ili9341_draw_string(buf, len);
}


/* 8001b60 - todo */
void draw_background_clock(RTC_TimeTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   lcdSetTextFont(&Data_2000004c);
   lcdSetTextColor(COLOR_WHITE, COLOR_BLACK);

   lcdSetCursor(160 - (len * Data_2000004c.Width) / 2, 96);
   ili9341_draw_string(buf, len);
}


/* 8001bd8 - todo */
void draw_channel_number_box(uint16_t r7_6, uint16_t r7_4, uint8_t r7_3, uint8_t isFav)
{
   uint8_t r7_17;
   uint16_t color;
   uint8_t r7_c[8];

   if (isFav != 0)
   {
      color = COLOR_MAGENTA;
      r7_17 = siprintf(r7_c, "F%u", r7_3 + 1);
   }
   else
   {
      color = COLOR_CYAN;
      r7_17 = siprintf(r7_c, "%u", r7_3 + 1);
   }

   lcdFillRect(r7_6, r7_4, 50, 36, color);
   lcdDrawRect(r7_6, r7_4, 50, 36, COLOR_BLACK);
   lcdSetCursor(r7_6 - r7_17 * Data_20000044.Width / 2 + 25, r7_4 - Data_20000044.Height / 2 + 20);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, color);
   ili9341_draw_string(r7_c, r7_17);
}


/* 8001cc4 - todo */
void draw_signal_strength_bars(uint16_t r7_6, uint16_t r7_4, int8_t* r7)
{
   int8_t r7_f = *r7;

   if (r7_f < 20)
   {
      lcdFillRect(r7_6, r7_4 - 7, 10, 7, COLOR_WHITE);
      lcdDrawRect(r7_6, r7_4 - 7, 10, 7, COLOR_BLACK);
   }
   else
   {
      //loc_8001d16
      lcdFillRect(r7_6, r7_4 - 7, 10, 7, COLOR_BLACK);
   }
   //loc_8001d2e
   if (r7_f < 25)
   {
      lcdFillRect(r7_6 + 15, r7_4 - 14, 10, 14, COLOR_WHITE);
      lcdDrawRect(r7_6 + 15, r7_4 - 14, 10, 14, COLOR_BLACK);
   }
   else
   {
      //loc_8001d72
      lcdFillRect(r7_6 + 15, r7_4 - 14, 10, 14, COLOR_BLACK);
   }
   //loc_8001d8e
   if (r7_f < 35)
   {
      lcdFillRect(r7_6 + 30, r7_4 - 21, 10, 21, COLOR_WHITE);
      lcdDrawRect(r7_6 + 30, r7_4 - 21, 10, 21, COLOR_BLACK);
   }
   else
   {
      //loc_8001dd2
      lcdFillRect(r7_6 + 30, r7_4 - 21, 10, 21, COLOR_BLACK);
   }
   //loc_8001dee
   if (r7_f < 45)
   {
      lcdFillRect(r7_6 + 45, r7_4 - 28, 10, 28, COLOR_WHITE);
      lcdDrawRect(r7_6 + 45, r7_4 - 28, 10, 28, COLOR_BLACK);
   }
   else
   {
      //loc_8001e32
      lcdFillRect(r7_6 + 45, r7_4 - 28, 10, 28, COLOR_BLACK);
   }
   //loc_8001e4e
   if (r7_f < 50)
   {
      lcdFillRect(r7_6 + 60, r7_4 - 35, 10, 35, COLOR_WHITE);
      lcdDrawRect(r7_6 + 60, r7_4 - 35, 10, 35, COLOR_BLACK);
   }
   else
   {
      //loc_8001e92
      lcdFillRect(r7_6 + 60, r7_4 - 35, 10, 35, COLOR_BLACK);
   }
   //loc_8001eae
}


/* 8001eb6 - todo */
void draw_volume_bar(uint8_t r7_7)
{
   lcdFillRect(r7_7 + 242, 6, 63, 36, COLOR_WHITE);
   lcdDrawRect(242, 6, 63, 36, COLOR_BLACK);
   lcdFillRect(242, 6, r7_7, 35, COLOR_BLACK);
}


/* 8001f04 - todo */
void draw_radio_text(void* r7_4, uint8_t r7_3)
{
   uint8_t r7_1f;
   uint8_t r7_1e;
   uint8_t r7_1d;
   uint8_t* r7_18;
   uint8_t* r7_14;
   uint8_t* r7_10;
   uint8_t r7_f = 0;

   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdFillRect(0, 120, 320, 71, COLOR_WHITE);

   r7_18 = r7_4;
   r7_10 = r7_18;

   if ((r7_3 * Data_20000044.Width) > 320)
   {
      for (r7_1e = 0; r7_1e < 3; r7_1e++)
      {
         //loc_8001f56
         r7_1d = 0;
         for (r7_1f = 0; r7_1f < (320 / Data_20000044.Width); r7_1f++)
         {
            //loc_8001f60
        	if ((r7_f + r7_1f) == r7_3)
        	{
               //->loc_8001f9c
        	   break;
        	}

            if (*r7_18++ == ' ')
            {
               r7_14 = r7_18;
               r7_1d = r7_1f;
            }
            //loc_8001f80
         }
         //loc_8001f9c
         //loc_8001f9e
         if (r7_1d != r7_1f)
         {
            r7_18 = r7_14;
            r7_f = r7_1d + r7_f + 1;
            //->loc_8001fce
         }
         else
         {
            //loc_8001fb8
            r7_f += 320 / Data_20000044.Width;
         }
         //loc_8001fce
         lcdSetCursor(160 - r7_1d * Data_20000044.Width / 2, r7_1e * 24 + 120);
         ili9341_draw_string(r7_10, r7_1d);
         r7_10 = r7_18;
      }
      //->loc_8002046
   }
   else
   {
      //loc_800201c
      lcdSetCursor(160 - r7_3 * Data_20000044.Width / 2, 120);
      ili9341_draw_string(r7_4, r7_3);
   }
}


/* 8002054 - todo */
void sub_8002054(Tuner_Channel* r7_c, uint8_t r7_b, uint8_t r7_a, void* r7_4, uint8_t r7_18)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);

   sub_80023d0(r7_c, r7_b, r7_a);

   draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
   draw_36x36(61, 196, COLOR_GREEN, ICON_UP);

   if ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) == 0)
   {
	   draw_36x36(114, 196, COLOR_RED, 5);
   }
   //loc_80020ca
   draw_36x36(167, 196, COLOR_YELLOW, 6);
   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);

   draw_scroll_bar(r7_b, r7_a);

   draw_signal_strength_bars(142, 42, r7_4);

   draw_snr_indicator(222, 7, r7_4, 1);

   draw_volume_bar(r7_18);

   draw_channel_freq_mux_label(r7_c, r7_b);
}


/* 8002128 - todo */
int menu_channel_select_check_touch_fields(uint16_t a, uint16_t b)
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

   if ((a > 113) && (a < 151) && (b > 195) && (b < 233) &&
		   ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) == 0)) //TODO
   {
      lcdFillRect(114, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(114, 196, COLOR_RED, 5);
      return 1;
   }

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
      lcdFillRect(167, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(167, 196, COLOR_YELLOW, 6);
      return 4;
   }

   if ((a > 272) && (a < 311) && (b > 197) && (b < 233))
   {
      lcdFillRect(273, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
      return 5;
   }

   if ((a > 241) && (a <= 305) && (b > 5) && (b < 43))
   {
      return 24;
   }

   if ((a <= (Data_20000044.Width * 24)) && (b > 71) && (b < 97))
   {
      return 7;
   }

   if ((a <= (Data_20000044.Width * 24)) && (b > 95) && (b < 121))
   {
      return 8;
   }

   if ((a <= (Data_20000044.Width * 24)) && (b > 119) && (b < 145))
   {
      return 9;
   }

   if ((a <= (Data_20000044.Width * 24)) && (b > 143) && (b < 169))
   {
      return 10;
   }

   if ((a <= (Data_20000044.Width * 24)) && (b > 167) && (b < 193))
   {
      return 11;
   }

   if ((a > (Data_20000044.Width * 24)) && (a < 321) && (b > 47) && (b < 73))
   {
      return 12;
   }

   if ((a > (Data_20000044.Width * 24)) && (a < 321) && (b > 167) && (b < 193))
   {
      return 13;
   }

   return 0;
}


/* 80023d0 - todo */
void sub_80023d0(Tuner_Channel* r7_4, uint8_t r7_3, uint8_t r7_2)
{
   uint8_t r7_f;
   uint8_t r7_e = (r7_3 < 2)? 0: r7_3 - 2;
   uint8_t r7_d = (r7_2 > 4)? 5: r7_2 + 1;
   uint8_t r7_c;
   uint8_t r7_b;

   lcdFillRect(0, 72, 295, 119, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);

   for (r7_f = 0; (r7_f < r7_d) && ((r7_e + r7_f ) < r7_2); r7_f++)
   {
      //loc_800241c
      if ((r7_e + r7_f) == r7_3)
      {
         lcdSetTextColor(COLOR_WHITE, COLOR_BLACK);
      }
      else
      {
         //loc_8002434
         lcdSetTextColor(0, COLOR_WHITE);
      }
      //loc_800243e
      lcdSetCursor(0, r7_f * 24 + 72);
      lcdPrintf("%u", r7_e + r7_f + 1);

      r7_c = sub_800c88c(&r7_4[r7_e + r7_f].Data_8, 16);

      lcdSetCursor(Data_20000044.Width * 4, r7_f * 24 + 72);

      if (( ((uint8_t*)&r7_4[r7_e + r7_f].Data_8)[0] == 0) ||
    		  ( ((uint32_t*)&r7_4[r7_e + r7_f].Data_8)[0] == 0xffffffff))
      {
         //loc_80024ea
         ili9341_draw_string("DAB Sender", 10);
         //->loc_8002516
      }
      else
      {
         //loc_80024f4
         ili9341_draw_string(&r7_4[r7_e + r7_f].Data_8, r7_c);
      }
      //loc_8002516
      if ((r7_4[r7_e + r7_f].frequency < 42) && (r7_4[r7_e + r7_f].service_id != 0))
      {
         lcdSetCursor(Data_20000044.Width * 21, r7_f * 24 + 72);
         lcdPrintf(Data_8012cdc[0]);
         //->loc_80025bc
      }
      else
      {
         //loc_8002586
         lcdSetCursor(Data_20000044.Width * 21, r7_f * 24 + 72);
         lcdPrintf(Data_8012cdc[1]);
      }
      //loc_80025bc
      r7_b = sub_800b4ec(&r7_4[r7_e + r7_f]);
      if (r7_b != 0xff)
      {
         lcdSetCursor(Data_20000044.Width * 25, r7_f * 24 + 72);
         lcdPrintf("F%1u", r7_b + 1);
      }
      //loc_800261e
   }
}


/* 8002658 - todo */
void draw_scroll_bar(uint8_t r7_7, uint8_t r7_6)
{
   lcdFillRect(296, 49, 24, 142, COLOR_WHITE);
   lcdDrawVLine(320, 48, 192, COLOR_BLACK);
   lcdDrawVLine(296, 48, 192, COLOR_BLACK);
   lcdDrawHLine(296, 320, 72, COLOR_BLACK);
   lcdDrawHLine(296, 320, 168, COLOR_BLACK);
   lcdFillTriangle(308, 52, 300, 68, 316, 68, COLOR_BLACK);
   lcdFillTriangle(308, 188, 300, 172, 316, 172, COLOR_BLACK);
   lcdFillRect(296, r7_7 * 92 / r7_6 + 72, 24, 8, COLOR_BLACK);
}


/* 80027b8 - todo */
void draw_channel_freq_mux_label(Tuner_Channel* r7_4, uint8_t r7_3)
{
   lcdFillRect(0, 24, Data_20000044.Width * 11, 23, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 24);

   if ((r7_4[r7_3].frequency < 42) && (r7_4[r7_3].service_id != 0))
   {
      lcdPrintf(" MUX:%s", Data_8012cdc[r7_4[r7_3].frequency + 10]);
   }
   else
   {
      lcdPrintf(" %3u.%02uMHz", r7_4[r7_3].frequency / 100, r7_4[r7_3].frequency % 100);
   }
}


/* 80028b8 - todo */
void sub_80028b8(Tuner_Channel* r7_4, uint8_t r7_3, uint8_t r7_2)
{
   sub_80023d0(r7_4, r7_3, r7_2);
   draw_scroll_bar(r7_3, r7_2);
   draw_channel_freq_mux_label(r7_4, r7_3);
}


/* 80028f2 - todo */
void draw_automatic_search_screen(Tuner_Channel* r7_4, uint8_t r7_3, uint8_t r7_2, uint16_t r7, uint16_t r7_10, void* r7_14, uint16_t r7_18)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_freq_mux_label(r7_18);
   draw_progress_bar(242, 42, r7, r7_10);

   if (r7_2 != 0)
   {
      draw_channel_list(r7_4, r7_2);
      draw_signal_strength_bars(142, 42, r7_14);
   }
   //loc_800295e
   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
}


/* 8002976 - todo */
int menu_automatic_search_check_touch_fields(uint16_t a, uint16_t b)
{

}


/* 80029da - todo */
void draw_progress_bar(uint16_t x, uint16_t y, uint16_t currentValue, uint16_t maxValue)
{
   uint32_t width = currentValue * 64 / maxValue;

   lcdFillRect(width + x, y - 36, 64, 36, COLOR_WHITE);
   lcdDrawRect(x, y - 36, 64, 36, 0x00);
   lcdFillRect(x, y - 36, width, 35, 0x00);
}


/* 8002a60 - todo */
void draw_channel_list(Tuner_Channel* r7_4, uint8_t r7_3)
{
   uint8_t r7_f;
   uint8_t r7_e = (r7_3 < 6)? 0: r7_3 - 5;
   uint8_t r7_d;

   lcdFillRect(0, 72, 295, 119, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);

   for (r7_f = 0; (r7_e + r7_f) < r7_3; r7_f++)
   {
      //loc_8002aa4
      lcdSetCursor(0, r7_f * 24 + 72);
      lcdPrintf("%u", r7_e + r7_f + 1);

      r7_d = sub_800c88c(&r7_4[r7_e + r7_f].Data_8, 16);

      lcdSetCursor(Data_20000044.Width * 4, r7_f * 24 + 72);
      ili9341_draw_string(&r7_4[r7_e + r7_f].Data_8, r7_d);

      if ((r7_4[r7_e + r7_f].frequency < 41) && (r7_4[r7_e + r7_f].service_id != 0))
      {
         lcdSetCursor(Data_20000044.Width * 21, r7_f * 24 + 72);
         lcdPrintf("DAB");
      }
      else
      {
         //loc_8002ba6
         lcdSetCursor(Data_20000044.Width * 21, r7_f * 24 + 72);
         lcdPrintf("FM");
      }
      //loc_8002bdc
   }
}


const char* Data_8012cdc[] = //8012cdc
{
   "DAB", //0x080125c8
   "FM", //0x080125cc
   "RSSI:", //0x080125d0
   "SNR:", //0x080125d8
   "FIB:", //0x080125e0
   "FREQ:", //0x080125e8
   "dBuV", //0x080125f0
   "dB", //0x080125f8
   "MHz", //0x080125fc
   "FM Radio", //0x08012600
   "5A", //10 0x0801260c
   "5B", //0x08012610
   "5C", //0x08012614
   "5D", //0x08012618
   "6A", //0x0801261c
   "6B", //0x08012620
   "6C", //0x08012624
   "6D", //0x08012628
   "7A", //0x0801262c
   "7B", //0x08012630
   "7C", //0x08012634
   "7D", //0x08012638
   "8A", //0x0801263c
   "8B", //0x08012640
   "8C", //0x08012644
   "8D", //0x08012648
   "9A", //0x0801264c
   "9B", //0x08012650
   "9C", //0x08012654
   "9D", //0x08012658
   "10A", //0x0801265c
   "10N", //0x08012660
   "10B", //0x08012664
   "10C", //0x08012668
   "10D", //0x0801266c
   "11A", //0x08012670
   "11N",
   "11B",
   "11C",
   "11D",
   "12A",
   "12N",
   "12B",
   "12C",
   "12D",
   "13A",
   "13B",
   "13C",
   "13D",
   "13E",
   "13F",
};

/* 8002c04 - todo */
void draw_freq_mux_label(uint16_t r7_6)
{
   lcdFillRect(0, 24, Data_20000044.Width * 10, 23, COLOR_WHITE);
   lcdSetTextFont(&Data_20000044);
   lcdSetTextColor(0, COLOR_WHITE);
   lcdSetCursor(0, 24);

   if (r7_6 > 41)
   {
      lcdPrintf(" %3u.%02uMHz", r7_6 / 100, r7_6 % 100);
   }
   else
   {
      lcdPrintf(" MUX:%s", Data_8012cdc[r7_6 + 10]);
   }
}


/* 8002e0c - todo */
void sub_8002e0c(uint16_t r7_6, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_screen_caption(r7_6, &Data_2000004c);
   sub_8002cac(r7_4, r7_3, r7_2);
   draw_36x36(8, 196, COLOR_BLUE, ICON_DOWN);
   draw_36x36(61, 196, COLOR_GREEN, ICON_UP);
   draw_36x36(167, 196, COLOR_YELLOW, 6);
}


/* 80049bc - todo */
void draw_volume_change_screen(uint8_t a)
{
   lcdFillRGB(COLOR_WHITE);
   lcdDrawHLine(0, 320, 48, COLOR_BLACK);
   lcdDrawHLine(0, 320, 192, COLOR_BLACK);
   draw_screen_caption(36, &Data_2000004c);
   draw_volume_change_bar(a);
   draw_36x36(114, 196, COLOR_RED, ICON_LEFT);
   draw_36x36(167, 196, COLOR_YELLOW, ICON_RIGHT);
   draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
}


/* 8004a34 - todo */
void draw_volume_change_bar(uint8_t a)
{
   lcdFillRect((a + 8)*4, 72, 252, 24, COLOR_WHITE);
   lcdDrawRect(32, 72, 252, 24, COLOR_BLACK);
   lcdFillRect(32, 72, a * 4, 23, COLOR_BLACK);
}


/* 8004a8a - todo */
int volume_change_screen_check_touch_fields(uint16_t r7_6, uint16_t r7_4)
{
   if ((r7_6 > 113) && (r7_6 < 151) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(114, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(114, 196, COLOR_RED, ICON_LEFT);
      return 1;
   }

   if ((r7_6 > 166) && (r7_6 < 204) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(167, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(167, 196, COLOR_YELLOW, ICON_RIGHT);
      return 4;
   }

   if ((r7_6 > 272) && (r7_6 < 311) && (r7_4 > 195) && (r7_4 < 233))
   {
      lcdFillRect(273, 196, 36, 36, COLOR_GRAY_200);
      main_delay(100);
      draw_36x36(273, 196, COLOR_WHITE, ICON_BACK);
      return 5;
   }

   return 0;
}


/* 800b1c8 - todo */
void button_poll(void)
{
   if (KeyEvent.bData_0 != 1)
   {
      return;
   }

   bData_20000056--;
   if (bData_20000056 != 0)
   {
      return;
   }

   bData_20000056 = 4;

   if (0 == HAL_GPIO_ReadPin(Button_Yellow_GPIO_Port, Button_Yellow_Pin))
   {
      KeyEvent.bData_0 = 0;
      KeyEvent.bData_1 = 4; //yellow
   }

   if (0 == HAL_GPIO_ReadPin(Button_Red_GPIO_Port, Button_Red_Pin))
   {
      KeyEvent.bData_0 = 0;
      KeyEvent.bData_1 = 1; //red
   }

   if (0 == HAL_GPIO_ReadPin(Button_Green_GPIO_Port, Button_Green_Pin))
   {
      KeyEvent.bData_0 = 0;
      KeyEvent.bData_1 = 2; //green
   }

   if (0 == HAL_GPIO_ReadPin(Button_Blue_GPIO_Port, Button_Blue_Pin))
   {
      KeyEvent.bData_0 = 0;
      KeyEvent.bData_1 = 3; //blue
   }
}


/* 8002722 - todo */
void draw_snr_indicator(uint16_t r7_e, uint16_t r7_c, Tuner_Values* r7_8, uint8_t r7_7)
{
   uint8_t r7_17;
   uint8_t r7_16;
   uint16_t r7_14;

   if (r7_7 == 0)
   {
      r7_17 = 20;
      r7_16 = 20;
   }
   else
   {
      r7_17 = 35;
      r7_16 = 10;
   }

   if (r7_8->snr < 1)
   {
      r7_14 = COLOR_RED;
   }
   else if (r7_8->snr < 4)
   {
      r7_14 = COLOR_YELLOW;
   }
   else
   {
      r7_14 = COLOR_GREEN;
   }

   lcdFillRect(r7_e, r7_c, r7_16, r7_17, r7_14);
   lcdDrawRect(r7_e, r7_c, r7_16, r7_17, COLOR_BLACK);
}


/* 8004b74 - todo */
void sub_8004b74(int a, int b, char* c)
{

}


/* 800c830 - todo */
uint32_t calculate_crc(uint32_t startVal, void* data, uint32_t count)
{
   uint32_t crc = ~startVal;
   uint32_t i;
   uint8_t* bData = data;

   for (i = 0; i < count; i++)
   {
	   extern const uint32_t crc_table[]; //8018fa4
	   crc = (crc >> 8) ^ crc_table[ (bData[i] ^ crc) & 0xff ];
   }

   return ~crc;
}


