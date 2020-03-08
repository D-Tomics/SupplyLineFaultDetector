#ifndef ADC_H
#define	ADC_H

#include <xc.h>

void adc_init() {
    ADCON0 = 0x00;   // sampling freq = osc_freq/2 , ADC off initially
    ADCON1 = 0x80;   // right justified and all inp are analogue
}

int adc_read(int channel) {
    ADCON0 = 0b00000001 | (channel << 3); //select required channel and turn ON adc
    GO_DONE = 1;                          // start conversion
    while(GO_DONE);                       // wait for completion
    
    return ((ADRESH<<8) + ADRESL);        // returns right justified 10 bit result
}

#endif	/* XC_HEADER_TEMPLATE_H */

