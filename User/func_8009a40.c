
#include <string.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"

extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi2;

extern void Error_Handler(void);
extern void sub_800c7e0(int);
int si46xx_send_command(uint16_t numTxBytes, uint16_t b, uint16_t c);
int si46xx_read_stc_reply(uint16_t a, uint16_t b);
uint8_t si46xx_read_reply(uint16_t a, uint16_t numRxBytes);
int si46xx_load_and_boot(uint8_t a);
int si46xx_set_dab_config(void);
int si46xx_set_config(void);
int si46xx_set_audio_output(uint8_t a);
int si46xx_set_property(uint16_t name, uint16_t value);
int sub_800b2ac(void* a, void* b);

typedef struct
{
   uint32_t service_id; //0
   uint32_t component_id; //4
   int fill8[4]; //8
   uint16_t wData_24; //24
   //28
} struct_8008d84;

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
Struct_2000002c_Inner8 Data_2000004c = //2000004c (8019444)
{
   0, //0x08014ec4/*TODO*/,
   17,
   24
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

uint8_t Data_200001f0[100]; //200001f0 size?
uint8_t bData_20000a48; //20000a48
struct
{
	uint16_t a;
	uint16_t b;
} Data_20000a4c; //20000a4c
struct
{
	int b0: 1;
	uint8_t b1: 1;
	uint8_t b2: 1;
	int a: 5;
	uint8_t b: 6;
} Data_20000a50; //20000a50
uint16_t wData_20000a56; //20000a56
uint8_t bData_20000a58; //20000a58
uint8_t bData_20000a59; //20000a59
uint8_t bData_20000a6c; //20000a6c
uint8_t bData_20000a6d; //20000a6d
int Data_20000a70; //20000a70
RTC_DateTypeDef Data_20000a74; //20000a74
uint8_t bData_20000b7d; //20000b7d
//uint8_t bData_20000bc0; //20000bc0
struct
{
	uint8_t bData_0; //0
	uint16_t wData_2; //2
	uint16_t wData_4; //4

} Data_20000bc0;
int* Data_20000bc8; //20000bc8
char strFMVersion[12]; //20000bcc
char strDABVersion[12]; //20000bd8
uint8_t bData_20000be4; //20000be4
struct_8008d84 Data_20000be8[8]; //20000be8 +224
struct_8008d84 Data_20000cc8[200]; //20000cc8 +5600
uint8_t bData_200022a8; //200022a8
struct_8008d84* Data_200023e0; //200023e0

extern int sub_800bc04(struct_8008d84* a, struct_8008d84* b, void* c, void* d);

extern const uint8_t si46xx_image_data[]; //8018af4


#define SI46XX_RD_REPLY                      0x00
#define SI46XX_POWER_UP                      0x01
#define SI46XX_HOST_LOAD                     0x04
#define SI46XX_FLASH_LOAD                    0x05
#define SI46XX_LOAD_INIT                     0x06
#define SI46XX_BOOT                          0x07
#define SI46XX_GET_FUNC_INFO                 0x12
#define SI46XX_SET_PROPERTY                  0x13

#define SI46XX_FM_TUNE_FREQ                  0x30

#define SI46XX_DAB_START_DIGITAL_SERVICE     0x81
#define SI46XX_DAB_TUNE_FREQ                 0xB0

#define SI46XX_FM_INT_CTL_ENABLE             0x0000
#define SI46XX_DIGITAL_IO_OUTPUT_SELECT      0x0200
#define SI46XX_AUDIO_ANALOG_VOLUME           0x0300
#define SI46XX_AUDIO_MUTE                    0x0301
#define SI46XX_PIN_CONFIG_ENABLE             0x0800
#define SI46XX_FM_SEEK_FREQUENCY_SPACING     0x3102
#define SI46XX_FM_VALID_SNR_THRESHOLD        0x3204
#define SI46XX_FM_RSQ_SNR_HIGH_THRESHOLD     0x3301
#define SI46XX_FM_RSQ_RSSI_HIGH_THRESHOLD    0x3303
#define SI46XX_FM_RDS_INTERRUPT_SOURCE       0x3C00
#define SI46XX_FM_RDS_INTERRUPT_FIFO_COUNT   0x3C01
#define SI46XX_FM_RDS_CONFIG                 0x3C02
#define SI46XX_FM_RDS_CONFIDENCE             0x3C03
#define SI46XX_DAB_TUNE_FE_CFG               0x1712
#define SI46XX_DAB_TUNE_FE_VARM              0x1710
#define SI46XX_DAB_TUNE_FE_VARB              0x1711


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

void sub_8005a34(int16_t a, int16_t b, int c, int d, int e);
void sub_800581e(int16_t a, int16_t b, int c, int d, int e);

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
void sub_8005198(uint16_t r7_6, uint16_t r7_4,
		uint16_t r7_2, uint8_t r7_1)
{
   sub_8005a34(r7_6, r7_4, 0x24, 0x24, r7_2);

   (Funcs_20000000)[r7_1](r7_6 + 18, r7_4 + 18, 0, r7_2);

   sub_800581e(r7_6, r7_4, 0x24, 0x24, 0);
}


/* 8005204 - todo */
void sub_8005204(uint8_t a)
{

}


/* 8005238 - todo */
void sub_8005238(void)
{

}


struct
{
   uint16_t wData_0; //0
   uint16_t wData_2; //2

} Data_200000e4; //200000e4


extern void sub_8006234(uint16_t a);


/* 8005574 - todo */
void sub_8005574(uint16_t a, uint16_t b, uint16_t c)
{
   if ((a >= Data_20000024.wData_0) ||
		   (b >= Data_20000024.wData_2))
   {
	   return;
   }

   sub_8006128(a, b, a, b);
   sub_8006234(c);
}


/* 800581e - todo */
void sub_800581e(int16_t a, int16_t b, int c, int d, int e)
{

}


/* 8005a34 - todo */
void sub_8005a34(int16_t a, int16_t b, int c, int d, int e)
{

}


/* 8005d8c - todo */
void sub_8005d8c(int16_t a/*r7_6*/, int16_t b/*r7_4*/, char c/*r7_3*/, uint16_t d/*r7*/, uint16_t e)
{
   uint8_t r7_f;
   uint8_t r7_e;
   uint8_t r7_d;
   uint8_t r7_c;
   uint8_t r7_b;
   uint8_t r7_a;

   if ((a < Data_20000024.wData_0) &&
		   (b < Data_20000024.wData_2) &&
		   ((a + Data_2000002c.Data_8->wData_4) >= 0) &&
		   ((b + Data_2000002c.Data_8->wData_6) >= 0))
   {
      r7_a = Data_2000002c.Data_8->wData_6 / 8;
      r7_f = 0;
      r7_e = 0;

      while (r7_e < Data_2000002c.Data_8->wData_6)
      {
         //loc_8005dfc
         r7_c = 0;
         while (r7_c < r7_a)
         {
            //loc_8005e02
            r7_d = Data_2000002c.Data_8->Data_0[((c - ' ') * Data_2000002c.Data_8->wData_6 + r7_e) * r7_a + r7_c];

            r7_b = 0;
        	while (r7_b < 8)
        	{
               //loc_8005e30
               if (r7_d & (1 << 7))
               {
                  sub_8005574(r7_b + a + r7_f, r7_e + b, d);
               }
               else
               {
                  //loc_8005e5e
                  if (e != d)
                  {
                     sub_8005574(r7_b + a + r7_f, r7_e + b, e);
                  }
               }
               //loc_8005e8a
               r7_d <<= 1;
               r7_b++;
        	}

            r7_f += 8;
            r7_c++;
         }

         r7_f = 0;
         r7_e++;
      }
   }
}


/* 8005edc - todo */
void sub_8005edc(int a)
{

}


/* 8005ff0 - todo */
void sub_8005ff0(char* a, uint8_t b)
{
   char* r7_c;
   uint8_t i = 0;
   r7_c = a;

   while (i++ < b)
   {
      sub_8005d8c(
    		  Data_200000e4.wData_0,
			  Data_200000e4.wData_2,
			  r7_c[0],
			  Data_2000002c.Data_0,
			  Data_2000002c.Data_4);

      Data_200000e4.wData_0 += Data_2000002c.Data_8->wData_4;

      if (Data_2000002c.bData_12 != 0)
      {
         if (Data_200000e4.wData_0 > (Data_20000024.wData_0 - Data_2000002c.Data_8->wData_4))
         {
            Data_200000e4.wData_2 += Data_2000002c.Data_8->wData_6;
            Data_200000e4.wData_0 = 0;
         }
      }

      r7_c++;

      if (Data_200000e4.wData_2 >= Data_20000024.wData_2)
      {
         Data_200000e4.wData_2 = 0;
      }
   }
}


/* 80060ac - todo */
void sub_80060ac(Struct_2000002c_Inner8* a)
{
   Data_2000002c.Data_8 = a;
}


/* 8001224 - todo */
int sub_8001224(int a)
{

}


extern void sub_80060f4(uint16_t a, int b);


/* 8003038 - todo */
void sub_8003038(uint16_t a, Struct_2000002c_Inner8* b)
{
   uint16_t r7_e;

   sub_80060ac(b);

   sub_8005a34(0, 0x17, 0x140, 0x18, 0xffff);

   sub_80060c8(0, 0xffff);

   r7_e = sub_8001224(Data_20000bc8[a]);

   sub_80060f4(160 - (r7_e * b->wData_4) / 2, 0x18);

   sub_8005edc(Data_20000bc8[a]);
}


void sub_80060c8()
{

}


void sub_80060f4(uint16_t a, int b)
{

}


/* 8006128 - todo */
void sub_8006128(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{

}


/* 8006234 - todo */
void sub_8006234(uint16_t a)
{
   *((uint16_t*)(FSMC_BANK1 + 0x20000)) = a;
}


/* 8006434 - todo */
void sub_8006434(void)
{

}


/* 8008670 - todo */
void sub_8008670(void)
{

}


/* 8008a88 - todo */
int si46xx_set_volume(uint8_t a)
{
   if (a > 0x3f)
   {
      a = 0x3f;
   }

   if (0 != si46xx_set_property(SI46XX_AUDIO_ANALOG_VOLUME, a & 0x3f))
   {
      return 1;
   }

   return 0;
}


/* 8008ac4 - todo */
int si46xx_mute(uint8_t a)
{
   if (0 != si46xx_set_property(SI46XX_AUDIO_MUTE,
               (a == 0)? 0/*Do not mute audio outputs*/:
                         3/*Mute both Left and Right Audio Out*/))
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
int si46xx_dab_tune_freq(uint8_t index)
{
   uint8_t f;

   Data_200001f0[0] = SI46XX_DAB_TUNE_FREQ;
   Data_200001f0[1] = 0x00;
   Data_200001f0[2] = index;
   Data_200001f0[3] = 0x00;
   Data_200001f0[4] = 0x00;
   Data_200001f0[5] = 0x00;

   if (0 != si46xx_send_command(6, 4, 5))
   {
      return 1;
   }

   f = si46xx_read_stc_reply(200, 4);

   f |= si46xx_read_reply(100, 4);

   return f;
}


/* 8008d84 - todo */
int si46xx_dab_start_digital_service(struct_8008d84* a)
{
   if (si46xx_dab_tune_freq(a->wData_24) != 0)
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_DAB_START_DIGITAL_SERVICE;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = 0;
   Data_200001f0[3] = 0;
   Data_200001f0[4] = a->service_id;
   Data_200001f0[5] = a->service_id >> 8;
   Data_200001f0[6] = a->service_id >> 16;
   Data_200001f0[7] = a->service_id >> 24;
   Data_200001f0[8] = a->component_id;
   Data_200001f0[9] = a->component_id >> 8;
   Data_200001f0[10] = a->component_id >> 16;
   Data_200001f0[11] = a->component_id >> 24;

   if (si46xx_send_command(12, 4, 10) != 0)
   {
      return 1;
   }

   return 0;
}


/* 8008ed8 - todo */
int sub_8008ed8(RTC_TimeTypeDef* a, RTC_DateTypeDef* b)
{

}


/* 8009020 - todo */
int si46xx_start_dab(uint8_t a)
{
   si46xx_mute(1);

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

   if (0 != si46xx_load_and_boot(1))
   {
      return 1;
   }

   if (0 != si46xx_set_dab_config())
   {
      return 1;
   }

   if (0 != si46xx_set_audio_output(0))
   {
      return 1;
   }

   if (0 != si46xx_set_volume(a))
   {
      return 1;
   }

   wData_20000a56 |= 1;

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

   si46xx_mute(0);

   return 0;
}


/* 80093a8 - todo */
int sub_80093a8(void* a, void* b, void* c, void* d, void* e, void* f)
{

}


/* 800995c - todo */
int si46xx_fm_tune_freq(uint16_t khz)
{
   Data_200001f0[0] = SI46XX_FM_TUNE_FREQ;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = khz;
   Data_200001f0[3] = khz >> 8;
   Data_200001f0[4] = 0;
   Data_200001f0[5] = 0;

   if (si46xx_send_command(6, 4, 5) != 0)
   {
      return 1;
   }

   return 0;
}


/* 80099b4 - todo */
int si46xx_start_fm(uint8_t a)
{
   si46xx_mute(1);

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

   if (0 != si46xx_load_and_boot(0))
   {
      return 1;
   }

   if (0 != si46xx_set_config())
   {
      return 1;
   }

   if (0 != si46xx_set_audio_output(0))
   {
      return 1;
   }

   if (0 != si46xx_set_volume(a))
   {
      return 1;
   }

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

   si46xx_mute(0);

   wData_20000a56 &= ~1;

   return 0;
}


/* 8009a40 - todo */
int si46xx_read_stc_reply(uint16_t a, uint16_t b)
{
   uint8_t i = 20;

   do
   {
      i--;

      sub_800c7e0(a);

      /* CS to low */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

      Data_200001f0[0] = SI46XX_RD_REPLY;

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
   while (((Data_200001f0[0] & 1/*STCINT*/) == 0) && (i != 0));

   if ((i == 0) || (Data_200001f0[0] & 0x40)) //ERR_CMD
   {
      return 1;
   }

   return 0;
}


/* 8009aec - todo */
uint8_t si46xx_read_reply(uint16_t a, uint16_t numRxBytes)
{
   uint8_t f = 0;
   uint8_t i = 10;

   while (i--)
   {
      sub_800c7e0(a);

      /* CS to low */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

      Data_200001f0[0] = SI46XX_RD_REPLY;

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

      if (Data_200001f0[0] & 0x80) //CTS
      {
         break;
      }
   }

   if (Data_200001f0[0] & 0x40) //ERR_CMD
   {
      f = (Data_200001f0[4] != 0); //error code
   }

   if (i == 0)
   {
      f = (Data_200001f0[4] != 0);
   }

   return f;
}


/* 8009bb8 - todo */
int si46xx_load_and_boot(uint8_t a)
{
   uint8_t arData_8[943];

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);

   sub_800c7e0(10);

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

   if (0 != si46xx_read_reply(100, 6))
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_POWER_UP;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = (1 << 4)/*1: Reference clock generator is in crystal mode.*/
                      | 9/*TR_SIZE*/;
   Data_200001f0[3] = 0x3f;

   Data_200001f0[4] = 0; //XTAL_FREQ: 0x016e3600 = 24000000
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

   if (0 != si46xx_send_command(16, 4, 100))
   {
      return 1;
   }

   if ((Data_200001f0[3] & 0xC0) != 0x80)
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_LOAD_INIT;
   Data_200001f0[1] = 0;

   if (0 != si46xx_send_command(2, 4, 1))
   {
      return 1;
   }
   //loc_8009c96: TODO
   memcpy(arData_8, si46xx_image_data, 943);

   /* CS to low */
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

   Data_200001f0[0] = SI46XX_HOST_LOAD;

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

   if (0 != si46xx_read_reply(1, 4))
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_LOAD_INIT;
   Data_200001f0[1] = 0;

   if (0 != si46xx_send_command(2, 4, 1))
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_FLASH_LOAD;
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

   if (0 != si46xx_send_command(8, 4, 1))
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_LOAD_INIT;
   Data_200001f0[1] = 0;

   if (0 != si46xx_send_command(2, 6, 10))
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_FLASH_LOAD;
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

   if (0 != si46xx_send_command(12, 4, 50))
   {
      return 1;
   }

   Data_200001f0[0] = SI46XX_BOOT;
   Data_200001f0[2] = 0; /* BUG!! */

   if (0 != si46xx_send_command(2, 4, 100))
   {
      return 1;
   }

   if ((Data_200001f0[3] & 0xC0) != 0xC0)
   {
      return 1;
   }

   return 0;
}


/* 8009eac - todo */
int si46xx_set_dab_config(void)
{
   if (0 != si46xx_set_property(0x8100, 1))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_DAB_TUNE_FE_VARM, 0xfbf5))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_DAB_TUNE_FE_VARB, 0x122))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_DAB_TUNE_FE_CFG, 1))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_INT_CTL_ENABLE,
               (1 << 4)/*DSRVIEN (Interrupt when DSRVINT is set)*/))
   {
      return 1;
   }

   return 0;
}


