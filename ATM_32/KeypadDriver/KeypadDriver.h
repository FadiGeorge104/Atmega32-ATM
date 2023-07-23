/*
 * KeypadDriver.h
 *
 * Created: 7/20/2023 5:32:20 PM
 *  Author: fady
 */ 


#ifndef KEYPADDRIVER_H_
#define KEYPADDRIVER_H_
#include "../include/util.h"
#define KEYPAD_PORT PORTD   // Port connected to keypad
#define KEYPAD_PIN PIND     // Pin connected to keypad
#define KEYPAD_DDR DDRD    // Data direction register for keypad port

char keypad[4][4];
char scan_keypad(void);


#endif /* KEYPADDRIVER_H_ */