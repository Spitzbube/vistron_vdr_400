
#include "main.h"


/* 800ba74 - todo */
int persist_write(struct_8008d84* channels, struct_8008d84* favs, void* r7_4, void* r7)
{
   uint8_t r7_1f = 0;

   if (0 == persist_clear())
   {
      uint16_t r7_16 = 0x524d;

      if (0 != flash_write(0x807e800, &r7_16, 1))
      {
         r7_1f = 1;
      }
	  //loc_800baae
	  r7_16 = 1;
	  if (0 != flash_write(0x807e802, &r7_16, 1))
	  {
		 r7_1f = 1;
	  }
      //loc_800baca
	  uint32_t r7_18 = calculate_crc(0, channels, 5600);
	  r7_18 = calculate_crc(r7_18, favs, 224);
	  r7_18 = calculate_crc(r7_18, r7_4, 4);
	  r7_18 = calculate_crc(r7_18, r7, 4);
	  r7_16 = r7_18;
	  if (0 != flash_write(0x807e804, &r7_16, 1))
	  {
         r7_1f = 1;
	  }
	  //loc_800bb1a
	  r7_16 = r7_18 >> 16;
	  if (0 != flash_write(0x807e806, &r7_16, 1))
	  {
         r7_1f = 1;
	  }
	  //loc_800bb3a
	  if (0 != flash_write(0x807e808, (uint16_t*)channels, 2800))
	  {
         r7_1f = 1;
	  }
	  //loc_800bb50
	  if (0 != flash_write(0x807fde8, (uint16_t*)favs, 112))
	  {
		r7_1f = 1;
	  }
	  //loc_800bb64
	  if (0 != flash_write(0x807feca, (uint16_t*)r7_4, 2))
	  {
		r7_1f = 1;
	  }
	  //loc_800bb78
	  if (0 != flash_write(0x807fece, (uint16_t*)r7, 2))
	  {
		r7_1f = 1;
	  }
   }
   else
   {
      //loc_800bb8e
      r7_1f = 1;
   }

   return r7_1f;
}


/* 800bbbc - todo */
int persist_clear(void)
{
   uint8_t i;
   uint8_t res = 0;
   int addr = 0x807e800;

   for (i = 0; i < 3; i++)
   {
      if (0 != flash_erase(addr))
      {
         res = 1;
         break;
      }

      addr += 0x800;
   }

   return res;
}


/* 800bc04 - todo */
int persist_read(struct_8008d84* r7_c, struct_8008d84* r7_8, void* r7_4, void* r7)
{
   uint16_t* r7_2c;
   uint16_t* r7_28;
   uint32_t r7_24;
   uint32_t* r7_20;
   uint32_t* r7_1c;
   uint32_t r7_18;
   uint32_t r7_14;

   r7_20 = (void*) 0x807e804;
   r7_1c = &r7_14;
   *r7_1c = *r7_20;

   r7_28 = (void*) 0x807e808;
   r7_2c = (void*) r7_c;

   for (r7_24 = 0; r7_24 < 2800; r7_24++)
   {
	   //loc_800bc32
      *r7_2c++ = *r7_28++;
   }

   r7_28 = (void*) 0x807fde8;
   r7_2c = (void*) r7_8;

   for (r7_24 = 0; r7_24 < 112; r7_24++)
   {
	   //loc_800bc5e
      *r7_2c++ = *r7_28++;
   }

   r7_20 = (void*) 0x807feca;
   r7_1c = r7_4;
   *r7_1c++ = *r7_20++;

   r7_20 = (void*) 0x807fece;
   r7_1c = r7;
   *r7_1c = *r7_20;

   r7_18 = calculate_crc(0, r7_c, 0x15e0);
   r7_18 = calculate_crc(r7_18, r7_8, 0xe0);
   r7_18 = calculate_crc(r7_18, r7_4, 4);
   r7_18 = calculate_crc(r7_18, r7, 4);

   if (r7_14 != r7_18)
   {
      persist_clear();

      memset(r7_c, 0xff, 0x15e0);
      memset(r7_8, 0xff, 0xe0);
      memset(r7_4, 0xff, 4);
      memset(r7, 0xff, 4);

      return 1;
   }
   //loc_800bd0e
   return 0;
}


