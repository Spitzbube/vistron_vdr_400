
#include "main.h"


/* 8006d40 - todo */
int menu_channel_list(void)
{
   typedef int (*funcs)(void);
   funcs r7_4[] = //8012c68
   {
	  menu_automatic_search, //Automatic search
	  menu_manual_search, //Manual search
	  menu_channel_delete //Delete channel
   };
   uint8_t r7_17 = 0;
   uint8_t r7_16 = 1;
   uint8_t itemSelected = 0;
   uint8_t itemIndex = 0;
   uint8_t oldItem = 0;
   uint8_t keyCode;
   uint8_t touchCode;
   uint8_t irCode;

   draw_menu_page(TEXT_ID_CHANNEL_LIST, TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;
   //->loc_8006f00
   while (r7_16 != 0)
   {
      //loc_8006d7e
      keyCode = 0;
      if (KeyEvent.bData_0 == 0)
      {
         keyCode = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
      }
      //loc_8006d96
      touchCode = 0;
      if (TouchEvent.bData_0 == 0)
      {
         touchCode = sub_8002e98(TouchEvent.wData_2, TouchEvent.wData_4);
      }

      irCode = 0;
      ir_rc5_get_data(&rc5Data);
      if (rc5Data.Command != 0xff)
      {
          irCode = menu_list_convert_rc5_code(rc5Data.Command);
      }

      if ((touchCode | keyCode | irCode) != 0)
      {
         switch (touchCode | keyCode | irCode)
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

            draw_menu_page(TEXT_ID_CHANNEL_LIST, TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);
         }
      }
      //loc_8006ee8
      if (itemIndex != oldItem)
      {
         oldItem = itemIndex;

         draw_menu_list(TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);
      }
   }

   return r7_17;
}

