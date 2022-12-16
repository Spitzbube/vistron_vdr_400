
#include <stdio.h>
#include <stdarg.h>
#include "stm32f1xx_hal.h"
#include "main.h"


#define ILI9341_COLUMN_ADDRESS_SET           0x2a
#define ILI9341_PAGE_ADDRESS_SET             0x2b
#define ILI9341_MEMORY_WRITE                 0x2c


enum {
  MemoryAccessControlNormalOrder,
  MemoryAccessControlReverseOrder
} MemoryAccessControlRefreshOrder;

enum {
	MemoryAccessControlColorOrderRGB,
	MemoryAccessControlColorOrderBGR
} MemoryAccessControlColorOrder;



/* 8005238 - todo */
void lcdInit(void)
{
   lcdPortraitConfig = lcdBuildMemoryAccessControlConfig(0, 1, 0, 0, 1, 0);
   lcdLandscapeConfig = lcdBuildMemoryAccessControlConfig(0, 0, 1, 0, 1, 0);
   lcdPortraitMirrorConfig = lcdBuildMemoryAccessControlConfig(1, 0, 0, 0, 1, 0);
   lcdLandscapeMirrorConfig = lcdBuildMemoryAccessControlConfig(1, 1, 1, 0, 1, 0);

   ili9341_setup_interface();
   lcdWriteCommand(0x28);
   // display off

   lcdWriteCommand(0xcf);
   lcdWriteData(0x00);
   lcdWriteData(0x83);
   lcdWriteData(0x30);
   lcdWriteCommand(0xed);
   lcdWriteData(0x64);
   lcdWriteData(0x03);
   lcdWriteData(0x12);
   lcdWriteData(0x81);
   lcdWriteCommand(0xe8);
   lcdWriteData(0x85);
   lcdWriteData(0x01);
   lcdWriteData(0x79);
   lcdWriteCommand(0xcb);
   lcdWriteData(0x39);
   lcdWriteData(0x2c);
   lcdWriteData(0x00);
   lcdWriteData(0x34);
   lcdWriteData(0x02);
   lcdWriteCommand(0xf7);
   lcdWriteData(0x20);
   lcdWriteCommand(0xea);
   lcdWriteData(0x00);
   lcdWriteData(0x00);
   //------------power control------------------------------
   lcdWriteCommand(0xc0);
   lcdWriteData(0x26);
   lcdWriteCommand(0xc1);
   lcdWriteData(0x11);
   //--------------VCOM
   lcdWriteCommand(0xc5);
   lcdWriteData(0x35);
   lcdWriteData(0x3e);
   lcdWriteCommand(0xc7);
   lcdWriteData(0xbe);
   //------------memory access control------------------------
   lcdWriteCommand(0x36);
   lcdWriteData(lcdLandscapeMirrorConfig); //my,mx,mv,ml,BGR,mh,0.0

   lcdWriteCommand(0x3a); // pixel format set
   lcdWriteData(0x55); //16bit /pixel
   //----------------- frame rate------------------------------
   lcdWriteCommand(0xb1);
   // frame rate
   lcdWriteData(0x00);
   lcdWriteData(0x1b);
   //----------------Gamma---------------------------------
   lcdWriteCommand(0xf2);  // 3Gamma Function Disable
   lcdWriteData(0x08);
   lcdWriteCommand(0x26);
   lcdWriteData(0x01); // gamma set 4 gamma curve 01/02/04/08

   lcdWriteCommand(0xe0); //positive gamma correction
   lcdWriteData(0x1f);
   lcdWriteData(0x1a);
   lcdWriteData(0x18);
   lcdWriteData(0x0a);
   lcdWriteData(0x0f);
   lcdWriteData(0x06);
   lcdWriteData(0x45);
   lcdWriteData(0x87);
   lcdWriteData(0x32);
   lcdWriteData(0x0a);
   lcdWriteData(0x07);
   lcdWriteData(0x02);
   lcdWriteData(0x07);
   lcdWriteData(0x05);
   lcdWriteData(0x00);
   lcdWriteCommand(0xe1); //negamma correction
   lcdWriteData(0x00);
   lcdWriteData(0x25);
   lcdWriteData(0x27);
   lcdWriteData(0x05);
   lcdWriteData(0x10);
   lcdWriteData(0x09);
   lcdWriteData(0x3a);
   lcdWriteData(0x78);
   lcdWriteData(0x4d);
   lcdWriteData(0x05);
   lcdWriteData(0x18);
   lcdWriteData(0x0d);
   lcdWriteData(0x38);
   lcdWriteData(0x3a);
   lcdWriteData(0x1f);
   //--------------ddram ---------------------
   lcdWriteCommand(ILI9341_COLUMN_ADDRESS_SET);
   // column set
   // size = 239
   lcdWriteData(0x00);
   lcdWriteData(0x00);
   lcdWriteData(0x00);
   lcdWriteData(0xef); //240-1
   lcdWriteCommand(ILI9341_PAGE_ADDRESS_SET);
   // page address set
   // size = 319
   lcdWriteData(0x00);
   lcdWriteData(0x00);
   lcdWriteData(0x01);
   lcdWriteData(0x3f); //320-1
	// lcdWriteCommand(0x34);
	//lcdWriteCommand(0x35);
	// tearing effect off
	// tearing effect on
	// lcdWriteCommand(0xb4); // display inversion
	// lcdWriteData(0x00);
   lcdWriteCommand(0xb7); //entry mode set
   lcdWriteData(0x07);
   //-----------------display---------------------
   lcdWriteCommand(0xb6);
   lcdWriteData(0x0a);
   lcdWriteData(0x82);
   lcdWriteData(0x27);
   lcdWriteData(0x00);
   lcdWriteCommand(0x11); //sleep out
   HAL_Delay(100);
   lcdWriteCommand(0x29); // display on
   HAL_Delay(100);

   lcdWriteCommand(ILI9341_MEMORY_WRITE);
}


