
#include <string.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "func_8001ae8.h"

extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi2;

extern void Error_Handler(void);
int sub_800b2ac(void* a, void* b);


//_sdata: 20000000 - 200000c8 -> 080193f8 - 80194C0

Func_20000000 Funcs_20000000[] = //20000000 (80193f8)
{
   sub_8004be8, //arrow up
   sub_8004c4c, //arrow down
   sub_8004cb0, //arrow left
   sub_8004d14, //arrow right
   sub_8004d78, //three horizontal lines
   sub_8004e74,
   sub_8004f24,
   sub_8004fc4,
   sub_8005074
};
Screen_Resolution ScreenResolution = //20000024 (801941C)
{
   320, 240
};
//20000028 (8019420)
Text_Attributes TextAttributes = //2000002c (8019424)
{
   0xffe0,
   0,
   &Data_2000003c, //0x2000003c,
   1
};
Struct_2000002c_Inner8 Data_2000003c = //2000003c (8019434)
{
   0, //0x08012f90/TODO*/,
   7,
   12
};
#if 0 //->font2.c
Struct_2000002c_Inner8 Data_20000044 = //20000044 (801943c)
{
   0, //8013404
   11,
   16
};
#endif
#if 0 //->font1.c
Struct_2000002c_Inner8 Data_2000004c = //2000004c (8019444)
{
   0, //8014ec4
   17,
   24
};
#endif
uint8_t bData_20000054 = 1; //20000054 (801944C)
uint8_t bData_20000055 = 0xff; //20000055 (801944D)
uint8_t bData_20000056 = 4; //20000056 (801944E)
uint8_t bData_20000057 = 31; //20000057 (801944F)
//uint32_t SystemCoreClock; //20000058 (8019450)
//uint32_t uwTickPrio; //2000005C (8019454)
//HAL_TickFreqTypeDef uwTickFreq; //20000060 (8019458)
//_impure_ptr; //?? //20000064 (801945C)
//impure_data; //?? //20000068 (8019460 -> 80194C0?)
Struct_200000e4 TextCursor; //200000e4
uint8_t bData_200000e8; //200000e8
uint8_t bData_200000e9; //200000e9
uint8_t bData_200000ea; //200000ea
uint8_t bData_200000eb; //200000eb
char Data_200000ec[256]; //200000ec, size?
uint16_t wData_200001ec; //200001ec
uint16_t wData_200001ee; //200001ee
uint8_t Data_200001f0[100]; //200001f0 size?
Struct_20000a48 Data_20000a48; //20000a48
Struct_20000a4c Data_20000a4c; //20000a4c
Struct_20000a50 Data_20000a50; //20000a50
uint16_t wData_20000a56; //20000a56
uint8_t bData_20000a58; //20000a58
uint8_t bData_20000a59; //20000a59
uint8_t bData_20000a6c; //20000a6c
uint8_t bData_20000a6d; //20000a6d
RTC_TimeTypeDef Data_20000a70; //20000a70
RTC_DateTypeDef Data_20000a74; //20000a74
uint8_t bData_20000b7d; //20000b7d
Struct_20000b90 Data_20000b90; //20000b90
Struct_20000bc0 Data_20000bc0;
char** CurrentTextTable; //20000bc8
char strFMVersion[12]; //20000bcc
char strDABVersion[12]; //20000bd8
uint8_t bData_20000be4; //20000be4
struct_8008d84 Data_20000be8[8]; //20000be8 +224
struct_8008d84 Data_20000cc8[200]; //20000cc8 +5600
uint8_t bData_200022a8; //200022a8
struct_8008d84* Data_200023e0; //200023e0

extern int sub_800bc04(struct_8008d84* a, struct_8008d84* b, void* c, void* d);


/* 800173c - todo */
void sub_800173c(RTC_TimeTypeDef r7_c, void* r7_8, uint8_t r7_7, void* r7, uint8_t r7_18, void* f, int g, uint16_t h)
//new: RTC_TimeTypeDef a, void* b, uint8_t c, void* d, uint8_t e, int f, void* g, uint16_t h
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   draw_channel_name(r7_8);
   sub_8001f04(r7, r7_18);

   draw_channel_number_box(12, 6, f, h & 4);

   draw_signal_strength_bars(142, 42, g);

   sub_8001eb6(r7_7);

   sub_8001ae8(r7_c); //Clock display

   draw_on_off_icon(291, 214); //On-Off icon display (low right corner - red)

   sub_8005198(8, 196, 0x1f, 1); //blue touch area, 1 = black arrow down
   sub_8005198(61, 196, 0x7e0, 0); //x+53 green touch area, 0 = black arrow up
   sub_8005198(114, 196, 0xf800, 2); //red touch area, 2 = black arrow left
   sub_8005198(167, 196, 0xffe0, 3); //yellow touch area, 3 = black arrow right
   sub_8005198(79, 6, 0xfd20, 4); //orange touch area, 4 = three horizontal lines
}


