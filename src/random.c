#include "random.h"

// using pin ACC0 
#define ANALOG_CHANGEL 000000

void initRandom(){
    ADMUX |= ANALOG_CHANGEL;
    // prescaler speed of ADC should be in range 50kHz to 200kHz
    ADCSRA |= (1 << ADPS2 | 1 << ADPS1);
    // enable
    ADCSRA |= (1 << ADEN);
}

uint8_t randomBit(){
    // start conversion
    ADCSRA |= (1 << ADSC);
    while((ADCSRA & (1 << ADSC))){}
    // loop_until_bit_is_clear(ADCSRA, ADSC);
    return ADC & 1;
}

uint8_t randomByte(){
    uint8_t n = 0;
    for(uint8_t i = 0; i < 8; i++){
        uint8_t byte = randomBit();
        n |= (byte & 1) << i;
    }

    return n;
}

uint8_t random(){
    // uint8_t n = randomByte();
    // while(n == 0 || n == 0xff){
    //     n = randomByte();
    // }
    uint8_t n = 0;
    for(uint8_t i = 0; i < 10; i++){
        n ^= randomByte();
    }
    return n;
}
