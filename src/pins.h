#ifndef PINS
#define PINS

#include <avr/io.h>

#define SPI_DDR     DDRA
#define SPI_PORT    PORTA
#define SCK         PA4
#define MISO        PA5
#define MOSI        PA6

// CLOCK for 74HC595
#define CLOCK_DDR   DDRB
#define CLOCK_PORT  PORTB
#define CLOCK       PB0

#define LATCH_DDR   DDRB
#define LATCH_PORT  PORTB
#define LATCH       PB1

#define DATA_DDR    DDRB
#define DATA_PORT   PORTB
#define DATA        PB2

#define DP1         PA2
#define DP2         PA3
#define DP3         PA7
#define DP4         PA1
#define DP_DDR      DDRA
#define DP_PORT     PORTA

#define BUTTON_DDR  DDRA
#define BUTTON_PORT PORTA
#define BUTTON_PIN  PINA
#define BUTTON      PA0

#endif 
