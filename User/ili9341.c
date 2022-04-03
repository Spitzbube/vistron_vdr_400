
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
   bData_200000e8 = sub_8006254(0, 1, 0, 0, 1, 0);
   bData_200000e9 = sub_8006254(0, 0, 1, 0, 1, 0);
   bData_200000ea = sub_8006254(1, 0, 0, 0, 1, 0);
   bData_200000eb = sub_8006254(1, 1, 1, 0, 1, 0);

   ili9341_setup_interface();
   ili9341_write_command(0x28);
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
   ili9341_write_command(0xc0);
   ili9341_write_data(0x26);
   ili9341_write_command(0xc1);
   ili9341_write_data(0x11);
   ili9341_write_command(0xc5);
   ili9341_write_data(0x35);
   ili9341_write_data(0x3e);
   ili9341_write_command(0xc7);
   ili9341_write_data(0xbe);

   ili9341_write_command(0x36);
   ili9341_write_data(bData_200000eb);

   ili9341_write_command(0x3a);
   ili9341_write_data(0x55);

   ili9341_write_command(0xb1);
   ili9341_write_data(0x00);
   ili9341_write_data(0x1b);
   ili9341_write_command(0xf2);
   ili9341_write_data(0x08);
   ili9341_write_command(0x26);
   ili9341_write_data(0x01);
   ili9341_write_command(0xe0);
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
   ili9341_write_command(0xe1);
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

   ili9341_write_command(ILI9341_COLUMN_ADDRESS_SET);
   ili9341_write_data(0x00);
   ili9341_write_data(0x00);
   ili9341_write_data(0x00);
   ili9341_write_data(0xef); //240-1

   ili9341_write_command(ILI9341_PAGE_ADDRESS_SET);
   ili9341_write_data(0x00);
   ili9341_write_data(0x00);
   ili9341_write_data(0x01);
   ili9341_write_data(0x3f); //320-1

   ili9341_write_command(0xb7);
   ili9341_write_data(0x07);
   ili9341_write_command(0xb6);
   ili9341_write_data(0x0a);
   ili9341_write_data(0x82);
   ili9341_write_data(0x27);
   ili9341_write_data(0x00);
   ili9341_write_command(0x11);

   HAL_Delay(100);
   ili9341_write_command(0x29);
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
   sub_80062d8();
   sub_80063a4();

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
   sub_800c7e0(100);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
   sub_800c7e0(300);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
   sub_800c7e0(100);

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


