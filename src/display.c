#include "display.h"
#include "pins.h"

#define CHAR_SIZE 11
const uint8_t charMap[CHAR_SIZE] = {
    0b01111110, // 0
    0b00100010, // 1
    0b10111100, // 2
    0b10111010, // 3
    0b11100010, // 4
    0b11011010, // 5
    0b11011110, // 6
    0b00110010, // 7
    0b11111110, // 8
    0b11110010, // 9
    0b00000000, // 10
};

#define ANIMATION_SIZE 6
const uint8_t animation[ANIMATION_SIZE] = {
    0b00010000,
    0b00100000,
    0b00000010,
    0b00001000,
    0b00000100,
    0b01000000,
};

struct{
    int8_t index;
    struct Segment segments[DISPLAY_SIZE];
} display = {
    0,
    {
        {CLEAR, &DP4_DDR, &DP4_PORT, DP4},
        {CLEAR, &DP3_DDR, &DP3_PORT, DP3},
        {CLEAR, &DP2_DDR, &DP2_PORT, DP2},
        {CLEAR, &DP1_DDR, &DP1_PORT, DP1},
    };
};

void initDisplay(){
    DP4_DDR |= (1 << DP4);
    DP3_DDR |= (1 << DP3);
    DP2_DDR |= (1 << DP2);
    DP1_DDR |= (1 << DP1);

    DP4_PORT |= (1 << DP4);
    DP3_PORT |= (1 << DP3);
    DP2_PORT |= (1 << DP2);
    DP1_PORT |= (1 << DP1);
}

void enableDisplay(){
    TCCR1A |= (1 << WGM12); // set CTC mode
    // prescaler 8000000 / 1024 = 7812.5
    // clock = 8000000
    // pre = 1024
    // f = (clock/pre) / (1 + OCR1A)
    // f = (8000000/1024) / (1 + 99)
    // f = 78.125 Hz
    // d = 1 / f
    // d = 1 / 78.125 = 0.0128 s
    TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
    OCR1A = 99;

    TIMSK1 |= (1 << OCIE1A); // enable Output COmpare Interrupt Enable Timer/Counter1 A
    TIFR1 |= (1 << OCF1A); // fire
}

void dissableDisplay(){
    TIMSK1 &= ~(1 << OCIE1A);
}

Segment curr;
ISR(TIM1_COMPA_vect){
    curr = display.segments[display.index++];

    DP4_PORT |= (1 << DP4);
    DP3_PORT |= (1 << DP3);
    DP2_PORT |= (1 << DP2);
    DP1_PORT |= (1 << DP1);

    *(curr.dpPORT) &= ~(1 << curr.dp);
    sendSPI(curr.data, &CSD_PORT, CSD);
    if(DISPLAY_SIZE <= display.index){
        display.index = 0;
    }
}

void displayUpdate(uint16_t n){
    int8_t index = 0;
    
    while(n){
        display.segments[index++].data = charMap[n % 10];
        n /= 10;
    }

    for(;index < DISPLAY_SIZE; index++){
        display.segments[index].data = charMap[0];
    }
}