/* 8005520 - todo */
void lcdFillRGB(uint16_t color)
{
   uint32_t count;

   lcdSetWindow(0, 0, lcdProperties.width - 1, lcdProperties.height - 1);

   count = lcdProperties.width * lcdProperties.height;
   while (count--)
   {
      lcdWriteData(color);
   }
}


/* 8005574 - todo */
void lcdDrawPixel(uint16_t a, uint16_t b, uint16_t color)
{
   if ((a >= lcdProperties.width) ||
		   (b >= lcdProperties.height))
   {
	   return;
   }

   lcdSetWindow(a, b, a, b);
   lcdWriteData(color);
}


/* 80055bc - todo */
void lcdDrawHLine(uint16_t x1, uint16_t x2, uint16_t y, uint16_t color)
{
   int i;

   if (x2 < x1)
   {
      uint16_t r7_a = x1;
      x1 = x2;
      x2 = r7_a;
   }

   if (x2 >= lcdProperties.width)
   {
      x2 = lcdProperties.width - 1;
   }

   if (x1 >= lcdProperties.width)
   {
      x1 = lcdProperties.width - 1;
   }

   lcdSetWindow(x1, y, x2, y);

   for (i = x1; i <= x2; i++)
   {
	   lcdWriteData(color);
   }
}


/* 8005648 - todo */
void lcdDrawVLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color)
{
   int i;

   if (y2 < y1)
   {
      uint16_t r7_a = y1;
      y1 = y2;
      y2 = r7_a;
   }

   if (x >= lcdProperties.width)
   {
      x = lcdProperties.width - 1;
   }

   if (y1 >= lcdProperties.height)
   {
      y1 = lcdProperties.height - 1;
   }

   if (y2 >= lcdProperties.height)
   {
      y2 = lcdProperties.height - 1;
   }

   lcdSetWindow(x, y1, x, y2);

   for (i = y1; i <= y2; i++)
   {
      lcdWriteData(color);
   }
}


/* 800581e - todo */
void lcdDrawRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
   lcdDrawHLine(x, x + width, y, color);
   lcdDrawHLine(x, x + width, y + height, color);
   lcdDrawVLine(x, y, y + height, color);
   lcdDrawVLine(x + width, y, y + height, color);
}


/* 8005898 - todo */
void lcdFillCircle(int16_t a, int16_t b, uint16_t c, uint16_t color)
{
   lcdDrawVLine(a, b - c, b + c, color);
   lcdFillCircleHelper(a, b, c, 1|2, 0, color);
}


