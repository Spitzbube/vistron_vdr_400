
#include <stdio.h>
#include <stdarg.h>
#include "stm32f1xx_hal.h"
#include "main.h"


#define ILI9341_COLUMN_ADDRESS_SET           0x2a
#define ILI9341_PAGE_ADDRESS_SET             0x2b
#define ILI9341_MEMORY_WRITE                 0x2c


/* 8005238 - todo */
void ili9341_init(void)
{
   g_bDisplayMemoryAccessCtrl1 = ili9341_get_madctl(0, 1, 0, 0, 1, 0);
   g_bDisplayMemoryAccessCtrl2 = ili9341_get_madctl(0, 0, 1, 0, 1, 0);
   g_bDisplayMemoryAccessCtrl3 = ili9341_get_madctl(1, 0, 0, 0, 1, 0);
   g_bDisplayMemoryAccessCtrl4 = ili9341_get_madctl(1, 1, 1, 0, 1, 0);

   ili9341_setup_interface();
   ili9341_write_command(0x28);
   // display off

   ili9341_write_command(0xcf);
   ili9341_write_data(0x00);
   ili9341_write_data(0x83);
   ili9341_write_data(0x30);
   ili9341_write_command(0xed);
   ili9341_write_data(0x64);
   ili9341_write_data(0x03);
   ili9341_write_data(0x12);
   ili9341_write_data(0x81);
   ili9341_write_command(0xe8);
   ili9341_write_data(0x85);
   ili9341_write_data(0x01);
   ili9341_write_data(0x79);
   ili9341_write_command(0xcb);
   ili9341_write_data(0x39);
   ili9341_write_data(0x2c);
   ili9341_write_data(0x00);
   ili9341_write_data(0x34);
   ili9341_write_data(0x02);
   ili9341_write_command(0xf7);
   ili9341_write_data(0x20);
   ili9341_write_command(0xea);
   ili9341_write_data(0x00);
   ili9341_write_data(0x00);
   //------------power control------------------------------
   ili9341_write_command(0xc0);
   ili9341_write_data(0x26);
   ili9341_write_command(0xc1);
   ili9341_write_data(0x11);
   //--------------VCOM
   ili9341_write_command(0xc5);
   ili9341_write_data(0x35);
   ili9341_write_data(0x3e);
   ili9341_write_command(0xc7);
   ili9341_write_data(0xbe);
   //------------memory access control------------------------
   ili9341_write_command(0x36);
   ili9341_write_data(g_bDisplayMemoryAccessCtrl4); //my,mx,mv,ml,BGR,mh,0.0

   ili9341_write_command(0x3a); // pixel format set
   ili9341_write_data(0x55); //16bit /pixel
   //----------------- frame rate------------------------------
   ili9341_write_command(0xb1);
   // frame rate
   ili9341_write_data(0x00);
   ili9341_write_data(0x1b);
   //----------------Gamma---------------------------------
   ili9341_write_command(0xf2);  // 3Gamma Function Disable
   ili9341_write_data(0x08);
   ili9341_write_command(0x26);
   ili9341_write_data(0x01); // gamma set 4 gamma curve 01/02/04/08

   ili9341_write_command(0xe0); //positive gamma correction
   ili9341_write_data(0x1f);
   ili9341_write_data(0x1a);
   ili9341_write_data(0x18);
   ili9341_write_data(0x0a);
   ili9341_write_data(0x0f);
   ili9341_write_data(0x06);
   ili9341_write_data(0x45);
   ili9341_write_data(0x87);
   ili9341_write_data(0x32);
   ili9341_write_data(0x0a);
   ili9341_write_data(0x07);
   ili9341_write_data(0x02);
   ili9341_write_data(0x07);
   ili9341_write_data(0x05);
   ili9341_write_data(0x00);
   ili9341_write_command(0xe1); //negamma correction
   ili9341_write_data(0x00);
   ili9341_write_data(0x25);
   ili9341_write_data(0x27);
   ili9341_write_data(0x05);
   ili9341_write_data(0x10);
   ili9341_write_data(0x09);
   ili9341_write_data(0x3a);
   ili9341_write_data(0x78);
   ili9341_write_data(0x4d);
   ili9341_write_data(0x05);
   ili9341_write_data(0x18);
   ili9341_write_data(0x0d);
   ili9341_write_data(0x38);
   ili9341_write_data(0x3a);
   ili9341_write_data(0x1f);
   //--------------ddram ---------------------
   ili9341_write_command(ILI9341_COLUMN_ADDRESS_SET);
   // column set
   // size = 239
   ili9341_write_data(0x00);
   ili9341_write_data(0x00);
   ili9341_write_data(0x00);
   ili9341_write_data(0xef); //240-1
   ili9341_write_command(ILI9341_PAGE_ADDRESS_SET);
   // page address set
   // size = 319
   ili9341_write_data(0x00);
   ili9341_write_data(0x00);
   ili9341_write_data(0x01);
   ili9341_write_data(0x3f); //320-1
	// ili9341_write_command(0x34);
	//ili9341_write_command(0x35);
	// tearing effect off
	// tearing effect on
	// ili9341_write_command(0xb4); // display inversion
	// ili9341_write_data(0x00);
   ili9341_write_command(0xb7); //entry mode set
   ili9341_write_data(0x07);
   //-----------------display---------------------
   ili9341_write_command(0xb6);
   ili9341_write_data(0x0a);
   ili9341_write_data(0x82);
   ili9341_write_data(0x27);
   ili9341_write_data(0x00);
   ili9341_write_command(0x11); //sleep out
   HAL_Delay(100);
   ili9341_write_command(0x29); // display on
   HAL_Delay(100);

   ili9341_write_command(ILI9341_MEMORY_WRITE);
}


