#include "../include/app.h"


void clearCardData(ST_cardData_t *data)
{
	memset(data,0,sizeof(*data));
}
void clearTerminalData(ST_terminalData_t *data)
{
	memset(data,0,sizeof(*data));
}
void clearServerData(ST_transaction_t *data)
{
	memset(data,0,sizeof(*data));
}

void appStart()
{
	while(1)
	{
		LCD_Clear();
		ST_cardData_t  cardData;
		ST_terminalData_t term;
		ST_transaction_t trans;
		clearCardData(&cardData);
		clearTerminalData(&term);
		clearServerData(&trans);
		LCD_Clear();
		//CARD PAN
		EN_cardError_t PAN = getCardPAN(&cardData);
		if (PAN != OK)
		{
			LCD_StringError("invalid PAN");
			continue;
		}
		// Expiry Data
		EN_cardError_t expiryData = getCardExpiryDate(&cardData);
		if(expiryData != OK)
		{
			LCD_StringError("invalid expiry");
			continue;
		}
		EN_terminalError_t tranAmount = getTransactionAmount(&term);
		if (tranAmount != TERMINAL_OK)
		{
			continue;
		}
		EN_terminalError_t setMaxamount = setMaxAmount(&term);
		if(setMaxamount != TERMINAL_OK)
		{
			continue;
		}
		EN_terminalError_t maxAmount = isBelowMaxAmount(&term);
		if (maxAmount != TERMINAL_OK)
		{
			continue;
		}
		//Server
		
		trans.cardHolderData = cardData;
		trans.terminalData = term;
		EN_transState_t dataError = recieveTransactionData(&trans);
		if (dataError != APPROVED)
		{
			LCD_StringError("se_1");
			continue;
		}
		
		EN_serverError_t accountAvilable = isValidAccount(&cardData);
		if(accountAvilable != SERVER_OK)
		{
			LCD_StringError("se_2");
			continue;
		}
		
		EN_serverError_t checkBalance = isAmountAvailable(&term);
		if(checkBalance != SERVER_OK)
		{
			LCD_StringError("se_3");
			continue;
		}
	}
}