/* 8001224 - todo */
int sub_8001224(char* a)
{
   char* b;
   for (b = a; *b != 0; b++) {}
   return b-a-1;
}


/* 8001a14 - todo */
void draw_channel_name(void* a)
{
   uint16_t len;

   if (bData_200022a8 != 0)
   {
      ili9341_set_font(&Data_2000004c);
      ili9341_draw_box(0, 63, 320, 24, 0xffff);
      ili9341_set_text_color(0, 0xffff);
      len = sub_800c88c(a, 16);
      ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 63);
      ili9341_draw_string(a, len);
   }
   else
   {
      len = sub_8001224(CurrentTextTable[TEXT_ID_NO_CHANNEL]);
      ili9341_set_font(&Data_2000004c);
      ili9341_set_text_color(0, 0xffff);
      ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 63);
      ili9341_draw_format_string(CurrentTextTable[TEXT_ID_NO_CHANNEL]);
   }
}


/* 8002cac - todo */
void sub_8002cac(uint16_t firstTextId, uint8_t lines, uint8_t focus)
{
   uint8_t i;
   uint8_t r7_e = (focus > 5)? focus - 2: 0;
   uint8_t r7_d = (lines < 5)? lines + 1: 5;

   ili9341_set_font(&Data_20000044);
   ili9341_set_text_color(0, 0xffff);

   for (i = 0; (i < r7_d) && ((r7_e + i) < lines); )
   {
      //loc_8002cf4
      if ((r7_e + i) == focus)
      {
         ili9341_set_text_color(0xffff, 0);
      }
      else
      {
         ili9341_set_text_color(0, 0xffff);
      }

      ili9341_set_cursor(0, 72 + 24 * i);
      ili9341_draw_format_string(CurrentTextTable[firstTextId + i]);
      i++;
   }
}


/* 8002d70 - todo */
void sub_8002d70(uint16_t textId, uint16_t r7_4, uint8_t r7_3, uint8_t r7_2)
{
   ili9341_fill_screen(0xffff);
   ili9341_draw_hor_line(0, 320, 48, 0);
   ili9341_draw_hor_line(0, 320, 192, 0);
   sub_8003038(textId, &Data_2000004c);
   sub_8002cac(r7_4, r7_3, r7_2);
   sub_8005198(8, 196, 0x1f, 1); //blue box / down arrow
   sub_8005198(61, 196, 0x7e0, 0); // green box / up arrow
   sub_8005198(167, 196, 0xffe0, 6); //yellow box
   sub_8005198(273, 196, 0xffff, 7); //white box / back arrow
}


/* 8002e98 - todo */
uint8_t sub_8002e98(uint16_t a, uint16_t b)
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

   if ((a > 166) && (a < 204) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(167, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(167, 196, 0xffe0, 6);
      return 4;
   }

   if ((a > 272) && (a < 311) && (b > 195) && (b < 233))
   {
      ili9341_draw_box(273, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(273, 196, 0xffff, 7);
      return 5;
   }

   if ((a < 320) && (b > 71) && (b < 97))
   {
      return 25;
   }

   if ((a < 320) && (b > 95) && (b < 121))
   {
      return 26;
   }

   if ((a < 320) && (b > 119) && (b < 145))
   {
      return 27;
   }

   if ((a < 320) && (b > 143) && (b < 169))
   {
      return 28;
   }

   if ((a < 320) && (b > 167) && (b < 193))
   {
      return 29;
   }

   return 0;
}


/* 8003038 - todo */
void sub_8003038(uint16_t textId, Struct_2000002c_Inner8* font)
{
   uint16_t len;

   ili9341_set_font(font);
   ili9341_draw_box(0, 23, 320, 24, 0xffff);
   ili9341_set_text_color(0, 0xffff);
   len = sub_8001224(CurrentTextTable[textId]);
   ili9341_set_cursor(160 - (len * font->width) / 2, 24);
   ili9341_draw_format_string(CurrentTextTable[textId]);
}


/* 8004560 - todo */
void draw_on_off_icon(uint16_t a, uint16_t b)
{
   ili9341_draw_box(a - 16, b - 11, 32, 40, 0xffff);
   ili9341_draw_circle(a, b, 13, 0xf800);
   ili9341_draw_circle(a, b, 9, 0xffff);
   ili9341_draw_box(a - 4, b - 20, 9, 16, 0xffff);
   ili9341_draw_box(a - 1, b - 15, 3, 12, 0xf800);
}


/* 80045f8 - todo */
void sub_80045f8(RTC_TimeTypeDef r7_c, RTC_DateTypeDef r7_8, Struct_20000a4c* r7_4, uint8_t r7_3)
{
   HAL_GPIO_WritePin(GPIOA/*todo*/, GPIO_PIN_5, GPIO_PIN_SET);

   ili9341_fill_screen(0);
   ili9341_draw_hor_line(0, 320, 48, 0xffff);
   ili9341_draw_hor_line(0, 320, 192, 0xffff);
   sub_8001b60(r7_c);
   sub_800465c(r7_8);

   if (r7_3 != 0)
   {
	   sub_80046d8(r7_4);
   }
}


/* 800465c - todo */
void sub_800465c(RTC_DateTypeDef a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%d.%d.%d", a.Date, a.Month, a.Year + 2000);

   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0xffff, 0);

   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 72);
   ili9341_draw_string(buf, len);
}


