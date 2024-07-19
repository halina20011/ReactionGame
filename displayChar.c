// gcc displayChar.c -Wall -o ./build/displayChar && ./build/displayChar
#include <stdio.h>
#include <stdint.h>

#define CHAR_SIZE 11

//     A
//   ----
// F|    | B
//  |    |
//   ----
// E| G  | C
//  |    |
//   ---
//    D
const uint8_t charMap[CHAR_SIZE] = {
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

#define A   7
#define B   0
#define C   1
#define D   5
#define E   4
#define F   6
#define G   2
#define DP  3

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

void number2Char(uint8_t d, uint8_t buffer[]){
    size_t size = 0;

    while(d){
        buffer[size++] = (d & 1) ? '1' : '0';
        d >>= 1;
    }

    for(size_t i = size; i < 8; i++){
        buffer[size++] = '0';
    }

    for(uint8_t i = 0; i < 8/2; i++){
        uint8_t temp = buffer[i];
        buffer[i] = buffer[size - 1 - i];
        buffer[size - 1 - i] = temp;
    }

    buffer[8] = 0;
}

int main(){
    uint8_t buffer[10];
    printf("#define CHAR_SIZE %i\n", CHAR_SIZE);
    printf("const uint8_t charMap[CHAR_SIZE] = {\n");
    for(int i = 0; i < CHAR_SIZE; i++){
        uint8_t d = remap(reverse(charMap[i]));
        number2Char(d, buffer);
        printf("    0b%s, // %i\n", buffer, i);
    }
    printf("};\n\n");
    
    printf("#define ANIMATION_SIZE %i\n", ANIMATION_SIZE);
    printf("const uint8_t animation[ANIMATION_SIZE] = {\n");
    for(int i = 0; i < ANIMATION_SIZE; i++){
        uint8_t d = remap(reverse(animation[i]));
        number2Char(d, buffer);
        printf("    0b%s,\n", buffer);
    }
    printf("};\n");

    return 0;
}
