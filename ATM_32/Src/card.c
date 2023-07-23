#include "../include/card.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//CARD PAN
extern ST_accountsDB_t accounts[5];

EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
	LCD_String_xy(0,0,"Enter PAN");
	uint8_t i = 0;
	char string[10];
	while(i != 20)
	{
		if(scan_keypad() != 0)
		{
			char input = scan_keypad();
			if(input == 'E')
			{
				LCD_Clear();
				break;
			}
			if(input == 'C')
			{
				i = 0;
				memset(cardData->primaryAccountNumber,0,sizeof(cardData->primaryAccountNumber));
				LCD_Clear();
				LCD_String_xy(0,0,"Enter PAN");
				continue;
			}
			cardData->primaryAccountNumber[i] = input;
			LCD_String_xy(1,1,(char*)cardData->primaryAccountNumber);
			sprintf(string, "%d" ,i+1);
			LCD_String_xy(0,13,string );
			i++;
		}
	}
	int8_t af = 0;
	int8_t len = strlen((char *)cardData->primaryAccountNumber);
	int8_t  an = 0;
	if(len != 9 )
	{
		return WRONG_PAN;
	}
	for (an = 0 ; an < 5 ; an ++)
	{
		if(strcmp((char*)cardData->primaryAccountNumber , (char*)accounts[an].primaryAccountNumber) == 0)
		{
			af = 1;
			break;
		}
		else
		{
			af = 0;
		}
	}
	if (af  == 1)
	{
		LCD_Clear();
		LCD_String_xy(0,0,"Welcome: ");
		LCD_String_xy(1,0,(char*)accounts[an].accountHolderName);
		_delay_ms(1000);
		LCD_Clear();
		return OK;
	}
	if(af == 0)
	{
		return WRONG_NAME;
	}
	return OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {

	LCD_Clear();
	LCD_String("Enter expiry data");
	uint8_t countExData = 0;
	while( countExData != 7)
	{
		if(scan_keypad() != 0)
		{
			char input	= scan_keypad();
			if(input == 'E')
			{
				break;
			}
			if(input == 'C')
			{
				LCD_Clear();
				LCD_String("Enter expiry data");
				countExData = 0;
				memset(cardData->cardExpirationDate,0,sizeof(cardData->cardExpirationDate));
				continue;
			}
			cardData->cardExpirationDate[countExData] = input;
			LCD_String_xy(1,0,(char*)cardData->cardExpirationDate);
			countExData++;
		}
	}
	
	uint8_t len = strlen((char *)cardData->cardExpirationDate);
	// Error Handling
	if (len != 5 || (char)cardData->cardExpirationDate[2] != '/') {
		LCD_StringError("e1");
		return WRONG_EXP_DATE;
	}
	if ((char)cardData->cardExpirationDate[0] > '1' ||
	(((char)cardData->cardExpirationDate[0] == '1') &&
	((char)cardData->cardExpirationDate[1] > '2')))
	{
		LCD_StringError("e2");
		return WRONG_EXP_DATE;
	}
	int16_t yearAsInt = ((int)(cardData->cardExpirationDate[3] - '0') * 10 +
	(int)(cardData->cardExpirationDate[4] - '0')) +
	2000; // 2023
	int16_t monAsInt = (int)(cardData->cardExpirationDate[0] - '0') * 10 +
	(int)(cardData->cardExpirationDate[1] - '0');
	if (yearAsInt < 2023)
	{
		LCD_StringError("e3");
		return WRONG_EXP_DATE;
	}
	if (monAsInt < 7 && yearAsInt <= 2023)
	{
		LCD_StringError("e4");
		return WRONG_EXP_DATE;
	}
	return OK;
}
