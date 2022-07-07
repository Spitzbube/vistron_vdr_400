
#include "main.h"


/* 8008200 - todo */
int menu_sleep_timer(void)
{
   uint8_t r7_7 = 1;
   uint8_t r7_6;
   uint8_t r7_5;
   uint8_t r7_4 = 0;
   uint8_t r7_3;
   uint8_t r7_2;

   sleepTimerCount = (wMainloopEvents & MAIN_LOOP_EVENT_SLEEP_TIMER)? sleepTimerCount: 0;
   r7_5 = sleepTimerCount;
   r7_6 = sleepTimerCount / 10;

   draw_sleep_timer_screen(r7_5);

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;

   while (r7_7 != 0)
   {
      //loc_8008250
      r7_3 = 0;
      if (Data_20000a48.bData_0 == 0)
      {
         r7_3 = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }

      r7_2 = 0;
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_2 = sub_8004894(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }

      if ((r7_2 | r7_3) != 0)
      {
         switch (r7_2 | r7_3)
         {
            case 2:
               //0x080082b9
               r7_6++;
               if (r7_6 > 9) r7_6 = 0;
               r7_5 = r7_6 * 10;
               //8008336
               break;

            case 3:
               //0x080082d7
               r7_6--;
               if (r7_6 == 0xff) r7_6 = 9;
               r7_5 = r7_6 * 10;
               break;

            case 4:
               //0x080082f5
               if (r7_6 != 0)
               {
                  sleepTimerCount = r7_6 * 10;
                  wMainloopEvents |= MAIN_LOOP_EVENT_SLEEP_TIMER;
               }
               else
               {
                  //800831A
                  wMainloopEvents &= ~MAIN_LOOP_EVENT_SLEEP_TIMER;
               }
               r7_7 = 0;
               break;

            case 5:
               //0x0800832f
               r7_7 = 0;
               break;
         }
         //loc_8008334
         Data_20000bc0.bData_0 = 1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_8008342
      if (r7_6 != r7_4)
      {
         r7_4 = r7_6;
         draw_sleep_timer_value(r7_5);
      }
      //loc_8008356
   }

   return 0;
}


