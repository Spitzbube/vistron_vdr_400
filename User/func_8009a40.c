
#include "stm32f1xx_hal.h"
#include "func_8001ae8.h"

extern SPI_HandleTypeDef hspi2;
extern void sub_800c7e0(int);
int sub_800a940(uint16_t numTxBytes, uint16_t b, uint16_t c);
int sub_8009a40(uint16_t a, uint16_t b);
uint8_t sub_8009aec(uint16_t a, uint16_t numRxBytes);
int sub_8009bb8(uint8_t a);
int sub_800a25c(void);
int sub_800a884(int a);
int sub_800a8d8(uint16_t a, uint16_t b);

typedef struct
{
   uint32_t Data_0; //0
   uint32_t Data_4; //4
   int fill8[4]; //8
   uint16_t wData_24; //24
   //28
} struct_8008d84;


int Data_2000004c; //2000004c
uint8_t bData_20000054; //20000054
uint8_t bData_20000057; //20000057
uint8_t Data_200001f0[100]; //200001f0 size?
int Data_20000a4c; //20000a4c
uint8_t bData_20000a50; //20000a50
uint16_t wData_20000a56; //20000a56
uint8_t bData_20000a58; //20000a58
int Data_20000a70; //20000a70
int Data_20000a74; //20000a74
uint8_t bData_20000be4; //20000be4
struct_8008d84 Data_20000be8[8]; //20000be8 +224
struct_8008d84 Data_20000cc8[200]; //20000cc8 +5600
uint8_t bData_200022a8; //200022a8
void* Data_200023e0; //200023e0


extern const uint8_t Data_8018af4[]; //8018af4


/* 800173c - todo */
void sub_800173c(/*struct_8001ae8*/RTC_TimeTypeDef r7_c, void* r7_8, uint8_t r7_7, void* r7, uint8_t r7_18, void* f, int g, uint16_t h)
{
   sub_8005520(0xffff);
   sub_80055bc(0, 0x140, 0x30, 0);
   sub_80055bc(0, 0x140, 0xc0, 0);
   sub_8001a14(r7_8);
   sub_8001f04(r7, r7_18);

   extern void sub_8001bd8(int, int, void*, uint8_t);
   sub_8001bd8(0x0c, 6, f, h & 4);

   sub_8001cc4(0x8e, 0x2a, g);

   sub_8001eb6(r7_7);

   sub_8001ae8(r7_c);

   sub_8004560(0x123, 0xd6);

   sub_8005198(8, 0xc4, 0x1f, 1);
   sub_8005198(0x3d, 0xc4, 0x7e0, 0);
   sub_8005198(0x72, 0xc4, 0xf800, 2);
   sub_8005198(0xa7, 0xc4, 0xffe0, 3);
   sub_8005198(0x4f, 6, 0xfd20, 4);
}


void sub_80045f8()
{

}


void sub_8005ff0()
{

}


void sub_80060ac()
{

}


void sub_80060c8()
{

}


void sub_80060f4()
{

}


/* 8008a88 - todo */
int sub_8008a88(uint8_t a)
{

}


/* 8008ac4 - todo */
int sub_8008ac4(uint8_t a)
{
   if (0 != sub_800a8d8(0x0301, (a == 0)? 0: 3))
   {
      return 1;
   }

   if (a != 0)
   {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
   }
   else
   {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
   }

   return 0;
}


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


/* 8008d84 - todo */
int sub_8008d84(struct_8008d84* a)
{
   if (sub_8008d14(a->wData_24) != 0)
   {
      return 1;
   }

   Data_200001f0[0] = 0x81;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = 0;
   Data_200001f0[3] = 0;
   Data_200001f0[4] = a->Data_0;
   Data_200001f0[5] = a->Data_0 >> 8;
   Data_200001f0[6] = a->Data_0 >> 16;
   Data_200001f0[7] = a->Data_0 >> 24;
   Data_200001f0[8] = a->Data_4;
   Data_200001f0[9] = a->Data_4 >> 8;
   Data_200001f0[10] = a->Data_4 >> 16;
   Data_200001f0[11] = a->Data_4 >> 24;

   if (sub_800a940(12, 4, 10) != 0)
   {
      return 1;
   }

   return 0;
}


/* 8009020 - todo */
void sub_8009020(uint8_t a)
{

}


/* 800995c - todo */
int sub_800995c(uint16_t a)
{
   Data_200001f0[0] = 0x30;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = a;
   Data_200001f0[3] = a >> 8;
   Data_200001f0[4] = 0;
   Data_200001f0[5] = 0;

   if (sub_800a940(6, 4, 5) != 0)
   {
      return 1;
   }

   return 0;
}


