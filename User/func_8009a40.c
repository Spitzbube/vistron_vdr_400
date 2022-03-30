
#include <string.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"

extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi2;

extern void Error_Handler(void);
extern void sub_800c7e0(int);
int sub_800b2ac(void* a, void* b);


//_sdata: 20000000 - 200000c8 -> 080193f8 - 80194C0

Func_20000000 Funcs_20000000[] = //20000000 (80193f8)
{
   sub_8004be8,
   sub_8004c4c,
   sub_8004cb0,
   sub_8004d14,
   sub_8004d78,
   sub_8004e74,
   sub_8004f24,
   sub_8004fc4,
   sub_8005074
};
Struct_20000024 Data_20000024 = //20000024 (801941C)
{
   320, 240
};
//20000028 (8019420)
Struct_2000002c Data_2000002c = //2000002c (8019424)
{
   0x0000ffe0,
   0,
   &Data_2000003c, //0x2000003c,
   1
};
Struct_2000002c_Inner8 Data_2000003c = //2000003c (8019434)
{
   0, //0x08012f90/TODO*/,
   7,
   12
};

uint8_t bData_20000054 = 1; //20000054 (801944C)
uint8_t bData_20000055 = 0xff; //20000055 (801944D)
uint8_t bData_20000056 = 4; //20000056 (801944E)
uint8_t bData_20000057 = 31; //20000057 (801944F)
//uint32_t SystemCoreClock; //20000058 (8019450)
//uint32_t uwTickPrio; //2000005C (8019454)
//HAL_TickFreqTypeDef uwTickFreq; //20000060 (8019458)
//_impure_ptr; //?? //20000064 (801945C)
//impure_data; //?? //20000068 (8019460 -> 80194C0?)
Struct_200000e4 Data_200000e4; //200000e4
uint8_t bData_200000e8; //200000e8
uint8_t bData_200000e9; //200000e9
uint8_t bData_200000ea; //200000ea
uint8_t bData_200000eb; //200000eb

uint8_t Data_200001f0[100]; //200001f0 size?
//uint8_t bData_20000a48; //20000a48
uint8_t bData_20000a48[2]; //20000a48, size?
Struct_20000a4c Data_20000a4c; //20000a4c
Struct_20000a50 Data_20000a50; //20000a50
uint16_t wData_20000a56; //20000a56
uint8_t bData_20000a58; //20000a58
uint8_t bData_20000a59; //20000a59
uint8_t bData_20000a6c; //20000a6c
uint8_t bData_20000a6d; //20000a6d
RTC_TimeTypeDef Data_20000a70; //20000a70
RTC_DateTypeDef Data_20000a74; //20000a74
uint8_t bData_20000b7d; //20000b7d
struct
{
   int Data_0; //0
   uint16_t wData_4; //4
   uint16_t wData_6; //6
   uint16_t wData_8; //8
   uint16_t wData_10; //19
   int Data_12; //12
   int Data_16; //16
   int Data_20; //20
   int Data_24; //24
   int Data_28; //28
   int Data_32; //32
   uint16_t wData_36; //36
   uint16_t wData_38; //38
   uint16_t wData_40; //40
   uint16_t wData_42; //42
   uint16_t wData_44; //44
   uint16_t wData_46; //46

} Data_20000b90; //20000b90
Struct_20000bc0 Data_20000bc0;
int* Data_20000bc8; //20000bc8
char strFMVersion[12]; //20000bcc
char strDABVersion[12]; //20000bd8
uint8_t bData_20000be4; //20000be4
struct_8008d84 Data_20000be8[8]; //20000be8 +224
struct_8008d84 Data_20000cc8[200]; //20000cc8 +5600
uint8_t bData_200022a8; //200022a8
struct_8008d84* Data_200023e0; //200023e0

extern int sub_800bc04(struct_8008d84* a, struct_8008d84* b, void* c, void* d);


/* 800173c - todo */
void sub_800173c(RTC_TimeTypeDef r7_c, void* r7_8, uint8_t r7_7, void* r7, uint8_t r7_18, void* f, int g, uint16_t h)
//new: RTC_TimeTypeDef a, void* b, uint8_t c, void* d, uint8_t e, int f, void* g, uint16_t h
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   sub_8001a14(r7_8);
   sub_8001f04(r7, r7_18);

   extern void sub_8001bd8(int, int, void*, uint8_t);
   sub_8001bd8(0x0c, 6, f, h & 4);

   sub_8001cc4(0x8e, 0x2a, g);

   sub_8001eb6(r7_7);

   sub_8001ae8(r7_c);

   sub_8004560(0x123, 0xd6);

   sub_8005198(8, 196, 0x1f, 1);
   sub_8005198(61, 196, 0x7e0, 0); //x+53
   sub_8005198(114, 196, 0xf800, 2);
   sub_8005198(167, 196, 0xffe0, 3);
   sub_8005198(79, 6, 0xfd20, 4);
}


