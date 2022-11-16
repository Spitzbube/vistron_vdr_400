
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
#define SI46XX_GET_DIGITAL_SERVICE_DATA      0x84
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
int sub_8008670(void)
{
   uint8_t r7_7 = 1;
   uint8_t r7_6 = UserSettings.b2;
   uint8_t r7_5 = UserSettings.b2;
   uint8_t r7_4;
   uint8_t r7_3;
   uint8_t r7_2 = UserSettings.b2;

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   sub_8002e0c(28, 34, 2, r7_6);

   while (r7_7 != 0)
   {
	  //loc_80086b8
	  r7_4 = 0;
	  if (KeyEvent.bData_0 == 0)
	  {
		 r7_4 = KeyEvent.bData_1;
		 KeyEvent.bData_0 = 1;
	  }
	  //loc_80086d0
	  r7_3 = 0;
	  if (TouchEvent.bData_0 == 0)
	  {
		 r7_3 = sub_8002e98(TouchEvent.wData_2, TouchEvent.wData_4);
	  }
	  //loc_80086f0
	  if ((r7_3 | r7_4) != 0)
	  {
		 switch (r7_3 | r7_4)
		 {
			case 2:
			   //0x08008775
			   r7_6++;
			   if (r7_6 == 2) r7_6 = 0;
			   break;

			case 3:
			   //0x08008787
			   r7_6--;
			   if (r7_6 == 0xff) r7_6 = 1;
			   break;

			case 4:
			   //0x08008799
			   r7_3 = r7_6 + 25;
//        	   break;

			case 25:
			case 26:
			   //0x0800879f
			   if (r7_2 != (r7_3 - 25))
			   {
				  UserSettings.b2 = r7_3 - 25;

				  menu_set_language(UserSettings.b2);
			   }
			   //80087CE
			   r7_7 = 0;
			   break;

			default:
			   //loc_80087d4
			   break;
		 }
		 //loc_80087de
		 TouchEvent.bData_0 = 1;
		 KeyEvent.bData_0 = 1;
	  }
	  //loc_80087ea
	  if (r7_6 != r7_5)
	  {
		 UserSettings.b2 = r7_6;

		 menu_set_language(UserSettings.b2);

		 sub_8003038(28, &Data_2000004c);

		 r7_5 = r7_6;

		 sub_8002cac(34, 2, r7_6);
	  }
	  //loc_800882c
   }

   return 0;
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
   uint8_t mux = 0; //r7_27
   uint8_t r7_26;
   uint8_t r7_25;
   uint16_t r7_22;
   uint8_t r7_21;
   uint8_t r7_20;
   uint8_t r7_1f = bChannelCount;
   uint16_t r7_1c;
   uint8_t r7_1b;

   r7_26 = bChannelCount;
   r7_25 = 0;

   Tuner_Values r7_8 = {0};

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   do
   {
	   //loc_8008b54
	   if (0 != si46xx_dab_tune_freq(mux))
	   {
		   //->loc_8008cd2
		   continue;
	   }
	   else
	   {
		  if (TouchEvent.bData_0 == 0)
		  {
			 r7_21 = 0;
			 if (KeyEvent.bData_0 == 0)
			 {
				r7_21 = KeyEvent.bData_1;
				KeyEvent.bData_0 = 1;
			 }
			 //loc_8008b8a
			 r7_20 = 0;
			 if (TouchEvent.bData_0 == 0)
			 {
				r7_20 = menu_automatic_search_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
			 }
			 //loc_8008bae
			 TouchEvent.bData_0 = 1;
			 KeyEvent.bData_0 = 1;

			 if ((r7_20 | r7_21) == 5)
			 {
				return 1;
			 }
			 //loc_8008bce
		  }
		  //loc_8008bce
		  draw_freq_mux_label(mux);
		  draw_progress_bar(242, 42, mux, 41);

		  if (bChannelCount != r7_26)
		  {
			 r7_26 = bChannelCount;

			 draw_channel_list(ChannelList, bChannelCount);
		  }
		  //loc_8008c0a
		  si46xx_get_dab_values(&r7_8);
		  draw_signal_strength_bars(142, 42, &r7_8.rssi);
		  if (0 != si46xx_get_dab_status())
		  {
			 return 1;
		  }
		  //loc_8008c30
		  if (((si46xx_buffer[5] & 1) != 0) &&
				  (si46xx_buffer[8] > 29))
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
					  si46xx_is_dab_service_list_avail(100);

					  if (TouchEvent.bData_0 == 0)
					  {
						  TouchEvent.bData_0 = 1;
						  if (5 == menu_automatic_search_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4))
						  {
							  return 1;
						  }
						  //loc_8008c80
					  }
					  //loc_8008c80
				  }
				  while (((si46xx_buffer[5] & 1) == 0) && (r7_22++ < 3600));
				  //loc_8008c98
				  sub_8009f70(&r7_1b);
			  }
			  while ((r7_1b == 0) && (++r7_25 < 10));
			  //loc_8008cba
			  si46xx_is_dab_service_list_avail(10);

			  si46xx_get_digital_service_list(mux, &r7_1c);
			  //->loc_8008cd4
		  }
		  //loc_8008cd4
	   }
	   //loc_8008cd4
   }
   while (++mux < 41);

   *r7_4 = bChannelCount - r7_1f;

   return 0;
}


/* 8008d14 - todo */
int si46xx_dab_tune_freq(uint8_t index)
{
   uint8_t f;

   si46xx_buffer[0] = SI46XX_DAB_TUNE_FREQ;
   si46xx_buffer[1] = 0x00;
   si46xx_buffer[2] = index;
   si46xx_buffer[3] = 0x00;
   si46xx_buffer[4] = 0x00;
   si46xx_buffer[5] = 0x00;

   if (0 != si46xx_send_command(6, 4, 5))
   {
      return 1;
   }

   f = si46xx_read_stc_reply(200, 4);

   f |= si46xx_read_reply(100, 4);

   return f;
}


/* 8008d84 - todo */
int si46xx_dab_start_digital_service(Tuner_Channel* a)
{
   if (si46xx_dab_tune_freq(a->frequency) != 0)
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_DAB_START_DIGITAL_SERVICE;
   si46xx_buffer[1] = 0;
   si46xx_buffer[2] = 0;
   si46xx_buffer[3] = 0;
   si46xx_buffer[4] = a->service_id;
   si46xx_buffer[5] = a->service_id >> 8;
   si46xx_buffer[6] = a->service_id >> 16;
   si46xx_buffer[7] = a->service_id >> 24;
   si46xx_buffer[8] = a->component_id;
   si46xx_buffer[9] = a->component_id >> 8;
   si46xx_buffer[10] = a->component_id >> 16;
   si46xx_buffer[11] = a->component_id >> 24;

   if (si46xx_send_command(12, 4, 10) != 0)
   {
      return 1;
   }

   return 0;
}