/* 800a25c - todo */
int si46xx_set_config(void)
{
   if (0 != si46xx_set_property(SI46XX_FM_SEEK_FREQUENCY_SPACING, 5/*50kHz*/))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_VALID_SNR_THRESHOLD, 10))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_RSQ_SNR_HIGH_THRESHOLD, 10))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_RSQ_RSSI_HIGH_THRESHOLD, 10))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_RDS_INTERRUPT_SOURCE, 1))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_RDS_INTERRUPT_FIFO_COUNT, 0x25))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_RDS_CONFIG, 1))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_RDS_CONFIDENCE, 0x7777))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_DAB_TUNE_FE_VARM, 0))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_DAB_TUNE_FE_VARB, 0))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_DAB_TUNE_FE_CFG, 0))
   {
      return 1;
   }

   if (0 != si46xx_set_property(SI46XX_FM_INT_CTL_ENABLE,
                (1 << 2)/*RDSIEN (Interrupt when RDSINT is set)*/))
   {
      return 1;
   }

   return 0;
}


/* 800a68c - todo */
int sub_800a68c(void* a)
{

}


/* 800a6ec - todo */
int sub_800a6ec(void* a)
{

}


/* 800a76c - todo */
int sub_800a76c(void* a, void* b)
{

}


/* 800a82c - todo */
int si46xx_get_func_info(char* a)
{
   Data_200001f0[0] = SI46XX_GET_FUNC_INFO;
   Data_200001f0[1] = 0;

   if (0 != si46xx_send_command(2, 12, 10))
   {
	  return 1;
   }

   sprintf(a, "%d.%d.%d",
      Data_200001f0[4],
      Data_200001f0[5],
      Data_200001f0[6]);

   return 0;
}