/* 8001224 - todo */
int sub_8001224(int a)
{

}


/* 8001a14 - todo */
void sub_8001a14(void* a)
{
   uint16_t r7_e;

   if (bData_200022a8 != 0)
   {
      ili9341_set_font(&Data_2000004c);
      ili9341_draw_box(0, 63, 320, 24, 0xffff);
      sub_80060c8(0, 0xffff);
      r7_e = sub_800c88c(a, 0x10);
      ili9341_set_cursor(160 - (r7_e * Data_2000004c.width) / 2, 63);
      ili9341_draw_string(a, r7_e);
   }
   else
   {
      r7_e = sub_8001224(Data_20000bc8[8]);
      ili9341_set_font(&Data_2000004c);
      sub_80060c8(0, 0xffff);
      ili9341_set_cursor(160 - (r7_e * Data_2000004c.width) / 2, 63);
      sub_8005edc(Data_20000bc8[8]);
   }
}


/* 8003038 - todo */
void sub_8003038(uint16_t a, Struct_2000002c_Inner8* b)
{
   uint16_t r7_e;

   ili9341_set_font(b);

   ili9341_draw_box(0, 23, 320, 24, 0xffff);

   sub_80060c8(0, 0xffff);

   r7_e = sub_8001224(Data_20000bc8[a]);

   ili9341_set_cursor(160 - (r7_e * b->width) / 2, 0x18);

   sub_8005edc(Data_20000bc8[a]);
}


void sub_80045f8()
{

}


