#ifndef RANDOM
#define RANDOM

#include <stdint.h>
#include <avr/io.h>

void initRandom();

uint8_t randomBit();
uint8_t randomByte();
uint8_t random();

#endif