/* 80058f0 - todo */
void lcdFillCircleHelper(int16_t r7_6, int16_t r7_4, int16_t r7_2, uint8_t r7_1, int16_t r7_28, uint16_t color)
{
   int16_t r7_16 = 1 - r7_2;
   uint16_t r7_14 = 1;
   uint16_t r7_12 = r7_2 * 65534;
   uint16_t r7_10 = 0;
   uint16_t r7_e = r7_2;
   //->loc_8005a20
   while (r7_10 < r7_e)
   {
      //loc_8005934
      if (r7_16 >= 0)
      {
         r7_e--;
         r7_12 += 2;
         r7_16 += r7_12;
      }
      //loc_800595a
      r7_10++;
      r7_14 += 2;
      r7_16 += (r7_14 + 1);

      if (r7_1 & 1) //right side
      {
         lcdDrawVLine(r7_6 + r7_10, r7_4 - r7_e, r7_4 + r7_e + r7_28, color);
         lcdDrawVLine(r7_6 + r7_e, r7_4 - r7_10, r7_4 + r7_10 + r7_28, color);
      }
      //loc_80059ce
      if (r7_1 & 2) //left side
      {
         lcdDrawVLine(r7_6 - r7_10, r7_4 - r7_e, r7_4 + r7_e + r7_28, color);
         lcdDrawVLine(r7_6 - r7_e, r7_4 - r7_10, r7_4 + r7_10 + r7_28, color);
      }
   }
}


/* 8005a34 - todo */
void lcdFillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
   int16_t line;

   if ((x >= lcdProperties.width) ||
		   (y >= lcdProperties.height))
   {
      return;
   }

   if ((x - 1 + width) >= lcdProperties.width)
   {
      width = lcdProperties.width - x;
   }

   if ((y - 1 + height) >= lcdProperties.height)
   {
      height = lcdProperties.height - y;
   }

   for (line = y; line <= (y + height); line++)
   {
      lcdDrawHLine(x, x + width, line, color);
   }
}


/* 8005af0 - todo */
void lcdFillTriangle(int16_t r7_6, int16_t r7_4, int16_t r7_2, int16_t r7, int16_t r7_48, int16_t r7_4c, uint16_t g/*r7_50*/)
{
   int16_t r7_36;
   int16_t r7_34;
   int16_t r7_32;
   int16_t r7_30;
   int r7_2c;
   int r7_28;
   int16_t r7_26;
   int16_t r7_24;
   int16_t r7_22;
   int16_t r7_20;
   int16_t r7_1e;
   int16_t r7_1c;
   int16_t r7_1a;
   int16_t r7_18;
   int16_t r7_16;
   int16_t r7_14;
   int16_t r7_12;
   int16_t r7_10;
   int16_t r7_e;
   int16_t r7_c;

   if (r7_4 > r7)
   {
      r7_26 = r7_4;
      r7_4 = r7;
      r7 = r7_26;
      r7_24 = r7_6;
      r7_6 = r7_2;
      r7_2 = r7_24;
   }

   if (r7 > r7_4c)
   {
	  r7_22 = r7_4c;
	  r7_4c = r7;
	  r7 = r7_22;
	  r7_20 = r7_48;
	  r7_48 = r7_2;
	  r7_2 = r7_20;
   }

   if (r7_4 > r7)
   {
	  r7_1e = r7_4;
	  r7_4 = r7;
	  r7 = r7_1e;
	  r7_1c = r7_6;
	  r7_6 = r7_2;
	  r7_2 = r7_1c;
   }

   if (r7_4 == r7_4c)
   {
      r7_34 = r7_6;
      r7_36 = r7_34;

      if (r7_2 < r7_36)
      {
         r7_36 = r7_2;
      }
      //loc_8005ba8
      else if (r7_2 > r7_34)
      {
         r7_34 = r7_2;
      }
      //loc_8005bb8
      if (r7_48 < r7_36)
      {
         r7_36 = r7_48;
      }
      else if (r7_48 > r7_34)
      {
         r7_34 = r7_48;
      }
      //loc_8005bde
      lcdDrawHLine(r7_36, r7_34 + 1, r7_4, g);
      //->loc_8005d84
   }
   else
   {
      //loc_8005bf2
      r7_1a = r7_2 - r7_6;
      r7_18 = r7 - r7_4;
      r7_16 = r7_48 - r7_6;
      r7_14 = r7_4c - r7_4;
      r7_12 = r7_48 - r7_2;
      r7_10 = r7_4c - r7;
      r7_2c = 0;
      r7_28 = 0;

      if (r7 == r7_4c)
      {
         r7_30 = r7;
      }
      else
      {
         r7_30 = r7 - 1;
      }
      //->loc_8005cd0
      for (r7_32 = r7_4; r7_32 <= r7_30; r7_32++)
      {
         //loc_8005c5e
         r7_36 = r7_2c / r7_18 + r7_6;
         r7_34 = r7_28 / r7_14 + r7_6;
         r7_2c += r7_1a;
         r7_28 += r7_16;

         if (r7_36 > r7_34)
         {
            r7_c = r7_36;
            r7_36 = r7_34;
            r7_34 = r7_c;
         }
         //loc_8005cb2
         lcdDrawHLine(r7_36, r7_34 + 1, r7_32, g);
      }
      //08005cdc
      r7_2c = (r7_32 - r7) * r7_12;
      r7_28 = (r7_32 - r7_4) * r7_16;
      //->loc_8005d78
      for (; r7_32 <= r7_4c; r7_32++)
      {
         //loc_8005d06
         r7_36 = r7_2c / r7_10 + r7_2;
         r7_34 = r7_28 / r7_14 + r7_6;
         r7_2c += r7_12;
         r7_28 += r7_16;

         if (r7_36 > r7_34)
         {
            r7_e = r7_36;
            r7_36 = r7_34;
            r7_34 = r7_e;
         }
         //loc_8005d5a
         lcdDrawHLine(r7_36, r7_34 + 1, r7_32, g);
      }
   }
}


