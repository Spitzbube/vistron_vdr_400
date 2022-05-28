
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"


#if 0
/* 80013a0 - todo */
int sub_80013a0(uint16_t a)
{

}

/* 8001450 - todo */
int sub_8001450(int a, int b)
{

}


/* 80016f0 - todo */
int sub_80016f0(int a)
{

}
#endif


/* 8001ae8 - todo */
void sub_8001ae8(RTC_TimeTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0, 0xffff);

   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 93);
   ili9341_draw_string(buf, len);
}


/* 8001b60 - todo */
void sub_8001b60(RTC_TimeTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0xffff, 0);

   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 96);
   ili9341_draw_string(buf, len);
}


/* 8002054 - todo */
void sub_8002054(struct_8008d84* r7_c, uint8_t r7_b, uint8_t r7_a, void* r7_4, uint8_t r7_18)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);

   sub_80023d0(r7_c, r7_b, r7_a);

   sub_8005198(8, 196, 0x1f, 1);
   sub_8005198(61, 196, 0x7e0, 0);

   if ((wData_20000a56 & 0x04) == 0)
   {
	   sub_8005198(114, 196, 0xf800, 5);
   }
   //loc_80020ca
   sub_8005198(167, 196, 0xffe0, 6);
   sub_8005198(273, 196, 0xffff, 7);

   draw_scroll_bar(r7_b, r7_a);

   draw_signal_strength_bars(142, 42, r7_4);

   draw_snr_indicator(222, 7, r7_4, 1);

   sub_8001eb6(r7_18);

   draw_channel_freq_mux_label(r7_c, r7_b);
}


/* 8002128 - todo */
int sub_8002128(uint16_t a, uint16_t b)
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

   if ((a > 113) && (a < 151) && (b > 195) && (b < 233) &&
		   ((wData_20000a56 & 0x04) == 0)) //TODO
   {
      ili9341_draw_box(114, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(114, 196, 0xf800, 5);
      return 1;
   }

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(167, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(167, 196, 0xffe0, 6);
      return 4;
   }

   if ((a > 272) && (a < 311) && (b > 197) && (b < 233))
   {
      ili9341_draw_box(273, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(273, 196, 0xffff, 7);
      return 5;
   }

   if ((a > 241) && (a <= 305) && (b > 5) && (b < 43))
   {
      return 24;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 71) && (b < 97))
   {
      return 7;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 95) && (b < 121))
   {
      return 8;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 119) && (b < 145))
   {
      return 9;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 143) && (b < 169))
   {
      return 10;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 167) && (b < 193))
   {
      return 11;
   }

   if ((a > (Data_20000044.width * 24)) && (a < 321) && (b > 47) && (b < 73))
   {
      return 12;
   }

   if ((a > (Data_20000044.width * 24)) && (a < 321) && (b > 167) && (b < 193))
   {
      return 13;
   }

   return 0;
}


/* 80023d0 - todo */
void sub_80023d0(struct_8008d84* r7_c, uint8_t r7_b, uint8_t r7_a)
{

}


/* 8002658 - todo */
void draw_scroll_bar(uint8_t r7_7, uint8_t r7_6)
{
   ili9341_draw_box(296, 49, 24, 142, 0xffff);
   ili9341_draw_vert_line(320, 48, 192, 0);
   ili9341_draw_vert_line(296, 48, 192, 0);
   ili9341_draw_hor_line(296, 320, 72, 0);
   ili9341_draw_hor_line(296, 320, 168, 0);
   sub_8005af0(308, 52, 300, 68, 316, 68, 0);
   sub_8005af0(308, 188, 300, 172, 316, 172, 0);
   ili9341_draw_box(296, r7_7 * 92 / r7_6 + 72, 24, 8, 0);
}


/* 80027b8 - todo */
void draw_channel_freq_mux_label(struct_8008d84* r7_4, uint8_t r7_3)
{
   ili9341_draw_box(0, 24, Data_20000044.width * 11, 23, 0xffff);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 24);

   if ((r7_4[r7_3].wData_24 < 42) && (r7_4[r7_3].service_id != 0))
   {
      ili9341_draw_format_string(" MUX:%s", Data_8012cdc[r7_4[r7_3].wData_24 + 10]);
   }
   else
   {
      ili9341_draw_format_string(" %3u.%02uMHz", r7_4[r7_3].wData_24 / 100, r7_4[r7_3].wData_24 % 100);
   }
}


