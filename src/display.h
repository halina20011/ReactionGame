#ifndef DISPLAY
#define DISPLAY

#include <util/delay.h>
#include <inttypes.h>

#include "pins.h"
#include "sSPI.h"

#define DISPLAY_SIZE    4
#define DISPLAY_DELAY   500

#define CLEAR   10

struct Segment{
    uint8_t data;
    volatile uint8_t *dpDDR, *dpPORT;
    uint8_t dp;
};

void initDisplay();


void enableDisplay();
void dissableDisplay();

void displayUpdate(uint16_t n);

// uint8_t showDigit(struct SSPI sSPI, uint8_t n);
// void displayShow();

#endif
