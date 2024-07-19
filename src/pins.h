#ifndef PINS
#define PINS

#include <avr/io.h>

#define SPI_DDR     DDRA
#define SPI_PORT    PORTA
#define SCK         PA4
#define MISO        PA5
#define MOSI        PA6

#define CSS_DDR     DDRB
#define CSS_PORT    PORTB
#define CSS         PB0
#define CSD_DDR     DDRA
#define CSD_PORT    PORTA
#define CSD         PA3

// TODO: move DP3 to PA7
// display pins
#define DP1_DDR     DDRA
#define DP1_PORT    PORTA
#define DP1         PA1

#define DP2_DDR     DDRA
#define DP2_PORT    PORTA
#define DP2         PA0

#define DP3_DDR     DDRB
#define DP3_PORT    PORTB
#define DP3         PB2

#define DP4_DDR     DDRA
#define DP4_PORT    PORTA
#define DP4         PA2

#define BUTTON_DDR  DDRA
#define BUTTON_PORT PORTA
#define BUTTON_PIN  PINA
#define BUTTON      PA0

#endif 
