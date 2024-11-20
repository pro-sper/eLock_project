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
	int i;
	int delta;
	
	unsigned char data[] = "Hello World";
	unsigned char data2[] = "How are you?";
	unsigned char data3[] = "Goodbye";
	
	LCD_Init();
	
	LCD_draw_line(1 , 1, data);
  
}














/*  
		LCD_display_on();
		LCD_display_clear();
		LCD_display_on();

		// write "Hello World" on line 1, column 1
    // write "How are you?" on line 2, column 2
    // write "Goodbye" on line 3, column 3
	// (HINT: Use LCD_draw_line)
	  
		
		LCD_draw_line(1 , 1, data);
    //LCD_write_display(data);
    
		LCD_draw_line(2 , 2, data2);
		//LCD_write_display(data2);
    
		LCD_draw_line(3 , 3, data3);
		//LCD_write_display(data3);
    
	// create some fake 14-bit camera line data 0 - >2^14 in a 128 short array that utilizes all 14 bits
	
	for (i = 0; i < 128; i++){
		lineData[i] =  i * 128;
	}
	
	while(1)
	{
			LCD_write_display(LCD_TEXT_ARR);
			msdelay(500);
			LCD_DisplayCameraData(lineData);
			msdelay(500);

	}*/