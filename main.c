/**
 * main.c
 */
#include "msp.h"
#include "lcd.h"
#include "uart.h"		

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define CHAR_COUNT 10      //change this to modify the max. permissible length of a sentence

void LCD_main(void)
{
	const char data[] = "Sonic";
	const char data2[] = "Shadow";
	const char data3[] = "Silver";
	
	i2c0_Init(LCD_ADDR);
	
	LCD_Init();

	LCD_SetCursor(1, 0);
	LCD_SendChar('A');
	LCD_Clear();
	
	LCD_Print("Hello world!");

	LCD_SetCursor(2, 1);
	LCD_Print("LCD Tutorial");

	msdelay(500);
	LCD_Clear();

	while (1) {
		LCD_Print(data);
		msdelay(200);
		LCD_Clear();
		LCD_Print(data2);
		msdelay(200);
		LCD_Clear();
		LCD_Print(data3);
		msdelay(500);
		LCD_Clear();
	}
	
}

void UART_main()
{
	BYTE c = 0;											// declare a character 'c' (initilized to NULL)
	char inputStr[CHAR_COUNT];
	int char_indx = 0;			// Keeps track of current length of string
	
	//SystemCoreClock
	uart0_init();
	
	
	uart0_put("\r\n IDE Lab2: Enter a sentence: \r\n");    /*Transmit this through UART*/
	
	
	for (;;){
		c = uart0_getchar();
		
//	uart0_putchar(c);
		if (c != '\r'){
			if (char_indx < CHAR_COUNT){
				inputStr[char_indx] = c;
				uart0_putchar(c);
				char_indx++;
			}
		}else if (c == '\r'){
			inputStr[char_indx++] = '\0';
			uart0_put("\r\n");
			
			uart0_put(inputStr);
			
			uart0_put("\r\n");
			
			inputStr[0] = '\0';
			char_indx = 0;
		}
	}
}  

int tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    } else {
        return c;
    }
}

int checkPassWord(char* inPass) {
    char* the_password = "Killmonger";
    int i;

    // Convert both strings to lowercase for case-insensitive comparison
    for (i = 0; inPass[i] != '\0' && the_password[i] != '\0'; i++) {
        inPass[i] = tolower(inPass[i]);
        the_password[i] = tolower(the_password[i]);
    }

    return strcmp(inPass, the_password);
}

int main()
{
	BYTE c = 0;											// declare a character 'c' (initilized to NULL)
	char inputStr[CHAR_COUNT];
	int char_indx = 0;			// Keeps track of current length of string
	
	
	// Initialize the device for I2C and LCD
	i2c0_Init(LCD_ADDR);
	LCD_Init();
	
	// Initialize the UART
	uart0_init();
	uart0_put("\r\n eLock PIN: \r\n");
	
	LCD_Clear();
	LCD_SetCursor(1, 0);
	LCD_Print("eLock PIN:");

	LCD_SetCursor(2, 1);
	
	while (1){
		c = uart0_getchar();
		
//	uart0_putchar(c);
		if (c != '\r'){
			if (char_indx < CHAR_COUNT){
				inputStr[char_indx] = c;
				uart0_putchar(c);
				LCD_SendChar(c);
				char_indx++;
			}
		}else if (c == '\r'){
			inputStr[char_indx++] = '\0';
			uart0_put("\r\n");
			
			uart0_put(inputStr);
			
			if (checkPassWord(inputStr)){
				LCD_Clear();
				LCD_SetCursor(1, 0);
				LCD_Print("ACCESS GRANTED");
				msdelay(50);
				LCD_Clear();
				LCD_SetCursor(1, 0);
				LCD_Print("ACCESS GRANTED");
				msdelay(50);
				LCD_Clear();
				LCD_SetCursor(1, 0);
				LCD_Print("ACCESS GRANTED");
				msdelay(50);
			}else{
				LCD_Clear();
				LCD_SetCursor(1, 0);
				LCD_Print("ACCESS DENIED");
				msdelay(50);
				LCD_Clear();
				LCD_SetCursor(1, 0);
				LCD_Print("ACCESS DENIED");
				msdelay(50);
				LCD_Clear();
				LCD_SetCursor(1, 0);
				LCD_Print("ACCESS DENIED");
				msdelay(50);
				
				LCD_Clear();
				LCD_SetCursor(1, 0);
				LCD_Print("Try Again: ");
				LCD_SetCursor(2, 1);
			}
			
			uart0_put("\r\n");
			
			inputStr[0] = '\0';
			char_indx = 0;
		}
	}
	
}
