#ifndef DISPLAY
#define DISPLAY

#include <util/delay.h>
#include <inttypes.h>

#include "pins.h"
#include "sSPI.h"

#define DISPLAY_SIZE    4
#define DISPLAY_DELAY   500
void initDisplay();

uint8_t remap(uint8_t o);

uint8_t showDigit(struct SSPI sSPI, uint8_t n);
void displayShow(struct SSPI sSPI, uint16_t n);

#endif