/* 8008e38 - todo */
int si46xx_dab_stop_digital_service(Tuner_Channel* a)
{
   si46xx_buffer[0] = SI46XX_DAB_STOP_DIGITAL_SERVICE;
   si46xx_buffer[1] = 0x00;
   si46xx_buffer[2] = 0x00;
   si46xx_buffer[3] = 0x00;
   si46xx_buffer[4] = a->service_id;
   si46xx_buffer[5] = a->service_id >> 8;
   si46xx_buffer[6] = a->service_id >> 16;
   si46xx_buffer[7] = a->service_id >> 24;
   si46xx_buffer[8] = a->component_id;
   si46xx_buffer[9] = a->component_id >> 8;
   si46xx_buffer[10] = a->component_id >> 16;
   si46xx_buffer[11] = a->component_id >> 24;

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

   si46xx_buffer[0] = SI46XX_DAB_GET_TIME;
   si46xx_buffer[1] = 0x00;

   if (0 != si46xx_send_command(2, 11, 50))
   {
      return 0;
   }

   wData_14 = si46xx_buffer[4] | (si46xx_buffer[5] << 8);
   if ((wData_14 > 2099) ||
		   (wData_14 < 2018) ||
		   (si46xx_buffer[6] > 12) ||
		   (si46xx_buffer[7] > 31) ||
		   (si46xx_buffer[8] > 23) ||
		   (si46xx_buffer[10] > 59) ||
		   (si46xx_buffer[6] == 0))
   {
      return 0;
   }
   //loc_8008f62
   wData_12 = wData_14 - ((si46xx_buffer[6] < 3)? 1: 0);

   r7->Year = wData_14 + 48;
   r7->Month = si46xx_buffer[6];
   r7->Date = si46xx_buffer[7];
   r7->WeekDay = (wData_12 + wData_12 / 4 - wData_12 / 100 + wData_12 / 400 + r7_8[si46xx_buffer[6] - 1] + si46xx_buffer[7]) % 7;

   r7_4->Hours = si46xx_buffer[8];
   r7_4->Minutes = si46xx_buffer[9];
   r7_4->Seconds = si46xx_buffer[10];

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

   wMainloopEvents |= MAIN_LOOP_EVENT_DAB_ACTIVE;

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

   si46xx_mute(0);

   return 0;
}


/* 8009168 - todo */
int si46xx_fm_search(uint8_t* r7_4)
{
   uint16_t freq = 8750; //r7_2e
   uint8_t r7_27 = bChannelCount;
   uint8_t r7_2d = bChannelCount;
   uint16_t r7_2a;
   uint8_t r7_29;
   uint8_t r7_28;
   uint8_t r7_1c[8];
   Tuner_Values r7_c;

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   if (0 != si46xx_fm_tune_freq(freq))
   {
      return 1;
   }
   //->loc_800936e
   while (freq < 10790)
   {
      //loc_80091a6
      if (TouchEvent.bData_0 == 0)
      {
         r7_29 = 0;
         if (KeyEvent.bData_0 == 0)
         {
            r7_29 = KeyEvent.bData_1;
            KeyEvent.bData_0 = 1;
         }
         //loc_80091ca
         r7_28 = 0;
         if (TouchEvent.bData_0 == 0)
         {
            r7_28 = menu_automatic_search_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
         }
         //loc_80091ee
         TouchEvent.bData_0 = 1;
         KeyEvent.bData_0 = 1;

         if ((r7_28 | r7_29) == 5)
         {
            return 1;
         }
      }
      //loc_800920e
      si46xx_get_fm_values(&r7_c);
      draw_signal_strength_bars(142, 42, &r7_c.rssi);
      draw_freq_mux_label(freq);
      draw_progress_bar(242, 42, freq - 8750, 2040 /*10790-8750*/);

      if (bChannelCount != r7_2d)
      {
         r7_2d = bChannelCount;

         draw_channel_list(ChannelList, bChannelCount);
      }
      //loc_8009264
      r7_2a = 650;
      //->loc_80092e8
      while (r7_2a-- != 0)
      {
         //loc_800926c
         si46xx_read_reply(10, 4);

         if ((si46xx_buffer[0] & 1) != 0)
         {
        	 //->loc_80092f4
            break;
         }

         if (TouchEvent.bData_0 == 0)
         {
            r7_29 = 0;
            if (KeyEvent.bData_0 == 0)
            {
               r7_29 = KeyEvent.bData_1;
               KeyEvent.bData_0 = 1;
            }
            //loc_80092a4
            r7_28 = 0;
            if (TouchEvent.bData_0 == 0)
            {
               r7_28 = menu_automatic_search_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
            }
            //loc_80092c8
            TouchEvent.bData_0 = 1;
            KeyEvent.bData_0 = 1;

            if ((r7_28 | r7_29) == 5)
            {
               return 1;
            }
         }
         //loc_80092e8
      }
      //loc_80092f6
      if (0 != si46xx_get_fm_received_signal_quality())
      {
    	  return 1;
      }
      //loc_8009304
      freq = si46xx_buffer[6] | (si46xx_buffer[7] << 8);

      if ((si46xx_buffer[10] != 0) &&
    		  ((si46xx_buffer[10] & 0x80) == 0) &&
			  (0 == si46xx_get_fm_rds_status(3, 50)) &&
			  (0 == sub_8009868(r7_1c)) &&
			  (1 == sub_800b398(freq, r7_1c)))
      {
         return 1;
      }
      //loc_8009360
      if (0 != si46xx_start_fm_seek())
      {
         return 1;
      }
      //loc_800936e
   } //while (freq < 10790)

   *r7_4 = bChannelCount - r7_27;

   return 0;
}


