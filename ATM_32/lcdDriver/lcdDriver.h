/*
 * lcdDriver.h
 *
 * Created: 7/20/2023 6:25:54 PM
 *  Author: fady
 */ 


#ifndef LCDDRIVER_H_
#define LCDDRIVER_H_
#include "../include/util.h"

#define LCD_Dir  DDRC			/* Define LCD data port direction */
#define LCD_Port PORTC			/* Define LCD data port */
#define RS PC0				/* Define Register Select pin */
#define EN PC1 				/* Define Enable signal pin */

//												????														
void LCD_StringError (char *str);
void LCD_Command(unsigned char cmd);
void lcd_init();
void LCD_Char( unsigned char data );
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();

#endif /* LCDDRIVER_H_ */