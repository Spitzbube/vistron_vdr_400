
#include "main.h"


/* 800c4b8 - todo */
void menu_signal_information(void)
{
   uint8_t r7_1f = 1;
   int8_t rssi = 0;
   int8_t snr = 0;
   uint16_t fib_error_count = 0;
   uint8_t multipath = 0;
   uint8_t r7_18;
   uint8_t r7_17;
   struct_8008d84* channels;
   Tuner_Values r7 = {0};

   channels = (wMainloopEvents & 0x04)? FavouriteList: ChannelList;

   TouchEvent.bData_0 = 1;
#if 0 //BUG?
   KeyEvent.bData_0 = 1;
#endif

   if ((channels[bCurrentChannelNumber].wData_24 < 42) && (channels[bCurrentChannelNumber].service_id != 0))
   {
      si46xx_get_dab_values(&r7);
   }
   else
   {
      si46xx_get_fm_values(&r7);
   }

   draw_signal_information_screen(channels, bCurrentChannelNumber, &r7);

   while (r7_1f != 0)
   {
      //loc_800c54e
      r7_18 = 0;
      if (KeyEvent.bData_0 == 0)
      {
         r7_18 = KeyEvent.bData_1;
         KeyEvent.bData_0 = 1;
      }
      //loc_800c566
      r7_17 = 0;
      if (TouchEvent.bData_0 == 0)
      {
         r7_17 = signal_information_screen_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
      }
      //loc_800c586
      if ((r7_17 | r7_18) != 0)
      {
         switch (r7_17 | r7_18)
         {
            case 3:
               //0x0800c5c1
               channel_previous();
               channel_set(&channels[bCurrentChannelNumber]);
               if ((channels[bCurrentChannelNumber].wData_24 < 42) &&
            		   (channels[bCurrentChannelNumber].service_id != 0))
               {
                  si46xx_get_dab_values(&r7);
               }
               else
               {
                  //loc_800c61c
                  si46xx_get_fm_values(&r7);
               }
               //loc_800c624
               draw_signal_information_screen(channels, bCurrentChannelNumber, &r7);
               //->800C6BC
               break;

            case 2:
                //0x0800c635
	            channel_next();
	            channel_set(&channels[bCurrentChannelNumber]);
	            if ((channels[bCurrentChannelNumber].wData_24 < 42) &&
	            		   (channels[bCurrentChannelNumber].service_id != 0))
	            {
	               si46xx_get_dab_values(&r7);
	            }
	            else
	            {
	               si46xx_get_fm_values(&r7);
	            }
	            draw_signal_information_screen(channels, bCurrentChannelNumber, &r7);
                break;

			 case 1:
				 //0x0800c6a9
				 volume_down();
				 break;

			 case 4:
				 //0x0800c6af
				 volume_up();
				 break;

			 case 5:
				 //0x0800c6b5
				 r7_1f = 0;
				 break;

			 default:
				 //loc_800c6ba
				 break;
         }
         //800C6BC
         TouchEvent.bData_0 = 1;
      #if 0 //BUG?
         KeyEvent.bData_0 = 1;
      #endif
      }
      //loc_800c6c2
      if ((wMainloopEvents & 0x10) != 0)
      {
         wMainloopEvents &= ~0x10;

         if ((channels[bCurrentChannelNumber].wData_24 < 42) && (channels[bCurrentChannelNumber].service_id != 0))
         {
            if (0 == si46xx_get_dab_values(&r7))
            {
               if (r7.rssi != rssi)
               {
                  rssi = r7.rssi;
                  draw_signal_level_line(&r7);
               }
               //loc_800c736
               if (r7.snr != snr)
               {
                  snr = r7.snr;
                  draw_signal_quality_line(&r7);
               }
               //loc_800c74e
               if (r7.fib_error_count != fib_error_count)
               {
                  fib_error_count = r7.fib_error_count;
                  draw_signal_error_rate_line(&r7);
               }
            }
            //loc_800c7b6
         }
         else
         {
            //loc_800c764
             if (0 == si46xx_get_fm_values(&r7))
             {
                 if (r7.rssi != rssi)
                 {
                    rssi = r7.rssi;
                    draw_signal_level_line(&r7);
                 }

                 if (r7.snr != snr)
                 {
                    snr = r7.snr;
                    draw_signal_quality_line(&r7);
                 }

                 if (r7.multipath != multipath)
                 {
                    multipath = r7.multipath;
                    draw_signal_multipath_line(&r7);
                 }
             }
             //loc_800c7b6
         }
      }
      //loc_800c7b6
   }
}