/* 8005520 - todo */
void ili9341_fill_screen(uint16_t a)
{
   uint32_t count;

   ili9341_set_address(0, 0, ScreenResolution.width - 1, ScreenResolution.height - 1);

   count = ScreenResolution.width * ScreenResolution.height;
   while (count--)
   {
      ili9341_write_data(a);
   }
}


/* 8005574 - todo */
void ili9341_draw_pixel(uint16_t a, uint16_t b, uint16_t c)
{
   if ((a >= ScreenResolution.width) ||
		   (b >= ScreenResolution.height))
   {
	   return;
   }

   ili9341_set_address(a, b, a, b);
   ili9341_write_data(c);
}


/* 80055bc - todo */
void ili9341_draw_hor_line(uint16_t x1, uint16_t x2, uint16_t y, uint16_t color)
{
   int i;

   if (x2 < x1)
   {
      uint16_t r7_a = x1;
      x1 = x2;
      x2 = r7_a;
   }

   if (x2 >= ScreenResolution.width)
   {
      x2 = ScreenResolution.width - 1;
   }

   if (x1 >= ScreenResolution.width)
   {
      x1 = ScreenResolution.width - 1;
   }

   ili9341_set_address(x1, y, x2, y);

   for (i = x1; i <= x2; i++)
   {
	   ili9341_write_data(color);
   }
}


/* 8005648 - todo */
void ili9341_draw_vert_line(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color)
{
   int i;

   if (y2 < y1)
   {
      uint16_t r7_a = y1;
      y1 = y2;
      y2 = r7_a;
   }

   if (x >= ScreenResolution.width)
   {
      x = ScreenResolution.width - 1;
   }

   if (y1 >= ScreenResolution.height)
   {
      y1 = ScreenResolution.height - 1;
   }

   if (y2 >= ScreenResolution.height)
   {
      y2 = ScreenResolution.height - 1;
   }

   ili9341_set_address(x, y1, x, y2);

   for (i = y1; i <= y2; i++)
   {
      ili9341_write_data(color);
   }
}


