#ifndef USI
#define USI

#include <avr/io.h>
#include "pins.h"

#ifndef MESSAGE_BUFFER_SIZE
#define MESSAGE_BUFFER_SIZE 100
#endif

void initUSI();
int sendUSI(uint8_t data);

#endif
