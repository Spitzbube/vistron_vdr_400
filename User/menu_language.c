
#include "main.h"


/* 8008030 - todo */
int menu_language(void)
{
   uint8_t r7_7 = 1;
   uint8_t itemIndex = Data_20000a50.b2;
   uint8_t oldItem = Data_20000a50.b2;
   uint8_t r7_4;
   uint8_t r7_3;
   uint8_t r7_2 = Data_20000a50.b2;

   sub_8002d70(TEXT_ID_LANGUAGE, TEXT_ID_LANGUAGE_FIRST, TEXT_ID_LANGUAGE_ITEMS, itemIndex);

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;
   //->loc_80081d4
   while (r7_7 != 0)
   {
      //loc_8008078
      r7_4 = 0;
      if (Data_20000a48.bData_0 == 0)
      {
         r7_4 = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_8008090
      r7_3 = 0;
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_3 = sub_8002e98(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_80080b0
      if ((r7_3 | r7_4) != 0)
      {
         switch (r7_3 | r7_4)
         {
            case 2:
               //0x08008135
               itemIndex++;
               if (itemIndex == 2) itemIndex = 0;
               break;

            case 3:
               //0x08008147
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = 1;
               break;

            case 4:
               //0x08008159
               r7_3 = itemIndex + 25;
               //break; //fall through

            case 25:
            case 26:
               //0x0800815f
               if (r7_2 != (r7_3 - 25))
               {
                  Data_20000a50.b2 = (r7_3 - 25) & 1;
                  menu_set_language(Data_20000a50.b2);
                  sub_800ba74(ChannelList, FavouriteList, &currentAlarmTime, &Data_20000a50);
               }
               //800819A
               r7_7 = 0;
               break;

            case 5:
               //0x080081a1
               r7_7 = 0;
               break;

            default:
               //0x080081a7
               //->loc_80081b0
               break;
         }
         //loc_80081b0
         Data_20000bc0.bData_0 = 1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_80081bc
      if (itemIndex != oldItem)
      {
         oldItem = itemIndex;

         sub_8002cac(TEXT_ID_LANGUAGE_FIRST, TEXT_ID_LANGUAGE_ITEMS, itemIndex);
      }
      //loc_80081d4
   }

   return 0;
}