/* 800581e - todo */
void ili9341_draw_rect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
   ili9341_draw_hor_line(x, x + width, y, color);
   ili9341_draw_hor_line(x, x + width, y + height, color);
   ili9341_draw_vert_line(x, y, y + height, color);
   ili9341_draw_vert_line(x + width, y, y + height, color);
}


/* 8005898 - todo */
void ili9341_draw_circle(int16_t a, int16_t b, uint16_t c, uint16_t color)
{
   ili9341_draw_vert_line(a, b - c, b + c, color);
   sub_80058f0(a, b, c, 1|2, 0, color);
}


/* 80058f0 - todo */
void sub_80058f0(int16_t r7_6, int16_t r7_4, int16_t r7_2, uint8_t r7_1, int16_t r7_28, uint16_t color)
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
         ili9341_draw_vert_line(r7_6 + r7_10, r7_4 - r7_e, r7_4 + r7_e + r7_28, color);
         ili9341_draw_vert_line(r7_6 + r7_e, r7_4 - r7_10, r7_4 + r7_10 + r7_28, color);
      }
      //loc_80059ce
      if (r7_1 & 2) //left side
      {
         ili9341_draw_vert_line(r7_6 - r7_10, r7_4 - r7_e, r7_4 + r7_e + r7_28, color);
         ili9341_draw_vert_line(r7_6 - r7_e, r7_4 - r7_10, r7_4 + r7_10 + r7_28, color);
      }
   }
}


/* 8005a34 - todo */
void ili9341_draw_box(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
   int16_t line;

   if ((x >= ScreenResolution.width) ||
		   (y >= ScreenResolution.height))
   {
      return;
   }

   if ((x - 1 + width) >= ScreenResolution.width)
   {
      width = ScreenResolution.width - x;
   }

   if ((y - 1 + height) >= ScreenResolution.height)
   {
      height = ScreenResolution.height - y;
   }

   for (line = y; line <= (y + height); line++)
   {
      ili9341_draw_hor_line(x, x + width, line, color);
   }
}


/* 8005af0 - todo */
void sub_8005af0(int16_t r7_6, int16_t r7_4, int16_t r7_2, int16_t r7, int16_t r7_48, int16_t r7_4c, uint16_t g/*r7_50*/)
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
      ili9341_draw_hor_line(r7_36, r7_34 + 1, r7_4, g);
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
         ili9341_draw_hor_line(r7_36, r7_34 + 1, r7_32, g);
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
         ili9341_draw_hor_line(r7_36, r7_34 + 1, r7_32, g);
      }
   }
}


/* 8005d8c - todo */
void ili9341_draw_char(int16_t x, int16_t y, char c, uint16_t fg, uint16_t bg)
{
   uint8_t col;
   uint8_t row;
   uint8_t pixels;
   uint8_t bytes;
   uint8_t bit;
   uint8_t num_bytes;

   if ((x >= ScreenResolution.width) ||
		   (y >= ScreenResolution.height) ||
		   ((x + TextAttributes.pFont->width) < 0) ||
		   ((y + TextAttributes.pFont->height) < 0))
   {
	   return;
   }

   num_bytes = TextAttributes.pFont->height / 8;
   col = 0;

   for (row = 0; row < TextAttributes.pFont->height; row++)
   {
      for (bytes = 0; bytes < num_bytes; bytes++)
      {
         pixels = TextAttributes.pFont->Data_0[((c - ' ') * TextAttributes.pFont->height + row) * num_bytes + bytes];

         for (bit = 0; bit < 8; bit++)
         {
            if (pixels & (1 << 7))
            {
               ili9341_draw_pixel(bit + x + col, row + y, fg);
            }
            else if (bg != fg)
            {
               ili9341_draw_pixel(bit + x + col, row + y, bg);
            }

            pixels <<= 1;
         }

         col += 8;
      }

      col = 0;
   }
}


