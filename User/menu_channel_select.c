
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
   struct_8008d84* r7_14;
   Tuner_Values r7_4 = {0};

   r7_1e = 0;
   r7_1d = 0;
   r7_1a = 0;
   r7_18 = (wData_20000a56 & 0x04)? bData_20000be4: bChannelCount;
   r7_14 = (wData_20000a56 & 0x04)? Data_20000be8: Data_20000cc8;

   if (bChannelCount == 0)
   {
      return;
   }

   sub_8002054(r7_14, bCurrentChannelNumber, r7_18, &r7_4, bData_20000057);

   Data_20000bc0.bData_0 = 1;
   //->loc_800c312
   while (r7_1f != 0)
   {
      //loc_800bda8
      r7_18 = (wData_20000a56 & 0x04)? bData_20000be4: bChannelCount;

      r7_1c = 0;
      if (Data_20000a48.bData_0 == 0)
      {
         r7_1c = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_800bdd8
      r7_1b = 0;
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_1b = menu_channel_select_check_touch_fields(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_800bdf8
      if ((r7_1b | r7_1c) != 0)
      {
         switch (r7_1b | r7_1c)
         {
         case 3:
        	 //800be7c
        	 channel_next();
        	 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
        	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 //->800C1E8
        	 break;

         case 2:
        	 //800beaa
        	 channel_previous();
        	 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
        	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 //->800C1E8
        	 break;

         case 4:
        	 //800bed8
        	 r7_1f = 0;
        	 if (r7_1a != 0)
        	 {
        		 sub_800ba74(Data_20000cc8, Data_20000be8, &Data_20000a4c, &Data_20000a50);
        	 }
        	 //->800C1C6
        	 break;

         case 1:
        	 //800bef2
        	 if ((wData_20000a56 & 4) == 0)
        	 {
        		 sub_800b610(bCurrentChannelNumber);
        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
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

        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1CE
        	 break;

         case 8:
        	 //800bf8a
        	 if (r7_18 > 1)
        	 {
        		 bCurrentChannelNumber -= 1; //TODO

        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1D2
        	 break;

         case 9:
        	 //800bfd0
        	 if ((r7_18 > 2) && (bCurrentChannelNumber < 2))
        	 {
        		 bCurrentChannelNumber = 2;
        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1D6
        	 break;

         case 10:
        	 //800c040
        	 if ((r7_18 > 3) && ((bCurrentChannelNumber + 1) < r7_18))
        	 {
        		 bCurrentChannelNumber++;
        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1DA
        	 break;

         case 11:
        	 //800c08c
        	 if ((r7_18 > 4) && ((bCurrentChannelNumber + 2) < r7_18))
        	 {
        		 bCurrentChannelNumber += 2;
        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
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
        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
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
        		 sub_80028b8(r7_14, bCurrentChannelNumber, r7_18);
            	 channel_set(&r7_14[bCurrentChannelNumber]);
        	 }
        	 //800C1E6
        	 break;

         case 24:
        	 //800c1a6
        	 sub_8008554();
        	 sub_8002054(r7_14, bCurrentChannelNumber, r7_18, &r7_4, bData_20000057);
        	 //800C1E8
        	 break;

         default:
        	 //loc_800c1c2 -> loc_800c1e8
        	 break;

         }//switch ((r7_1b | r7_1c))
         //loc_800c1e8
    	 Data_20000bc0.bData_0 = 1;
      } //if ((r7_1b | r7_1c) != 0)
      //loc_800c1ee
      if (wData_20000a56 & 0x10)
      {
    	  wData_20000a56 &= ~0x10;

    	  if ((Data_20000cc8[bCurrentChannelNumber].wData_24 < 41) && (Data_20000cc8[bCurrentChannelNumber].service_id != 0))
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