/* 8005d8c - todo */
void lcdDrawChar(int16_t x, int16_t y, char c, uint16_t fg, uint16_t bg)
{
   uint8_t col;
   uint8_t row;
   uint8_t pixels;
   uint8_t bytes;
   uint8_t bit;
   uint8_t num_bytes;

   if ((x >= lcdProperties.width) ||
		   (y >= lcdProperties.height) ||
		   ((x + lcdFont.pFont->Width) < 0) ||
		   ((y + lcdFont.pFont->Height) < 0))
   {
	   return;
   }

   num_bytes = lcdFont.pFont->Height / 8;
   col = 0;

   for (row = 0; row < lcdFont.pFont->Height; row++)
   {
      for (bytes = 0; bytes < num_bytes; bytes++)
      {
         pixels = lcdFont.pFont->table[((c - ' ') * lcdFont.pFont->Height + row) * num_bytes + bytes];

         for (bit = 0; bit < 8; bit++)
         {
            if (pixels & (1 << 7))
            {
               lcdDrawPixel(bit + x + col, row + y, fg);
            }
            else if (bg != fg)
            {
               lcdDrawPixel(bit + x + col, row + y, bg);
            }

            pixels <<= 1;
         }

         col += 8;
      }

      col = 0;
   }
}


/* 8005edc - todo */
void lcdPrintf(const char * format, ...)
{
   va_list args;
   va_start(args, format);
   vsprintf(Data_200000ec, format, args);

   for (char* pch = Data_200000ec; *pch; )
   {
      if (*pch == 10)
      {
         cursorXY.y += lcdFont.pFont->Height;
         cursorXY.x = 0;
      }
      else if (*pch != 13)
      {
         if (*pch == 9)
         {
            cursorXY.x += lcdFont.pFont->Width * 4;
         }
         else
         {
            lcdDrawChar(cursorXY.x,
            		cursorXY.y,
					*pch,
					lcdFont.TextColor,
					lcdFont.BackColor);

            cursorXY.x += lcdFont.pFont->Width;

            if (lcdFont.TextWrap != 0)
            {
            	if (cursorXY.x > (lcdProperties.width - lcdFont.pFont->Width))
            	{
                   cursorXY.y += lcdFont.pFont->Height;
                   cursorXY.x = 0;
            	}
            }
         }
      }

      pch++;

      if (cursorXY.y >= lcdProperties.height)
      {
         cursorXY.y = 0;
      }
   }
}


/* 8005ff0 - todo */
void ili9341_draw_string(char* a, uint8_t len)
{
   char* r7_c;
   uint8_t i = 0;
   r7_c = a;

   while (i++ < len)
   {
      lcdDrawChar(
    		  cursorXY.x,
			  cursorXY.y,
			  r7_c[0],
			  lcdFont.TextColor,
			  lcdFont.BackColor);

      cursorXY.x += lcdFont.pFont->Width;

      if (lcdFont.TextWrap != 0)
      {
         if (cursorXY.x > (lcdProperties.width - lcdFont.pFont->Width))
         {
            cursorXY.y += lcdFont.pFont->Height;
            cursorXY.x = 0;
         }
      }

      r7_c++;

      if (cursorXY.y >= lcdProperties.height)
      {
         cursorXY.y = 0;
      }
   }
}


/* 80060ac - todo */
void lcdSetTextFont(sFONT* a)
{
   lcdFont.pFont = a;
}


