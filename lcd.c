#include "msp.h"
#include "lcd.h"
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "math.h"

/*
 * lcd.c
 *
 *  Created on: 04-26-2024
 *      Author: Prosper Omiponle
 *
 *   
 */

/*******************************************************************
*						FUNCTION DEFINITIONS
*******************************************************************/

void msdelay(int delay)
{
    int i,j;
    for(i=0;i<delay;i++)
        for(j=0;j<16000;j++);
}

void LCD_SendCommand(uint8_t cmd) {
    uint8_t data[6];

    // High nibble (upper 4 bits of cmd)
    data[0]	= (cmd & 0xF0) | 0x08;		        // High nibble with backlight ON
    data[1] = data[0] | 0x04;					// High nibble + Enable bit ON
    data[2] = data[0];                          // High nibble + Enable bit OFF

    data[3] = ((cmd & 0x0F) << 4) | 0x08;       // Low nibble with backlight ON
    data[4] = data[3] | 0x04;                   // Low nibble + Enable bit ON
    data[5] = data[3];                          // Low nibble + Enable bit OFF

    // Send the command sequence using i2c0_put
    i2c0_put(data, 6);
}

void LCD_Init() {
    // Initialize the LCD by sending a sequence of commands
	
    // 4 bit initialization
    msdelay(50);          // Wait for >40ms
    LCD_SendCommand(0x30);
    msdelay(5);           // Wait for >4.1ms
    LCD_SendCommand(0x30);
    msdelay(1);            // Wait for >100us
    LCD_SendCommand(0x30);
    msdelay(10);      
    LCD_SendCommand(0x20);  // Set to 4-bit mode
    msdelay(10);

    // Display Initialization
    LCD_SendCommand(0x28);   // Function set: 4-bit mode, 2-line, 5x7 matrix
    msdelay(1);
    LCD_SendCommand(0x08);   // Display OFF
    msdelay(1);
    LCD_SendCommand(0x01);   // Clear display
    msdelay(1);
    LCD_SendCommand(0x06);   // Entry mode set: auto-increment cursor
    msdelay(1);
    LCD_SendCommand(0x0C);   // Display ON, cursor OFF
    msdelay(1);
}

void LCD_SendChar(char c) {
    uint8_t data[6];

    // Send high nibble (RS=1 for data register)
    data[0] = (c & 0xF0) | 0x09;        // High nibble with RS=1
    data[1] = data[0] | 0x04;           // Enable high
    data[2] = data[0];                  // Enable low

    // Send low nibble (RS=1 for data register)
    data[3] = ((c & 0x0F) << 4) | 0x09; // Low nibble with RS=1
    data[4] = data[3] | 0x04;           // Enable high
    data[5] = data[3];                  // Enable low
	
    // Send all bytes via I2C
    i2c0_put(data, 6);
}

void LCD_Print(const char* str) {
    while (*str) {
        LCD_SendChar(*str++);
    }
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0 ? 0x80 : 0xC0) | col;
    LCD_SendCommand(address);
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
		msdelay(1);
}
