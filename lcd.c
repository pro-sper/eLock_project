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
    uint8_t init_commands[] = {
        0x33,   // Initialize LCD in 4-bit mode (send twice as per datasheet)
        0x32,   // Set to 4-bit mode
        0x28,   // Function set: 4-bit mode, 2-line, 5x7 matrix
        0x0C,   // Display ON, cursor OFF
        0x06,   // Entry mode set: auto-increment cursor
        0x01,   // Clear display
    };

    int n = sizeof(init_commands) / sizeof(init_commands[0]);
	int i;
    // Loop through and send each command
    for (i = 0; i < n; i++) {
        LCD_SendCommand(init_commands[i]);
        __delay_cycles(2000);
    }
}

void LCD_SendChar(char c) {
    uint8_t data[4];

    // Send high nibble (RS=1 for data register)
    data[0] = (c & 0xF0) | 0x09;        // High nibble with RS=1
    data[1] = data[0] | 0x04;           // Enable high
    data[2] = data[0];

    // Send low nibble (RS=1 for data register)
    data[3] = ((c & 0x0F) << 4) | 0x09; // Low nibble with RS=1

    // Send all bytes via I2C
    i2c0_put(data, 4);
}

void LCD_Print(const char* str) {
    while (*str) {
        LCD_SendChar(*str++);
    }
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0 ? 0x80 : 0xC0) + col;
    LCD_SendCommand(address);
}
