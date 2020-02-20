/*
 * File:   main.c
 * Author: hp
 *
 * Created on 24 January, 2020, 2:30 AM
 */

#define _XTAL_FREQ 20000000

#define RS RC0
#define EN RC2
#define output RD0

#define LCD_DATA PORTB
#include <xc.h>
#include <stdint.h>

void ADC_Init() {
    ADCON0 = 0b01000001;
    ADCON1 = 0b11000000;
}

int ADC_Read(uint8_t channel ){
    ADCON0 &= 0b11000101; // clearing channnel selection bits
    ADCON0 |= channel << 3; // setting requred bits
    __delay_ms(1);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH<<8)+ADRESL);
}

void Lcd_Cmd(char a)
{
    RS = 0;           
    LCD_DATA = a; //Incoming Hex value
    EN  = 1;         
    __delay_ms(1);
    EN  = 0;         
}

Lcd_Clear()
{
    Lcd_Cmd(0); //Clear the LCD
    Lcd_Cmd(1); //Move the curser to first position
}

void Lcd_Start()
{
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x38);
  Lcd_Cmd(0x08); //Select Row 1
  Lcd_Cmd(0x00); //Clear Row 1 Display
  Lcd_Cmd(0x0C); //Select Row 2
  Lcd_Cmd(0x00); //Clear Row 2 Display
  Lcd_Cmd(0x06);
}

void Lcd_Print_Char(char data)  //Send 8-bits through 4-bit mode
{
    RS = 1;
    LCD_DATA = data;
    EN = 1;
    __delay_ms(1);
    EN = 0;
}

void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
}

void Lcd_Print_Num(int num) {
    int temp = num;
    int reverse = 0;
    for(;temp > 0; ) {
        int rem = temp%10;
        temp /= 10;
        reverse = reverse * 10 + rem;
    }
    
    for(; reverse > 0;) {
        Lcd_Print_Char(reverse % 10 + 48);
        reverse /= 10;
    }
}

void Lcd_Print_Float(double value) {
    double integer = (int)value;
    double decimal = (int)((value - integer) * 100);
    Lcd_Print_Num((int)integer);
    Lcd_Print_Char('.');
    Lcd_Print_Num((int)decimal);
}

int main()
{
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    output = 1;
    Lcd_Start();
    ADC_Init();
    while(1)
    {
        Lcd_Clear();
        //Lcd_Cmd(0x80);
        int adc = ADC_Read(4);
        float input = (adc * (5.0f / 1024.0f)) * 100;
        
        if(input > 200 & input < 250)
            output = 1;
        else
            output = 0;
        Lcd_Print_Float(input);
    }
    return 0;
}


