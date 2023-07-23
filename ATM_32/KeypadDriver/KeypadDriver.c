/*
* KeypadDriver.c
*
* Created: 7/20/2023 5:32:08 PM
*  Author: fady
*/
#include "KeypadDriver.h"


// Keypad array
char keypad[4][4] = {
	{'7', '8', '9', 'A'},
	{'4', '5', '6', 'B'},
	{'1', '2', '3', '/'},
	{'C', '0', 'F', 'E'}
};

// Function to scan keypad for pressed keys
char scan_keypad(void) {
	// Set all keypad pins to inputs with pull-up resistors
	KEYPAD_DDR = 0x00; //0b00000000
	KEYPAD_PORT = 0xFF; //0b1111111
	// Row scanning loop
	for (int row = 0; row < 4; row++) {
		// Set current row pin as output low
		KEYPAD_DDR |= (1 << row);
		KEYPAD_PORT &= ~(1 << row);

		// Column reading loop
		for (int col = 0; col < 4; col++) {
			
			if ((KEYPAD_PIN & (1 << (col + 4))) == 0) {
				// Key pressed
				// Debounce delay
				_delay_ms(130);
				return keypad[row][col];
			}
		}

		// Set current row pin back to input high
		KEYPAD_DDR &= ~(1 << row);
		KEYPAD_PORT |= (1 << row);
	}

	// No key pressed
	return 0;
}
