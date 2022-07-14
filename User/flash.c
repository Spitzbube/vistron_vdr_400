
#include "main.h"


/* 8006a8e - todo */
int flash_write(uint32_t addr, uint16_t data[], uint16_t r7_6)
{
   uint8_t r7_17 = 0;
   uint16_t i;

   HAL_FLASH_Unlock();

   for (i = 0; i < r7_6; i++)
   {
      //loc_8006aaa
      if (0 != HAL_FLASH_Program(1, addr, (uint64_t)(data[i])))
      {
         r7_17 = 1;
         break;
      }

      addr += 2;
   }

   HAL_FLASH_Lock();

   return r7_17;
}


/* 8006af4 - todo */
int flash_erase(uint32_t addr)
{
   uint8_t res = 0;
   FLASH_EraseInitTypeDef eraseInit;
   uint32_t PageError;

   eraseInit.PageAddress = addr;
   eraseInit.NbPages = 1;
   eraseInit.TypeErase = 0;
   eraseInit.Banks = 1;

   HAL_FLASH_Unlock();
   if (0 != HAL_FLASHEx_Erase(&eraseInit, &PageError))
   {
      res = 1;
   }

   HAL_FLASH_Lock();

   return res;
}