/* 800a884 - todo */
int si46xx_set_audio_output(uint8_t a)
{
   if (a == 1)
   {
      if (0 != si46xx_set_property(SI46XX_DIGITAL_IO_OUTPUT_SELECT,
                  (1 << 15)/*Master mode selected*/))
      {
         return 1;
      }
   }

   if (0 != si46xx_set_property(SI46XX_PIN_CONFIG_ENABLE, (a == 0)?
                (1 << 15)/*INTBOUTEN*/ | (1 << 0)/*DACOUTEN*/:
                (1 << 15)/*INTBOUTEN*/ | (1 << 1)/*I2SOUTEN*/))
   {
      return 1;
   }

   return 0;
}


/* 800a8d8 - todo */
int si46xx_set_property(uint16_t name, uint16_t value)
{
   Data_200001f0[0] = SI46XX_SET_PROPERTY;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = name;
   Data_200001f0[3] = name >> 8;
   Data_200001f0[4] = value;
   Data_200001f0[5] = value >> 8;

   if (0 != si46xx_send_command(6, 4, 1))
   {
      return 1;
   }

   return 0;
}


/* 800a940 - todo */
int si46xx_send_command(uint16_t numTxBytes, uint16_t numRxBytes, uint16_t c)
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

   f = si46xx_read_reply(c, numRxBytes);

   return f;
}


