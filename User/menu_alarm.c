
#include "main.h"


/* 8007114 - todo */
int menu_alarm(void)
{
   uint8_t r7_17 = 1;
   uint8_t r7_16 = 0;
   uint8_t editFocus = 0;
   uint8_t currentValue = currentAlarmTime.hours;
   uint8_t oldValue = 0;
   uint8_t maxValue;
   uint8_t offOn;
   uint8_t r7_10;
   uint8_t r7_f;
   RTC_AlarmTypeDef sAlarm = {0};
   Alarm_Time r7;

   offOn = UserSettings.b1;

   TouchEvent.bData_0 = 1;
   KeyEvent.bData_0 = 1;

   r7.hours = currentAlarmTime.hours;
   r7.minutes = currentAlarmTime.minutes;

   draw_alarm_screen(&r7, offOn, editFocus);

   while (r7_17 != 0)
   {
      //loc_800716c
      switch (editFocus)
      {
	     case 0:
	    	 //loc_8007178
	    	 maxValue = 23;
	    	 break;

	     case 1:
	    	 //loc_800717e
	    	 maxValue = 59;
	    	 break;

	     default:
	    	 //loc_8007184
	    	 maxValue = 1;
	    	 break;
      }
      //loc_800718a
      r7_10 = 0;
      if (KeyEvent.bData_0 == 0)
      {
         r7_10 = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
      }
      //loc_80071a2
      r7_f = 0;
      if (TouchEvent.bData_0 == 0)
      {
         r7_f = alarm_screen_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
      }
      //loc_80071c2
      if ((r7_f | r7_10) != 0)
      {
         switch (r7_f | r7_10)
         {
            case 2:
               //0x080071f5
               currentValue++;
               if (currentValue > maxValue) currentValue = 0;
               break;

            case 3:
            	//0x08007209
            	currentValue--;
            	if (currentValue == 0xff) currentValue = maxValue;
            	break;

            case 4:
            	//0x0800721b
            	switch (editFocus)
            	{
                   case 0:
                      //8007226
                      currentAlarmTime.hours = currentValue;
                      currentValue = currentAlarmTime.minutes;
                      editFocus = 1;
                      break;

                   case 1:
                      //800723A
                      currentAlarmTime.minutes = currentValue;
                      currentValue = UserSettings.b1;
                      editFocus = 2;
                      //->8007276
                      break;

                   default:
                	   //8007256
                	   UserSettings.b1 = (currentValue != 0)? 1: 0;
                	   r7_16 = 1;
                	   r7_17 = 0;
                	   break;
            	}
            	//->8007288
            	break;

            case 5:
            	//0x08007279
            	r7_17 = 0;
            	break;

            default:
            	//loc_800727e
            	break;
         }
         //8007288
         TouchEvent.bData_0 = 1;
         KeyEvent.bData_0 = 1;
         oldValue = 0xff;
      }
      //loc_8007298
      if (currentValue != oldValue)
      {
         oldValue = currentValue;

         switch (editFocus)
         {
            case 0:
               //loc_80072b0
               r7.hours = currentValue;
               break;

            case 1:
               //loc_80072b8
               r7.minutes = currentValue;
               break;

            default:
            	//loc_80072c0
            	offOn = currentValue;
            	break;
         }
         //loc_80072c6
         draw_alarm_time_edit(&r7, offOn, editFocus);
      }
      //loc_80072d2
   }

   if (r7_16 != 0)
   {
      if (UserSettings.b1 != 0)
      {
         sAlarm.AlarmTime.Hours = (currentAlarmTime.hours / 10 << 4) | (currentAlarmTime.hours % 10);
         sAlarm.AlarmTime.Minutes = (currentAlarmTime.minutes / 10 << 4) | (currentAlarmTime.minutes % 10);

         if (0 != HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD))
         {
            Error_Handler();
         }
      }
      else
      {
         //loc_800736e
         if (0 != HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A))
         {
            Error_Handler();
         }
      }
      //loc_8007380
      if (0 != persist_write(ChannelList, FavouriteList, &currentAlarmTime, &UserSettings))
      {
         Error_Handler();
      }
   }
   //loc_8007396
   return r7_16;
}


