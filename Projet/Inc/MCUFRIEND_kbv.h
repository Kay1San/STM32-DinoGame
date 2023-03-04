/*
 * MCUFRIEND_kbv class inherits from Adafruit_GFX class and the Arduino Print class.
 * Any use of MCUFRIEND_kbv class and examples is dependent on Adafruit and Arduino licenses
 * The license texts are in the accompanying license.txt file
 */

#ifndef MCUFRIEND_KBV_H_
#define MCUFRIEND_KBV_H_   298

#include "stdint.h"
#include "stdbool.h"
	void     LCD_Reset(void);                                // you only need the constructor
	void     LCD_Begin(void); 
	void     LCD_DrawPixel(int16_t x, int16_t y, uint16_t color);  // and these three
	void     LCD_WriteCmdData(uint16_t cmd, uint16_t dat);                 // ?public methods !!!
  	void     LCD_PushCommand(uint16_t cmd, uint8_t * block, int8_t N);
	uint16_t LCD_Color565(uint8_t r, uint8_t g, uint8_t b);
	uint16_t LCD_ReadID(void);
	void     LCD_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void     LCD_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void     LCD_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	void     LCD_FillScreen(uint16_t color);
	void     LCD_SetRotation(uint8_t r);
  	void     LCD_InvertDisplay(bool i);

	uint16_t LCD_ReadReg(uint16_t reg, int8_t index);
	int16_t  LCD_ReadGRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h);
	uint16_t LCD_ReadPixel(int16_t x, int16_t y);
	void     LCD_SetAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
	void     LCD_PushColors16(uint16_t *block, int16_t n, bool first);
	void     LCD_PushColors8(uint8_t *block, int16_t n, bool first);
	void     LCD_PushColors(const uint8_t *block, int16_t n, bool first, bool bigend);
  	void     LCD_VertScroll(int16_t top, int16_t scrollines, int16_t offset);
	
	// Extra functions to draw 
	void LCD_SetCursor(unsigned int x, unsigned int y);
	void LCD_SetTextSize(uint8_t s);
	void LCD_SetTextColor(uint16_t c, uint16_t b);
	void LCD_DrawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
	void LCD_Printf(const char *fmt, ...);
	void LCD_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void LCD_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
	void LCD_DrawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
	void LCD_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void LCD_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	
	uint32_t LCD_ReadReg32(uint16_t reg);
	uint32_t LCD_ReadReg40(uint16_t reg);
  
	extern uint16_t _lcd_xor, _lcd_capable;
	extern uint16_t _lcd_ID, _lcd_rev, _lcd_madctl, _lcd_drivOut, _MC, _MP, _MW, _SC, _EC, _SP, _EP;
	
	//JP Patch
  extern int16_t
    WIDTH,          ///< This is the 'raw' display width - never changes
    HEIGHT;         ///< This is the 'raw' display height - never changes
  extern int16_t
    _width,         ///< Display width as modified by current rotation
    _height,        ///< Display height as modified by current rotation
    cursor_x,       ///< x location to start print()ing text
    cursor_y;       ///< y location to start print()ing text
  extern uint16_t
    textcolor,      ///< 16-bit background color for print()
    textbgcolor;    ///< 16-bit text color for print()
  extern uint8_t
    textsize_x,      ///< Desired magnification in X-axis of text to print()
    textsize_y,      ///< Desired magnification in Y-axis of text to print()
    rotation;       ///< Display rotation (0 thru 3)
  extern bool
    wrap,           ///< If set, 'wrap' text at right edge of display
    _cp437;         ///< If set, use correct CP437 charset (default is off)
	
	#define width() _width	
	#define height() _height	
	#define pgm_read_byte(x) (*x)
	#define pgm_read_word(x) (*x)
	//End JP Patch
		

// New color definitions.  thanks to Bodmer
#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFDA0      /* 255, 180,   0 */
#define GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define PINK        0xFC9F

#endif
