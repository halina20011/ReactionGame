#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "pins.h"
#include "sSPI.h"
// #include "random.h"
#include "display.h"

// TODO: USE DO/DI for SPI
// TODO:? use hardware SPI
// #include "USI.h"
// TODO: sleep mode

#define EVER ;;

// uint8_t debounce(){
//     if(bit_is_clear(BUTTON_PIN,BUTTON)){
//         _delay_us(1000);
//         if(bit_is_clear(BUTTON_PIN,BUTTON)){
//             return 1;
//         }
//     }
//
//     return 0;
// }

// uint8_t i = 1;
// ISR(PCINT0_vect){
//     if(bit_is_clear(BUTTON_PIN, BUTTON)){
//         i++;
//         if(10 < i){
//             i = 1;
//         }
//     }
// }

int main(){
    initSPI();

    // initRandom();
    // initDisplay();
    // 
    // BUTTON_DDR &= ~(1U << BUTTON);
    // BUTTON_PORT |= (1 << BUTTON);
    //
    // GIMSK |= (1 << PCIE0); // enable interrupt
    // PCMSK0 |= (1 << PCINT0); // pin change mask
    // sei();
    
    // DP_PORT &= ~(1U << DP4);
    
    initDisplay();
    enableDisplay();
    uint8_t i = 0;
    for(EVER){
        displayUpdate(i++);
        // sendSPI(i++, &CSS_PORT, CSS);
        // sendSPI(0xff, &CSS_PORT, CSS);
        // uint8_t d = showDigit(displaySSPI, i);
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
        _delay_ms(500);
        // PORTA = 0;
        // _delay_ms(1000);
    }

    return 0;
}
