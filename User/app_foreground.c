
#include "main.h"
#include "cmsis_os.h"

extern EventGroupHandle_t xEventGroup;


void main_foreground_task(void* pTaskData)
{
	Tuner_Channel* pChannels = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)?
					  FavouriteList: ChannelList;
	uint16_t standbyCounter = 10800;
	EventBits_t uxBits;
	EventBits_t uxExpectBits = EVENTGROUP_BIT_FOREGROUND;

//	vTaskSuspend(NULL); //wait for startup

	while (1)
	{
#if 0
		uint32_t ulNotificationValue;
		if (pdTRUE == xTaskNotifyWait(0, 0xffffffff, &ulNotificationValue, portMAX_DELAY))
		{
			if ((ulNotificationValue & (1 << 0)) != 0)
			{

			}
		}
#endif
		uxBits = xEventGroupWaitBits(xEventGroup, uxExpectBits, pdFALSE, pdFALSE, portMAX_DELAY);

	    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);

		if (uxBits & EVENTGROUP_BIT_FOREGROUND)
		{
			xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_FOREGROUND);

            standbyCounter = 10800;

            // Display On
            HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_RESET);

            channel_start_current();

            wMainloopEvents |= 0x02;
			xEventGroupSetBits(xEventGroup, EVENTGROUP_BIT_CHANNEL);

            draw_main_screen(rtcTime,
                 &pChannels[bCurrentChannelNumber].Data_8,
   				 bCurrentVolume,
   				 &radioText,
				 radioText.bLength,
				 bCurrentChannelNumber,
				 &Data_20000a5c,
  				 wMainloopEvents
            	);

            uxExpectBits |= EVENTGROUP_BIT_TOUCH |
            		EVENTGROUP_BIT_BUTTON |
            		EVENTGROUP_BIT_RTC |
					EVENTGROUP_BIT_CHANNEL |
					EVENTGROUP_BIT_RADIO_TEXT |
					EVENTGROUP_BIT_DACQ;

		} //if (uxBits & EVENTGROUP_BIT_FOREGROUND)

		if ((uxBits & (EVENTGROUP_BIT_TOUCH | EVENTGROUP_BIT_BUTTON)))
		{
			xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_TOUCH | EVENTGROUP_BIT_BUTTON);

	         bMainKeyCode = 0;
	         if (KeyEvent.bData_0 == 0)
	         {
	            bMainKeyCode = KeyEvent.bData_1;
	            KeyEvent.bData_0 = 1;
	         }
	         //loc_800cd7a
	         bMainTouchCode = 0;
	         if (TouchEvent.bData_0 == 0)
	         {
	            bMainTouchCode = main_screen_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
	            TouchEvent.bData_0 = 1;
	         }
	         //loc_800cda0
	         if ((bMainTouchCode | bMainKeyCode))
	         {
	            //800cdb2
	            standbyCounter = 10800;

	            switch (bMainTouchCode | bMainKeyCode)
	            {
	            case 2:
	               //800ce78 - green
	               channel_next();
	               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
	               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
	               //->800D116
	               break;

	            case 3:
	               //800ceb2 - blue
	               channel_previous();
	               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
	               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
	               //->800D116
	               break;

	            case 1:
	               //800ceec - red
	               volume_down();
	               draw_volume_bar(bCurrentVolume);
	               //->800D116
	               break;

	            case 4:
	               //800cefc - yellow
	               volume_up();
	               draw_volume_bar(bCurrentVolume);
	               break;

	            case 14:
	               //800cf0c - OnOff
	               channel_stop_playing();

	               uxExpectBits = EVENTGROUP_BIT_FOREGROUND; //Wait for foreground
//	               vTaskResume(defaultTaskHandle); //Enable background
	               xEventGroupSetBits(xEventGroup, EVENTGROUP_BIT_BACKGROUND);
	               //->800D116
	               break;

	            case 6:
	               //800cf2a
	               menu_channel_select();

	               radioText.bLength = 0;

	               draw_main_screen(rtcTime,
	            		   &pChannels[bCurrentChannelNumber].Data_8,
						   bCurrentVolume,
	            		   &radioText,
						   radioText.bLength,
						   bCurrentChannelNumber,
						   &Data_20000a5c,
						   wMainloopEvents);
	               //->800D116
	               break;

	            case 20:
	               //800cf7a - Channel number box
	               if ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)
	               {
	                  bCurrentChannelNumber = 0;
	                  wMainloopEvents &= ~MAIN_LOOP_EVENT_FAV_ACTIVE;
	                  wMainloopEvents |= 0x02;
                      xEventGroupSetBits(xEventGroup, EVENTGROUP_BIT_CHANNEL);
	                  //->800CFC6
	               }
	               else
	               {
	                  //800CFAA
	                  if (bFavouriteCount != 0)
	                  {
	                     bCurrentChannelNumber = 0;
	                     wMainloopEvents |= (0x02|MAIN_LOOP_EVENT_FAV_ACTIVE);
                         xEventGroupSetBits(xEventGroup, EVENTGROUP_BIT_CHANNEL);
	                  }
	                  //800CFC6
	               }
	               //800CFC6
	               pChannels = ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)? FavouriteList: ChannelList;

	               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
	               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
	               //800CFD6
	               break;

	            case 21:
	               //800d010 - orange (Menu)
	               menu_main();

	               if (((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0) && (bFavouriteCount == 0))
	               {
	                  bCurrentChannelNumber = 0;
	                  pChannels = ChannelList;
	                  wMainloopEvents &= ~MAIN_LOOP_EVENT_FAV_ACTIVE;
	               }
	               //800D040
	               draw_main_screen(rtcTime,
	            		   &pChannels[bCurrentChannelNumber].Data_8,
						   bCurrentVolume,
	            		   &radioText,
						   radioText.bLength,
						   bCurrentChannelNumber,
						   &Data_20000a5c,
						   wMainloopEvents);
	               //->800D116
	               break;

	            case 22:
	               //800d084
	               menu_signal_information();

	               draw_main_screen(rtcTime,
	            		   &pChannels[bCurrentChannelNumber].Data_8,
						   bCurrentVolume,
	            		   &radioText,
						   radioText.bLength,
						   bCurrentChannelNumber,
						   &Data_20000a5c,
						   wMainloopEvents);
	               //->800D116
	               break;

	            case 23:
	               //800d0cc
	               menu_volume_change();

	               draw_main_screen(rtcTime,
	            		   &pChannels[bCurrentChannelNumber].Data_8,
						   bCurrentVolume,
	            		   &radioText,
						   radioText.bLength,
						   bCurrentChannelNumber,
						   &Data_20000a5c,
						   wMainloopEvents);
	               break;

	            default:
	               //loc_800d114
	               //goto loc_800c9c4;
	               break;
	            }
	         } //if ((bMainTouchCode | bMainKeyCode))
		} //if (uxBits & EVENTGROUP_BIT_TOUCH)

		if (uxBits & EVENTGROUP_BIT_RTC)
		{
			xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_RTC);

            if (0 == HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
            {
               draw_foreground_clock(rtcTime);
            }

            if ((Data_200023e0->frequency < 41) && (Data_200023e0->service_id != 0))
            {
#if 0
               if (((wMainloopEvents & MAIN_LOOP_EVENT_BACKGROUND_TIME) == 0) &&
            		   (0 != si46xx_dab_get_time_date(&rtcTime, &rtcDate)))
               {
                  if (0 != HAL_RTC_SetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca48
                  if (0 != HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca5c
                  wMainloopEvents |= MAIN_LOOP_EVENT_BACKGROUND_TIME;

                  si46xx_mute(0);
               }
#endif

#if 0
               if ((0 == si46xx_get_dab_values(&Data_20000a5c)) &&
            		   (Data_20000a5c.rssi/5 != Data_20000a5a/5))
               {
           	      Data_20000a5a = Data_20000a5c.rssi;

                  draw_signal_strength_bars(142, 42, &Data_20000a5c.rssi);
               }
#endif
            }
            else
            {
               //loc_800cabe
#if 0
               if ((0 == si46xx_get_fm_values(&Data_20000a5c)) &&
             		   (Data_20000a5c.rssi/5 != Data_20000a5a/5))
               {
                  Data_20000a5a = Data_20000a5c.rssi;

                  draw_signal_strength_bars(142, 42, &Data_20000a5c.rssi);
               }
#endif
               //loc_800cb0e
            }

		} //if (uxBits & EVENTGROUP_BIT_RTC)

		if (uxBits & EVENTGROUP_BIT_CHANNEL)
		{
			xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_CHANNEL);

		   channel_set(&pChannels[bCurrentChannelNumber]);

		   radioText.bLength = 0;

		   draw_radio_text(&radioText, radioText.bLength);

		} //if (uxBits & EVENTGROUP_BIT_CHANNEL)

		if (uxBits & EVENTGROUP_BIT_RADIO_TEXT)
		{
			xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_RADIO_TEXT);

			draw_radio_text(&radioText, radioText.bLength);

		} //if (uxBits & EVENTGROUP_BIT_RADIO_TEXT)

		if (uxBits & EVENTGROUP_BIT_DACQ)
		{
			xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_DACQ);

            if ((0 == si46xx_get_dab_values(&Data_20000a5c)) &&
         		   (Data_20000a5c.rssi/5 != Data_20000a5a/5))
            {
        	      Data_20000a5a = Data_20000a5c.rssi;

               draw_signal_strength_bars(142, 42, &Data_20000a5c.rssi);
            }
		}
	}
}