/* 8005edc - todo */
void ili9341_draw_format_string(const char * format, ...)
{
   va_list args;
   va_start(args, format);
   vsprintf(Data_200000ec, format, args);

   for (char* pch = Data_200000ec; *pch; )
   {
      if (*pch == 10)
      {
         TextCursor.y += TextAttributes.pFont->height;
         TextCursor.x = 0;
      }
      else if (*pch != 13)
      {
         if (*pch == 9)
         {
            TextCursor.x += TextAttributes.pFont->width * 4;
         }
         else
         {
            ili9341_draw_char(TextCursor.x,
            		TextCursor.y,
					*pch,
					TextAttributes.fg_color,
					TextAttributes.bg_color);

            TextCursor.x += TextAttributes.pFont->width;

            if (TextAttributes.bData_12 != 0)
            {
            	if (TextCursor.x > (ScreenResolution.width - TextAttributes.pFont->width))
            	{
                   TextCursor.y += TextAttributes.pFont->height;
                   TextCursor.x = 0;
            	}
            }
         }
      }

      pch++;

      if (TextCursor.y >= ScreenResolution.height)
      {
         TextCursor.y = 0;
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
      ili9341_draw_char(
    		  TextCursor.x,
			  TextCursor.y,
			  r7_c[0],
			  TextAttributes.fg_color,
			  TextAttributes.bg_color);

      TextCursor.x += TextAttributes.pFont->width;

      if (TextAttributes.bData_12 != 0)
      {
         if (TextCursor.x > (ScreenResolution.width - TextAttributes.pFont->width))
         {
            TextCursor.y += TextAttributes.pFont->height;
            TextCursor.x = 0;
         }
      }

      r7_c++;

      if (TextCursor.y >= ScreenResolution.height)
      {
         TextCursor.y = 0;
      }
   }
}


/* 80060ac - todo */
void ili9341_set_font(Struct_2000002c_Inner8* a)
{
   TextAttributes.pFont = a;
}


/* 80060c8 - todo */
void ili9341_set_text_color(uint16_t fg, uint16_t bg)
{
   TextAttributes.fg_color = fg;
   TextAttributes.bg_color = bg;
}


/* 80060f4 - todo */
void ili9341_set_cursor(uint16_t x, uint16_t y)
{
   TextCursor.x = x;
   TextCursor.y = y;

   ili9341_set_address(x, y, x, y);
}


/* 8006128 - todo */
void ili9341_set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
   ili9341_write_command(ILI9341_COLUMN_ADDRESS_SET);

   ili9341_write_data(x1 >> 8);
   ili9341_write_data(x1 & 0xff);

   ili9341_write_data(x2 >> 8);
   ili9341_write_data(x2 & 0xff);

   ili9341_write_command(ILI9341_PAGE_ADDRESS_SET);

   ili9341_write_data(y1 >> 8);
   ili9341_write_data(y1 & 0xff);

   ili9341_write_data(y2 >> 8);
   ili9341_write_data(y2 & 0xff);

   ili9341_write_command(ILI9341_MEMORY_WRITE);
}


/* 80061c0 - todo */
void ili9341_setup_interface(void)
{
   ili9341_configure_gpio();
   ili9341_configure_fsmc();

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
   main_delay(100);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
   main_delay(300);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
   main_delay(100);

   ili9341_write_command(1);

   HAL_Delay(50);
}


/* 8006214 - todo */
void ili9341_write_command(uint8_t a)
{
   *((uint16_t*)(FSMC_BANK1)) = a;
}


/* 8006234 - todo */
void ili9341_write_data(uint16_t a)
{
   *((uint16_t*)(FSMC_BANK1 + 0x20000)) = a;
}


/* 8006254 - todo */
uint8_t ili9341_get_madctl(uint8_t my, uint8_t mx, uint8_t mv, uint8_t ml, uint8_t bgr, uint8_t mh)
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

   GPIO_InitStruct.Pin = GPIO_PIN_1;
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


