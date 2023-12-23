#include "display.h"
#include "pins.h"

// TODO: make display event timer driven
// TODO: remap the pins before compilation
//     A
//   ----
// F|    | B
//  |    |
//   ----
// E| G  | C
//  |    |
//   ---
//    D
const uint8_t DIGIT_MAP[11] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11100110, // 9
    0b00000000  // 10
};

#define ANIMATION_SIZE 6
const uint8_t animation[ANIMATION_SIZE] = {
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
};

#define A   2
#define B   0
#define C   4
#define D   6
#define E   7
#define F   1
#define G   3
#define DP  5

#define EXTRACT(oPosition, number) (((1 << (7 - oPosition)) & number) != 0)
#define REMAP(oPosition, nPosition, number) (EXTRACT(oPosition, number) << (7 - nPosition));

uint8_t reverse(uint8_t b){
    b = (b & 0b11110000) >> 4 | (b & 0b00001111) << 4;
    b = (b & 0b11001100) >> 2 | (b & 0b00110011) << 2;
    b = (b & 0b10101010) >> 1 | (b & 0b01010101) << 1;

    return b;
}

uint8_t remap(uint8_t o){
    uint8_t mapped = 0;
    mapped |= REMAP(0, A, o);
    mapped |= REMAP(1, B, o);
    mapped |= REMAP(2, C, o);
    mapped |= REMAP(3, D, o);
    mapped |= REMAP(4, E, o);
    mapped |= REMAP(5, F, o);
    mapped |= REMAP(6, G, o);
    mapped |= REMAP(7, DP, o);
    return mapped;
}

const uint8_t DISPLAY_PINS[DISPLAY_SIZE] = {
    DP4, DP3, DP2, DP1
};

void initDisplay(){
    CLOCK_DDR |= (1 << CLOCK);
    LATCH_DDR |= (1 << LATCH);
    DATA_PORT |= (1 << DATA);
    DP_DDR |= ((1 << DP1) | (1 << DP2) | (1 << DP3) | (1 << DP4));
    DP_PORT |= (1 << DP1) | (1 << DP2) | (1 << DP3) | (1 << DP4);
}

uint8_t showDigit(struct SSPI sSPI, uint8_t n){
    uint8_t digit = (n < 10) ? n : 10;
    uint8_t remaped = reverse(remap(DIGIT_MAP[digit]));
    sendSSPI(sSPI, remaped);
    return remaped;
}

void displayShow(struct SSPI sSPI, uint16_t n){
    // make sure that all display ports are off
    DP_PORT |= (1 << DP1) | (1 << DP2) | (1 << DP3) | (1 << DP4);
    
    for(uint8_t i = 0; i < DISPLAY_SIZE && n; i++){
        DP_PORT &= ~(1U << DISPLAY_PINS[i]);
        uint8_t d = n % 10;
        showDigit(sSPI, d);
        n /= 10;
        _delay_ms(DISPLAY_DELAY);
        DP_PORT |= (1 << DISPLAY_PINS[i]);
        _delay_ms(DISPLAY_DELAY);
    }
}