/* 80028b8 - todo */
void sub_80028b8(struct_8008d84* r7_4, uint8_t r7_3, uint8_t r7_2)
{
   sub_80023d0(r7_4, r7_3, r7_2);
   draw_scroll_bar(r7_3, r7_2);
   draw_channel_freq_mux_label(r7_4, r7_3);
}


/* 80028f2 - todo */
void sub_80028f2(struct_8008d84* r7_4, uint8_t r7_3, uint8_t r7_2, uint16_t r7, uint16_t r7_10, void* r7_14, uint16_t r7_18)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   draw_freq_mux_label(r7_18);
   draw_progress_bar(242, 42, r7, r7_10);

   if (r7_2 != 0)
   {
      sub_8002a60(r7_4, r7_2);
      draw_signal_strength_bars(142, 42, r7_14);
   }
   //loc_800295e
   sub_8005198(273, 196, 0xffff, 7); //Back button
}


/* 8002976 - todo */
int sub_8002976(uint16_t a, uint16_t b)
{

}


/* 80029da - todo */
void draw_progress_bar(uint16_t x, uint16_t y, uint16_t currentValue, uint16_t maxValue)
{
   uint32_t width = currentValue * 64 / maxValue;

   ili9341_draw_box(width + x, y - 36, 64, 36, 0xffff);
   sub_800581e(x, y - 36, 64, 36, 0x00);
   ili9341_draw_box(x, y - 36, width, 35, 0x00);
}


/* 8002a60 - todo */
void sub_8002a60(struct_8008d84* r7_4, uint8_t r7_3)
{
   uint8_t r7_f;
   uint8_t r7_e = (r7_3 < 5)? 5: r7_3 - 5;
   uint8_t r7_d;

   ili9341_draw_box(0, 72, 295, 119, 0xffff);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);

   for (r7_f = 0; (r7_e + r7_f) < 0; r7_f++)
   {
      //loc_8002aa4
      ili9341_set_cursor(0, r7_f * 24 + 72);
      ili9341_draw_format_string("%u", r7_e + r7_f + 1);

      r7_d = sub_800c88c(&r7_4[r7_e + r7_f].Data_8, 16);

      ili9341_set_cursor(Data_20000044.width * 4, r7_f * 24 + 72);
      ili9341_draw_string(&r7_4[r7_e + r7_f].Data_8, r7_d);

      if ((r7_4[r7_e + r7_f].wData_24 < 41) && (r7_4[r7_e + r7_f].service_id != 0))
      {
         ili9341_set_cursor(Data_20000044.width * 21, r7_f * 24 + 72);
         ili9341_draw_format_string("DAB");
      }
      else
      {
         //loc_8002ba6
         ili9341_set_cursor(Data_20000044.width * 21, r7_f * 24 + 72);
         ili9341_draw_format_string("FM");
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
   ili9341_draw_box(0, 24, Data_20000044.width * 10, 23, 0xffff);
   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);
   ili9341_set_cursor(0, 24);

   if (r7_6 > 41)
   {
      ili9341_draw_format_string(" %3u.%02uMHz", r7_6 / 100, r7_6 % 100);
   }
   else
   {
      ili9341_draw_format_string(" MUX:%s", Data_8012cdc[r7_6 + 10]);
   }
}


/* 800581e - todo */
void sub_800581e(int16_t r7_6, int16_t r7_4, int16_t r7_2, int16_t r7, uint16_t e)
{
   ili9341_draw_hor_line(r7_6, r7_6 + r7_2, r7_4, e);
   ili9341_draw_hor_line(r7_6, r7_6 + r7_2, r7_4 + r7, e);
   ili9341_draw_vert_line(r7_6, r7_4, r7_4 + r7, e);
   ili9341_draw_vert_line(r7_6 + r7_2, r7_4, r7_4 + r7, e);
}


/* 800ad68 - todo */
void sub_800ad68(void)
{

}


/* 800adb8 - todo */
void sub_800adb8(void)
{

}


/* 800b1c8 - todo */
void button_gpio_check(void)
{
   if (Data_20000a48.bData_0 != 1)
   {
      return;
   }

   bData_20000056--;
   if (bData_20000056 != 0)
   {
      return;
   }

   bData_20000056 = 4;

   if (0 == HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 4; //yellow
   }

   if (0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 1; //red
   }

   if (0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 2; //green
   }

   if (0 == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 3; //blue
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
      r7_14 = 0xf800;
   }
   else if (r7_8->snr < 4)
   {
      r7_14 = 0xffe0;
   }
   else
   {
      r7_14 = 0x7e0;
   }

   ili9341_draw_box(r7_e, r7_c, r7_16, r7_17, r7_14);
   sub_800581e(r7_e, r7_c, r7_16, r7_17, 0);
}


