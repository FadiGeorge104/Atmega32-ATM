#include "../include/terminal.h"

float strtof(const char *nptr, char **endptr) {
	// Determine the sign of the number
	int sign = 1;
	if (*nptr == '-') {
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+') {
		nptr++;
	}

	// Parse the integer part of the number
	float value = 0;
	while (*nptr >= '0' && *nptr <= '9') {
		value = value * 10 + (*nptr - '0');
		nptr++;
	}

	// Parse the fractional part of the number, if any
	if (*nptr == '.') {
		nptr++;
		float factor = 0.1f;
		while (*nptr >= '0' && *nptr <= '9') {
			value += factor * (*nptr - '0');
			factor *= 0.1f;
			nptr++;
		}
	}

	// Handle exponent, if any
	if (*nptr == 'e' || *nptr == 'E') {
		nptr++;
		int exponent_sign = 1;
		if (*nptr == '-') {
			exponent_sign = -1;
			nptr++;
		}
		else if (*nptr == '+') {
			nptr++;
		}
		int exponent = 0;
		while (*nptr >= '0' && *nptr <= '9') {
			exponent = exponent * 10 + (*nptr - '0');
			nptr++;
		}
		value *= powf(10, exponent_sign * exponent);
	}

	// Set the end pointer, if requested
	if (endptr != NULL) {
		*endptr = (char *)nptr;
	}

	// Return the final value, with sign applied
	return sign * value;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	LCD_Clear();
	LCD_String_xy(0,0,"Enter Trans Amount");
	
	char transactionValue[20] = "";
	uint8_t tc = 0;
	while(tc != 10)
	{
		if(scan_keypad() != 0)
		{
			char input = scan_keypad();
			if (input == 'E')
			{
				break;
			}
			if(input == 'C')
			{
				tc = 0;
				memset(transactionValue,0,sizeof(transactionValue));
				LCD_Clear();
				LCD_String_xy(0,0,"Enter Trans Amount");
				continue;
			}
			transactionValue[tc] = input;
			LCD_String_xy(1,tc,&transactionValue[tc]);
			tc++;
		}
	}
	termData->transAmount = strtof (transactionValue,NULL);
	if (termData->transAmount <= 0)
	return INVALID_AMOUNT;
	return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData) {
	// Set max amount
	termData->maxTransAmount = 500;
	if (termData->maxTransAmount <= 0)
	return INVALID_MAX_AMOUNT;
	return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
	if (termData->maxTransAmount < termData->transAmount)
	{
		char buffer[20];
		memset(buffer,0,sizeof(buffer));
	    sprintf(buffer,"%d",termData->maxTransAmount);
		LCD_Clear();
		LCD_String("Max Trans Amount is:");
		LCD_String_xy(1, 5,buffer);
		_delay_ms(3000);
		LCD_Clear();
		return EXCEED_MAX_AMOUNT;
	}
	else
	return TERMINAL_OK;
}