const uint8_t Data_8018ea4[] = //8018ea4
{
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x20,
   0x21,
   0x22,
   0x23,
   0x24,
   0x25,
   0x26,
   0x27,
   0x28,
   0x29,
   0x2a,
   0x2b,
   0x2c,
   0x2d,
   0x2e,
   0x2f,
   0x30,
   0x31,
   0x32,
   0x33,
   0x34,
   0x35,
   0x36,
   0x37,
   0x38,
   0x39,
   0x3a,
   0x3b,
   0x3c,
   0x3d,
   0x3e,
   0x3f,
   0x40,
   0x41,
   0x42,
   0x43,
   0x44,
   0x45,
   0x46,
   0x47,
   0x48,
   0x49,
   0x4a,
   0x4b,
   0x4c,
   0x4d,
   0x4e,
   0x4f,
   0x50,
   0x51,
   0x52,
   0x53,
   0x54,
   0x55,
   0x56,
   0x57,
   0x58,
   0x59,
   0x5a,
   0x5b,
   0x5c,
   0x5d,
   0x2d,
   0x5f,
   0x60,
   0x61,
   0x62,
   0x63,
   0x64,
   0x65,
   0x66,
   0x67,
   0x68,
   0x69,
   0x6a,
   0x6b,
   0x6c,
   0x6d,
   0x6e,
   0x6f,
   0x70,
   0x71,
   0x72,
   0x73,
   0x74,
   0x75,
   0x76,
   0x77,
   0x78,
   0x79,
   0x7a,
   0x7b,
   0x7c,
   0x7d,
   0x7e,
   0x7f,
   0x80,
   0x81,
   0x82,
   0x83,
   0x84,
   0x85,
   0x86,
   0x87,
   0x88,
   0x89,
   0x8a,
   0x8b,
   0x8c,
   0x8d,
   0xb5,
   0x8f,
   0x90,
   0x91,
   0x92,
   0x93,
   0x94,
   0x95,
   0x96,
   0x97,
   0x98,
   0x99,
   0x9a,
   0x9b,
   0x9c,
   0x9d,
   0x8e,
   0x8f,
   0xa0,
   0xa1,
   0x20,
   0x20,
   0xa4,
   0xa5,
   0xa6,
   0x97,
   0xa8,
   0x20,
   0xaa,
   0xab,
   0xac,
   0xad,
   0xae,
   0xaf,
   0xb0,
   0xb1,
   0xb2,
   0xb3,
   0xb4,
   0xb5,
   0xb6,
   0xb7,
   0xb8,
   0xb9,
   0xba,
   0xbb,
   0xbc,
   0xbd,
   0xbe,
   0xbf,
   0x80,
   0x81,
   0x82,
   0x83,
   0x84,
   0x85,
   0x86,
   0x87,
   0x88,
   0x89,
   0x52,
   0x43,
   0x53,
   0x5a,
   0x44,
   0x4c,
   0xa3,
   0x91,
   0x92,
   0x93,
   0x94,
   0x95,
   0x96,
   0x97,
   0x99,
   0x99,
   0x72,
   0x63,
   0x73,
   0x7a,
   0x64,
   0x49,
   0x41,
   0xa3,
   0xa7,
   0xa9,
   0x79,
   0x59,
   0x4f,
   0xb1,
   0x20,
   0x6e,
   0x52,
   0x43,
   0x53,
   0x5a,
   0x46,
   0x64,
   0xb2,
   0xb3,
   0xb7,
   0xbb,
   0x77,
   0x79,
   0x6f,
   0xbc,
   0x20,
   0x6e,
   0x72,
   0x63,
   0x73,
   0x7a,
   0x74,
   0x20,
};

/* 80093a8 - todo */
int si46xx_fm_get_rds_data(void* r7_c, uint8_t* r7_8, void* r7_4, void* r7, uint16_t* r7_30, uint8_t* r7_34)
{
   uint8_t r7_27;
   uint8_t* r7_20;
   uint8_t r7_1f;
   uint32_t r7_18;
   uint8_t r7_17;
   uint8_t r7_16;

   r7_17 = 0;
   r7_1f = 0;

   if (*r7_30 != 0)
   {
      bData_200009f0 = 0;
      Data_200009f4 = 0;
      Data_200009f8 = 0;
   }
   //loc_80093dc
   if (0 != si46xx_read_reply(0, 4))
   {
      return 1;
   }
   //loc_80093ee
   if ((si46xx_buffer[0] & 4) != 0) do
   {
      //loc_80093fc
      if (0 != si46xx_get_fm_rds_status(1, 2))
      {
         return 1;
      }
      //loc_800940e
      if (si46xx_buffer[10] != 0)
      {
         switch (si46xx_buffer[15] & 0xf8)
         {
            case 0:
            case 0x08:
               //loc_8009442
               if (r7_c != 0)
               {
                  r7_16 = (si46xx_buffer[14] << 1) & 0x06;
                  if ((r7_16 == 0) || ((*r7_30 & 0x40) != 0))
                  {
                     //loc_800946a
                     bData_200009fc = 0;
                     *r7_30 &= ~0x40;
                  }
                  //loc_800947e
                  if (((si46xx_buffer[11]) & 0x03) < 3)
                  {
                     r7_20 = &Data_20000a00[r7_16];
                     *r7_20 = si46xx_buffer[19];
                     bData_200009fc |= (1 << r7_16);
                  }
                  //loc_80094b4
                  if (((si46xx_buffer[11]) & 0x0c) < 12)
                  {
                     r7_20 = &Data_20000a00[r7_16 + 1];
                     *r7_20 = si46xx_buffer[18];
                     bData_200009fc |= (1 << (r7_16 + 1));
                  }
                  //loc_80094f0
                  if (bData_200009fc == 0xff)
                  {
                	  r7_20 = r7_c;
                	  for (r7_27 = 0; r7_27 < 8; r7_27++)
                	  {
                         //loc_8009506
                	     *r7_20++ = Data_8018ea4[ Data_20000a00[r7_27] ];
                	  }

                	  r7_1f |= 0x02;
                	  bData_200009fc = 0;
                  }
                  //loc_800982c
               }
               //loc_800982c
               break;

            case 0x20:
            case 0x28:
               //loc_800953e
               if ((r7_34 != 0) && (r7_8 != 0))
               {
                  r7_16 = (si46xx_buffer[14] << 2) & 0x3c;
                  if (r7_16 == 0)
                  {
                     Data_200009f4 = 0;
                     Data_200009f8 = 0;
                  }
                  //loc_800956e
                  if ((si46xx_buffer[11] & 0x03) < 3)
                  {
                     r7_20 = &Data_20000a08[r7_16];
                     *r7_20 = si46xx_buffer[17];

                     if (r7_16 > 31)
                     {
                        Data_200009f8 |= (1 << (r7_16 - 32));
                     }
                     else
                     {
                        //loc_80095aa
                        Data_200009f4 |= (1 << r7_16);
                     }
                  }
                  //loc_80095be
                  if ((si46xx_buffer[11] & 0x0c) < 12)
                  {
                     r7_20 = &Data_20000a08[r7_16 + 1];
                     *r7_20 = si46xx_buffer[16];

                     if (r7_16 > 31)
                     {
                        Data_200009f8 |= (1 << (r7_16 - 31));
                     }
                     else
                     {
                        //loc_80095fc
                        Data_200009f4 |= (1 << (r7_16 + 1));
                     }
                  }
                  //loc_8009614
                  if ((si46xx_buffer[11] & 0x30) < 48)
                  {
                     r7_20 = &Data_20000a08[r7_16 + 2];
                     *r7_20 = si46xx_buffer[19];

                     if (r7_16 > 31)
                     {
                        Data_200009f8 |= (1 << (r7_16 - 30));
                     }
                     else
                     {
                        //loc_8009674
                        Data_200009f4 |= (1 << (r7_16 + 2));
                     }
                  }
                  //loc_800968c
                  if ((si46xx_buffer[11] & 0xC0) < 192)
                  {
                     r7_20 = &Data_20000a08[r7_16 + 3];
                     *r7_20 = si46xx_buffer[18];

                     if (r7_16 > 31)
                     {
                        Data_200009f8 |= (1 << (r7_16 - 29));
                     }
                     else
                     {
                        //loc_80096ca
                        Data_200009f4 |= (1 << (r7_16 + 3));
                     }
                  }
                  //loc_80096e2
                  if (bData_200009f0 < r7_16)
                  {
                     bData_200009f0 = r7_16;
                  }
                  //loc_80096f2
                  r7_18 = 1;

                  for (r7_27 = 0; r7_27 < (uint8_t)(bData_200009f0 - 29); r7_27++)
                  {
                     //loc_80096fe
                     r7_18 = (r7_18 << 1) + 1;
                  }
                  //08009720
                  if ((Data_200009f4 == 0xffffffff) &&
                		  (Data_200009f8 == r7_18))
                  {
                     *r7_34 = bData_200009f0 + 4;

                     for (r7_27 = 0; r7_27 < *r7_34; r7_27++)
                     {
                        //loc_800974a
                        r7_8[r7_27] = Data_8018ea4[ Data_20000a08[r7_27] ];
                     }

                     r7_1f |= 0x04;
                     Data_200009f4 = 0;
                     Data_200009f8 = 0;

                     for (r7_27 = 0; r7_27 < (uint8_t)(*r7_34 - 3); r7_27++)
                     {
                        //loc_8009794
                        if ((r7_8[r7_27] == ' ') &&
                        		(r7_8[r7_27 + 1] == ' ') &&
								(r7_8[r7_27 + 2] == ' '))
                        {
                           *r7_34 = r7_27 + 1;
                           //->loc_80097ea
                           break;
                        }
                     }
                     //loc_80097ea
                     r7_1f |= 0x04;
                  }
               }
               //loc_8009830
               break;

            case 0x40:
               //loc_80097f4
               si46xx_get_rds_time(r7_4, r7);
               HAL_RTC_SetTime(&hrtc, r7_4, RTC_FORMAT_BIN);
               HAL_RTC_SetDate(&hrtc, r7, RTC_FORMAT_BIN);

               *r7_30 |= 0x80;
               r7_1f |= 0x08;
               break;

            default:
               //loc_8009832
               break;
         }
         //
      }
      //loc_8009828 -> loc_8009832
      //loc_8009832
      r7_17 = si46xx_buffer[10];
   }
   while (r7_17 != 0);
   //loc_8009840
   return r7_1f;
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
      if (0 != si46xx_get_fm_rds_status(1, 2))
      {
         return 1;
      }
      //loc_800988e
      if (si46xx_buffer[10] != 0)
      {
         if (((si46xx_buffer[15] & 0xf8) == 0) ||
        		 ((si46xx_buffer[15] & 0xf8) == 0))
         {
             //loc_80098ae
             r7_17 = (si46xx_buffer[14] << 1) & 0x06;

             if ((si46xx_buffer[11] & 0x03) < 3)
             {
                r7_10 = &r7_4[r7_17];
                *r7_10 = si46xx_buffer[19];
                r7_1e = 1;
                r7_1f |= r7_1e << r7_17;
             }
             //loc_80098f0
             if ((si46xx_buffer[11] & 0x0c) < 12)
             {
                r7_10 = &r7_4[r7_17 + 1];
                *r7_10 = si46xx_buffer[18];
                r7_1f |= r7_1e << (uint8_t)(r7_17 + 1);
             }
         }
         //loc_8009924
      }
      //loc_8009924
      r7_f = si46xx_buffer[10];
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
   si46xx_buffer[0] = SI46XX_FM_TUNE_FREQ;
   si46xx_buffer[1] = 0;
   si46xx_buffer[2] = khz;
   si46xx_buffer[3] = khz >> 8;
   si46xx_buffer[4] = 0;
   si46xx_buffer[5] = 0;

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

   wMainloopEvents &= ~MAIN_LOOP_EVENT_DAB_ACTIVE;

   return 0;
}