/* 8008554 - todo */
void sub_8008554(void)
{

}


/* 800b610 - todo */
void sub_800b610(uint8_t a)
{

}


/* 8006a8e - todo */
int sub_8006a8e(uint32_t addr, uint16_t data[], uint16_t r7_6)
{
   uint8_t r7_17 = 0;
   uint16_t i;

   HAL_FLASH_Unlock();

   for (i = 0; i < r7_6; i++)
   {
      //loc_8006aaa
      if (0 != HAL_FLASH_Program(1, addr, (uint64_t)(data[i])))
      {
         r7_17 = 1;
         break;
      }

      addr += 2;
   }

   HAL_FLASH_Lock();

   return r7_17;
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


/* 800ba74 - todo */
int sub_800ba74(struct_8008d84* r7_c, struct_8008d84* r7_8, void* r7_4, void* r7)
{
   uint8_t r7_1f = 0;

   if (0 == sub_800bbbc())
   {
      uint16_t r7_16 = 0x524d;

      if (0 != sub_8006a8e(0x807e800, &r7_16, 1))
      {
         r7_1f = 1;
      }
	  //loc_800baae
	  r7_16 = 1;
	  if (0 != sub_8006a8e(0x807e802, &r7_16, 1))
	  {
		 r7_1f = 1;
	  }
      //loc_800baca
	  uint32_t r7_18 = calculate_crc(0, r7_c, 0x15e0);
	  r7_18 = calculate_crc(r7_18, r7_8, 0xe0);
	  r7_18 = calculate_crc(r7_18, r7_4, 4);
	  r7_18 = calculate_crc(r7_18, r7, 4);
	  r7_16 = r7_18;
	  if (0 != sub_8006a8e(0x807e804, &r7_16, 1))
	  {
         r7_1f = 1;
	  }
	  //loc_800bb1a
	  r7_16 = r7_18 >> 16;
	  if (0 != sub_8006a8e(0x807e806, &r7_16, 1))
	  {
         r7_1f = 1;
	  }
	  //loc_800bb3a
	  if (0 != sub_8006a8e(0x807e808, (uint16_t*)r7_c, 0xaf0))
	  {
         r7_1f = 1;
	  }
	  //loc_800bb50
	  if (0 != sub_8006a8e(0x807fde8, (uint16_t*)r7_8, 0x70))
	  {
		r7_1f = 1;
	  }
	  //loc_800bb64
	  if (0 != sub_8006a8e(0x807feca, (uint16_t*)r7_4, 2))
	  {
		r7_1f = 1;
	  }
	  //loc_800bb78
	  if (0 != sub_8006a8e(0x807fece, (uint16_t*)r7, 2))
	  {
		r7_1f = 1;
	  }
   }
   else
   {
      //loc_800bb8e
      r7_1f = 1;
   }

   return r7_1f;
}


/* 800bbbc - todo */
int sub_800bbbc(void)
{
   uint8_t r7_7;
   uint8_t r7_6 = 0;
   int r7 = 0x807e800;

   for (r7_7 = 0; r7_7 < 3; r7_7++)
   {
      if (0 != sub_8006af4(r7))
      {
         r7_6 = 1;
         break;
      }

      r7 += 0x800;
   }

   return r7_6;
}


/* 800bc04 - todo */
int sub_800bc04(struct_8008d84* r7_c, struct_8008d84* r7_8, void* r7_4, void* r7)
{
   uint16_t* r7_2c;
   uint16_t* r7_28;
   uint32_t r7_24;
   uint32_t* r7_20;
   uint32_t* r7_1c;
   uint32_t r7_18;
   uint32_t r7_14;

   r7_20 = (void*) 0x807e804;
   r7_1c = &r7_14;
   *r7_1c = *r7_20;

   r7_28 = (void*) 0x807e808;
   r7_2c = (void*) r7_c;

   for (r7_24 = 0; r7_24 < 2800; r7_24++)
   {
	   //loc_800bc32
      *r7_2c++ = *r7_28++;
   }

   r7_28 = (void*) 0x807fde8;
   r7_2c = (void*) r7_8;

   for (r7_24 = 0; r7_24 < 112; r7_24++)
   {
	   //loc_800bc5e
      *r7_2c++ = *r7_28++;
   }

   r7_20 = (void*) 0x807feca;
   r7_1c = r7_4;
   *r7_1c++ = *r7_20++;

   r7_20 = (void*) 0x807fece;
   r7_1c = r7;
   *r7_1c = *r7_20;

   r7_18 = calculate_crc(0, r7_c, 0x15e0);
   r7_18 = calculate_crc(r7_18, r7_8, 0xe0);
   r7_18 = calculate_crc(r7_18, r7_4, 4);
   r7_18 = calculate_crc(r7_18, r7, 4);

   if (r7_14 != r7_18)
   {
      sub_800bbbc();

      memset(r7_c, 0xff, 0x15e0);
      memset(r7_8, 0xff, 0xe0);
      memset(r7_4, 0xff, 4);
      memset(r7, 0xff, 4);

      return 1;
   }
   //loc_800bd0e
   return 0;
}


/* 8006af4 - todo */
int sub_8006af4(uint32_t addr)
{
   uint8_t r7_1f = 0;
   FLASH_EraseInitTypeDef eraseInit;
   uint32_t r7_8;

   eraseInit.PageAddress = addr;
   eraseInit.NbPages = 1;
   eraseInit.TypeErase = 0;
   eraseInit.Banks = 1;

   HAL_FLASH_Unlock();
   if (0 != HAL_FLASHEx_Erase(&eraseInit, &r7_8))
   {
      r7_1f = 1;
   }

   HAL_FLASH_Lock();

   return r7_1f;
}


/* 800bd2c - todo */
void menu_channel_select(void)
{
   uint8_t r7_1f = 1;
   int8_t r7_1e;
   int8_t r7_1d;
   uint8_t r7_1c;
   uint8_t r7_1b;
   uint8_t r7_1a;
   uint8_t r7_19 = bData_20000a58;
   uint8_t r7_18;
   struct_8008d84* r7_14;
   Tuner_Values r7_4 = {0};

   r7_1e = 0;
   r7_1d = 0;
   r7_1a = 0;
   r7_18 = (wData_20000a56 & 0x04)? bData_20000be4: bData_200022a8;
   r7_14 = (wData_20000a56 & 0x04)? Data_20000be8: Data_20000cc8;

   if (bData_200022a8 == 0)
   {
      return;
   }

   sub_8002054(r7_14, bData_20000a58, r7_18, &r7_4, bData_20000057);

   Data_20000bc0.bData_0 = 1;
   //->loc_800c312
   while (r7_1f != 0)
   {
      //loc_800bda8
      r7_18 = (wData_20000a56 & 0x04)? bData_20000be4: bData_200022a8;
      r7_1c = 0;

      if (Data_20000a48.bData_0 == 0)
      {
         r7_1c = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_800bdd8
      r7_1b = 0;

      if (Data_20000bc0.bData_0 == 0)
      {
         r7_1b = sub_8002128(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_800bdf8
      if ((r7_1b | r7_1c) != 0)
      {
         switch (r7_1b | r7_1c)
         {
         case 3:
        	 //800be7c
        	 channel_next();
        	 sub_80028b8(r7_14, bData_20000a58, r7_18);
        	 sub_800abb0(&r7_14[bData_20000a58]);
        	 //->800C1E8
        	 break;

         case 2:
        	 //800beaa
        	 channel_previous();
        	 sub_80028b8(r7_14, bData_20000a58, r7_18);
        	 sub_800abb0(&r7_14[bData_20000a58]);
        	 //->800C1E8
        	 break;

         case 4:
        	 //800bed8
        	 r7_1f = 0;
        	 if (r7_1a != 0)
        	 {
        		 sub_800ba74(Data_20000cc8, Data_20000be8, &Data_20000a4c, &Data_20000a50);
        	 }
        	 //->800C1C6
        	 break;

         case 1:
        	 //800bef2
        	 if ((wData_20000a56 & 4) == 0)
        	 {
        		 sub_800b610(bData_20000a58);
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
        		 r7_1a = 1;
        	 }
        	 //800C1CA
        	 break;

         case 5:
        	 //800bf1e
        	 bData_20000a58 = r7_19;
        	 sub_800abb0(&r7_14[bData_20000a58]);
        	 r7_1f = 0;
        	 //->800C1E8
        	 break;

         case 7:
        	 //800bf44
        	 if (r7_18 != 0)
        	 {
        		 bData_20000a58 -= 2; //TODO

        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1CE
        	 break;

         case 8:
        	 //800bf8a
        	 if (r7_18 > 1)
        	 {
        		 bData_20000a58 -= 1; //TODO

        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1D2
        	 break;

         case 9:
        	 //800bfd0
        	 if ((r7_18 > 2) && (bData_20000a58 < 2))
        	 {
        		 bData_20000a58 = 2;
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1D6
        	 break;

         case 10:
        	 //800c040
        	 if ((r7_18 > 3) && ((bData_20000a58 + 1) < r7_18))
        	 {
        		 bData_20000a58++;
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1DA
        	 break;

         case 11:
        	 //800c08c
        	 if ((r7_18 > 4) && ((bData_20000a58 + 2) < r7_18))
        	 {
        		 bData_20000a58 += 2;
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1DE
        	 break;

         case 12:
        	 //800c0d8
        	 if (r7_18 > 4)
        	 {
        		 if (bData_20000a58 == 0)
        		 {
        			 bData_20000a58 = r7_18 - 1;
        			 //->800C118
        		 }
        		 //800C0F4
        		 else if (bData_20000a58 > 4)
        		 {
        			 bData_20000a58 -= 5; //TODO
        			 //->800C118
        		 }
        		 else
        		 {
        			 //800C112
        			 bData_20000a58 = 0;
        		 }
        		 //800C118
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
            	 //->800C1E2
        	 }
        	 //800C1E2
        	 break;

         case 13:
        	 //800c142
        	 if (r7_18 > 4)
        	 {
        		 if ((bData_20000a58 + 1) < r7_18)
        		 {
        			 bData_20000a58 = ((bData_20000a58 + 5) > r7_18)? r7_18 - 1: bData_20000a58 + 5;
        			 //->800C17C
        		 }
        		 else
        		 {
        			 //800C176
        			 bData_20000a58 = 0;
        		 }
        		 //800C17C
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1E6
        	 break;

         case 24:
        	 //800c1a6
        	 sub_8008554();
        	 sub_8002054(r7_14, bData_20000a58, r7_18, &r7_4, bData_20000057);
        	 //800C1E8
        	 break;

         default:
        	 //loc_800c1c2 -> loc_800c1e8
        	 break;

         }//switch ((r7_1b | r7_1c))
         //loc_800c1e8
    	 Data_20000bc0.bData_0 = 1;
      } //if ((r7_1b | r7_1c) != 0)
      //loc_800c1ee
      if (wData_20000a56 & 0x10)
      {
    	  wData_20000a56 &= ~0x10;

    	  if ((Data_20000cc8[bData_20000a58].wData_24 < 41) && (Data_20000cc8[bData_20000a58].service_id != 0))
    	  {
    		  //0800c23c
    		  si46xx_get_dab_values(&r7_4);
    		  if (0 == si46xx_get_dab_values(&r7_4))
    		  {
    			  //0800c252
    			  if (r7_4.rssi/5 != r7_1e/5)
    			  {
    				  //0800c27a
    				  r7_1e = r7_4.rssi;

    				  draw_signal_strength_bars(142, 42, &r7_4.rssi);
    			  }
    			  //loc_800c28a
    			  if (r7_4.snr != r7_1d)
    			  {
    				  //0800c296
    				  r7_1d = r7_4.snr;

    				  draw_snr_indicator(0xde, 0x07, &r7_4, 1);
    			  }
    			  //loc_800c312
    		  }
    		  //loc_800c312
    	  }
    	  else
    	  {
        	  //loc_800c2a8
    		  si46xx_get_fm_values(&r7_4);
    		  if (0 == si46xx_get_fm_values(&r7_4))
    		  {
    			  if (r7_4.rssi/5 != r7_1e/5)
    			  {
    				  //0800c2e6
    				  r7_1e = r7_4.rssi;

    				  draw_signal_strength_bars(142, 42, &r7_4.rssi);
    			  }
    			  //loc_800c2f6
    			  if (r7_4.snr != r7_1d)
    			  {
    				  //0800c302
    				  r7_1d = r7_4.snr;

    				  draw_snr_indicator(0xde, 0x07, &r7_4, 1);
    			  }
    		  }
    	  }
      }
      //loc_800c312 -> loc_800bda8
   } //while (r7_1f != 0)
   //loc_800c31a
}

