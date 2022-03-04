
#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi2;
extern void sub_800c7e0(int);
int sub_800a940(uint16_t numTxBytes, uint16_t b, uint16_t c);
int sub_8009a40(uint16_t a, uint16_t b);
uint8_t sub_8009aec(uint16_t a, uint16_t numRxBytes);

uint8_t Data_200001f0[100]; //200001f0 size?


/* 8008d14 - todo */
int sub_8008d14(uint8_t a)
{
   uint8_t f;

   Data_200001f0[0] = 0xb0;
   Data_200001f0[1] = 0x00;
   Data_200001f0[2] = a;
   Data_200001f0[3] = 0x00;
   Data_200001f0[4] = 0x00;
   Data_200001f0[5] = 0x00;

   if (0 != sub_800a940(6, 4, 5))
   {
      return 1;
   }

   f = sub_8009a40(200, 4);

   f |= sub_8009aec(100, 4);

   return f;
}


/* 8009a40 - todo */
int sub_8009a40(uint16_t a, uint16_t b)
{
   uint8_t i = 20;

   do
   {
      i--;

      sub_800c7e0(a);

      /* CS to low */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

      Data_200001f0[0] = 0;

      if (0 != HAL_SPI_Transmit(&hspi2, Data_200001f0, 1, 10))
      {
         return 0;
      }

      if (0 != HAL_SPI_Receive(&hspi2, Data_200001f0, b, 10))
      {
         return 0;
      }

      /* CS to high */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
   }
   while (((Data_200001f0[0] & 1) == 0) && (i != 0));

   if ((i == 0) || (Data_200001f0[0] & 0x40))
   {
      return 1;
   }

   return 0;
}


/* 8009aec - todo */
uint8_t sub_8009aec(uint16_t a, uint16_t numRxBytes)
{
   uint8_t f = 0;
   uint8_t i = 10;

   while (i--)
   {
      sub_800c7e0(a);

      /* CS to low */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

      Data_200001f0[0] = 0;

      if (0 != HAL_SPI_Transmit(&hspi2, Data_200001f0, 1, 10))
      {
         return 0;
      }

      if (0 != HAL_SPI_Receive(&hspi2, Data_200001f0, numRxBytes, 10))
      {
         return 0;
      }

      /* CS to high */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

      if (Data_200001f0[0] & 0x80)
      {
         break;
      }
   }

   if (Data_200001f0[0] & 0x40)
   {
      f = (Data_200001f0[4] != 0);
   }

   if (i == 0)
   {
      f = (Data_200001f0[4] != 0);
   }

   return f;
}


/* 800a940 - todo */
int sub_800a940(uint16_t numTxBytes, uint16_t numRxBytes, uint16_t c)
{
   uint8_t f;

   /* CS to low */
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

   if (0 != HAL_SPI_Transmit(&hspi2, Data_200001f0, numTxBytes, 10))
   {
      return 1;
   }

   /* CS to high */
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

   f = sub_8009aec(c, numRxBytes);

   return f;
}