/* 8009a40 - todo */
int si46xx_read_stc_reply(uint16_t a, uint16_t b)
{
   uint8_t i = 20;

   do
   {
      i--;

      main_delay(a);

      /* CS to low */
      HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_RESET);

      si46xx_buffer[0] = SI46XX_RD_REPLY;

      if (0 != HAL_SPI_Transmit(&hspi2, si46xx_buffer, 1, 10))
      {
         return 0;
      }

      if (0 != HAL_SPI_Receive(&hspi2, si46xx_buffer, b, 10))
      {
         return 0;
      }

      /* CS to high */
      HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_SET);
   }
   while (((si46xx_buffer[0] & 1/*STCINT*/) == 0) && (i != 0));

   if ((i == 0) || (si46xx_buffer[0] & 0x40)) //ERR_CMD
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
      main_delay(a);

      /* CS to low */
      HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_RESET);

      si46xx_buffer[0] = SI46XX_RD_REPLY;

      if (0 != HAL_SPI_Transmit(&hspi2, si46xx_buffer, 1, 10))
      {
         return 0;
      }

      if (0 != HAL_SPI_Receive(&hspi2, si46xx_buffer, numRxBytes, 10))
      {
         return 0;
      }

      /* CS to high */
      HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_SET);

      if (si46xx_buffer[0] & 0x80) //CTS
      {
         break;
      }
   }

   if (si46xx_buffer[0] & 0x40) //ERR_CMD
   {
      f = (si46xx_buffer[4] != 0); //error code
   }

   if (i == 0)
   {
      f = (si46xx_buffer[4] != 0);
   }

   return f;
}


