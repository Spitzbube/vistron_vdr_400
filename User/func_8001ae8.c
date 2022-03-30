
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"


/* 8001ae8 - todo */
void sub_8001ae8(/*struct_8001ae8*/RTC_TimeTypeDef a)
{
   char r7_c[10];
   uint8_t r7_17 = 0;

   r7_17 = sprintf(r7_c, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   ili9341_set_font(&Data_2000004c);
   sub_80060c8(0, 0xffff);

   ili9341_set_cursor(160 - (r7_17 * Data_2000004c.width) / 2, 93);
   ili9341_draw_string(r7_c, r7_17);
}


/* 8001b60 - todo */
void sub_8001b60(RTC_TimeTypeDef a)
{
   char r7_c[10];
   uint8_t r7_17 = 0;

   r7_17 = sprintf(r7_c, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   ili9341_set_font(&Data_2000004c);
   sub_80060c8(0xffff, 0);

   ili9341_set_cursor(160 - (r7_17 * Data_2000004c.width) / 2, 96);
   ili9341_draw_string(r7_c, r7_17);
}


