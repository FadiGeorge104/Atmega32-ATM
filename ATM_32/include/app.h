#ifndef APP_H
#define APP_H
#include "terminal.h"
#include "card.h"
#include "server.h"
#include <stdlib.h>

void appStart(void);
void clearCardData(ST_cardData_t *data);
void clearTerminalData(ST_terminalData_t *data);
#endif // !APP_H