/* 8009bb8 - todo */
int si46xx_load_and_boot(uint8_t a)
{
   uint8_t arData_8[943];

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);

   main_delay(10);

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

   if (0 != si46xx_read_reply(100, 6))
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_POWER_UP;
   si46xx_buffer[1] = 0;
   si46xx_buffer[2] = (1 << 4)/*1: Reference clock generator is in crystal mode.*/
                      | 9/*TR_SIZE*/;
   si46xx_buffer[3] = 0x3f;

   si46xx_buffer[4] = 0; //XTAL_FREQ: 0x016e3600 = 24000000
   si46xx_buffer[5] = 0x36;
   si46xx_buffer[6] = 0x6e;
   si46xx_buffer[7] = 1;

   si46xx_buffer[8] = 0;
   si46xx_buffer[9] = 0x10;
   si46xx_buffer[10] = 0;
   si46xx_buffer[11] = 0;
   si46xx_buffer[12] = 0;
   si46xx_buffer[13] = 0;
   si46xx_buffer[14] = 0;
   si46xx_buffer[15] = 0;

   if (0 != si46xx_send_command(16, 4, 100))
   {
      return 1;
   }

   if ((si46xx_buffer[3] & 0xC0) != 0x80)
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_LOAD_INIT;
   si46xx_buffer[1] = 0;

   if (0 != si46xx_send_command(2, 4, 1))
   {
      return 1;
   }
   //loc_8009c96: TODO
   memcpy(arData_8, si46xx_image_data, 943);

   /* CS to low */
   HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_RESET);

   si46xx_buffer[0] = SI46XX_HOST_LOAD;

   if (0 != HAL_SPI_Transmit(&hspi2, si46xx_buffer, 1, 10))
   {
      return 1;
   }

   if (0 != HAL_SPI_Transmit(&hspi2, arData_8, 943, 10))
   {
      return 1;
   }

   /* CS to high */
   HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_SET);

   if (0 != si46xx_read_reply(1, 4))
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_LOAD_INIT;
   si46xx_buffer[1] = 0;

   if (0 != si46xx_send_command(2, 4, 1))
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_FLASH_LOAD;
   si46xx_buffer[1] = 0;
   si46xx_buffer[2] = 0;
   si46xx_buffer[3] = 0;

   if (a != 0)
   {
      si46xx_buffer[4] = 0;
      si46xx_buffer[5] = 0;
      si46xx_buffer[6] = 0x21;
      si46xx_buffer[7] = 0;
   }
   else
   {
      si46xx_buffer[4] = 0;
      si46xx_buffer[5] = 0;
      si46xx_buffer[6] = 0x20;
      si46xx_buffer[7] = 0;
   }

   if (0 != si46xx_send_command(8, 4, 1))
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_LOAD_INIT;
   si46xx_buffer[1] = 0;

   if (0 != si46xx_send_command(2, 6, 10))
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_FLASH_LOAD;
   si46xx_buffer[1] = 0;
   si46xx_buffer[2] = 0;
   si46xx_buffer[3] = 0;

   if (a != 0)
   {
      si46xx_buffer[4] = 0;
      si46xx_buffer[5] = 0;
      si46xx_buffer[6] = 0x2C;
      si46xx_buffer[7] = 0;
   }
   else
   {
      si46xx_buffer[4] = 0;
      si46xx_buffer[5] = 0;
      si46xx_buffer[6] = 0x22;
      si46xx_buffer[7] = 0;
   }

   si46xx_buffer[8] = 0;
   si46xx_buffer[9] = 0;
   si46xx_buffer[10] = 0;
   si46xx_buffer[11] = 0;

   if (0 != si46xx_send_command(12, 4, 50))
   {
      return 1;
   }

   si46xx_buffer[0] = SI46XX_BOOT;
   si46xx_buffer[2] = 0; /* BUG!! */

   if (0 != si46xx_send_command(2, 4, 100))
   {
      return 1;
   }

   if ((si46xx_buffer[3] & 0xC0) != 0xC0)
   {
      return 1;
   }

   return 0;
}


