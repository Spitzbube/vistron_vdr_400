
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
#define SI46XX_FM_SEEK_START                 0x31
#define SI46XX_FM_RSQ_STATUS                 0x32
#define SI46XX_FM_RDS_STATUS                 0x34

#define SI46XX_GET_DIGITAL_SERVICE_LIST      0x80
#define SI46XX_DAB_START_DIGITAL_SERVICE     0x81
#define SI46XX_DAB_STOP_DIGITAL_SERVICE      0x82
#define SI46XX_DAB_TUNE_FREQ                 0xB0
#define SI46XX_DAB_DIGRAD_STATUS             0xB2
#define SI46XX_DAB_GET_EVENT_STATUS          0xB3
#define SI46XX_DAB_GET_TIME                  0xBC

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


/* 8008b18 - todo */
int si46xx_dab_search(uint8_t* r7_4)
{
   uint8_t r7_27 = 0;
   uint8_t r7_26;
   uint8_t r7_25;
   uint16_t r7_22;
   uint8_t r7_21;
   uint8_t r7_20;
   uint8_t r7_1f = bData_200022a8;
   uint8_t r7_1c;
   uint8_t r7_1b;

   r7_26 = bData_200022a8;
   r7_25 = 0;

   Tuner_Values r7_8 = {0};

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;

   do
   {
	   //loc_8008b54
	   if (0 != si46xx_dab_tune_freq(r7_27))
	   {
		   //->loc_8008cd2
		   continue;
	   }
	   else
	   {
		  if (Data_20000bc0.bData_0 == 0)
		  {
			 r7_21 = 0;
			 if (Data_20000a48.bData_0 == 0)
			 {
				r7_21 = Data_20000a48.bData_1;
				Data_20000a48.bData_0 = 1;
			 }
			 //loc_8008b8a
			 r7_20 = 0;
			 if (Data_20000bc0.bData_0 == 0)
			 {
				r7_20 = sub_8002976(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
			 }
			 //loc_8008bae
			 Data_20000bc0.bData_0 = 1;
			 Data_20000a48.bData_0 = 1;

			 if ((r7_20 | r7_21) == 5)
			 {
				return 1;
			 }
			 //loc_8008bce
		  }
		  //loc_8008bce
		  draw_freq_mux_label(r7_27);
		  draw_progress_bar(242, 42, r7_27, 41);

		  if (bData_200022a8 != r7_26)
		  {
			 r7_26 = bData_200022a8;

			 sub_8002a60(Data_20000cc8, bData_200022a8);
		  }
		  //loc_8008c0a
		  si46xx_get_dab_values(&r7_8);
		  draw_signal_strength_bars(142, 42, &r7_8.rssi);
		  if (0 != si46xx_get_dab_status())
		  {
			 return 1;
		  }
		  //loc_8008c30
		  if (((Data_200001f0[5] & 1) != 0) &&
				  (Data_200001f0[8] > 29))
		  {
			  r7_1b = 0;
			  r7_25 = 0;
			  do
			  {
				  //loc_8008c4e
				  r7_22 = 0;
				  do
				  {
					  //loc_8008c52
					  sub_8009f1c(100);

					  if (Data_20000bc0.bData_0 == 0)
					  {
						  Data_20000bc0.bData_0 = 1;
						  if (5 == sub_8002976(Data_20000bc0.wData_2, Data_20000bc0.wData_4))
						  {
							  return 1;
						  }
						  //loc_8008c80
					  }
					  //loc_8008c80
				  }
				  while (((Data_200001f0[5] & 1) == 0) && (r7_22++ < 3600));
				  //loc_8008c98
				  sub_8009f70(&r7_1b);
			  }
			  while ((r7_1b == 0) && (++r7_25 < 10));
			  //loc_8008cba
			  sub_8009f1c(10);

			  sub_8009fb0(r7_27, &r7_1c);
			  //->loc_8008cd4
		  }
		  //loc_8008cd4
	   }
	   //loc_8008cd4
   }
   while (++r7_27 < 41);

   *r7_4 = bData_200022a8 - r7_1f;

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


/* 8008e38 - todo */
int si46xx_dab_stop_digital_service(struct_8008d84* a)
{
   Data_200001f0[0] = SI46XX_DAB_STOP_DIGITAL_SERVICE;
   Data_200001f0[1] = 0x00;
   Data_200001f0[2] = 0x00;
   Data_200001f0[3] = 0x00;
   Data_200001f0[4] = a->service_id;
   Data_200001f0[5] = a->service_id >> 8;
   Data_200001f0[6] = a->service_id >> 16;
   Data_200001f0[7] = a->service_id >> 24;
   Data_200001f0[8] = a->component_id;
   Data_200001f0[9] = a->component_id >> 8;
   Data_200001f0[10] = a->component_id >> 16;
   Data_200001f0[11] = a->component_id >> 24;

   if (0 != si46xx_send_command(12, 4, 10))
   {
	  return 1;
   }

   return 0;
}


/* 8008ed8 - todo */
int si46xx_dab_get_time_date(RTC_TimeTypeDef* r7_4, RTC_DateTypeDef* r7)
{
   uint16_t wData_12; //12
   uint16_t wData_14; //14
   uint8_t r7_8[12] = //8012c9c
      {0x00, 0x03, 0x02, 0x05, 0x00, 0x03, 0x05, 0x01, 0x04, 0x06, 0x02, 0x04};

   Data_200001f0[0] = SI46XX_DAB_GET_TIME;
   Data_200001f0[1] = 0x00;

   if (0 != si46xx_send_command(2, 11, 50))
   {
      return 0;
   }

   wData_14 = Data_200001f0[4] | (Data_200001f0[5] << 8);
   if ((wData_14 > 2099) ||
		   (wData_14 < 2018) ||
		   (Data_200001f0[6] > 12) ||
		   (Data_200001f0[7] > 31) ||
		   (Data_200001f0[8] > 23) ||
		   (Data_200001f0[10] > 59) ||
		   (Data_200001f0[6] == 0))
   {
      return 0;
   }
   //loc_8008f62
   wData_12 = wData_14 - ((Data_200001f0[6] < 3)? 1: 0);

   r7->Year = wData_14 + 48;
   r7->Month = Data_200001f0[6];
   r7->Date = Data_200001f0[7];
   r7->WeekDay = (wData_12 + wData_12 / 4 - wData_12 / 100 + wData_12 / 400 + r7_8[Data_200001f0[6] - 1] + Data_200001f0[7]) % 7;

   r7_4->Hours = Data_200001f0[8];
   r7_4->Minutes = Data_200001f0[9];
   r7_4->Seconds = Data_200001f0[10];

   return 1;
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


/* 8009168 - todo */
int si46xx_fm_search(uint8_t* r7_4)
{
   uint16_t r7_2e = 8750;
   uint8_t r7_27 = bData_200022a8;
   uint8_t r7_2d = bData_200022a8;
   uint16_t r7_2a;
   uint8_t r7_29;
   uint8_t r7_28;
   uint8_t r7_1c[8];
   Tuner_Values r7_c;

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;

   if (0 != si46xx_fm_tune_freq(r7_2e))
   {
      return 1;
   }
   //->loc_800936e
   while (r7_2e < 10790)
   {
      //loc_80091a6
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_29 = 0;
         if (Data_20000a48.bData_0 == 0)
         {
            r7_29 = Data_20000a48.bData_1;
            Data_20000a48.bData_0 = 1;
         }
         //loc_80091ca
         r7_28 = 0;
         if (Data_20000bc0.bData_0 == 0)
         {
            r7_28 = sub_8002976(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
         }
         //loc_80091ee
         Data_20000bc0.bData_0 = 1;
         Data_20000a48.bData_0 = 1;

         if ((r7_28 | r7_29) == 5)
         {
            return 1;
         }
      }
      //loc_800920e
      si46xx_get_fm_values(&r7_c);
      draw_signal_strength_bars(142, 42, &r7_c.rssi);
      draw_freq_mux_label(r7_2e);
      draw_progress_bar(242, 42, r7_2e - 8750, 2040 /*10790-8750*/);

      if (bData_200022a8 != r7_2d)
      {
         r7_2d = bData_200022a8;

         sub_8002a60(Data_20000cc8, bData_200022a8);
      }
      //loc_8009264
      r7_2a = 650;
      //->loc_80092e8
      while (r7_2a-- != 0)
      {
         //loc_800926c
         si46xx_read_reply(10, 4);

         if ((Data_200001f0[0] & 1) != 0)
         {
        	 //->loc_80092f4
            break;
         }

         if (Data_20000bc0.bData_0 == 0)
         {
            r7_29 = 0;
            if (Data_20000a48.bData_0 == 0)
            {
               r7_29 = Data_20000a48.bData_1;
               Data_20000a48.bData_0 = 1;
            }
            //loc_80092a4
            r7_28 = 0;
            if (Data_20000bc0.bData_0 == 0)
            {
               r7_28 = sub_8002976(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
            }
            //loc_80092c8
            Data_20000bc0.bData_0 = 1;
            Data_20000a48.bData_0 = 1;

            if ((r7_28 | r7_29) == 5)
            {
               return 1;
            }
         }
         //loc_80092e8
      }
      //loc_80092f6
      if (0 != sub_800a174())
      {
    	  return 1;
      }
      //loc_8009304
      r7_2e = Data_200001f0[6] | (Data_200001f0[7] << 8);

      if ((Data_200001f0[10] != 0) &&
    		  ((Data_200001f0[10] & 0x80) == 0) &&
			  (0 == sub_800a1a4(3, 50)) &&
			  (0 == sub_8009868(r7_1c)) &&
			  (1 == sub_800b398(r7_2e, r7_1c)))
      {
         return 1;
      }
      //loc_8009360
      if (0 != sub_800a214())
      {
         return 1;
      }
      //loc_800936e
   }

   *r7_4 = bData_200022a8 - r7_27;

   return 0;
}


/* 80093a8 - todo */
int sub_80093a8(void* a, void* b, void* c, void* d, void* e, void* f)
{

}


/* 8009868 - todo */
int sub_8009868(uint8_t r7_4[])
{
   uint8_t r7_1f = 0;
   uint8_t r7_1e = 0;
   uint32_t r7_18 = 0;
   uint8_t* r7_10;
   uint8_t r7_17;
   uint8_t r7_f;

   do
   {
      //loc_800987c
      if (0 != sub_800a1a4(1, 2))
      {
         return 1;
      }
      //loc_800988e
      if (Data_200001f0[10] != 0)
      {
         if (((Data_200001f0[15] & 0xf8) == 0) ||
        		 ((Data_200001f0[15] & 0xf8) == 0))
         {
             //loc_80098ae
             r7_17 = (Data_200001f0[14] << 1) & 0x06;

             if ((Data_200001f0[11] & 0x03) < 3)
             {
                r7_10 = &r7_4[r7_17];
                *r7_10 = Data_200001f0[19];
                r7_1e = 1;
                r7_1f |= r7_1e << r7_17;
             }
             //loc_80098f0
             if ((Data_200001f0[11] & 0x0c) < 12)
             {
                r7_10 = &r7_4[r7_17 + 1];
                *r7_10 = Data_200001f0[18];
                r7_1f |= r7_1e << (uint8_t)(r7_17 + 1);
             }
         }
         //loc_8009924
      }
      //loc_8009924
      r7_f = Data_200001f0[10];
   }
   while ((r7_f != 0) || ((r7_1f != 0xff) && (r7_18++ < 1000)));

   if (r7_18 >= 1000)
   {
      return 1;
   }

   return 0;
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


/* 8009e7c - todo */
int si46xx_get_dab_status(void)
{
   Data_200001f0[0] = SI46XX_DAB_DIGRAD_STATUS;
   Data_200001f0[1] = 0;

   if (0 != si46xx_send_command(2, 23, 20))
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


/* 8009f1c - todo */
int sub_8009f1c(uint8_t a)
{
   while (a-- != 0)
   {
      Data_200001f0[0] = SI46XX_DAB_GET_EVENT_STATUS;
      Data_200001f0[1] = 0;

      (void) si46xx_send_command(2, 12, 10);

      if ((Data_200001f0[5] & 1) != 0)
      {
         break;
      }
   }

   if (a == 0)
   {
      return 1;
   }

   return 0;
}


/* 8009f70 - todo */
int sub_8009f70(uint8_t* a)
{
   Data_200001f0[1] = 0x80;
   Data_200001f0[0] = SI46XX_RD_REPLY;

   if (0 != si46xx_send_command(2, 9, 1))
   {
	  return 1;
   }

   *a = Data_200001f0[8];

   return 0;
}


/* 8009fb0 - todo */
int sub_8009fb0(int r7, uint8_t r7_7)
{

}


/* 800a174 - todo */
int sub_800a174(void)
{
   Data_200001f0[0] = SI46XX_FM_RSQ_STATUS;
   Data_200001f0[1] = 0;

   if (0 != si46xx_send_command(2, 22, 20))
   {
      return 1;
   }

   return 0;
}


/* 800a1a4 - todo */
int sub_800a1a4(uint8_t r7_7, uint8_t r7_6)
{
   uint8_t r7_f = 0;

   do
   {
      //loc_800a1b8
      Data_200001f0[0] = SI46XX_FM_RDS_STATUS;
      Data_200001f0[1] = r7_7 & 0x07;

      if (0 != si46xx_send_command(2, 20, 1))
      {
         return 1;
      }
      //loc_800a1de
      r7_f++;
   }
   while (((Data_200001f0[5] & 0x02) == 0) && (r7_f < r7_6));
   //loc_800a1f8
   if (r7_f == r7_6)
   {
      return 1;
   }

   return 0;
}


/* 800a214 - todo */
int sub_800a214(void)
{
   Data_200001f0[0] = SI46XX_FM_SEEK_START;
   Data_200001f0[1] = 0;
   Data_200001f0[2] = 2;
   Data_200001f0[3] = 0;
   Data_200001f0[4] = 0;
   Data_200001f0[5] = 0;

   if (0 != si46xx_send_command(6, 4, 30))
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
int si46xx_get_fm_values(Tuner_Values* r7_4)
{
   int8_t rssi;
   int8_t snr;

   if (0 != sub_800a174())
   {
      return 1;
   }

   rssi = Data_200001f0[9];
   snr = Data_200001f0[10];

   r7_4->rssi = rssi;
   r7_4->snr = snr;
   r7_4->multipath = Data_200001f0[11];
   r7_4->frequency = Data_200001f0[6] | (Data_200001f0[7] << 8);
   r7_4->freq_offset = Data_200001f0[8];

   return 0;
}


/* 800a6ec - todo */
int si46xx_get_dab_values(Tuner_Values* a)
{
   int8_t rssi;
   int8_t snr;

   if (0 != si46xx_get_dab_status())
   {
      return 1;
   }

   rssi = Data_200001f0[6];
   snr = Data_200001f0[7];

   a->rssi = rssi;
   a->snr = snr;
   a->fib_error_count = Data_200001f0[10] | (Data_200001f0[11] << 8);
   a->freq_index = Data_200001f0[16];
   a->frequency = Data_200001f0[12] | (Data_200001f0[13] << 8) |
		 (Data_200001f0[14] << 16)  | (Data_200001f0[15] << 24);
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
      menu_automatic_search();

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


/* 800ac74 - todo */
void channel_next(void)
{
   uint8_t r7_7 = (wData_20000a56 & 4)? bData_20000be4: bData_200022a8;

   if (r7_7 != 0)
   {
      bData_20000a59 = bData_20000a58;
      if (bData_20000a58 < (r7_7 - 1))
      {
   	     bData_20000a58++;
      }
      else
      {
         bData_20000a58 = 0;
      }

      wData_20000a56 |= 0x02;
   }
}


/* 800acf0 - todo */
void channel_previous(void)
{
   uint8_t r7_7 = (wData_20000a56 & 4)? bData_20000be4: bData_200022a8;

   if (r7_7 != 0)
   {
      bData_20000a59 = bData_20000a58;
      if (bData_20000a58 != 0)
      {
   	     bData_20000a58--;
      }
      else
      {
         bData_20000a58 = r7_7 - 1;
      }

      wData_20000a56 |= 0x02;
   }
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
   struct_8008d84* r7_4 = (wData_20000a56 & 4)? Data_20000be8: Data_20000cc8;

   si46xx_dab_stop_digital_service(&r7_4[bData_20000a58]);

   si46xx_mute(1);

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
   sub_800c7e0(10);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

   wData_20000a56 &= ~0x300;
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


/* 800b398 - todo */
int sub_800b398(uint16_t r7_6, void* r7)
{
   uint8_t r7_f = 0;

   if (bData_200022a8 < 200)
   {
      if (0xff == sub_800b43c(r7_6))
      {
         Data_20000cc8[bData_200022a8].wData_24 = r7_6;
         memset(&Data_20000cc8[bData_200022a8].Data_8, ' ', 16);
         memcpy(&Data_20000cc8[bData_200022a8].Data_8, r7, 8);
         bData_200022a8++;
      }
      else
      {
         //loc_800b420
         r7_f = 2;
      }
   }
   else
   {
      //loc_800b426
      r7_f = 1;
   }

   return r7_f;
}


/* 800b43c - todo */
int sub_800b43c(uint16_t r7_6)
{
   uint8_t r7_f = 0xff;
   uint8_t r7_e = 0;

   while (r7_e < bData_200022a8)
   {
      //loc_800b450
      if (Data_20000cc8[r7_e].wData_24 == r7_6)
      {
         r7_f = r7_e;
         //->loc_800b47e
         break;
      }
      //loc_800b46e
      r7_e++;
   }
   //loc_800b47e
   return r7_f;
}


/* 800b5e0 - todo */
uint8_t sub_800b5e0(void)
{
   uint8_t r7_7 = 0;
   memset(Data_20000cc8, 0xff, 200 * sizeof(struct_8008d84));
   bData_200022a8 = 0;
   return r7_7;
}


