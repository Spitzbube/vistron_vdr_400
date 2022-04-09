
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"


/* 80013a0 - todo */
int sub_80013a0(uint16_t a)
{

}


/* 8001450 - todo */
int sub_8001450(int a, int b)
{

}


/* 80016f0 - todo */
int sub_80016f0(int a)
{

}


/* 8001ae8 - todo */
void sub_8001ae8(RTC_TimeTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0, 0xffff);

   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 93);
   ili9341_draw_string(buf, len);
}


/* 8001b60 - todo */
void sub_8001b60(RTC_TimeTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0xffff, 0);

   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 96);
   ili9341_draw_string(buf, len);
}


/* 8002054 - todo */
void sub_8002054(struct_8008d84* a, uint8_t b, uint8_t c, void* d, uint8_t e)
{

}


/* 8002128 - todo */
int sub_8002128(uint16_t a, uint16_t b)
{
   if ((a > 7) && (a < 45) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(8, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(8, 196, 0x1f, 1);
      return 3;
   }

   if ((a > 60) && (a < 98) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(61, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(61, 196, 0x7e0, 0);
      return 2;
   }

   if ((a > 113) && (a < 151) && (b > 195) && (b < 233) &&
		   ((wData_20000a56 & 0x04) == 0)) //TODO
   {
      ili9341_draw_box(114, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(114, 196, 0xf800, 5);
      return 1;
   }

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(167, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(167, 196, 0xffe0, 6);
      return 4;
   }

   if ((a > 272) && (a < 311) && (b > 197) && (b < 233))
   {
      ili9341_draw_box(273, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(273, 196, 0xffff, 7);
      return 5;
   }

   if ((a > 241) && (a <= 305) && (b > 5) && (b < 43))
   {
      return 24;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 71) && (b < 97))
   {
      return 7;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 95) && (b < 121))
   {
      return 8;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 119) && (b < 145))
   {
      return 9;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 143) && (b < 169))
   {
      return 10;
   }

   if ((a <= (Data_20000044.width * 24)) && (b > 167) && (b < 193))
   {
      return 11;
   }

   if ((a > (Data_20000044.width * 24)) && (a < 321) && (b > 47) && (b < 73))
   {
      return 12;
   }

   if ((a > (Data_20000044.width * 24)) && (a < 321) && (b > 167) && (b < 193))
   {
      return 13;
   }

   return 0;
}


/* 800ac74 - todo */
void sub_800ac74(void)
{

}


/* 800acf0 - todo */
void sub_800acf0(void)
{

}


/* 800ad68 - todo */
void sub_800ad68(void)
{

}


/* 800adb8 - todo */
void sub_800adb8(void)
{

}


/* 800b1c8 - todo */
void button_gpio_check(void)
{
   if (Data_20000a48.bData_0 != 1)
   {
      return;
   }

   bData_20000056--;
   if (bData_20000056 != 0)
   {
      return;
   }

   bData_20000056 = 4;

   if (0 == HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 4; //yellow
   }

   if (0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 1; //red
   }

   if (0 == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 2; //green
   }

   if (0 == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))
   {
      Data_20000a48.bData_0 = 0;
      Data_20000a48.bData_1 = 3; //blue
   }
}


/* 8002722 - todo */
void sub_8002722(int a, int b, void* c, int d)
{

}


/* 80028b8 - todo */
void sub_80028b8(struct_8008d84* a, uint8_t b, uint8_t c)
{

}


/* 8008554 - todo */
void sub_8008554(void)
{

}


/* 800b610 - todo */
void sub_800b610(uint8_t a)
{

}


/* 800ba74 - todo */
void sub_800ba74(struct_8008d84* a, struct_8008d84* b, void* c, void* d)
{

}