/* 8009e7c - todo */
int si46xx_get_dab_status(void)
{
   si46xx_buffer[0] = SI46XX_DAB_DIGRAD_STATUS;
   si46xx_buffer[1] = 0;

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
int si46xx_is_dab_service_list_avail(uint8_t a)
{
   while (a-- != 0)
   {
      si46xx_buffer[0] = SI46XX_DAB_GET_EVENT_STATUS;
      si46xx_buffer[1] = 0;

      (void) si46xx_send_command(2, 12, 10);

      if ((si46xx_buffer[5] & 1) != 0) //SVRLIST
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
   si46xx_buffer[1] = 0x80;
   si46xx_buffer[0] = SI46XX_RD_REPLY;

   if (0 != si46xx_send_command(2, 9, 1))
   {
	  return 1;
   }

   *a = si46xx_buffer[8];

   return 0;
}


/* 8009fb0 - todo */
int si46xx_get_digital_service_list(uint8_t mux, uint16_t* r7)
{
   uint8_t* pByte = &si46xx_buffer[12]; //r7_24
   uint8_t r7_23;
   uint8_t i; //r7_22
   uint8_t r7_21;
   uint8_t r7_20;
   uint32_t service_id; //r7_1c
   uint32_t component_id; //r7_18
   uint8_t station_name[16]; //r7_8

   si46xx_buffer[0] = SI46XX_GET_DIGITAL_SERVICE_LIST;
   si46xx_buffer[1] = 0;

   if (0 != si46xx_send_command(2, 2048, 1))
   {
      return 1;
   }

   *r7 = si46xx_buffer[6] | (si46xx_buffer[7] << 8);
   r7_20 = si46xx_buffer[8];

   for (i = 0; i < r7_20; i++)
   {
      //loc_800a00a
      r7_23 = pByte[5] & 0x0f;

      if ((pByte[4] & 0x01) == 0)
      {
         service_id = pByte[0] | (pByte[1] << 8) | (pByte[2] << 16) | (pByte[3] << 24);
         pByte += 4;
         pByte += 4;
         memcpy(station_name, pByte, 16);
         pByte += 16;
         component_id = pByte[0] | (pByte[1] << 8) | (pByte[2] << 16) | (pByte[3] << 24);
         pByte += 4;

         r7_21 = persist_add_dab_station(mux, service_id, component_id, station_name);

         if ((r7_21 != 1) && (r7_23 > 2))
         {
            r7_23--;
            do
            {
               //loc_800a0ca
               if ((pByte[1] & 0xc0) == 0)
               {
                  component_id = pByte[0] | (pByte[1] << 8) | (pByte[2] << 16) | (pByte[3] << 24);
                  r7_21 = persist_add_dab_station(mux, service_id, component_id, station_name);
               }
               //loc_800a112
               pByte += 4;
               r7_23--;

               if (r7_21 == 1)
               {
            	   //->loc_800a146
            	   break;
               }
            }
            while (r7_23 != 0);
         }
         //loc_800a148
      }
      else
      {
         //loc_800a134
         pByte += 4*(r7_23 + 6);
      }
   }

   return 0;
}


/* 800a174 - todo */
int si46xx_get_fm_received_signal_quality(void)
{
   si46xx_buffer[0] = SI46XX_FM_RSQ_STATUS;
   si46xx_buffer[1] = 0;

   if (0 != si46xx_send_command(2, 22, 20))
   {
      return 1;
   }

   return 0;
}


/* 800a1a4 - todo */
int si46xx_get_fm_rds_status(uint8_t arg1, uint8_t retry)
{
   uint8_t i = 0;

   do
   {
      //loc_800a1b8
      si46xx_buffer[0] = SI46XX_FM_RDS_STATUS;
      si46xx_buffer[1] = arg1 & 0x07; //STATUSONLY MTFIFO INTACK

      if (0 != si46xx_send_command(2, 20, 1))
      {
         return 1;
      }
      //loc_800a1de
      i++;
   }
   while (((si46xx_buffer[5] & (1 << 1)/*RDSSYNC*/) == 0) && (i < retry));
   //loc_800a1f8
   if (i == retry)
   {
      return 1;
   }

   return 0;
}


/* 800a214 - todo */
int si46xx_start_fm_seek(void)
{
   si46xx_buffer[0] = SI46XX_FM_SEEK_START;
   si46xx_buffer[1] = 0;
   si46xx_buffer[2] = 2;
   si46xx_buffer[3] = 0;
   si46xx_buffer[4] = 0;
   si46xx_buffer[5] = 0;

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


/* 800a358 - todo */
void si46xx_get_rds_time(RTC_TimeTypeDef* r7_4, RTC_DateTypeDef* r7)
{
   uint8_t m; //r7_27
   uint8_t h; //r7_26
   uint32_t mjd; //r7_20
   uint8_t r7_1f;
   uint32_t l; //r7_18
   uint32_t n; //r7_14
   uint32_t i; //r7_10
   uint32_t j; //r7_c
   uint16_t y; //r7_a
   uint8_t r7_9;
   uint8_t r7_8;

   if (((si46xx_buffer[11] & 0x03) < 3) &&
		   ((si46xx_buffer[11] & 0x0c) < 12) &&
		   ((si46xx_buffer[11] & 0x30) < 48) &&
		   ((si46xx_buffer[11] & 0xc0) < 192))
   {
      mjd = ((si46xx_buffer[16] >> 1) & 0x7f) |
			   (si46xx_buffer[17] << 7) |
			   ((si46xx_buffer[14] << 15) & 0x18000);
      r7_1f = si46xx_buffer[18] & 0x3f;
      m = (si46xx_buffer[18] >> 6) | ((si46xx_buffer[19] << 2) & 0x3c);
      h = (si46xx_buffer[19] >> 4) | ((si46xx_buffer[16] << 4) & 0x10);

      l = mjd + 2468570;
      n = l * 4 / 146097;
      l -= (n * 146097 + 3) / 4;
      i = (l + 1) * 4000 / 1461001;
      l -= i * 1461 / 4 - 31;
      j = l * 80 / 2447;
      r7->Date = l - (j * 2447 / 80);

      l = j / 11;
      r7->Month = j - l * 12 + 2;

      y = 100 * (n - 49) + i + l; //TODO

      if ((r7_1f & 0x20) != 0)
      {
    	  r7_9 = (r7_1f & 1) * 30;
    	  r7_8 = (r7_9 > m)? 1: 0;

    	  if (r7_9 > m)
    	  {
    		  m -= r7_9 - 59;
    		  //->loc_800a538
    	  }
    	  else
    	  {
    		  //loc_800a52c
    		  m -= r7_9;
    	  }
    	  //loc_800a538
    	  r7_9 = (r7_1f & 0x1f) / 2 + r7_8;

    	  if (r7_9 > h)
    	  {
    		  h -= r7_9 - 23;
    	  }
    	  else
    	  {
    		  //loc_800a568
    		  h -= r7_9;
    	  }
    	  //loc_800a624
      }
      else
      {
         //loc_800a576
    	  r7_9 = (r7_1f & 1) * 30;
    	  r7_8 = ((r7_9 + m) > 59)? 1: 0;

    	  if ((r7_9 + m) > 59)
    	  {
    		  m += r7_9 - 59;
    	  }
    	  else
    	  {
    		  //loc_800a5ba
    		  m += r7_9;
    	  }
    	  //loc_800a5c6
    	  r7_9 = (r7_1f & 0x1f) / 2 + r7_8;

    	  if ((r7_9 + h) > 23)
    	  {
    		  h += r7_9 - 23;
    	  }
    	  else
    	  {
    		  //loc_800a618
    		  h += r7_9;
    	  }
    	  //loc_800a624
      }
      //loc_800a624
      r7->Year = y + 48;
      r7_4->Hours = h;
      r7_4->Minutes = m;
      r7_4->Seconds = 0;

      r7->WeekDay = mjd % 7 + 3;
      if (r7->WeekDay > 7)
      {
    	  r7->WeekDay -= 7;
      }
      //loc_800a67c
   }
   //loc_800a67c
}


/* 800a68c - todo */
int si46xx_get_fm_values(Tuner_Values* r7_4)
{
   int8_t rssi;
   int8_t snr;

   if (0 != si46xx_get_fm_received_signal_quality())
   {
      return 1;
   }

   rssi = si46xx_buffer[9];
   snr = si46xx_buffer[10];

   r7_4->rssi = rssi;
   r7_4->snr = snr;
   r7_4->multipath = si46xx_buffer[11];
   r7_4->frequency = si46xx_buffer[6] | (si46xx_buffer[7] << 8);
   r7_4->freq_offset = si46xx_buffer[8];

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

   rssi = si46xx_buffer[6];
   snr = si46xx_buffer[7];

   a->rssi = rssi;
   a->snr = snr;
   a->fib_error_count = si46xx_buffer[10] | (si46xx_buffer[11] << 8);
   a->freq_index = si46xx_buffer[16];
   a->frequency = si46xx_buffer[12] | (si46xx_buffer[13] << 8) |
		 (si46xx_buffer[14] << 16)  | (si46xx_buffer[15] << 24);
}


/* 800a76c - todo */
int si46xx_get_digital_service_data(uint8_t r7_4[], uint8_t* r7)
{
   uint8_t i;
   uint8_t r7_e;

   if (0 != si46xx_read_reply(10, 4))
   {
      return 1;
   }

   if ((si46xx_buffer[0] & 0x10) != 0)
   {
      si46xx_buffer[0] = SI46XX_GET_DIGITAL_SERVICE_DATA;
      si46xx_buffer[1] = 1;

      if (0 != si46xx_send_command(2, 2048, 10))
      {
         return 1;
      }
      //loc_800a7b6
      if ((si46xx_buffer[19]/*byte_count_high*/ == 0) && ((si46xx_buffer[24] & 0x0f) == 0))
      {
         i = 0;
         r7_e = si46xx_buffer[18]/*byte_count_low*/;
         if (r7_e > 0x80)
         {
           r7_e = 0x80;
         }
         do
         {
            //loc_800a7de
            *r7_4++ = Data_8018ea4[ si46xx_buffer[i + 26] ];
            i++;
         }
         while (i < r7_e);
      }
      else
      {
         //loc_800a804
         return 1;
      }
      //loc_800a808
      *r7 = si46xx_buffer[18] - 2;
      return 0;
   }
   else
   {
      //loc_800a818
      return 1;
   }
}


/* 800a82c - todo */
int si46xx_get_func_info(char* a)
{
   si46xx_buffer[0] = SI46XX_GET_FUNC_INFO;
   si46xx_buffer[1] = 0;

   if (0 != si46xx_send_command(2, 12, 10))
   {
	  return 1;
   }

   sprintf(a, "%d.%d.%d",
      si46xx_buffer[4],
      si46xx_buffer[5],
      si46xx_buffer[6]);

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
   si46xx_buffer[0] = SI46XX_SET_PROPERTY;
   si46xx_buffer[1] = 0;
   si46xx_buffer[2] = name;
   si46xx_buffer[3] = name >> 8;
   si46xx_buffer[4] = value;
   si46xx_buffer[5] = value >> 8;

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
   HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_RESET);

   if (0 != HAL_SPI_Transmit(&hspi2, si46xx_buffer, numTxBytes, 10))
   {
      return 1;
   }

   /* CS to high */
   HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_SET);

   f = si46xx_read_reply(c, numRxBytes);

   return f;
}


/* 800a9a8 - todo */
int sub_800a9a8(void)
{
   RTC_AlarmTypeDef sAlarm = {0};
   uint8_t res = 0; //r7_f

   si46xx_start_dab(0);

   si46xx_get_func_info(strDABVersion);

   si46xx_start_fm(0);

   si46xx_get_func_info(strFMVersion);

   rtcDate.Date = 1;
   rtcDate.Month = 1;
   rtcDate.Year = 20;
   rtcDate.WeekDay = 3;

   HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   if (0 != sub_800b2ac(&currentAlarmTime, &UserSettings))
   {
      UserSettings.b = 0x1f;
   }

   bCurrentVolume = UserSettings.b;

   menu_set_language(UserSettings.b2);

   if ((currentAlarmTime.hours > 23) || (currentAlarmTime.minutes > 59))
   {
      currentAlarmTime.hours = 0;
      currentAlarmTime.minutes = 0;
      UserSettings.b1 = 0;
   }

   if (UserSettings.b1 != 0)
   {
      sAlarm.AlarmTime.Hours = ((currentAlarmTime.hours / 10) << 4) |
                ((currentAlarmTime.hours % 10));
      sAlarm.AlarmTime.Minutes = ((currentAlarmTime.minutes / 10) << 4) |
                ((currentAlarmTime.minutes % 10));

      if (0 != HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD))
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

   if (0 == bChannelCount)
   {
      sub_8008670();
      menu_automatic_search();

      if (0 != bChannelCount)
      {
         wMainloopEvents |= 2;
      }
      else
      {
         si46xx_mute(1);
      }

      wMainloopEvents |= MAIN_LOOP_EVENT_FOREGROUND;
      res = 1;
   }
   else
   {
      wMainloopEvents &= ~MAIN_LOOP_EVENT_FOREGROUND;
   }

   menu_set_language(UserSettings.b2);

   bData_20000a59 = 0;
   bCurrentChannelNumber = 0;

   return res;
}


/* 800ad68 - todo */
void volume_up(void)
{
   if (bCurrentVolume < 63)
   {
      bCurrentVolume++;
   }

   if ((wMainloopEvents & 0x20) != 0)
   {
      si46xx_mute(0);

      wMainloopEvents &= ~0x20;
   }

   si46xx_set_volume(bCurrentVolume);
}


/* 800adb8 - todo */
void volume_down(void)
{
   if (bCurrentVolume != 0)
   {
	  bCurrentVolume--;

      if ((wMainloopEvents & 0x20) != 0)
      {
         si46xx_mute(0);

         wMainloopEvents &= ~0x20;
      }
   }
   else
   {
      if ((wMainloopEvents & 0x20) == 0)
      {
         si46xx_mute(1);

         wMainloopEvents |= 0x20;
      }
   }

   si46xx_set_volume(bCurrentVolume);
}


/* 800abb0 - todo */
void channel_set(Tuner_Channel* a)
{
   Data_200023e0 = a;

   if (bCurrentChannelNumber != bData_20000054)
   {
      bData_20000054 = bCurrentChannelNumber;
   }

   if ((a->frequency < 42) && (a->service_id != 0))
   {
      if ((wMainloopEvents & MAIN_LOOP_EVENT_DAB_ACTIVE) == 0)
      {
         si46xx_start_dab(bCurrentVolume);
      }

      if (0 == si46xx_dab_start_digital_service(a))
      {
         wMainloopEvents &= ~2;
      }
   }
   else
   {
      if ((wMainloopEvents & MAIN_LOOP_EVENT_DAB_ACTIVE) != 0)
      {
         si46xx_start_fm(bCurrentVolume);
      }

      if (0 == si46xx_fm_tune_freq(a->frequency))
      {
         wMainloopEvents &= ~2;
      }
   }

   wMainloopEvents |= 0x40;
}


/* 800ac74 - todo */
void channel_next(void)
{
   uint8_t r7_7 = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)? bFavouriteCount: bChannelCount;

   if (r7_7 != 0)
   {
      bData_20000a59 = bCurrentChannelNumber;
      if (bCurrentChannelNumber < (r7_7 - 1))
      {
   	     bCurrentChannelNumber++;
      }
      else
      {
         bCurrentChannelNumber = 0;
      }

      wMainloopEvents |= 0x02;
   }
}