/* 80046d8 - todo */
void sub_80046d8(Struct_20000a4c* a)
{
   char buf[10];
   uint8_t len = 0;

   len = sprintf(buf, "%s %d:%02d", CurrentTextTable[TEXT_ID_ALARM], a->a, a->b);

   ili9341_draw_box(0, 120, 320, 23, 0);
   ili9341_set_font(&Data_2000004c);
   ili9341_set_text_color(0xffff, 0);
   ili9341_set_cursor(160 - (len * Data_2000004c.width) / 2, 120);
   ili9341_draw_string(buf, len);
}


/* 8004be8 - todo */
void sub_8004be8(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
   sub_8005af0(a - 9, b + 9, a + 9, b + 9, a, b - 9, c);
}


/* 8004c4c - todo */
void sub_8004c4c(uint16_t a, uint16_t b, int c, uint16_t d)
{
   sub_8005af0(a - 9, b - 9, a + 9, b - 9, a, b + 9, c);
}


/* 8004cb0 - todo */
void sub_8004cb0(uint16_t a, uint16_t b, int c, uint16_t d)
{
   sub_8005af0(a - 9, b, a + 9, b - 9, a + 9, b + 9, c);
}


/* 8004d14 - todo */
void sub_8004d14(uint16_t a, uint16_t b, int c, uint16_t d)
{
   sub_8005af0(a - 9, b - 9, a - 9, b + 9, a + 9, b, c);
}


/* 8004d78 - todo */
void sub_8004d78(uint16_t r7_6, uint16_t r7_4, uint16_t color, uint16_t d)
{
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 9, color); //      *--------+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 10, color); //    *---------+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 8, color); //       *-------+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4, color); //                   *
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 1, color); //              *+
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 1, color); //               +*
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 9, color); //               +--------*
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 8, color); //               +-------*
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 10, color); //              +---------*
}


/* 8004e74 - todo */
void sub_8004e74(uint16_t r7_6, uint16_t r7_4, int r7_2, uint16_t r7)
{
   uint16_t r7_e;
   char r7_8[] = "FAV"; //0x564146;

   ili9341_set_text_color(r7_2, r7);
   ili9341_set_font(&Data_20000044);
   r7_e = sub_8001224(r7_8);
   ili9341_set_cursor(r7_6 - (r7_e * Data_20000044.width) / 2/*??*/, r7_4 - Data_20000044.height / 2);
   ili9341_draw_string(r7_8, r7_e);
   ili9341_draw_box(r7_6 + 18, r7_4 - 18, 4, 36, 0xffff);
}


void sub_8004f24(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


/* 8004fc4 - todo */
void sub_8004fc4(uint16_t r7_6, uint16_t r7_4, int r7_2, uint16_t r7)
{
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 + 9, r7_2);
   ili9341_draw_vert_line(r7_6 + 9, r7_4 - 9, r7_4 + 9, r7_2);
   ili9341_draw_hor_line(r7_6 - 9, r7_6 + 9, r7_4 - 9, r7_2);
   sub_8005af0(r7_6 - 9, r7_4 - 9, r7_6 - 5, r7_4 - 11, r7_6 - 5, r7_4 - 7, r7_2);
}


void sub_8005074(uint16_t a, uint16_t b, int c, uint16_t d)
{

}


/* 8005198 - todo */
void sub_8005198(uint16_t x, uint16_t y, uint16_t color, uint8_t r7_1)
{
   ili9341_draw_box(x, y, 36, 36, color);

   (Funcs_20000000)[r7_1](x + 18, y + 18, 0, color);

   ili9341_draw_rect(x, y, 36, 36, 0);
}

