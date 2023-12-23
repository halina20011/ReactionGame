#ifndef _SSPI
#define _SSPI

#include <stdio.h>
#include <util/delay.h>

#define UNSET   0xff
#define UNSET_P &0

struct SSPI{
    volatile uint8_t *clockDDR, *clockPORT, clock;
    volatile uint8_t *outDDR, *outPORT, out;
    volatile uint8_t *inDDR, *inPORT, in;
    volatile uint8_t *csDDR, *csPORT, cs;
};


void configSSPI(struct SSPI sSPI);

void sendSSPI(struct SSPI sSPI, uint8_t data);
void sendSSPI16(struct SSPI sSPI, uint8_t data1, uint8_t data2);

#endif
