#include <inttypes.h>

#define RGB565(r, b, g ) ((((r)&0x1F)<<11)|(((g)&0x3F)<<5)|((b)&0x1F))

#define WHITE		0xFFFF
#define BLACK 	0x0000
#define RED			RGB565(31,0,0)
#define	GREEN		RGB565(0,63,0)
#define BLUE		RGB565(0,0,31)
#define GREY		RGB565(16,32,16)

//uint16_t RGB565(uint16_t r, uint16_t b, uint16_t g );
//void LCD_WriteReg( uint16_t cmd, uint16_t data );

void LCD_Init(void);
void LCD_SetCursor( uint16_t x, uint16_t y );
void LCD_DrawPixel( uint16_t color );
void LCD_ClearDisplay(uint16_t color);

void LCD_WriteLetter( uint16_t x, uint16_t y, uint16_t colForeground, uint16_t colBackground, char letter );
void LCD_WriteString( uint16_t x, uint16_t y, uint16_t colForeground, uint16_t colBackground, char * text );

void LCD_Output16BitWord(uint16_t data);


