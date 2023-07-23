/*
 * IncFile1.h
 *
 * Created: 7/20/2023 6:59:39 AM
 *  Author: fady
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include <avr/io.h>
#include <util/delay.h>

#define setPinOutput(DDR,pinNumber) DDR |= (1<<pinNumber)
#define setPinIput(DDR,pinNumber) DDR &=~(1<<pinNumber)
#define enablePinPULLUP(PORT,pinNumber) PORT |=(1<<pinNumber)
#define writeHigh(PORT,pinNumber) PORT |=(1<<pinNumber)
#define WriteLOW(PORT,pinNumber) PORT&=~(1<<pinNumber)
#define readInputValue(PIN,pinNumber) PIN&(1<<pinNumber)
#define toggleValue(port,pinNumber) port ^= (1<<pinNumber)


#endif /* INCFILE1_H_ */