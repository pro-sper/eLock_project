/**
 * main.c
 */
#include "msp.h"
#include "lcd.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern unsigned char LCD_clr_data[1024];
extern unsigned char LCD_TEXT_ARR[1024];
extern unsigned char LCD_GRAPH_ARR[1024];
uint16_t lineData[128];

void msdelay(int delay)
{
    int i,j;
    for(i=0;i<delay;i++)
        for(j=0;j<16000;j++);
}

int main(void)
{
	/*unsigned char data[] = "Hello World";
	unsigned char data2[] = "How are you?";
	unsigned char data3[] = "Goodbye";*/
	
	i2c0_Init(LCD_ADDR);
	
	LCD_Init();

	LCD_SetCursor(2, 1);
	LCD_SendChar('A');
	// LCD_Print("Hello world!");

	/*LCD_SetCursor(2, 1);
	LCD_Print("LCD Tutorial");*/


	return 0;
}