char* EnglishTextTable[] = //8012dc0
{
	"CHAN.UP",
	"CHAN.DOWN",
	"VOL.UP",
	"VOL.DOWN",
	"MUX.UP",
	"MUX.DOWN",
	"No new channel found!",
	"No signal!",
	"No channel", //TEXT_ID_NO_CHANNEL
	"FAV-list full!",
	"OK",
	"Exit",
	"Menu",
	"Main menu", //TEXT_ID_MAIN_MENU
	"Up",
	"Down",
	"Delete",
	"Next",
	"Channel list", //TEXT_ID_CHANNEL_LIST
	"Settings", //TEXT_ID_SETTINGS
	"Factory reset",
	"Alarm",  //TEXT_ID_ALARM
	"Information",
	"Automatic search", //TEXT_ID_AUTOMATIC_SEARCH
	"Manual search",
	"Delete channel",
	"Manual search DAB",
	"Manual search FM",
	"Language", //TEXT_ID_LANGUAGE
	"Sleep-Timer",
	"Auto-Standby",
	"Continue?",
	"NO",
	"YES",
	"Deutsch", //TEXT_ID_GERMAN
	"English",
	"Volume",
	"Off",
	"On",
	"Signal information",
	"Channel:",
	"Multiplex:",
	"Frequency:",
	"Level:",
	"SNR:",
	"Error rate:",
	"Multipath:",
	"Freq.offset:",
	"Audio information",
	"Data rate:",
	"Sampl.frequency:",
	"Audio mode:",
	"Stereo separation:",
	"Product:",
	"Hardware:",
	"Software:",
	"DAB Firmware:",
	"FM Firmware:",
};

char* GermanTextTable[] = //8012ea8
{
	"KAN.OBEN",
	"KAN.NIEDER",
	"LAUT.OBEN",
	"LAUT.NIEDER",
	"MUX.OBEN",
	"MUX.NIEDER",
	"Kein neuer Sender gefunden",
	"Kein Signal!",
	"Kein Sender",
	"FAV-Liste voll!",
	"OK",
	"Zurück",
	"Menü",
	"Hauptmenü",
	"Ab",
	"Auf",
	"Löschen",
	"N.hste",
	"Senderliste",
	"Einstellungen",
	"Werkzustand",
	"Wecker",
	"Information",
	"Automatische Suche",
	"Manuelle Suche",
	"Sender löschen",
	"Manuelle Suche DAB",
	"Manuelle Suche FM",
	"Sprache",
	"Sleep-Timer",
	"Autom. Abschaltung",
	"Weiter?",
	"NEIN",
	"JA",
	"Deutsch",
	"English",
	"Lautstärke",
	"Aus",
	"Ein",
	"Empfang",
	"Sendername:",
	"Multiplex:",
	"Frequenz:",
	"Pegel:",
	"SNR:",
	"Fehlerrate:",
	"Mehrweg:",
	"Frek.offset:",
	"Audio Information",
	"Datenrate:",
	"Abtastfreq.:",
	"Audio Modus:",
	"Stereo Tren:",
	"Produkt:",
	"Hardware:",
	"Software:",
	"DAB Firmware:",
	"FM Firmware:",
};

/* 8005204 - todo */
void sub_8005204(uint8_t a)
{
   if (a == 1)
   {
      CurrentTextTable = EnglishTextTable;
   }
   else
   {
      CurrentTextTable = GermanTextTable;
   }
}


/* 8006254 - todo */
uint8_t sub_8006254(uint8_t r7_7, uint8_t r7_6, uint8_t r7_5, uint8_t r7_4, uint8_t r7_18, uint8_t r7_1c)
{
   uint8_t r7_f = 0;

   if (r7_1c != 0)
   {
      r7_f |= 0x04;
   }

   if (r7_18 != 0)
   {
      r7_f |= 0x08;
   }

   if (r7_4 != 0)
   {
      r7_f |= 0x10;
   }

   if (r7_5 != 0)
   {
      r7_f |= 0x20;
   }

   if (r7_6 != 0)
   {
      r7_f |= 0x40;
   }

   if (r7_7 != 0)
   {
      r7_f |= 0x80;
   }

   return r7_f;
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


/* 8006434 - todo */
int touch_init(void)
{
   uint8_t r7_7 = 1;

   Data_20000bc0.bData_0 = 1;
   Data_20000bc0.wData_2 = 0;
   Data_20000bc0.wData_4 = 0;

   Data_20000b90.Data_0 = 0;
   Data_20000b90.wData_4 = 0x8000;
   Data_20000b90.wData_6 = 0x8000;
   Data_20000b90.wData_8 = 0;
   Data_20000b90.wData_10 = 0;
   Data_20000b90.Data_12 = 0x3db50005;
   Data_20000b90.Data_16 = 0x3ada36b7;
   Data_20000b90.Data_20 = 0xc1f9d490;
   Data_20000b90.Data_24 = 0xba638759;
   Data_20000b90.Data_28 = 0xbd878821;
   Data_20000b90.Data_32 = 0x437f9706;
   Data_20000b90.wData_36 = 0x869;
   Data_20000b90.wData_38 = 0x23a;
   Data_20000b90.wData_40 = 0x2a5;
   Data_20000b90.wData_42 = 0x7f8;
   Data_20000b90.wData_44 = 0xddb;
   Data_20000b90.wData_46 = 0xd7d;

   touch_configure_gpio();
   touch_read_xy(1);

   if ((Data_20000b90.wData_4 < 0x1000) &&
		   (Data_20000b90.wData_6 < 0x1000))
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
      sub_8006730();
      if ((0 == sub_8006838()) && (Data_20000bc0.bData_0 != 0))
      {
         Data_20000bc0.bData_0 = 0;
      }
   }
   else if (Data_20000bc0.bData_0 != 0)
   {
      Data_20000bc0.bData_0 = 1;
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
      Data_20000b90.wData_4 = touch_spi_transfer(0x900000);
      Data_20000b90.wData_6 = touch_spi_transfer(0xd00000);
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

      Data_20000b90.wData_4 = x / 4;
      Data_20000b90.wData_6 = y / 4;
   }
}


