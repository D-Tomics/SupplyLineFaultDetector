#ifndef TIMER_H
#define	TIMER_H

#include <xc.h>


struct Delay {
    int count;
    unsigned int ms;
    unsigned int us;
};

void timer0_init() {
    T0CS = 0;   // internal clock
    T0SE = 0;   // increment on low to high edge
    PSA = 0;    // use Prescallar
    PS2 = 0;    //
    PS1 = 0;    // set prescallar to 2
    PS0 = 0;    //
    
    
    TMR0 = 253; // load value to counter (EC == 1ms)
    TMR0IE = 1; // enable TMR0 interrupt
}

int delay_ms(struct Delay* delay) {
    delay -> us = delay -> ms * 1000;
    return delay_us(delay);
}

int delay_us(struct Delay* delay) {
    if(TMR0IF) {
        TMR0 = 254;
        delay -> count++;
        TMR0IF = 0;
        if(delay -> count >= delay -> us) {
            delay -> count = 0;
            return 1;
        }
    }
    return 0;
}

#endif

