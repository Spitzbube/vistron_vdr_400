
#include "main.h"


/* 8006d40 - todo */
int menu_channel_list(void)
{
   typedef int (*funcs)(void);
   funcs r7_4[] = //8012c68
   {
	  menu_automatic_search, //Automatic search
	  sub_8007414, //Manual search
	  sub_80075e9 //Delete channel
   };
   uint8_t r7_17 = 0;
   uint8_t r7_16 = 1;
   uint8_t itemSelected = 0;
   uint8_t itemIndex = 0;
   uint8_t oldItem = 0;
   uint8_t r7_12;
   uint8_t r7_11;

   sub_8002d70(TEXT_ID_CHANNEL_LIST, TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;
   //->loc_8006f00
   while (r7_16 != 0)
   {
      //loc_8006d7e
      r7_12 = 0;
      if (KeyEvent.bData_0 == 0)
      {
         r7_12 = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
      }
      //loc_8006d96
      r7_11 = 0;
      if (TouchEvent.bData_0 == 0)
      {
         r7_11 = sub_8002e98(TouchEvent.wData_2, TouchEvent.wData_4);
      }
      //loc_8006db6
      if ((r7_11 | r7_12) != 0)
      {
         switch (r7_11 | r7_12)
         {
            case 3:
               //0x08006e41
               itemIndex++;
               if (itemIndex == TEXT_ID_CHANNEL_LIST_ITEMS) itemIndex = 0;
               break;

            case 2:
               //0x08006e53
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = 2;
               break;

            case 4:
               //0x08006e65
               itemSelected = 1;
               break;

            case 5:
               //0x08006e6b
               r7_16 = 0;
               break;

            case 25:
               //0x08006e71
               itemIndex = 0;
               itemSelected = 1;
               break;

            case 26:
               //0x08006e7b
               itemIndex = 1;
               itemSelected = 1;
               break;

            case 27:
               //0x08006e85
               itemIndex = 2;
               itemSelected = 1;
               break;

            default:
               //0x08006e8f
               break;
         }
      }
      //loc_8006ea4
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
            //loc_8006edc
            TouchEvent.bData_0 = 1;
            KeyEvent.bData_0 = 1;

            sub_8002d70(TEXT_ID_CHANNEL_LIST, TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);
         }
      }
      //loc_8006ee8
      if (itemIndex != oldItem)
      {
         oldItem = itemIndex;

         sub_8002cac(TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);
      }
   }

   return r7_17;
}

