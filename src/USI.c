#include "USI.h"

#include <avr/interrupt.h>

// ISR(TIM0_COMPA_vect){
//     USICR |= (1 << USITC);
// }
//
// ISR(USI_OVF_vect){
//     TIMSK0 &= ~(1U << OCIE0A);
//
//     USISR = (1 << USIOIF);
//     // uint8_t data = USIDR;
// }

void initUSI(){
    SPI_DDR |= (1 << MOSI) | (1 << SCK); // Outputs
    SPI_DDR &= ~(1U << MISO); // Input
    SPI_PORT |= (1 << MISO); // Pull-up

    // set three wire mode
    USICR |= (1 << USIOIE);
    USICR |= (1 << USIWM0); // Three-wire mode
    USICR |= (1 << USICS1) | (1 << USICS0); // set clock sources
    USICR |= (1 << USICLK);

    TCCR0B |= (1 << CS01) | (1 << CS00); // set 64 timer prescaler
    OCR0A = 1;
}

int sendUSI(uint8_t data){
    USIDR = data;
    TIFR0 |= (1 << OCF0A);
    TIMSK0 |= (1 << OCIE0A);
    return 0;
}
