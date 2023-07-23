#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <time.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define setPinOutput(DDR,pinNumber) DDR |= (1<<pinNumber)
#define setPinIput(DDR,pinNumber) DDR &=~(1<<pinNumber)
#define enablePinPULLUP(PORT,pinNumber) PORT |=(1<<pinNumber)
#define writeHigh(PORT,pinNumber) PORT |=(1<<pinNumber)
#define WriteLOW(PORT,pinNumber) PORT&=~(1<<pinNumber)
#define readInputValue(PIN,pinNumber) PIN&(1<<pinNumber)
#define toggleValue(port,pinNumber) port ^= (1<<pinNumber)

typedef struct ST_accountsDB_t {
	int16_t balance;
	uint8_t accountHolderName[20];
	uint8_t primaryAccountNumber[21];
	uint16_t transactionData;
	bool active;
} ST_accountsDB_t;

extern ST_accountsDB_t accounts[5];
#endif