/* 800acf0 - todo */
void channel_previous(void)
{
   uint8_t r7_7 = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)? bFavouriteCount: bChannelCount;

   if (r7_7 != 0)
   {
      bData_20000a59 = bCurrentChannelNumber;
      if (bCurrentChannelNumber != 0)
      {
   	     bCurrentChannelNumber--;
      }
      else
      {
         bCurrentChannelNumber = r7_7 - 1;
      }

      wMainloopEvents |= 0x02;
   }
}


/* 800ae28 - todo */
void channel_start_current(void)
{
   Tuner_Channel* a = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)? FavouriteList: ChannelList;

   if ((a[bCurrentChannelNumber].frequency < 42) && (a[bCurrentChannelNumber].service_id != 0))
   {
      si46xx_start_dab(bCurrentVolume);
   }
   else
   {
      si46xx_start_fm(bCurrentVolume);
   }

   channel_set(&a[bCurrentChannelNumber]);

   wMainloopEvents |= MAIN_LOOP_EVENT_FOREGROUND;
}


/* 800aed0 - todo */
void channel_stop_playing(void)
{
   Tuner_Channel* r7_4 = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)? FavouriteList: ChannelList;

   si46xx_dab_stop_digital_service(&r7_4[bCurrentChannelNumber]);

   si46xx_mute(1);

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
   main_delay(10);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

   wMainloopEvents &= ~(MAIN_LOOP_EVENT_SLEEP_TIMER | MAIN_LOOP_EVENT_FOREGROUND);
}


