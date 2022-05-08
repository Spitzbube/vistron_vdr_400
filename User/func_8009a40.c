
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
Struct_2000002c_Inner8 Data_20000044 = //20000044 (801943c)
{
   0, //8013404
   11,
   16
};
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
   sub_8001a14(r7_8);
   sub_8001f04(r7, r7_18);

   sub_8001bd8(0x0c, 6, f, h & 4);

   sub_8001cc4(0x8e, 0x2a, g);

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
   char* b = a;
   while (b++) {}
   return b-a-1;
}


/* 8001a14 - todo */
void sub_8001a14(void* a)
{
#if 0
   uint16_t len;

   if (bData_200022a8 != 0)
   {
      ili9341_set_font(&Data_2000004c);
      ili9341_draw_box(0, 63, 320, 24, 0xffff);
      ili9341_set_text_color(0, 0xffff);
      len = sub_800c88c(a, 0x10);
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
#endif
}


/* 8003038 - todo */
void sub_8003038(uint16_t textId, Struct_2000002c_Inner8* font)
{
#if 0
   uint16_t len;

   ili9341_set_font(font);

   ili9341_draw_box(0, 23, 320, 24, 0xffff);

   ili9341_set_text_color(0, 0xffff);

   len = sub_8001224(CurrentTextTable[textId]);

   ili9341_set_cursor(160 - (len * font->width) / 2, 24);

   ili9341_draw_format_string(CurrentTextTable[textId]);
#endif
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
	"Main menu",
	"Up",
	"Down",
	"Delete",
	"Next",
	"Channel list",
	"Settings",
	"Factory reset",
	"Alarm",  //TEXT_ID_ALARM
	"Information",
	"Automatic search",
	"Manual search",
	"Delete channel",
	"Manual search DAB",
	"Manual search FM",
	"Language",
	"Sleep-Timer",
	"Auto-Standby",
	"Continue?",
	"NO",
	"YES",
	"Deutsch",
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


