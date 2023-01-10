
#include "main.h"


/* 8006b3c - todo */
void menu_main(void)
{
   typedef int (*funcs)(void);
   funcs r7_4[] = //8012c54
   {
      menu_channel_list, //Channel list
	  menu_settings, //Settings
	  sub_80088cc, //Factory reset
	  menu_alarm, //Alarm
	  menu_sw_information //Information
   };
   uint8_t isActive = 1;
   uint8_t itemSelected = 0;
   uint8_t itemIndex = 0;
   uint8_t oldItem = 0;
   uint8_t keyCode;
   uint8_t touchCode;
   uint8_t irCode;

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   draw_menu_page(TEXT_ID_MAIN_MENU, TEXT_ID_MAIN_MENU_FIRST, TEXT_ID_MAIN_MENU_ITEMS, itemIndex);
   //->loc_8006d20
   while (isActive != 0)
   {
      //loc_8006b7a
      keyCode = 0;
      if (KeyEvent.bData_0 == 0)
      {
         keyCode = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
      }
      //loc_8006b92
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
               //0x08006c45: blue
               itemIndex++;
               if (itemIndex == TEXT_ID_MAIN_MENU_ITEMS) itemIndex = 0;
               //->8006CAA
               break;

            case 2:
               //0x08006c57: green
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = TEXT_ID_MAIN_MENU_ITEMS - 1;
               //->8006CAE
               break;

            case 4:
               //0x08006c69: yellow
               itemSelected = 1;
               //->8006CB0
               break;

            case 5:
               //0x08006c6f: white (back)
               isActive = 0;
               //->8006CB0
               break;

            case 25:
               //0x08006c75
               itemIndex = 0;
               itemSelected = 1;
               break;

            case 26:
               //0x08006c7f
               itemIndex = 1;
               itemSelected = 1;
               break;

            case 27:
               //0x08006c89
               itemIndex = 2;
               itemSelected = 1;
               break;

            case 28:
               //0x08006c93
               itemIndex = 3;
               itemSelected = 1;
               break;

            case 29:
               //0x08006c9d
               itemIndex = 4;
               itemSelected = 1;
               break;

            default:
               //0x08006ca7
               //->loc_8006cb0
               break;
         }
         //loc_8006cb0
         TouchEvent.bData_0 = 1;
         KeyEvent.bData_0 = 1;
      }
      //loc_8006cbc
      if (itemSelected != 0)
      {
         itemSelected = 0;

         if (0 != r7_4[itemIndex]())
         {
            wMainloopEvents |= 0x02;
            isActive = 0;
         }
         else
         {
            //loc_8006cf0
            TouchEvent.bData_0 = 1;
            KeyEvent.bData_0 = 1;

            draw_menu_page(TEXT_ID_MAIN_MENU, TEXT_ID_MAIN_MENU_FIRST, TEXT_ID_MAIN_MENU_ITEMS, itemIndex);
         }
      }
      //loc_8006d08
      if (itemIndex != oldItem)
      {
         oldItem = itemIndex;

         draw_menu_list(TEXT_ID_MAIN_MENU_FIRST, TEXT_ID_MAIN_MENU_ITEMS, itemIndex);
      }
      //loc_8006d20
   }
}

