#include "sSPI.h"

#include "pins.h"

struct{
    uint8_t running;
    uint8_t data;
    uint8_t mask;
    uint8_t write;
    uint8_t cs;
    volatile uint8_t *csPort;
} SPI;

// 0        1        2
// |--------|        |---...
// |        |        |
// |        |        |
// |        |--------|
// on send start
//   enable Timer/Counter0 Compare Match A Interrupt
//   and trigger Timer/Counter0 Compare Match A Interrupt
//   set running flag
//
// on every edge (1/2/3...)
//   toggle the clock
//   write flag => write the data and shift the mask
//
// when all the data was writen wait one clock and then
//   dissable Timer/Counter0 Compare Match A Interrupt
//   turn off the data port
//   turn off the cs if needed
//   clear running flag
ISR(TIM0_COMPA_vect){
    SPI_DDR ^= (1 << SCK); // clock
    if(SPI.write){ // write data
        uint8_t bit = (SPI.mask & SPI.data) != 0;
        SPI_PORT = (bit << MOSI) | (((~(1 << MOSI)) & SPI_PORT));
        SPI.mask >>= 1;
    }

    SPI.write = !SPI.write;

    if(!SPI.mask && SPI.write){
        TIMSK0 &= ~(1U << OCIE0A);
        SPI.running = 0;
        SPI_PORT &= ~(1U << MOSI);
        if(SPI.cs != NO_CS){
            *(SPI.csPort) &= ~(1 << SPI.cs);
        }
    }
}

void initSPI(){
    SPI_DDR |= (1 << SCK) | (1 << MOSI);
    TCCR0A |= (1 << WGM01); // CTC mode
    TCCR0B |= (1 << CS01); // prescaler 8
    OCR0A = 10;
    sei();
}

void sendSPI(uint8_t data, volatile uint8_t *port, uint8_t cs){
    SPI.running = 1;
    SPI.data = data;
    SPI.write = 1;
    SPI.mask = (1 << 7);
    
    SPI.cs = cs;
    if(cs != NO_CS){
        SPI.csPort = port;

        *(SPI.csPort) = (1 << cs);
    }

    TIMSK0 |= (1 << OCIE0A);
    TIFR0 |= (1 << OCF0A);
}