void sub_8004be8(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8004c4c(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8004cb0(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8004d14(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8004d78(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8004e74(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8004f24(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8004fc4(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


void sub_8005074(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


/* 8005198 - todo */
void sub_8005198(uint16_t x, uint16_t y, uint16_t color, uint8_t r7_1)
{
   ili9341_draw_box(x, y, 36, 36, color);

   (Funcs_20000000)[r7_1](x + 18, y + 18, 0, color);

   ili9341_draw_rect(x, y, 36, 36, 0);
}


/* 8005204 - todo */
void sub_8005204(uint8_t a)
{

}


/* 8006254 - todo */
uint8_t sub_8006254(uint8_t r7_7, uint8_t r7_6, uint8_t r7_5, uint8_t r7_4, uint8_t r7_18, uint8_t r7_1c)
{
   uint8_t r7_f = 0;

   if (r7_1c != 0)
   {
      r7_f |= 0x04;
   }

   if (r7_18 != 0)
   {
      r7_f |= 0x08;
   }

   if (r7_4 != 0)
   {
      r7_f |= 0x10;
   }

   if (r7_5 != 0)
   {
      r7_f |= 0x20;
   }

   if (r7_6 != 0)
   {
      r7_f |= 0x40;
   }

   if (r7_7 != 0)
   {
      r7_f |= 0x80;
   }

   return r7_f;
}


/* 80062d8 - todo */
void sub_80062d8(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_GPIOE_CLK_ENABLE();

   GPIO_InitStruct.Pin = 0xcfb3; //1100 1111 1011 0011 = FSMC_D1, FSMC_D0, FSMC_A16, FSMC_D15 ... FSMC_D13, FSMC_D3, FSMC_D2
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = 0xff80; //1111 1111 1000 0000 = FSMC_D12 ... FSMC_D4
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = GPIO_PIN_1;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


/* 80063a4 - todo */
void sub_80063a4(void)
{
   SRAM_HandleTypeDef hsram;
   FSMC_NORSRAM_TimingTypeDef Timing = {0};

   hsram.Instance = FSMC_NORSRAM_DEVICE;
   hsram.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

   hsram.Init.NSBank = FSMC_NORSRAM_BANK1;
   hsram.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
   hsram.Init.MemoryType = FSMC_MEMORY_TYPE_NOR;
   hsram.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
   hsram.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
   hsram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
   hsram.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
   hsram.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
   hsram.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
   hsram.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
   hsram.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
   hsram.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
   hsram.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;

   Timing.AddressSetupTime = 3;
   Timing.AddressHoldTime = 0;
   Timing.DataSetupTime = 6;
   Timing.BusTurnAroundDuration = 0;
   Timing.CLKDivision = 1;
   Timing.DataLatency = 0;
   Timing.AccessMode = FSMC_ACCESS_MODE_B;

   HAL_SRAM_Init(&hsram, &Timing, NULL);
}


/* 8006434 - todo */
int sub_8006434(void)
{
   uint8_t r7_7 = 1;

   Data_20000bc0.bData_0 = 1;
   Data_20000bc0.wData_2 = 0;
   Data_20000bc0.wData_4 = 0;

   Data_20000b90.Data_0 = 0;
   Data_20000b90.wData_4 = 0x8000;
   Data_20000b90.wData_6 = 0x8000;
   Data_20000b90.wData_8 = 0;
   Data_20000b90.wData_10 = 0;
   Data_20000b90.Data_12 = 0x3db50005;
   Data_20000b90.Data_16 = 0x3ada36b7;
   Data_20000b90.Data_20 = 0xc1f9d490;
   Data_20000b90.Data_24 = 0xba638759;
   Data_20000b90.Data_28 = 0xbd878821;
   Data_20000b90.Data_32 = 0x437f9706;
   Data_20000b90.wData_36 = 0x869;
   Data_20000b90.wData_38 = 0x23a;
   Data_20000b90.wData_40 = 0x2a5;
   Data_20000b90.wData_42 = 0x7f8;
   Data_20000b90.wData_44 = 0xddb;
   Data_20000b90.wData_46 = 0xd7d;

   sub_800651c();
   sub_8006694(1);

   if ((Data_20000b90.wData_4 < 0x1000) &&
		   (Data_20000b90.wData_6 < 0x1000))
   {
      r7_7 = 0;

      sub_8006618();
      sub_8006624();
   }

   return r7_7;
}


/* 800651c - todo */
void sub_800651c(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();

   GPIO_InitStruct.Pin = GPIO_PIN_12;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = GPIO_PIN_7;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = GPIO_PIN_6;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = GPIO_PIN_7;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = GPIO_PIN_6;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   sub_800691c(1);
   sub_80068e4(0);
   sub_8006950(0);
}


/* 8006618 - complete */
void sub_8006618(void)
{
   /* empty */
}


/* 8006624 - complete */
void sub_8006624(void)
{
   /* empty */
}


/* 8006694 - todo */
void sub_8006694(uint8_t a)
{
   uint16_t i;
   uint32_t r7_10 = 0;
   uint32_t r7_c = 0;
   uint16_t r7_a;

   if (a == 0)
   {
      Data_20000b90.wData_4 = sub_80069b4(0x900000);
      Data_20000b90.wData_6 = sub_80069b4(0xd00000);
   }
   else
   {
      sub_80069b4(0x900000);

      for (i = 0; i < 3; i++)
      {
         //loc_80066dc
         r7_a = sub_80069b4(0x900000);
         r7_10 += r7_a;

         r7_a = sub_80069b4(0xd00000);
         r7_c += r7_a;
      }

      Data_20000b90.wData_4 = r7_10 / 4;
      Data_20000b90.wData_6 = r7_c / 4;
   }
}


/* 80068e4 - todo */
void sub_80068e4(uint8_t a)
{
   if (a == 1)
   {
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
   }
   else
   {
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
   }
}


/* 800691c - todo */
void sub_800691c(uint8_t a)
{
   if (a == 1)
   {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
   }
   else
   {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
   }
}


/* 8006950 - todo */
void sub_8006950(uint8_t a)
{
   if (a == 1)
   {
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
   }
   else
   {
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
   }
}


/* 8006984 - todo */
int sub_8006984(void)
{
   return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
}


/* sub_800699c - todo */
int sub_800699c(void)
{
   return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
}


/* 80069b4 - todo */
uint16_t sub_80069b4(int a)
{
   uint16_t i;
   uint32_t r7_10 = 0x800000;
   uint16_t r7_e = 0x800;
   uint16_t r7_c = 0;

   sub_8006a70(100);
   sub_800691c(0);
   sub_8006a70(500);

   for (i = 0; i < 24; i++)
   {
      if ((a & r7_10) == 0)
      {
         sub_8006950(0);
      }
      else
      {
         sub_8006950(1);
      }

      sub_80068e4(1);

      if ((i > 8) && (i < 21))
      {
         if (0 != sub_8006984())
         {
            r7_c |= r7_e;
         }

         r7_e >>= 1;
      }

      sub_8006a70(500);
      sub_80068e4(0);
      sub_8006a70(500);

      r7_10 >>= 1;
   }

   sub_8006a70(500);
   sub_800691c(1);
   sub_8006a70(500);

   return r7_c;
}


/* 8006a70 - todo */
void sub_8006a70(int a)
{
	while (a-- != 0)
	{
		/* delay */
	}
}

