#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "pins.h"
#include "sSPI.h"
#include "random.h"
#include "display.h"

// TODO: use USI not software/bit banged SPI
// #include "USI.h"
// TODO: use one SPI with chip select
// TODO: button on pb2
// TODO: sleep mode

#define EVER ;;

struct SSPI serialSSPI = {
    &SPI_DDR, &SPI_PORT, SCK, 
    &SPI_DDR, &SPI_PORT, MOSI, 
    &SPI_DDR, &SPI_PORT, MISO, 
    NULL, NULL, UNSET,
};
    
struct SSPI displaySSPI = {
    &CLOCK_DDR, &CLOCK_PORT, CLOCK,
    &DATA_DDR, &DATA_PORT, DATA,
    NULL, NULL, UNSET,
    &LATCH_DDR, &LATCH_PORT, LATCH,
};

uint8_t debounce(){
    if(bit_is_clear(BUTTON_PIN,BUTTON)){
        _delay_us(1000);
        if(bit_is_clear(BUTTON_PIN,BUTTON)){
            return 1;
        }
    }

    return 0;
}

uint8_t i = 1;
ISR(PCINT0_vect){
    if(bit_is_clear(BUTTON_PIN, BUTTON)){
        i++;
        if(10 < i){
            i = 1;
        }
    }
}

int main(){
    configSSPI(serialSSPI);
    configSSPI(displaySSPI);

    // initRandom();
    initDisplay();
    
    BUTTON_DDR &= ~(1U << BUTTON);
    BUTTON_PORT |= (1 << BUTTON);

    GIMSK |= (1 << PCIE0); // enable interrupt
    PCMSK0 |= (1 << PCINT0); // pin change mask
    sei();
    
    DP_PORT &= ~(1U << DP4);

    for(EVER){
        uint8_t d = showDigit(displaySSPI, i);
        // displayShow(displaySSPI, 3456);
        // displayShow(displaySSPI, i);
        // _delay_ms(4);
        // sendSSPI(serialSSPI, i);
        // PORTA = (1 << PA4);
        // sendSSPI16(serialSSPI, 0xff, 0xff);
        // uint8_t data = randomByte();
        // uint8_t data = random();
        // _delay_ms(10);
        // showDigit(displaySSPI, i++);
        // _delay_ms(500);
        // PORTA = 0;
        // _delay_ms(1000);
    }

    return 0;
}