/* 8006730 - todo */
void sub_8006730(void)
{
   int r7_24;
   int r7_20;
   int r7_1c = sub_80013a0(Data_20000b90.wData_4);
   int r7_18 = sub_80013a0(Data_20000b90.wData_6);
   int r7_14 = sub_8001450(r7_1c, Data_20000b90.Data_12);
   int r7_10 = sub_80016f0(r7_14);
   int r7_c = sub_8001450(r7_18, Data_20000b90.Data_16);
   int r7_8 = sub_80016f0(r7_c);
   int r7_4 = sub_80016f0(Data_20000b90.Data_20);
   r7_24 = r7_10 + r7_8 + r7_4;

   r7_14 = sub_8001450(r7_1c, Data_20000b90.Data_24);
   r7_10 = sub_80016f0(r7_14);
   r7_c = sub_8001450(r7_18, Data_20000b90.Data_28);
   r7_8 = sub_80016f0(r7_c);
   r7_4 = sub_80016f0(Data_20000b90.Data_32);
   r7_20 = r7_10 + r7_8 + r7_4;

   if (r7_24 >= 320)
   {
      r7_24 = 319;
   }

   if (r7_24 < 0)
   {
      r7_24 = 0;
   }

   if (r7_20 > 239)
   {
      r7_20 = 239;
   }

   if (r7_20 < 0)
   {
      r7_20 = 0;
   }

   Data_20000b90.wData_8 = r7_24;
   Data_20000b90.wData_10 = r7_20;
}


/* 8006838 - todo */
uint8_t sub_8006838(void)
{
   uint8_t r7_7 = 0;
   uint16_t r7_4;

   if (Data_20000b90.wData_8 >= wData_200001ec)
   {
      r7_4 = Data_20000b90.wData_8 - wData_200001ec;
   }
   else
   {
      r7_4 = wData_200001ec - Data_20000b90.wData_8;
   }

   if (r7_4 > 30)
   {
      r7_7 = 1;
   }

   if (Data_20000b90.wData_10 >= wData_200001ee)
   {
      r7_4 = Data_20000b90.wData_10 - wData_200001ee;
   }
   else
   {
      r7_4 = wData_200001ee - Data_20000b90.wData_10;
   }

   if (r7_4 > 30)
   {
      r7_7 = 1;
   }

   wData_200001ec = Data_20000b90.wData_8;
   wData_200001ee = Data_20000b90.wData_10;

   if (r7_7 == 0)
   {
      Data_20000bc0.wData_2 = Data_20000b90.wData_8;
      Data_20000bc0.wData_4 = Data_20000b90.wData_10;
   }

   return r7_7;
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

   sub_8006a70(100);
   touch_toggle_cs_line(0);
   sub_8006a70(500);

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

      sub_8006a70(500);
      touch_toggle_clk_line(0);
      sub_8006a70(500);

      mosi_bits >>= 1;
   }

   sub_8006a70(500);
   touch_toggle_cs_line(1);
   sub_8006a70(500);

   return data;
}


/* 8006a70 - todo */
void sub_8006a70(int a)
{
	while (a-- != 0)
	{
		/* delay */
	}
}


