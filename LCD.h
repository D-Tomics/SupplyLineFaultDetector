
#ifndef LCD_H
#define	LCD_H

#include <xc.h> 

#define LCD_PORT PORTB
#define RS RD5
#define RW RD6
#define EN RD7

/*
 * ----commands-------
	01	Clear display screen
	02	Return home
	04	Decrement cursor (shift cursor to left)
	06	Increment cursor (shift cursor to right)
	05	Shift display right
	07	Shift display left
	08	Display off, cursor off
	0A	Display off, cursor on
	0C	Display on, cursor off
	0E	Display on, cursor blinking
	0F	Display on, cursor blinking
	10	Shift cursor position to left
	14	Shift cursor position to right
	18	Shift the entire display to the left
	1C	Shift the entire display to the right
	80	Force cursor to beginning ( 1st line)
	C0	Force cursor to beginning ( 2nd line)
	38	2 lines and 5×7 matrix
*/

void lcd_data(unsigned char byte) {
    RS = 1;
    LCD_PORT = byte;
    RW = 0;
    EN = 1;
    __delay_us(1);
    EN = 0;
    __delay_ms(10);
}

void lcd_cmd(unsigned char byte) {
    RS = 0;
    LCD_PORT = byte;
    RW = 0;
    EN = 1;
    __delay_us(1);
    EN = 0;
    __delay_ms(10);
}

void lcd_string(char* a) {
    int i;
    for(i=0;a[i]!='\0';i++)
       lcd_data(a[i]);  //Split the string using pointers and call the Char function 
}

void lcd_init() {
    TRISB = 0x00;
    TRISD5 = 0;
    TRISD6 = 0;
    TRISD7 = 0;
    
    __delay_ms(255);
    lcd_cmd(0x38);
    lcd_cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
    lcd_cmd(0x08); //Select Row 1
    lcd_cmd(0x00); //Clear Row 1 Display
    lcd_cmd(0x0C); //Select Row 2
    lcd_cmd(0x00); //Clear Row 2 Display
    lcd_cmd(0x06);
}

void lcd_clear() {
    lcd_cmd(0x00);
    lcd_cmd(0x01);
}

char* getNum(int num) {
    switch(num) {
        case 0: return "zro";
        case 1: return "one";
        case 2: return "two";
        case 3: return "thr";
        case 4: return "for";
        case 5: return "fiv";
        case 6: return "six";
        case 7: return "sev";
        case 8: return "eig";
        case 9: return "nin";
    }
    return "null";
}

void lcd_num(int num) {
    int temp = num;
    int reverse = 0;
    for(;temp > 0; ) {
        int rem = temp%10;
        temp /= 10;
        reverse = reverse * 10 + rem;
    }
    
    for(; reverse > 0;) {
        //lcd_data(reverse % 10 + 97);
        
        char* numS = getNum(reverse%10);
        lcd_string(numS);
        reverse /= 10;
    }
}

void lcd_float(double value) {
    double integer = (int)value;
    double decimal = (int)((value - integer) * 100);
    lcd_num((int)integer);
    lcd_data('.');
    lcd_num((int)decimal);
}



#endif	/* LCD_H */