#ifndef _SSPI
#define _SSPI

#include <avr/interrupt.h>

#define NO_CS   0xff

void initSPI();

void sendSPI(uint8_t data, volatile uint8_t *port, uint8_t cs);

#endif
