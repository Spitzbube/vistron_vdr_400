
#include "main.h"
#include <string.h>


/* 800b494 - todo */
int sub_800b494(struct_8008d84* r7_4)
{
   uint8_t r7_f = 0xff;
   uint8_t i = 0;

   for (; i < bChannelCount; i++)
   {
      //loc_800b4a6
      if (0 == memcmp(&ChannelList[i], r7_4, sizeof(struct_8008d84)))
      {
         r7_f = i;
         break;
      }
   }

   return r7_f;
}


/* 800b53c - todo */
int sub_800b53c(uint8_t r7_7)
{
   uint8_t i;
   uint8_t r7_e = 0;

   if (r7_7 < 8)
   {
      for (i = r7_7; i < 7; i++)
      {
         memcpy(&FavouriteList[i], &FavouriteList[i + 1], sizeof(struct_8008d84));
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


/* 800b6f0 - todo */
int sub_800b6f0(struct_8008d84 a)
{
   uint8_t res = 0;
   uint8_t i;
   uint8_t r7_1d = 0;
   struct_8008d84 empty;

   memset(&empty, 0xff, sizeof(struct_8008d84));

   for (i = 0; i < 8; i++)
   {
      //loc_800b71a
      if (0 == memcmp(&FavouriteList[i], &empty, sizeof(struct_8008d84)))
      {
         break;
      }
      r7_1d++;
   }
   //loc_800b74e
   if (r7_1d < 8)
   {
      FavouriteList[r7_1d].wData_24 = a.wData_24;
      FavouriteList[r7_1d].service_id = a.service_id;
      FavouriteList[r7_1d].component_id = a.component_id;
      memset(&FavouriteList[r7_1d].Data_8, ' ', 16);
      memcpy(&FavouriteList[r7_1d].Data_8, &a.Data_8, 16);
      //FavouriteList[r7_1d].Data_8 = a.Data_8;
      r7_1d++;
      bFavouriteCount = r7_1d;
   }
   else
   {
      //loc_800b7da
      res = 1;
   }

   return res;
}


/* 800b7f8 - todo */
int sub_800b7f8(struct_8008d84 a)
{
   uint8_t res = 0;
   uint8_t i;
   uint8_t r7_1d = 0;
   struct_8008d84 empty;

   memset(&empty, 0xff, sizeof(struct_8008d84));

   for (i = 0; i < 8; i++)
   {
	  //loc_800b822
	  if (0 == memcmp(&FavouriteList[i], &empty, sizeof(struct_8008d84)))
	  {
		 break;
	  }
	  r7_1d++;
   }
   //loc_800b856
   if (r7_1d < 8)
   {
	  FavouriteList[r7_1d].wData_24 = a.wData_24;
	  memset(&FavouriteList[r7_1d].Data_8, ' ', 16);
	  memcpy(&FavouriteList[r7_1d].Data_8, &a.Data_8, 8);
	  //FavouriteList[r7_1d].Data_8 = a.Data_8;
	  r7_1d++;
	  bFavouriteCount = r7_1d;
   }
   else
   {
	  //loc_800b8b8
	  res = 1;
   }

   return res;
}