/* 80060c8 - todo */
void lcdSetTextColor(uint16_t fg, uint16_t bg)
{
   lcdFont.TextColor = fg;
   lcdFont.BackColor = bg;
}


/* 80060f4 - todo */
void lcdSetCursor(uint16_t x, uint16_t y)
{
   cursorXY.x = x;
   cursorXY.y = y;

   lcdSetWindow(x, y, x, y);
}


/* 8006128 - todo */
void lcdSetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
   lcdWriteCommand(ILI9341_COLUMN_ADDRESS_SET);

   lcdWriteData(x1 >> 8);
   lcdWriteData(x1 & 0xff);

   lcdWriteData(x2 >> 8);
   lcdWriteData(x2 & 0xff);

   lcdWriteCommand(ILI9341_PAGE_ADDRESS_SET);

   lcdWriteData(y1 >> 8);
   lcdWriteData(y1 & 0xff);

   lcdWriteData(y2 >> 8);
   lcdWriteData(y2 & 0xff);

   lcdWriteCommand(ILI9341_MEMORY_WRITE);
}


/* 80061c0 - todo */
void ili9341_setup_interface(void)
{
   ili9341_configure_gpio();
   ili9341_configure_fsmc();

   HAL_GPIO_WritePin(ILI9341_Reset_GPIO_Port, ILI9341_Reset_Pin, GPIO_PIN_SET);
   main_delay(100);
   HAL_GPIO_WritePin(ILI9341_Reset_GPIO_Port, ILI9341_Reset_Pin, GPIO_PIN_RESET);
   main_delay(300);
   HAL_GPIO_WritePin(ILI9341_Reset_GPIO_Port, ILI9341_Reset_Pin, GPIO_PIN_SET);
   main_delay(100);

   lcdWriteCommand(1);

   HAL_Delay(50);
}


/* 8006214 - todo */
void lcdWriteCommand(uint8_t command)
{
   LCD_CmdWrite(command);
}


/* 8006234 - todo */
void lcdWriteData(uint16_t data)
{
   LCD_DataWrite(data);
}


/* 8006254 - todo */
uint8_t lcdBuildMemoryAccessControlConfig(uint8_t my, uint8_t mx, uint8_t mv, uint8_t ml, uint8_t bgr, uint8_t mh)
{
   uint8_t madctl = 0;

   //Horizontal Refresh ORDER
   if (mh != 0)
   {
      madctl |= 0x04;
   }

   //RGB-BGR Order
   if (bgr != 0)
   {
      madctl |= 0x08;
   }

   //Vertical Refresh Order
   if (ml != 0)
   {
      madctl |= 0x10;
   }

   //Row / Column Exchange
   if (mv != 0)
   {
      madctl |= 0x20;
   }

   //Column Address Order
   if (mx != 0)
   {
      madctl |= 0x40;
   }

   //Row Address Order
   if (my != 0)
   {
      madctl |= 0x80;
   }

   return madctl;
}


/* 80062d8 - todo */
void ili9341_configure_gpio(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_GPIOE_CLK_ENABLE();

   GPIO_InitStruct.Pin = 0xcfb3; //1100 1111 1011 0011 = FSMC_D1, FSMC_D0, FSMC_A16, FSMC_D15 ... FSMC_D13, FSMC_D3, FSMC_D2
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = 0xff80; //1111 1111 1000 0000 = FSMC_D12 ... FSMC_D4
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

   GPIO_InitStruct.Pin = ILI9341_Reset_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


/* 80063a4 - todo */
void ili9341_configure_fsmc(void)
{
   SRAM_HandleTypeDef hsram;
   FSMC_NORSRAM_TimingTypeDef Timing = {0};

   hsram.Instance = FSMC_NORSRAM_DEVICE;
   hsram.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

   hsram.Init.NSBank = FSMC_NORSRAM_BANK1;
   hsram.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
   hsram.Init.MemoryType = FSMC_MEMORY_TYPE_NOR;
   hsram.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
   hsram.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
   hsram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
   hsram.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
   hsram.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
   hsram.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
   hsram.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
   hsram.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
   hsram.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
   hsram.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;

   Timing.AddressSetupTime = 3;
   Timing.AddressHoldTime = 0;
   Timing.DataSetupTime = 6;
   Timing.BusTurnAroundDuration = 0;
   Timing.CLKDivision = 1;
   Timing.DataLatency = 0;
   Timing.AccessMode = FSMC_ACCESS_MODE_B;

   HAL_SRAM_Init(&hsram, &Timing, NULL);
}