/* 800a9a8 - todo */
int sub_800a9a8(void)
{
   RTC_AlarmTypeDef r7_4 = {0};
   uint8_t r7_f = 0;

   si46xx_start_dab(0);

   si46xx_get_func_info(strDABVersion);

   si46xx_start_fm(0);

   si46xx_get_func_info(strFMVersion);

   Data_20000a74.Date = 1;
   Data_20000a74.Month = 1;
   Data_20000a74.Year = 20;
   Data_20000a74.WeekDay = 3;

   HAL_RTC_SetDate(&hrtc, &Data_20000a74, RTC_FORMAT_BIN);

   Data_20000bc0.bData_0 = 1;
   bData_20000a48 = 1;

   if (0 != sub_800b2ac(&Data_20000a4c, &Data_20000a50))
   {
      Data_20000a50.b = 0x1f;
   }

   bData_20000057 = Data_20000a50.b;

   sub_8005204(Data_20000a50.b2);

   if ((Data_20000a4c.a > 23) || (Data_20000a4c.b > 59))
   {
      Data_20000a4c.a = 0;
      Data_20000a4c.b = 0;
      Data_20000a50.b1 = 0;
   }

   if (Data_20000a50.b1 != 0)
   {
      r7_4.AlarmTime.Hours = ((Data_20000a4c.a / 10) << 4) |
                ((Data_20000a4c.a % 10));
      r7_4.AlarmTime.Minutes = ((Data_20000a4c.b / 10) << 4) |
                ((Data_20000a4c.b % 10));

      if (0 != HAL_RTC_SetAlarm_IT(&hrtc, &r7_4, RTC_FORMAT_BCD))
      {
         Error_Handler();
      }
   }
   else
   {
      if (0 != HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A))
      {
         Error_Handler();
      }
   }

   if (0 == bData_200022a8)
   {
      sub_8008670();
      sub_800c33c();

      if (0 != bData_200022a8)
      {
         wData_20000a56 |= 2;
      }
      else
      {
         si46xx_mute(1);
      }

      wData_20000a56 |= 0x100;
      r7_f = 1;
   }
   else
   {
      wData_20000a56 &= ~0x100;
   }

   sub_8005204(Data_20000a50.b2);

   bData_20000a59 = 0;
   bData_20000a58 = 0;

   return r7_f;
}


