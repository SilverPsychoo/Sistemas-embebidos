/*
 * File:   7segbutton.c
 * Author: jonat
 *
 * Created on 28 de octubre de 2025, 07:25 AM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000


void main(void) {
    
    TRISB = 0b00000000;
    TRISA = 0b11111111;
    
    if (PORTAbits.RA0 == 1) {
       PORTB = 0b00111111;
       __delay_ms(1000);
       PORTB = 0b00000110;
       __delay_ms(1000);
       PORTB = 0b01011011;
       __delay_ms(1000);
       PORTB = 0b01001111;
       __delay_ms(1000);
       PORTB = 0b01100110;
       __delay_ms(1000);
       PORTB = 0b01101101;
       __delay_ms(1000);
       PORTB = 0b01111101;
       __delay_ms(1000);
       PORTB = 0b00000111;
       __delay_ms(1000);
       PORTB = 0b01111111;
       __delay_ms(1000);
       PORTB = 0b01101111;
       __delay_ms(1000);            
    }
    if (PORTAbits.RA0 == 0) { 
    PORTB = 0b00000000;    
    }
    return;
}
