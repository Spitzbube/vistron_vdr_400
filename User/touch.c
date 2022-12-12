
#include "main.h"


/* 8006434 - todo */
int touch_init(void)
{
   uint8_t r7_7 = 1;

   TouchEvent.bData_0 = 1;
   TouchEvent.wData_2 = 0;
   TouchEvent.wData_4 = 0;

   g_stTouchData.timerCount = 0;
   g_stTouchData.raw_x = 0x8000;
   g_stTouchData.raw_y = 0x8000;
   g_stTouchData.x = 0;
   g_stTouchData.y = 0;
   g_stTouchData.Data_12 = 0.0883789;
   g_stTouchData.Data_16 = 0.00166484;
   g_stTouchData.Data_20 = -31.2288;
   g_stTouchData.Data_24 = -0.000867953;
   g_stTouchData.Data_28 = -0.0661776;
   g_stTouchData.Data_32 = 255.59;
#if 0
   g_stTouchData.wData_36 = 2153;
   g_stTouchData.wData_38 = 570;
   g_stTouchData.wData_40 = 677;
   g_stTouchData.wData_42 = 2040;
   g_stTouchData.wData_44 = 3547;
   g_stTouchData.wData_46 = 3453;
#endif

   touch_configure_gpio();
   touch_read_xy(1);

   if ((g_stTouchData.raw_x < 0x1000) &&
		   (g_stTouchData.raw_y < 0x1000))
   {
      r7_7 = 0;

      sub_8006618();
      sub_8006624();
   }

   return r7_7;
}


/* 800651c - todo */
void touch_configure_gpio(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();

   // CLK
   GPIO_InitStruct.Pin = GPIO_PIN_12;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   // MOSI
   GPIO_InitStruct.Pin = GPIO_PIN_7;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   // MISO
   GPIO_InitStruct.Pin = GPIO_PIN_6;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   // CS
   GPIO_InitStruct.Pin = GPIO_PIN_7;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   // IRQ
   GPIO_InitStruct.Pin = GPIO_PIN_6;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   touch_toggle_cs_line(1);
   touch_toggle_clk_line(0);
   touch_toggle_mosi_line(0);
}


/* 8006618 - complete */
void sub_8006618(void)
{
   /* empty */
}


/* 8006624 - complete */
void sub_8006624(void)
{
   /* empty */
}


/* 8006630 - todo */
void touch_poll(void)
{
   uint8_t r7_7 = 1;

   if (0 == touch_read_irq())
   {
      r7_7 = 0;
   }
   else
   {
      r7_7 = 1;
   }

   if (r7_7 == 0)
   {
      touch_read_xy(1);
      touch_convert_values();
      if ((0 == touch_detect_move()) && (TouchEvent.bData_0 != 0))
      {
         TouchEvent.bData_0 = 0;
      }
   }
   else if (TouchEvent.bData_0 != 0)
   {
      TouchEvent.bData_0 = 1;
   }
}


/* 8006694 - todo */
void touch_read_xy(uint8_t a)
{
   uint16_t i;
   uint32_t x = 0;
   uint32_t y = 0;
   uint16_t data;

   if (a == 0)
   {
      g_stTouchData.raw_x = touch_spi_transfer(0x900000);
      g_stTouchData.raw_y = touch_spi_transfer(0xd00000);
   }
   else
   {
      touch_spi_transfer(0x900000);

      for (i = 0; i < 4; i++)
      {
         //loc_80066dc
         data = touch_spi_transfer(0x900000);
         x += data;

         data = touch_spi_transfer(0xd00000);
         y += data;
      }

      g_stTouchData.raw_x = x / 4;
      g_stTouchData.raw_y = y / 4;
   }
}


/* 8006730 - todo */
void touch_convert_values(void)
{
   int x; //r7_24;
   int y; //r7_20;
   float r7_1c = (float)(g_stTouchData.raw_x);
   float r7_18 = (float)(g_stTouchData.raw_y);

   float r7_14 = r7_1c * g_stTouchData.Data_12;
   int r7_10 = (int)(r7_14);
   float r7_c = r7_18 * g_stTouchData.Data_16;
   int r7_8 = (int)(r7_c);
   int r7_4 = (int)(g_stTouchData.Data_20);
   x = r7_10 + r7_8 + r7_4;

   r7_14 = r7_1c * g_stTouchData.Data_24;
   r7_10 = (int)(r7_14);
   r7_c = r7_18 * g_stTouchData.Data_28;
   r7_8 = (int)(r7_c);
   r7_4 = (int)(g_stTouchData.Data_32);
   y = r7_10 + r7_8 + r7_4;

   if (x >= 320)
   {
      x = 319;
   }

   if (x < 0)
   {
      x = 0;
   }

   if (y > 239)
   {
      y = 239;
   }

   if (y < 0)
   {
      y = 0;
   }

   g_stTouchData.x = x;
   g_stTouchData.y = y;
}


/* 8006838 - todo */
uint8_t touch_detect_move(void)
{
   uint8_t move = 0;
   uint16_t diff;

   if (g_stTouchData.x >= g_wTouchX)
   {
      diff = g_stTouchData.x - g_wTouchX;
   }
   else
   {
      diff = g_wTouchX - g_stTouchData.x;
   }

   if (diff > 30)
   {
      move = 1;
   }

   if (g_stTouchData.y >= g_wTouchY)
   {
      diff = g_stTouchData.y - g_wTouchY;
   }
   else
   {
      diff = g_wTouchY - g_stTouchData.y;
   }

   if (diff > 30)
   {
      move = 1;
   }

   g_wTouchX = g_stTouchData.x;
   g_wTouchY = g_stTouchData.y;

   if (move == 0)
   {
      TouchEvent.wData_2 = g_stTouchData.x;
      TouchEvent.wData_4 = g_stTouchData.y;
   }

   return move;
}


/* 80068e4 - todo */
void touch_toggle_clk_line(uint8_t a)
{
   if (a == 1)
   {
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
   }
   else
   {
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
   }
}


/* 800691c - todo */
void touch_toggle_cs_line(uint8_t a)
{
   if (a == 1)
   {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
   }
   else
   {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
   }
}


/* 8006950 - todo */
void touch_toggle_mosi_line(uint8_t a)
{
   if (a == 1)
   {
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
   }
   else
   {
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
   }
}


/* 8006984 - todo */
int touch_read_miso_line(void)
{
   return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
}


/* 800699c - todo */
int touch_read_irq(void)
{
   return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
}


/* 80069b4 - todo */
uint16_t touch_spi_transfer(int cmd)
{
   uint16_t i;
   uint32_t mosi_bits = 0x800000;
   uint16_t miso_bits = 0x800;
   uint16_t data = 0;

   touch_spi_delay(100);
   touch_toggle_cs_line(0);
   touch_spi_delay(500);

   for (i = 0; i < 24; i++)
   {
      if ((cmd & mosi_bits) == 0)
      {
         touch_toggle_mosi_line(0);
      }
      else
      {
         touch_toggle_mosi_line(1);
      }

      touch_toggle_clk_line(1);

      if ((i > 8) && (i < 21))
      {
         if (0 != touch_read_miso_line())
         {
            data |= miso_bits;
         }

         miso_bits >>= 1;
      }

      touch_spi_delay(500);
      touch_toggle_clk_line(0);
      touch_spi_delay(500);

      mosi_bits >>= 1;
   }

   touch_spi_delay(500);
   touch_toggle_cs_line(1);
   touch_spi_delay(500);

   return data;
}


/* 8006a70 - todo */
void touch_spi_delay(int a)
{
	while (a-- != 0)
	{
		/* delay */
	}
}