/* 800abb0 - todo */
void sub_800abb0(struct_8008d84* a)
{
   Data_200023e0 = a;

   if (bData_20000a58 != bData_20000054)
   {
      bData_20000054 = bData_20000a58;
   }

   if ((a->wData_24 < 42) && (a->service_id != 0))
   {
      if ((wData_20000a56 & 1) == 0)
      {
         si46xx_start_dab(bData_20000057);
      }

      if (0 == si46xx_dab_start_digital_service(a))
      {
         wData_20000a56 &= ~2;
      }
   }
   else
   {
      if ((wData_20000a56 & 1) != 0)
      {
         si46xx_start_fm(bData_20000057);
      }

      if (0 == si46xx_fm_tune_freq(a->wData_24))
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

   if ((a[bData_20000a58].wData_24 < 42) && (a[bData_20000a58].service_id != 0))
   {
      si46xx_start_dab(bData_20000057);
   }
   else
   {
      si46xx_start_fm(bData_20000057);
   }

   sub_800abb0(&a[bData_20000a58]);

   wData_20000a56 |= 0x100;
}


/* 800aed0 - todo */
void sub_800aed0(void)
{

}


/* 800af5c - todo */
int sub_800af5c(void)
{

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


/* 800b2ac - todo */
int sub_800b2ac(void* a/*r7_4*/, void* b/*r7*/)
{
   struct_8008d84 r7_8;
   uint8_t r7_26;
   uint8_t i;

   memset(&r7_8, 0xff, 28);

   bData_200022a8 = 0;
   bData_20000be4 = 0;

   r7_26 = sub_800bc04(Data_20000cc8, Data_20000be8, a, b);

   for (i = 0; i < 200; i++)
   {
      if (0 == memcmp(&Data_20000cc8[i], &r7_8, 28))
      {
         break;
      }

      bData_200022a8++;
   }

   for (i = 0; i < 8; i++)
   {
      if (0 == memcmp(&Data_20000be8[i], &r7_8, 28))
      {
         break;
      }

      bData_20000be4++;
   }

   return r7_26;
}


/* 800bc04 - todo */
int sub_800bc04(struct_8008d84* a, struct_8008d84* b, void* c, void* d)
{

}


