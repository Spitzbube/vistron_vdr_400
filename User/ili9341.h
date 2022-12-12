/*
 * ili9341.h
 *
 *  Created on: 22 áåð. 2018 ð.
 *  Author: Andriy Honcharenko
 *  Version 1.1 date: 24.09.2019
 */

#ifndef ILI9341_H_
#define ILI9341_H_


#define LCD_BASE0        		((uint32_t)0x60000000)
#define LCD_BASE1        		((uint32_t)0x60020000)

#define LCD_CmdWrite(command)	*(volatile uint16_t *) (LCD_BASE0) = (command)
#define LCD_DataWrite(data)		*(volatile uint16_t *) (LCD_BASE1) = (data)

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#define ILI9341_PIXEL_WIDTH		240
#define ILI9341_PIXEL_HEIGHT 	320
#define ILI9341_PIXEL_COUNT		ILI9341_PIXEL_WIDTH * ILI9341_PIXEL_HEIGHT

// Any LCD needs to implement these common methods, which allow the low-level
// initialisation and pixel-setting details to be abstracted away from the
// higher level drawing and graphics code.

typedef enum
{
	LCD_ORIENTATION_PORTRAIT 			= 0,
	LCD_ORIENTATION_LANDSCAPE 			= 1,
	LCD_ORIENTATION_PORTRAIT_MIRROR 	= 2,
	LCD_ORIENTATION_LANDSCAPE_MIRROR 	= 3
} lcdOrientationTypeDef;

/**
  * @brief  Draw Properties structures definition
  */
typedef struct
{
   uint32_t TextColor; //0
   uint32_t BackColor; //4
   sFONT* pFont; //8;
   uint8_t TextWrap; //12

} lcdFontPropTypeDef;

typedef struct
{
	unsigned short	x;
	unsigned short	y;
}lcdCursorPosTypeDef;

// This struct is used to indicate the capabilities of different LCDs
typedef struct
{
  uint16_t				width;         // LCD width in pixels (default orientation)
  uint16_t				height;        // LCD height in pixels (default orientation)
#if 0
  lcdOrientationTypeDef	orientation;   // Whether the LCD orientation can be modified
  bool					touchscreen;   // Whether the LCD has a touch screen
  bool					hwscrolling;   // Whether the LCD support HW scrolling
#endif
} lcdPropertiesTypeDef;

#endif /* ILI9341_H_ */
