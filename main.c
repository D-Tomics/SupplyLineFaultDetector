// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000

#include <xc.h>
#include "LCD.h"
#include "ADC.h"

int main()
{
    lcd_init();
    adc_init();             //Initialize the ADC module

    while(1)
    {
        int adcValue = adc_read(0);       // Read the ADC value of channel zero
        lcd_clear();
        float adc = adcValue * (5.0 / 1024);
        lcd_float(adc);
    } 
}


 