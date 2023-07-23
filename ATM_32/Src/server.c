#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern ST_accountsDB_t accounts[5] =
{
	{.balance = 1000.0, .accountHolderName = "Fady Geroge", .primaryAccountNumber = "123456789" , .active = 1},
	{.balance = 2000.0,.accountHolderName = "Ahmed Saber", .primaryAccountNumber = "000011112" , .active = 0},
	{.balance = 3000,.accountHolderName = "Morcos", .primaryAccountNumber = "111122222" , .active = 1}
};


EN_transState_t recieveTransactionData(ST_transaction_t *transData) {
  //Check if the account exist
  int8_t checkAccountAvilabilty = 0;
  for (int i = 0; i < 255; i++) {
    if ((strcmp((char *)transData->cardHolderData.primaryAccountNumber,
                (char *)accounts[i].primaryAccountNumber)) == 0) {
      if (accounts[i].active != 0) {
        checkAccountAvilabilty = 1;
        break;
      }
    }
  }
  if (checkAccountAvilabilty != 1)
    return INTERNAL_SERVER_ERROR;
  return APPROVED;
}
uint8_t accountNumber ;
EN_serverError_t isValidAccount(ST_cardData_t *cardData) {
  // check accout number
  int8_t check = 0;
  for (int i = 0; i < 255; i++) {
    if ((strcmp((char *)cardData->primaryAccountNumber,
                (char *)accounts[i].primaryAccountNumber)) == 0) {
      check = 1;
      accountNumber = i;
      return SERVER_OK;
    }
  }
  if (check != 1)
    return ACCOUNT_NOT_FOUND;
  return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData) {

  if(termData->transAmount > accounts[accountNumber].balance)
  {
    LCD_StringError("Low Balance");
    return LOW_BALANCE;
  }
  LCD_Clear();
  LCD_String_xy(0,0,"Your New Balance is:");
  char currentBalance[20] = "";
  sprintf(currentBalance,"%d",accounts[accountNumber].balance -= termData->transAmount);
  LCD_String_xy(1,0,currentBalance);
  _delay_ms(2000);
  return SERVER_OK; 
}