/* 800bd2c - todo */
void sub_800bd2c(void)
{
   uint8_t r7_1f = 1;
   int8_t r7_1e;
   int8_t r7_1d;
   uint8_t r7_1c;
   uint8_t r7_1b;
   uint8_t r7_1a;
   uint8_t r7_19 = bData_20000a58;
   uint8_t r7_18;
   struct_8008d84* r7_14;
   struct
   {
	   int8_t bData_0; //0
	   int8_t bData_1; //1
	   int fill_0[3];
	   //16
   } r7_4 = {0};

   r7_1e = 0;
   r7_1d = 0;
   r7_1a = 0;
   r7_18 = (wData_20000a56 & 0x04)? bData_20000be4: bData_200022a8;
   r7_14 = (wData_20000a56 & 0x04)? Data_20000be8: Data_20000cc8;

   if (bData_200022a8 == 0)
   {
      return;
   }

   sub_8002054(r7_14, bData_20000a58, r7_18, &r7_4, bData_20000057);

   Data_20000bc0.bData_0 = 1;
   //->loc_800c312
   while (r7_1f != 0)
   {
      //loc_800bda8
      r7_18 = (wData_20000a56 & 0x04)? bData_20000be4: bData_200022a8;
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
         r7_1b = sub_8002128(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_800bdf8
      if ((r7_1b | r7_1c) != 0)
      {
         switch (r7_1b | r7_1c)
         {
         case 3:
        	 //800be7c
        	 sub_800ac74();
        	 sub_80028b8(r7_14, bData_20000a58, r7_18);
        	 sub_800abb0(&r7_14[bData_20000a58]);
        	 //->800C1E8
        	 break;

         case 2:
        	 //800beaa
        	 sub_800acf0();
        	 sub_80028b8(r7_14, bData_20000a58, r7_18);
        	 sub_800abb0(&r7_14[bData_20000a58]);
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
        		 sub_800b610(bData_20000a58);
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
        		 r7_1a = 1;
        	 }
        	 //800C1CA
        	 break;

         case 5:
        	 //800bf1e
        	 bData_20000a58 = r7_19;
        	 sub_800abb0(&r7_14[bData_20000a58]);
        	 r7_1f = 0;
        	 //->800C1E8
        	 break;

         case 7:
        	 //800bf44
        	 if (r7_18 != 0)
        	 {
        		 bData_20000a58 -= 2; //TODO

        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1CE
        	 break;

         case 8:
        	 //800bf8a
        	 if (r7_18 > 1)
        	 {
        		 bData_20000a58 -= 1; //TODO

        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1D2
        	 break;

         case 9:
        	 //800bfd0
        	 if ((r7_18 > 2) && (bData_20000a58 < 2))
        	 {
        		 bData_20000a58 = 2;
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1D6
        	 break;

         case 10:
        	 //800c040
        	 if ((r7_18 > 3) && ((bData_20000a58 + 1) < r7_18))
        	 {
        		 bData_20000a58++;
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1DA
        	 break;

         case 11:
        	 //800c08c
        	 if ((r7_18 > 4) && ((bData_20000a58 + 2) < r7_18))
        	 {
        		 bData_20000a58 += 2;
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1DE
        	 break;

         case 12:
        	 //800c0d8
        	 if (r7_18 > 4)
        	 {
        		 if (bData_20000a58 == 0)
        		 {
        			 bData_20000a58 = r7_18 - 1;
        			 //->800C118
        		 }
        		 //800C0F4
        		 else if (bData_20000a58 > 4)
        		 {
        			 bData_20000a58 -= 5; //TODO
        			 //->800C118
        		 }
        		 else
        		 {
        			 //800C112
        			 bData_20000a58 = 0;
        		 }
        		 //800C118
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
            	 //->800C1E2
        	 }
        	 //800C1E2
        	 break;

         case 13:
        	 //800c142
        	 if (r7_18 > 4)
        	 {
        		 if ((bData_20000a58 + 1) < r7_18)
        		 {
        			 bData_20000a58 = ((bData_20000a58 + 5) > r7_18)? r7_18 - 1: bData_20000a58 + 5;
        			 //->800C17C
        		 }
        		 else
        		 {
        			 //800C176
        			 bData_20000a58 = 0;
        		 }
        		 //800C17C
        		 sub_80028b8(r7_14, bData_20000a58, r7_18);
            	 sub_800abb0(&r7_14[bData_20000a58]);
        	 }
        	 //800C1E6
        	 break;

         case 24:
        	 //800c1a6
        	 sub_8008554();
        	 sub_8002054(r7_14, bData_20000a58, r7_18, &r7_4, bData_20000057);
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

    	  if ((Data_20000cc8[bData_20000a58].wData_24 < 41) && (Data_20000cc8[bData_20000a58].service_id != 0))
    	  {
    		  //0800c23c
    		  sub_800a6ec(&r7_4);
    		  if (0 == sub_800a6ec(&r7_4))
    		  {
    			  //0800c252
    			  if (r7_4.bData_0/5 != r7_1e/5)
    			  {
    				  //0800c27a
    				  r7_1e = r7_4.bData_0;

    				  sub_8001cc4(0x8e, 0x2a, &r7_4);
    			  }
    			  //loc_800c28a
    			  if (r7_4.bData_1 != r7_1d)
    			  {
    				  //0800c296
    				  r7_1d = r7_4.bData_1;

    				  sub_8002722(0xde, 0x07, &r7_4, 1);
    			  }
    			  //loc_800c312
    		  }
    		  //loc_800c312
    	  }
    	  else
    	  {
        	  //loc_800c2a8
    		  sub_800a68c(&r7_4);
    		  if (0 == sub_800a68c(&r7_4))
    		  {
    			  if (r7_4.bData_0/5 != r7_1e/5)
    			  {
    				  //0800c2e6
    				  r7_1e = r7_4.bData_0;

    				  sub_8001cc4(0x8e, 0x2a, &r7_4);
    			  }
    			  //loc_800c2f6
    			  if (r7_4.bData_1 != r7_1d)
    			  {
    				  //0800c302
    				  r7_1d = r7_4.bData_1;

    				  sub_8002722(0xde, 0x07, &r7_4, 1);
    			  }
    		  }
    	  }
      }
      //loc_800c312 -> loc_800bda8
   } //while (r7_1f != 0)
   //loc_800c31a
}

