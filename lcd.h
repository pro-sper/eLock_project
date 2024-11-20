/*
 * LCD.h
 *
 *  Created on: 04-26-2024
 *      Author: Prosper Omiponle
 *
 */

#include "i2c.h"
#include <stdint.h>

/*******************************************************************
*						FUNCTION PROTOTYPES
*******************************************************************/
void LCD_Init(void);
void LCD_Send_Command(uint8_t cmd);
void LCD_SendChar(char c);
void LCD_Print(const char* str);
void LCD_SetCursor(uint8_t col, uint8_t row);

/*******************************************************************
*							DEFINES
*******************************************************************/

// this is the predefined i2c address for the 1306 LCD display
#define LCD_ADDR            0x27

	// command table
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME	0x02
#define LCD_ETRYMODESET	0x06
#define LCD_DISPLAYCONTROL	0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x28

//#define LCD_DISPLAYOFF 0xAE
//#define LCD_DISPLAYON 0xAF
