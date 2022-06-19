
#include "main.h"
#include <string.h>


/* 800b494 - todo */
int sub_800b494(struct_8008d84* r7_4)
{
   uint8_t r7_f = 0xff;
   uint8_t r7_e = 0;

   for (; r7_e < bChannelCount; r7_e++)
   {
      //loc_800b4a6
      if (0 == memcmp(&ChannelList[r7_e], r7_4, sizeof(struct_8008d84)))
      {
         r7_f = r7_e;
         break;
      }
   }

   return r7_f;
}


/* 800b53c - todo */
int sub_800b53c(uint8_t r7_7)
{
   uint8_t r7_f;
   uint8_t r7_e = 0;

   if (r7_7 < 8)
   {
      for (r7_f = r7_7; r7_f < 7; r7_f++)
      {
         memcpy(&FavouriteList[r7_f], &FavouriteList[r7_f + 1], sizeof(struct_8008d84));
      }

      memset(&FavouriteList[7], 0xff, sizeof(struct_8008d84));

      bFavouriteCount++;
   }

   return r7_e;
}


/* 800b610 - todo */
void sub_800b610(uint8_t a)
{
   uint8_t r7_f;

   r7_f = sub_800b4ec(&ChannelList[a]);
   if (r7_f == 0xff)
   {
      if (bFavouriteCount < 8)
      {
         if ((ChannelList[a].wData_24 < 42) && (ChannelList[a].service_id != 0))
         {
            sub_800b6f0(ChannelList[a]);
         }
         else
         {
            //loc_800b68c
            sub_800b7f8(ChannelList[a]);
         }
      }
      else
      {
         //loc_800b6ae
         sub_8004b74(0, 72, CurrentTextTable[TEXT_ID_FAV_LIST_FULL]);
         sub_800c7e0(500);
      }
   }
   else
   {
      //loc_800b6ca
      if (bFavouriteCount != 0)
      {
         sub_800b53c(r7_f);
      }
   }
}


/* sub_800b6f0 - todo */
void sub_800b6f0(struct_8008d84 a)
{

}


/* 800b7f8 - todo */
void sub_800b7f8(struct_8008d84 a)
{

}


