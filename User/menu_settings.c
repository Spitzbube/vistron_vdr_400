
#include "main.h"


/* 8006f24 - todo */
int menu_settings(void)
{
   typedef int (*funcs)(void);
   funcs r7_4[] = //8012c74
   {
	  menu_language, //Language
	  menu_sleep_timer, //Sleep-Timer
	  menu_auto_standby, //Auto-Standby
   };
   uint8_t r7_17 = 0;
   uint8_t r7_16 = 1;
   uint8_t itemSelected = 0;
   uint8_t itemIndex = 0;
   uint8_t oldItem = 0;
   uint8_t r7_12;
   uint8_t r7_11;

   sub_8002d70(TEXT_ID_SETTINGS, TEXT_ID_SETTINGS_FIRST, TEXT_ID_SETTINGS_ITEMS, itemIndex);

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;
   //->loc_80070f0
   while (r7_16 != 0)
   {
      //loc_8006f62
	  r7_12 = 0;
	  if (KeyEvent.bData_0 == 0)
	  {
         r7_12 = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
	  }

	  r7_11 = 0;
	  if (TouchEvent.bData_0 == 0)
	  {
         r7_11 = sub_8002e98(TouchEvent.wData_2, TouchEvent.wData_4);
	  }

	  if ((r7_11 | r7_12) != 0)
	  {
         switch (r7_11 | r7_12)
         {
            case 3:
               //0x08007025
               itemIndex++;
               if (itemIndex == 3) itemIndex = 0;
               break;

            case 2:
               //0x08007037
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = 2;
               break;

            case 4:
               //0x08007049
               itemSelected = 1;
               break;

            case 5:
               //0x0800704f
               r7_16 = 0;
               break;

            case 25:
               //0x08007055
               itemIndex = 0;
               itemSelected = 1;
               break;

            case 26:
               //0x0800705f
               itemIndex = 1;
               itemSelected = 1;
               break;

            case 27:
               //0x08007069
               itemIndex = 2;
               itemSelected = 1;
               break;

            default:
               //0x08007073
               //->loc_800707c
               break;
         }
         //loc_800707c
         TouchEvent.bData_0 = 1;
         KeyEvent.bData_0 = 1;
	  }
	  //loc_8007088
	  if (itemSelected != 0)
	  {
         itemSelected = 0;

         if (0 != r7_4[itemIndex]())
         {
            wMainloopEvents |= 0x02;
            r7_16 = 0;
            r7_17 = 1;
         }
         else
         {
            //loc_80070c0
            sub_8002d70(TEXT_ID_SETTINGS, TEXT_ID_SETTINGS_FIRST, TEXT_ID_SETTINGS_ITEMS, itemIndex);

            TouchEvent.bData_0 = 1;
            KeyEvent.bData_0 = 1;
         }
	  }
	  //loc_80070d8
	  if (itemIndex != oldItem)
	  {
         oldItem = itemIndex;

         sub_8002cac(TEXT_ID_SETTINGS_FIRST, TEXT_ID_SETTINGS_ITEMS, itemIndex);
	  }
	  //loc_80070f0
   }

   return r7_17;
}

