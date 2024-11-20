/*
 * LCD.h
 *
  *  Created on: 04-26-2024
 *      Author: Prosper Omiponle
 *
 */
#include "msp.h"
#ifndef OLED_H_
#define OLED_H_

// this is the predefined i2c address for the 1306 LCD display
#define LCD_ADDR            0x27

#define LCD_DISPLAYON       0x04
#define LCD_DISPLAYOFF      0x00
#define LCD_BACKLIGHT   		0x08
#define LCD_NOBACKLIGHT   	0x00
#define LCD_MULTIPLEX_RATIO 0xA8

// registers
#define LCD_CONTROL_REG     0x00  // Co = 0, DC = 0
#define LCD_DATA_REG        0x40

// SSD1306 PARAMETERS
#define LCD_LCDWIDTH 128
#define LCD_LCDHEIGHT 64
#define LCD_MAXROWS 7
#define LCD_MAXCONTRAST 0xFF

	// command table
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME	0x02
#define LCD_ETRYMODESET	0x04
#define LCD_DISPLAYCONTROL	0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20 
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80
//#define LCD_DISPLAYOFF 0xAE
//#define LCD_DISPLAYON 0xAF

	// scrolling commands
#define LCD_SCROLL_RIGHT 0x26
#define LCD_SCROLL_LEFT 0X27
#define LCD_SCROLL_VERT_RIGHT 0x29
#define LCD_SCROLL_VERT_LEFT 0x2A
#define LCD_SET_VERTICAL 0xA3

	// address setting
#define LCD_SETLOWCOLUMN 0x00
#define LCD_SETHIGHCOLUMN 0x10
#define LCD_MEMORYMODE 0x20
#define LCD_COLUMNADDRESS 0x21
#define LCD_COLUMNADDRESS_MSB 0x00
#define LCD_COLUMNADDRESS_LSB 0x7F
#define LCD_PAGEADDRESS	0x22
#define LCD_PAGE_START_ADDRESS 0xB0

	// hardware configuration
#define LCD_SETSTARTLINE 0x40
#define LCD_SEGREMAP 0xA1
#define LCD_SETMULTIPLEX 0xA8
#define LCD_COMSCANINC 0xC0
#define LCD_COMSCANDEC 0xC8
#define LCD_SETDISPLAYOFFSET 0xD3
#define LCD_SETCOMPINS 0xDA

	// timing and driving
#define LCD_SETDISPLAYCLOCKDIV 0xD5
#define LCD_SETPRECHARGE 0xD9
#define LCD_SETVCOMDETECT 0xDB
#define LCD_NOP 0xE3

	// power supply configuration
#define LCD_CHARGEPUMP 0x8D
#define LCD_EXTERNALVCC 0x10
#define LCD_SWITCHCAPVCC 0x20

// #PO_added:
// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

extern void LCD_sendCommand(unsigned char);
extern void LCD_sendData(unsigned char*);
extern void LCD_write_display(unsigned char *data);
extern void LCD_Init(void);
extern void LCD_Print(int row, int col, char *text);
extern void LCD_draw(int x, int y, unsigned char ascii);
extern void LCD_PrintLine(char *str);
//************************logo_array****************************/
extern void LCD_display_logos(int x, int y, unsigned char ascii_index);

extern void LCD_draw_line(int x ,int y,unsigned char ascii_str[16]);


/* Set Entire Display OFF */
extern void LCD_display_off(void);
/* Set Entire Display ON */
extern void LCD_display_on(void);
/* Clear display */
extern void LCD_display_clear(void);
extern void LCD_DisplayCameraData(uint16_t line[]);

#endif /* LCD_H_ */
