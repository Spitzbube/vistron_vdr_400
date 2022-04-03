
#include "stm32f1xx_hal.h"
#include "main.h"


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
   Data_20000a48.bData_0 = 1;

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
   memset(Data_20000cc8, 0xff, 200 * sizeof(struct_8008d84));
   memset(Data_20000be8, 0xff, 8 * sizeof(struct_8008d84));

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


