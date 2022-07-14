
#include "main.h"

/* 80073c0 - todo */
int menu_sw_information(void)
{
   uint8_t r7_7 = 1;

   draw_sw_information_screen(strDABVersion, strFMVersion);

   while (r7_7 != 0)
   {
      if (5 == sub_80041e0(TouchEvent.wData_2, TouchEvent.wData_4))
      {
         r7_7 = 0;
      }
   }

   return 0;
}


