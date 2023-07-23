/*
* ATM_32.c
*
* Created: 7/20/2023 6:58:46 AM
* Author : fady
*/

#include <avr/io.h>
#define  F_CPU 16000000UL
#include "include/util.h"
#include "KeypadDriver/KeypadDriver.h"
#include "include/app.h"
#include "lcdDriver/lcdDriver.h"




int main(void)
{
	setPinOutput(DDRB,0);
	lcd_init();
	KEYPAD_PORT = 0xFF;
	appStart();
	
}

