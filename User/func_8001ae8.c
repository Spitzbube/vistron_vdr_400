
#include "stm32f1xx_hal.h"
#include "func_8001ae8.h"


/* 8001ae8 - todo */
void sub_8001ae8(/*struct_8001ae8*/RTC_TimeTypeDef a)
{
	extern struct
	{
		int fill_0; //0
		uint16_t wData_4; //4

	} Data_2000004c; //2000004c

   char r7_c[10];
   uint8_t r7_17 = 0;

   r7_17 = sprintf(r7_c, "%02d:%02d:%02d", a.Hours, a.Minutes, a.Seconds);

   sub_80060ac(&Data_2000004c);
   sub_80060c8(0, 0xffff);

   extern void sub_80060f4(uint16_t, int);
   sub_80060f4(160 - (r7_17 * Data_2000004c.wData_4) / 2, 0x5d);
   sub_8005ff0(r7_c, r7_17);
}