/* 80099b4 - todo */
int sub_80099b4(uint8_t a)
{
   sub_8008ac4(1);

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

   if (0 != sub_8009bb8(0))
   {
      return 1;
   }

   if (0 != sub_800a25c())
   {
      return 1;
   }

   if (0 != sub_800a884(0))
   {
      return 1;
   }

   if (0 != sub_8008a88(a))
   {
      return 1;
   }

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

   sub_8008ac4(0);

   wData_20000a56 &= ~1;

   return 0;
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


/* 8009bb8 - todo */
int sub_8009bb8(uint8_t a)
{
   uint8_t arData_8[943];

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);

   sub_800c7e0(10);

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

   if (0 != sub_8009aec(100, 6))
   {
      return 1;
   }

   Data_200001f0[0] = 1;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = 0x19;
   Data_200001f0[3] = 0x3f;
   Data_200001f0[4] = 0;
   Data_200001f0[5] = 0x36;
   Data_200001f0[6] = 0x6e;
   Data_200001f0[7] = 1;
   Data_200001f0[8] = 0;
   Data_200001f0[9] = 0x10;
   Data_200001f0[10] = 0;
   Data_200001f0[11] = 0;
   Data_200001f0[12] = 0;
   Data_200001f0[13] = 0;
   Data_200001f0[14] = 0;
   Data_200001f0[15] = 0;

   if (0 != sub_800a940(16, 4, 100))
   {
      return 1;
   }

   if ((Data_200001f0[3] & 0xC0) != 0x80)
   {
      return 1;
   }

   Data_200001f0[0] = 6;
   Data_200001f0[1] = 0;

   if (0 != sub_800a940(2, 4, 1))
   {
      return 1;
   }
   //loc_8009c96: TODO
   memcpy(arData_8, Data_8018af4, 943);

   /* CS to low */
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

   Data_200001f0[0] = 4;

   if (0 != HAL_SPI_Transmit(&hspi2, Data_200001f0, 1, 10))
   {
      return 1;
   }

   if (0 != HAL_SPI_Transmit(&hspi2, arData_8, 943, 10))
   {
      return 1;
   }

   /* CS to high */
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

   if (0 != sub_8009aec(1, 4))
   {
      return 1;
   }

   Data_200001f0[0] = 6;
   Data_200001f0[1] = 0;

   if (0 != sub_800a940(2, 4, 1))
   {
      return 1;
   }

   Data_200001f0[0] = 5;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = 0;
   Data_200001f0[3] = 0;

   if (a != 0)
   {
      Data_200001f0[4] = 0;
      Data_200001f0[5] = 0;
      Data_200001f0[6] = 0x21;
      Data_200001f0[7] = 0;
   }
   else
   {
      Data_200001f0[4] = 0;
      Data_200001f0[5] = 0;
      Data_200001f0[6] = 0x20;
      Data_200001f0[7] = 0;
   }

   if (0 != sub_800a940(8, 4, 1))
   {
      return 1;
   }

   Data_200001f0[0] = 6;
   Data_200001f0[1] = 0;

   if (0 != sub_800a940(2, 6, 10))
   {
      return 1;
   }

   Data_200001f0[0] = 5;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = 0;
   Data_200001f0[3] = 0;

   if (a != 0)
   {
      Data_200001f0[4] = 0;
      Data_200001f0[5] = 0;
      Data_200001f0[6] = 0x2C;
      Data_200001f0[7] = 0;
   }
   else
   {
      Data_200001f0[4] = 0;
      Data_200001f0[5] = 0;
      Data_200001f0[6] = 0x22;
      Data_200001f0[7] = 0;
   }

   Data_200001f0[8] = 0;
   Data_200001f0[9] = 0;
   Data_200001f0[10] = 0;
   Data_200001f0[11] = 0;

   if (0 != sub_800a940(12, 4, 50))
   {
      return 1;
   }

   Data_200001f0[0] = 7;
   Data_200001f0[2] = 0; /* BUG!! */

   if (0 != sub_800a940(2, 4, 100))
   {
      return 1;
   }

   if ((Data_200001f0[3] & 0xC0) != 0xC0)
   {
      return 1;
   }

   return 0;
}


/* 800a25c - todo */
int sub_800a25c(void)
{

}


/* 800a884 - todo */
int sub_800a884(int a)
{

}


/* 800a8d8 - todo */
int sub_800a8d8(uint16_t a, uint16_t b)
{
   Data_200001f0[0] = 0x13;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = a;
   Data_200001f0[3] = a >> 8;
   Data_200001f0[4] = b;
   Data_200001f0[5] = b >> 8;

   if (0 != sub_800a940(6, 4, 1))
   {
      return 1;
   }

   return 0;
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


/* 800a9a8 - todo */
int sub_800a9a8(void)
{

}


/* 800abb0 - todo */
void sub_800abb0(struct_8008d84* a)
{
   Data_200023e0 = a;

   if (bData_20000a58 != bData_20000054)
   {
      bData_20000054 = bData_20000a58;
   }

   if ((a->wData_24 < 42) && (a->Data_0 != 0))
   {
      if ((wData_20000a56 & 1) == 0)
      {
         sub_8009020(bData_20000057);
      }

      if (0 == sub_8008d84(a))
      {
         wData_20000a56 &= ~2;
      }
   }
   else
   {
      if ((wData_20000a56 & 1) != 0)
      {
         sub_80099b4(bData_20000057);
      }

      if (0 == sub_800995c(a->wData_24))
      {
         wData_20000a56 &= ~2;
      }
   }

   wData_20000a56 |= 0x40;
}


/* 800ae28 - todo */
void sub_800ae28(void)
{
   struct_8008d84* a = (wData_20000a56 & 4)? Data_20000be8: Data_20000cc8;

   if ((a[bData_20000a58].wData_24 < 42) && (a[bData_20000a58].Data_0 != 0))
   {
      sub_8009020(bData_20000057);
   }
   else
   {
      sub_80099b4(bData_20000057);
   }

   sub_800abb0(&a[bData_20000a58]);

   wData_20000a56 |= 0x100;
}


/* 800b270 - todo */
int sub_800b270(void)
{
   memset(Data_20000cc8, 0xff, sizeof(Data_20000cc8));
   memset(Data_20000be8, 0xff, sizeof(Data_20000be8));

   bData_200022a8 = 0;
   bData_20000be4 = 0;

   return 0;
}


