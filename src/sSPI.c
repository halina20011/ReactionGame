#include "sSPI.h"

#include "pins.h"

void configSSPI(struct SSPI sSPI){
    *(sSPI.clockDDR) |= (1 << sSPI.clock);
    *(sSPI.outDDR) |= (1 << sSPI.out);
    if(sSPI.in != UNSET){
        *(sSPI.inDDR) &= ~(1U << sSPI.in);
    }
    if(sSPI.cs != UNSET){
        *(sSPI.csDDR) |= (1 << sSPI.cs);
    }
}

// 1/115200*1000*1000 ~ 8.68
#define sSPI_DELAY 9

void sendSSPI(struct SSPI sSPI, uint8_t data){
    if(sSPI.cs != UNSET){
        *(sSPI.csPORT) |= (1 << sSPI.cs);
    }

    for(uint8_t i = 0; i < 8; i++){
        uint8_t bit = ((1 << (7 - i)) & data) != 0;
        *(sSPI.outPORT) = (bit << sSPI.out) | (((~(1 << sSPI.out)) & *(sSPI.outPORT)));
        _delay_us(sSPI_DELAY);
        *(sSPI.clockPORT) |= (1 << sSPI.clock);
        _delay_us(sSPI_DELAY);
        *(sSPI.clockPORT) &= ~(1U << sSPI.clock);
        _delay_us(sSPI_DELAY);
    }

    if(sSPI.cs != UNSET){
        *(sSPI.csPORT) &= ~(1U << sSPI.cs);
    }

    *(sSPI.outPORT) &= ~(1 << sSPI.out);
}

void sendSSPI16(struct SSPI sSPI, uint8_t data1, uint8_t data2){
    sendSSPI(sSPI, data1);
    sendSSPI(sSPI, data2);
}