/* 8006d40 - todo */
int menu_channel_list(void)
{
   typedef int (*funcs)(void);
   funcs r7_4[] = //8012c68
   {
	  menu_automatic_search, //Automatic search
	  sub_8007415, //Manual search
	  sub_80075e9 //Delete channel
   };
   uint8_t r7_17 = 0;
   uint8_t r7_16 = 1;
   uint8_t itemSelected = 0;
   uint8_t itemIndex = 0;
   uint8_t oldItem = 0;
   uint8_t r7_12;
   uint8_t r7_11;

   sub_8002d70(TEXT_ID_CHANNEL_LIST, TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;
   //->loc_8006f00
   while (r7_16 != 0)
   {
      //loc_8006d7e
      r7_12 = 0;
      if (Data_20000a48.bData_0 == 0)
      {
         r7_12 = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_8006d96
      r7_11 = 0;
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_11 = sub_8002e98(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_8006db6
      if ((r7_11 | r7_12) != 0)
      {
         switch (r7_11 | r7_12)
         {
            case 3:
               //0x08006e41
               itemIndex++;
               if (itemIndex == TEXT_ID_CHANNEL_LIST_ITEMS) itemIndex = 0;
               break;

            case 2:
               //0x08006e53
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = 2;
               break;

            case 4:
               //0x08006e65
               itemSelected = 1;
               break;

            case 5:
               //0x08006e6b
               r7_16 = 0;
               break;

            case 25:
               //0x08006e71
               itemIndex = 0;
               itemSelected = 1;
               break;

            case 26:
               //0x08006e7b
               itemIndex = 1;
               itemSelected = 1;
               break;

            case 27:
               //0x08006e85
               itemIndex = 2;
               itemSelected = 1;
               break;

            default:
               //0x08006e8f
               break;
         }
      }
      //loc_8006ea4
      if (itemSelected != 0)
      {
         itemSelected = 0;

         if (0 != r7_4[itemIndex]())
         {
            wData_20000a56 |= 0x02;
            r7_16 = 0;
            r7_17 = 1;
         }
         else
         {
            //loc_8006edc
            Data_20000bc0.bData_0 = 1;
            Data_20000a48.bData_0 = 1;

            sub_8002d70(TEXT_ID_CHANNEL_LIST, TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);
         }
      }
      //loc_8006ee8
      if (itemIndex != oldItem)
      {
         oldItem = itemIndex;

         sub_8002cac(TEXT_ID_CHANNEL_LIST_FIRST, TEXT_ID_CHANNEL_LIST_ITEMS, itemIndex);
      }
   }

   return r7_17;
}


/* 8006b3c - todo */
void menu_main(void)
{
   typedef int (*funcs)(void);
   funcs r7_4[] = //8012c54
   {
      menu_channel_list, //Channel list
	  menu_settings, //Settings
	  sub_80088cc, //Factory reset
	  sub_8007114, //Alarm
	  sub_80073c0 //Information
   };
   uint8_t r7_1f = 1;
   uint8_t itemSelected = 0;
   uint8_t itemIndex = 0;
   uint8_t oldItem = 0;
   uint8_t r7_1b;
   uint8_t r7_1a;

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;

   sub_8002d70(TEXT_ID_MAIN_MENU, TEXT_ID_MAIN_MENU_FIRST, TEXT_ID_MAIN_MENU_ITEMS, itemIndex);
   //->loc_8006d20
   while (r7_1f != 0)
   {
      //loc_8006b7a
      r7_1b = 0;
      if (Data_20000a48.bData_0 == 0)
      {
         r7_1b = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_8006b92
      r7_1a = 0;
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_1a = sub_8002e98(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_8006bb2
      if ((r7_1a | r7_1b) != 0)
      {
         switch (r7_1a | r7_1b)
         {
            case 3:
               //0x08006c45: blue
               itemIndex++;
               if (itemIndex == TEXT_ID_MAIN_MENU_ITEMS) itemIndex = 0;
               //->8006CAA
               break;

            case 2:
               //0x08006c57: green
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = TEXT_ID_MAIN_MENU_ITEMS - 1;
               //->8006CAE
               break;

            case 4:
               //0x08006c69: yellow
               itemSelected = 1;
               //->8006CB0
               break;

            case 5:
               //0x08006c6f: white (back)
               r7_1f = 0;
               //->8006CB0
               break;

            case 25:
               //0x08006c75
               itemIndex = 0;
               itemSelected = 1;
               break;

            case 26:
               //0x08006c7f
               itemIndex = 1;
               itemSelected = 1;
               break;

            case 27:
               //0x08006c89
               itemIndex = 2;
               itemSelected = 1;
               break;

            case 28:
               //0x08006c93
               itemIndex = 3;
               itemSelected = 1;
               break;

            case 29:
               //0x08006c9d
               itemIndex = 4;
               itemSelected = 1;
               break;

            default:
               //0x08006ca7
               //->loc_8006cb0
               break;
         }
         //loc_8006cb0
         Data_20000bc0.bData_0 = 1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_8006cbc
      if (itemSelected != 0)
      {
         itemSelected = 0;

         if (0 != r7_4[itemIndex]())
         {
            wData_20000a56 |= 0x02;
            r7_1f = 0;
         }
         else
         {
            //loc_8006cf0
            Data_20000bc0.bData_0 = 1;
            Data_20000a48.bData_0 = 1;

            sub_8002d70(TEXT_ID_MAIN_MENU, TEXT_ID_MAIN_MENU_FIRST, TEXT_ID_MAIN_MENU_ITEMS, itemIndex);
         }
      }
      //loc_8006d08
      if (itemIndex != oldItem)
      {
         oldItem = itemIndex;

         sub_8002cac(TEXT_ID_MAIN_MENU_FIRST, TEXT_ID_MAIN_MENU_ITEMS, itemIndex);
      }
      //loc_8006d20
   }
}


/* 8006f24 - todo */
int menu_settings(void)
{
   typedef int (*funcs)(void);
   funcs r7_4[] = //8012c74
   {
	  menu_language, //Language
	  sub_8008200, //Sleep-Timer
	  sub_800837c, //Auto-Standby
   };
   uint8_t r7_17 = 0;
   uint8_t r7_16 = 1;
   uint8_t itemSelected = 0;
   uint8_t itemIndex = 0;
   uint8_t oldItem = 0;
   uint8_t r7_12;
   uint8_t r7_11;

   sub_8002d70(TEXT_ID_SETTINGS, TEXT_ID_SETTINGS_FIRST, TEXT_ID_SETTINGS_ITEMS, itemIndex);

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;
   //->loc_80070f0
   while (r7_16 != 0)
   {
      //loc_8006f62
	  r7_12 = 0;
	  if (Data_20000a48.bData_0 == 0)
	  {
         r7_12 = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
	  }

	  r7_11 = 0;
	  if (Data_20000bc0.bData_0 == 0)
	  {
         r7_11 = sub_8002e98(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
	  }

	  if ((r7_11 | r7_12) != 0)
	  {
         switch (r7_11 | r7_12)
         {
            case 3:
               //0x08007025
               itemIndex++;
               if (itemIndex == 3) itemIndex = 0;
               break;

            case 2:
               //0x08007037
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = 2;
               break;

            case 4:
               //0x08007049
               itemSelected = 1;
               break;

            case 5:
               //0x0800704f
               r7_16 = 0;
               break;

            case 25:
               //0x08007055
               itemIndex = 0;
               itemSelected = 1;
               break;

            case 26:
               //0x0800705f
               itemIndex = 1;
               itemSelected = 1;
               break;

            case 27:
               //0x08007069
               itemIndex = 2;
               itemSelected = 1;
               break;

            default:
               //0x08007073
               //->loc_800707c
               break;
         }
         //loc_800707c
         Data_20000bc0.bData_0 = 1;
         Data_20000a48.bData_0 = 1;
	  }
	  //loc_8007088
	  if (itemSelected != 0)
	  {
         itemSelected = 0;

         if (0 != r7_4[itemIndex]())
         {
            wData_20000a56 |= 0x02;
            r7_16 = 0;
            r7_17 = 1;
         }
         else
         {
            //loc_80070c0
            sub_8002d70(TEXT_ID_SETTINGS, TEXT_ID_SETTINGS_FIRST, TEXT_ID_SETTINGS_ITEMS, itemIndex);

            Data_20000bc0.bData_0 = 1;
            Data_20000a48.bData_0 = 1;
         }
	  }
	  //loc_80070d8
	  if (itemIndex != oldItem)
	  {
         oldItem = itemIndex;

         sub_8002cac(TEXT_ID_SETTINGS_FIRST, TEXT_ID_SETTINGS_ITEMS, itemIndex);
	  }
	  //loc_80070f0
   }

   return r7_17;
}


/* 8007114 - todo */
int sub_8007114(void)
{

}


/* 80073c0 - todo */
int sub_80073c0(void)
{

}


/* 8007415 - todo */
int sub_8007415(void)
{

}


/* 80075e9 - todo */
int sub_80075e9(void)
{

}


/* 8008030 - todo */
int menu_language(void)
{
   uint8_t r7_7 = 1;
   uint8_t itemIndex = Data_20000a50.b2;
   uint8_t oldItem = Data_20000a50.b2;
   uint8_t r7_4;
   uint8_t r7_3;
   uint8_t r7_2 = Data_20000a50.b2;

   sub_8002d70(TEXT_ID_LANGUAGE, TEXT_ID_LANGUAGE_FIRST, TEXT_ID_LANGUAGE_ITEMS, itemIndex);

   Data_20000bc0.bData_0 = 1;
   Data_20000a48.bData_0 = 1;
   //->loc_80081d4
   while (r7_7 != 0)
   {
      //loc_8008078
      r7_4 = 0;
      if (Data_20000a48.bData_0 == 0)
      {
         r7_4 = Data_20000a48.bData_1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_8008090
      r7_3 = 0;
      if (Data_20000bc0.bData_0 == 0)
      {
         r7_3 = sub_8002e98(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
      }
      //loc_80080b0
      if ((r7_3 | r7_4) != 0)
      {
         switch (r7_3 | r7_4)
         {
            case 2:
               //0x08008135
               itemIndex++;
               if (itemIndex == 2) itemIndex = 0;
               break;

            case 3:
               //0x08008147
               itemIndex--;
               if (itemIndex == 0xff) itemIndex = 1;
               break;

            case 4:
               //0x08008159
               r7_3 = itemIndex + 25;
               //break; //fall through

            case 25:
            case 26:
               //0x0800815f
               if (r7_2 != (r7_3 - 25))
               {
                  Data_20000a50.b2 = (r7_3 - 25) & 1;
                  sub_8005204(Data_20000a50.b2);
                  sub_800ba74(Data_20000cc8, Data_20000be8, &Data_20000a4c, &Data_20000a50);
               }
               //800819A
               r7_7 = 0;
               break;

            case 5:
               //0x080081a1
               r7_7 = 0;
               break;

            default:
               //0x080081a7
               //->loc_80081b0
               break;
         }
         //loc_80081b0
         Data_20000bc0.bData_0 = 1;
         Data_20000a48.bData_0 = 1;
      }
      //loc_80081bc
      if (itemIndex != oldItem)
      {
         oldItem = itemIndex;

         sub_8002cac(TEXT_ID_LANGUAGE_FIRST, TEXT_ID_LANGUAGE_ITEMS, itemIndex);
      }
      //loc_80081d4
   }

   return 0;
}


/* 8008200 - todo */
int sub_8008200(void)
{

}


/* 800837c - todo */
int sub_800837c(void)
{

}


/* 80088cc - todo */
int sub_80088cc(void)
{

}


/* 800b494 - todo */
int sub_800b494(struct_8008d84* r7_4)
{
   uint8_t r7_f = 0xff;
   uint8_t r7_e = 0;

   for (; r7_e < bData_200022a8; r7_e++)
   {
      //loc_800b4a6
      if (0 == memcmp(&Data_20000cc8[r7_e], r7_4, sizeof(struct_8008d84)))
      {
         r7_f = r7_e;
         break;
      }
   }

   return r7_f;
}


/* 800b53c - todo */
int sub_800b53c(uint8_t r7_7)
{
   uint8_t r7_f;
   uint8_t r7_e = 0;

   if (r7_7 < 8)
   {
      for (r7_f = r7_7; r7_f < 7; r7_f++)
      {
         memcpy(&Data_20000be8[r7_f], &Data_20000be8[r7_f + 1], sizeof(struct_8008d84));
      }

      memset(&Data_20000be8[7], 0xff, sizeof(struct_8008d84));

      bData_20000be4++;
   }

   return r7_e;
}


/* 800c33c - todo */
int menu_automatic_search(void)
{
   uint8_t r7_17;
   uint8_t r7_16;
   uint8_t r7_15 = 1;
   uint8_t r7_14 = 0;
   struct
   {
	   int fill[4];
   } r7_4;

   r7_17 = 0;
   r7_16 = 0;

   Data_20000bc0.bData_0 = 1;

   sub_800b5e0();

   sub_80028f2(Data_20000cc8, 0, bData_200022a8, 0, 0x29, &r7_4, 0);

   si46xx_mute(1);

   si46xx_start_dab(bData_20000057);

   if (0 != si46xx_dab_search(&r7_14))
   {
      r7_16 &= ~1;
   }
   else
   {
      //loc_800c3a0
      r7_16 |= 1;
      r7_17 += r7_14;
   }
   //loc_800c3b0
   sub_80028f2(Data_20000cc8, 0, bData_200022a8, 0, 0x7f8, &r7_4, 0x222e);

   si46xx_start_fm(bData_20000057);

   si46xx_mute(1);

   if (0 != si46xx_fm_search(&r7_14))
   {
      r7_16 &= ~2;
   }
   else
   {
      //loc_800c3f8
      r7_16 |= 2;
      r7_17 += r7_14;
   }
   //loc_800c408
   si46xx_mute(0);

   if (r7_16 != 0)
   {
      sub_800c460();
      sub_800ba74(Data_20000cc8, Data_20000be8, &Data_20000a4c, &Data_20000a50);
   }
   else
   {
      //loc_800c426
      sub_800b2ac(&Data_20000a4c, &Data_20000a50);
   }
   //loc_800c42e
   bData_20000a58 = 0;

   return r7_15;
}


/* 800c460 - todo */
void sub_800c460(void)
{
   uint8_t r7_7 = 0;
   uint8_t r7_6 = bData_20000be4;

   for (r7_7 = 0; r7_7 < r7_6; r7_7++)
   {
      if (0xff == sub_800b494(&Data_20000be8[r7_7]))
      {
         sub_800b53c(r7_7);
      }
   }
}






