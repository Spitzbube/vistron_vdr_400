
#include "main.h"


/* 800837c - todo */
int menu_auto_standby(void)
{
   uint8_t r7_7 = 1;
   uint8_t r7_6 = 0;
   uint8_t r7_5 = 0;
   uint8_t r7_4 = (wMainloopEvents & MAIN_LOOP_EVENT_AUTO_STANDBY) == 0? 1: 0;
   uint8_t r7_3 = r7_4;
   uint8_t r7_2;
   uint8_t r7_1;

   sub_8002d70(TEXT_ID_AUTO_STANDBY, 37, 2, r7_4);

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   while (r7_7 != 0)
   {
      //loc_80083c0
      r7_2 = 0;
      if (KeyEvent.bData_0 == 0)
      {
         r7_2 = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
      }
      //loc_80083d8
      r7_1 = 0;
      if (TouchEvent.bData_0 == 0)
      {
         r7_1 = sub_8002e98(TouchEvent.wData_2, TouchEvent.wData_4);
      }
      //loc_80083f8
      if ((r7_1 | r7_2) != 0)
      {
         switch (r7_1 | r7_2)
         {
         	 case 2:
         		 //0x0800847d
         		 r7_4++;
         		 if (r7_4 == 2) r7_4 = 0;
         		 //->80084CC
         		 break;

         	 case 3:
         		 //0x0800848f
         		 r7_4--;
         		 if (r7_4 == 0xff) r7_4 = 1;
         		 break;

         	 case 4:
         		 //0x080084a1
         		 r7_6 = 1;
         		 break;

         	 case 5:
         		 //0x080084a7
         		 r7_7 = 0;
         		 break;

         	 case 25:
         		 //0x080084ad
         		 r7_4 = 0;
         		 r7_6 = 1;
         		 r7_5 = 1;
         		 break;

         	 case 26:
         		 //0x080084bb
         		 r7_4 = 1;
         		 r7_6 = 1;
         		 r7_5 = 1;
         		 break;

         	 default:
         		 //loc_80084c8
         		 break;
         }

         TouchEvent.bData_0 = 1;
         KeyEvent.bData_0 = 1;
      }
      //loc_80084de
      if (r7_6 != 0)
      {
         r7_6 = 0;
         if (r7_4 != 0)
         {
            wMainloopEvents &= ~MAIN_LOOP_EVENT_AUTO_STANDBY;
         }
         else
         {
            //loc_80084fe
            wMainloopEvents |= MAIN_LOOP_EVENT_AUTO_STANDBY;
         }
         //loc_800850c
         r7_7 = 0;
      }
      //loc_8008510
      if (r7_4 != r7_3)
      {
         r7_3 = r7_4;
         sub_8002d70(TEXT_ID_AUTO_STANDBY, 37, 2, r7_4);
      }
      //loc_8008528
      if (r7_5 != 0)
      {
         sub_800c7e0(500);
      }
      //loc_8008536
   }

   return 0;
}


