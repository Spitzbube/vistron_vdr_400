
#include "main.h"


/* 800bd2c - todo */
void menu_channel_select(void)
{
   uint8_t r7_1f = 1;
   int8_t r7_1e;
   int8_t r7_1d;
   uint8_t r7_1c;
   uint8_t r7_1b;
   uint8_t r7_1a;
   uint8_t r7_19 = bCurrentChannelNumber;
   uint8_t r7_18;
   Tuner_Channel* r7_14;
   Tuner_Values r7_4 = {0};

   r7_1e = 0;
   r7_1d = 0;
   r7_1a = 0;
   r7_18 = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)? bFavouriteCount: bChannelCount;
   r7_14 = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)? FavouriteList: ChannelList;

   if (bChannelCount == 0)
   {
      return;
   }

   draw_channel_select_page(r7_14, bCurrentChannelNumber, r7_18, &r7_4, bCurrentVolume);

   TouchEvent.bData_0 = 1;
   //->loc_800c312
   while (r7_1f != 0)
   {
      //loc_800bda8
      r7_18 = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)? bFavouriteCount: bChannelCount;

      r7_1c = 0;
      if (KeyEvent.bData_0 == 0)
      {
         r7_1c = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
      }
      //loc_800bdd8
      r7_1b = 0;
      if (TouchEvent.bData_0 == 0)
      {
         r7_1b = menu_channel_select_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
      }
      //loc_800bdf8
      if ((r7_1b | r7_1c) != 0)
      {
         switch (r7_1b | r7_1c)
         {
         case 3:
        	 //800be7c
        	 channel_next();
        	 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
        	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 //->800C1E8
        	 break;

         case 2:
        	 //800beaa
        	 channel_previous();
        	 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
        	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 //->800C1E8
        	 break;

         case 4:
        	 //800bed8
        	 r7_1f = 0;
        	 if (r7_1a != 0)
        	 {
        		 persist_write(ChannelList, FavouriteList, &currentAlarmTime, &UserSettings);
        	 }
        	 //->800C1C6
        	 break;

         case 1:
        	 //800bef2
        	 if ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) == 0)
        	 {
        		 sub_800b610(bCurrentChannelNumber);
        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
        		 r7_1a = 1;
        	 }
        	 //800C1CA
        	 break;

         case 5:
        	 //800bf1e - Return
        	 bCurrentChannelNumber = r7_19;
        	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 r7_1f = 0;
        	 //->800C1E8
        	 break;

         case 7:
        	 //800bf44
        	 if (r7_18 != 0)
        	 {
        		 bCurrentChannelNumber -= 2; //TODO

        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1CE
        	 break;

         case 8:
        	 //800bf8a
        	 if (r7_18 > 1)
        	 {
        		 bCurrentChannelNumber -= 1; //TODO

        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1D2
        	 break;

         case 9:
        	 //800bfd0
        	 if ((r7_18 > 2) && (bCurrentChannelNumber < 2))
        	 {
        		 bCurrentChannelNumber = 2;
        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1D6
        	 break;

         case 10:
        	 //800c040
        	 if ((r7_18 > 3) && ((bCurrentChannelNumber + 1) < r7_18))
        	 {
        		 bCurrentChannelNumber++;
        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1DA
        	 break;

         case 11:
        	 //800c08c
        	 if ((r7_18 > 4) && ((bCurrentChannelNumber + 2) < r7_18))
        	 {
        		 bCurrentChannelNumber += 2;
        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1DE
        	 break;

         case 12:
        	 //800c0d8
        	 if (r7_18 > 4)
        	 {
        		 if (bCurrentChannelNumber == 0)
        		 {
        			 bCurrentChannelNumber = r7_18 - 1;
        			 //->800C118
        		 }
        		 //800C0F4
        		 else if (bCurrentChannelNumber > 4)
        		 {
        			 bCurrentChannelNumber -= 5; //TODO
        			 //->800C118
        		 }
        		 else
        		 {
        			 //800C112
        			 bCurrentChannelNumber = 0;
        		 }
        		 //800C118
        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
            	 //->800C1E2
        	 }
        	 //800C1E2
        	 break;

         case 13:
        	 //800c142
        	 if (r7_18 > 4)
        	 {
        		 if ((bCurrentChannelNumber + 1) < r7_18)
        		 {
        			 bCurrentChannelNumber = ((bCurrentChannelNumber + 5) > r7_18)? r7_18 - 1: bCurrentChannelNumber + 5;
        			 //->800C17C
        		 }
        		 else
        		 {
        			 //800C176
        			 bCurrentChannelNumber = 0;
        		 }
        		 //800C17C
        		 draw_updated_channel_select_list(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1E6
        	 break;

         case 24:
        	 //800c1a6
        	 menu_volume_change();
        	 draw_channel_select_page(r7_14, bCurrentChannelNumber, r7_18, &r7_4, bCurrentVolume);
        	 //800C1E8
        	 break;

         default:
        	 //loc_800c1c2 -> loc_800c1e8
        	 break;

         }//switch ((r7_1b | r7_1c))
         //loc_800c1e8
    	 TouchEvent.bData_0 = 1;
      } //if ((r7_1b | r7_1c) != 0)
      //loc_800c1ee
      if (wMainloopEvents & MAIN_LOOP_EVENT_RTC)
      {
    	  wMainloopEvents &= ~MAIN_LOOP_EVENT_RTC;

    	  if ((ChannelList[bCurrentChannelNumber].frequency < 41) &&
    			  (ChannelList[bCurrentChannelNumber].service_id != 0))
    	  {
    		  //0800c23c
    		  si46xx_get_dab_values(&r7_4);
    		  if (0 == si46xx_get_dab_values(&r7_4))
    		  {
    			  //0800c252
    			  if (r7_4.rssi/5 != r7_1e/5)
    			  {
    				  //0800c27a
    				  r7_1e = r7_4.rssi;

    				  draw_signal_strength_bars(142, 42, &r7_4.rssi);
    			  }
    			  //loc_800c28a
    			  if (r7_4.snr != r7_1d)
    			  {
    				  //0800c296
    				  r7_1d = r7_4.snr;

    				  draw_snr_indicator(0xde, 0x07, &r7_4, 1);
    			  }
    			  //loc_800c312
    		  }
    		  //loc_800c312
    	  }
    	  else
    	  {
        	  //loc_800c2a8
    		  si46xx_get_fm_values(&r7_4);
    		  if (0 == si46xx_get_fm_values(&r7_4))
    		  {
    			  if (r7_4.rssi/5 != r7_1e/5)
    			  {
    				  //0800c2e6
    				  r7_1e = r7_4.rssi;

    				  draw_signal_strength_bars(142, 42, &r7_4.rssi);
    			  }
    			  //loc_800c2f6
    			  if (r7_4.snr != r7_1d)
    			  {
    				  //0800c302
    				  r7_1d = r7_4.snr;

    				  draw_snr_indicator(0xde, 0x07, &r7_4, 1);
    			  }
    		  }
    	  }
      }
      //loc_800c312 -> loc_800bda8
   } //while (r7_1f != 0)
   //loc_800c31a
}

