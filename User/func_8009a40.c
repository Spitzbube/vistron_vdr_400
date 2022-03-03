
#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi2;
extern void sub_800c7e0(int);


uint8_t Data_200001f0[1]; //200001f0



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