/* 800af5c - todo */
int channel_search_time(void)
{
   uint8_t res;
   Radio_Text r7_c;
   uint8_t r7[12];

   memset(&r7_c, 0, sizeof(Radio_Text));

   res = 0;

   si46xx_mute(1);

   if (((wMainloopEvents & MAIN_LOOP_EVENT_BACKGROUND_TIME) == 0) &&
		   (bChannelCount != 0))
   {
      if (bBackgroundSearchRetry != 0)
      {
         if ((ChannelList[bBackgroundChannelNr].frequency < 42) &&
        		 (ChannelList[bBackgroundChannelNr].service_id != 0))
         {
            if (0 != si46xx_dab_get_time_date(&rtcTime, &rtcDate))
            {
               if (0 != HAL_RTC_SetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
               {
                  Error_Handler();
               }
               //loc_800aff2
               if (0 != HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN))
               {
                  Error_Handler();
               }
               //loc_800b006
               wMainloopEvents |= MAIN_LOOP_EVENT_BACKGROUND_TIME;
               res = 1;
            }
            //loc_800b01a
            bBackgroundSearchRetry = 0;
            //->loc_800b194
         }
         else
         {
            //loc_800b022
            if ((0 == HAL_GPIO_ReadPin(SI46xx_Interrupt_GPIO_Port, SI46xx_Interrupt_Pin)) &&
            		((si46xx_fm_get_rds_data(r7,
                 		   r7_c.str,
     					   &rtcTime,
     					   &rtcDate,
     					   &wMainloopEvents,
     					   &r7_c.bLength) & 0x08) != 0))
            {
                if (0 != HAL_RTC_SetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
                {
                   Error_Handler();
                }
                //loc_800b068
                if (0 != HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN))
                {
                   Error_Handler();
                }
                //loc_800b07c
                wMainloopEvents |= MAIN_LOOP_EVENT_BACKGROUND_TIME;
                res = 1;
            }
            //loc_800b090
            if ((wMainloopEvents & MAIN_LOOP_EVENT_RTC) != 0)
            {
            	bBackgroundSearchRetry--;
            }
            //loc_800b194
         }
      } //if (bBackgroundSearchRetry != 0)
      else
      {
         //loc_800b0aa
         bBackgroundChannelNr++;
         if (bBackgroundChannelNr > bChannelCount)
         {
            bBackgroundChannelNr = 0;
         }
         //loc_800b0c8
         if ((ChannelList[bBackgroundChannelNr].frequency < 42) &&
        		 (ChannelList[bBackgroundChannelNr].service_id != 0))
         {
            if ((wMainloopEvents & MAIN_LOOP_EVENT_DAB_ACTIVE) == 0)
            {
                si46xx_start_dab(bCurrentVolume);
                si46xx_mute(1);
            }
            //loc_800b116
            bBackgroundSearchRetry = 5;
            while (0 != si46xx_dab_start_digital_service(&ChannelList[bBackgroundChannelNr]))
            {
               //loc_800b11e
               bBackgroundSearchRetry--;
               if (bBackgroundSearchRetry == 0)
               {
            	   //->loc_800b152
            	   break;
               }
            }
            //->loc_800b194
         }
         else
         {
            //loc_800b156
            if ((wMainloopEvents & MAIN_LOOP_EVENT_DAB_ACTIVE) != 0)
            {
               si46xx_start_fm(bCurrentVolume);
               si46xx_mute(1);
            }
            //loc_800b172
            si46xx_fm_tune_freq(ChannelList[bBackgroundChannelNr].frequency);

            bBackgroundSearchRetry = 62;
         }
      }
   }
   //loc_800b194
   return res;
}


/* 800b270 - todo */
int sub_800b270(void)
{
   memset(ChannelList, 0xff, 200 * sizeof(Tuner_Channel));
   memset(FavouriteList, 0xff, 8 * sizeof(Tuner_Channel));

   bChannelCount = 0;
   bFavouriteCount = 0;

   return 0;
}


/* 800b2ac - todo */
int sub_800b2ac(void* a, void* b)
{
   Tuner_Channel empty;
   uint8_t res;
   uint8_t i;

   memset(&empty, 0xff, sizeof(Tuner_Channel));

   bChannelCount = 0;
   bFavouriteCount = 0;

   res = persist_read(ChannelList, FavouriteList, a, b);

   for (i = 0; i < 200; i++)
   {
      if (0 == memcmp(&ChannelList[i], &empty, sizeof(Tuner_Channel)))
      {
         break;
      }

      bChannelCount++;
   }

   for (i = 0; i < 8; i++)
   {
      if (0 == memcmp(&FavouriteList[i], &empty, sizeof(Tuner_Channel)))
      {
         break;
      }

      bFavouriteCount++;
   }

   return res;
}


/* 800b398 - todo */
int sub_800b398(uint16_t r7_6, void* r7)
{
   uint8_t r7_f = 0;

   if (bChannelCount < 200)
   {
      if (0xff == sub_800b43c(r7_6))
      {
         ChannelList[bChannelCount].frequency = r7_6;
         memset(&ChannelList[bChannelCount].Data_8, ' ', 16);
         memcpy(&ChannelList[bChannelCount].Data_8, r7, 8);
         bChannelCount++;
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

   while (r7_e < bChannelCount)
   {
      //loc_800b450
      if (ChannelList[r7_e].frequency == r7_6)
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


/* 800b4ec - todo */
int sub_800b4ec(Tuner_Channel* r7_4)
{
   uint8_t r7_f = 0xff;
   uint8_t r7_e;

   for (r7_e = 0; r7_e < 8; r7_e++)
   {
      //loc_800b4fe
      if (0 == memcmp(&FavouriteList[r7_e], r7_4, sizeof(Tuner_Channel)))
      {
         r7_f = r7_e;
         break;
      }
   }

   return r7_f;
}


/* 800b5e0 - todo */
uint8_t sub_800b5e0(void)
{
   uint8_t r7_7 = 0;
   memset(ChannelList, 0xff, 200 * sizeof(Tuner_Channel));
   bChannelCount = 0;
   return r7_7;
}


/* 800b8d4 - todo */
int persist_add_dab_station(uint8_t frequency, uint32_t service_id, uint32_t component_id, uint8_t* station_name)
{
   uint8_t res = 0;
   uint8_t i;

   if (bChannelCount < 200)
   {
      for (i = 0; i < bChannelCount; i++)
      {
         //loc_800b8f6
         if ((ChannelList[i].frequency == frequency) &&
        		 (ChannelList[i].service_id == service_id))
         {
            res = 2;
         }
         //loc_800b92a
      }

      if (res == 0)
      {
         ChannelList[bChannelCount].frequency = frequency;
         ChannelList[bChannelCount].service_id = service_id;
         ChannelList[bChannelCount].component_id = component_id;
         memset(&ChannelList[bChannelCount].Data_8, ' ', 16);
         memcpy(&ChannelList[bChannelCount].Data_8, station_name, 16);

         bChannelCount++;
         //->loc_800b9d8
      }
      //loc_800b9d8
   }
   else
   {
      //loc_800b9d4
      res = 1;
   }

   return res;
}

