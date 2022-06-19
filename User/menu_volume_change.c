
#include "main.h"

/* 8008554 - todo */
int menu_volume_change(void)
{
   uint32_t r7_c = 3000000;
   uint8_t r7_b = 0;
   uint8_t menuActive = 1;
   uint8_t newVolume = bCurrentVolume;
   uint8_t oldVolume = 0;
   uint8_t r7_7;
   uint8_t r7_6;

   draw_volume_change_screen(newVolume);

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;

   while ((menuActive != 0) && (r7_c -- != 0))
   {
      //loc_8008586
      r7_7 = 0;
      if (Data_20000a48.bData_0 == 0)
      {
         r7_7 = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_800859e
      r7_6 = 0;
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_6 = volume_change_screen_check_touch_fields(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_80085be
      if ((r7_6 | r7_7) != 0)
      {
         r7_c = 3000000;
         switch (r7_6 | r7_7)
         {
            case 4:
               //loc_80085e4
               if (newVolume < 63)
               {
                  newVolume++;
               }
               si46xx_set_volume(newVolume);
               r7_b = 1;
               break;

            case 1:
               //loc_80085fe
               if (newVolume != 0)
               {
                  newVolume--;
               }
               si46xx_set_volume(newVolume);
               r7_b = 1;
               break;

            case 5:
               //loc_8008618
               menuActive = 0;
               break;
#if 0
            default:
               //loc_800861e
               break;
#endif
         }
         //loc_800861e
         Data_20000bc0.bData_0 = 1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_800862a
      if (newVolume != oldVolume)
      {
         oldVolume = newVolume;
         draw_volume_change_bar(newVolume);
      }
   }
   //loc_800864e
   bCurrentVolume = newVolume;

   return r7_b;
}

