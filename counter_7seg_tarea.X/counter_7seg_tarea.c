/*
 * File:   counter_7seg_tarea.c
 * Author: jonat
 *
 * Created on 21 de noviembre de 2025, 11:29 AM
 */

#include <xc.h>
#define _XTAL_FREQ 20000000
#define DEBOUNCE_MS 20
#include "PIC16877A.h"

const unsigned char DISPLAY[10] = {
    0x3F, 
    0x06, 
    0x5B, 
    0x4F,
    0x66, 
    0x6D, 
    0x7D, 
    0x07, 
    0x7F, 
    0x6F  
};

unsigned char get_input_debounced(void) {
    unsigned char a = PORTBbits.RB2;
    __delay_ms(DEBOUNCE_MS);
    unsigned char b = PORTBbits.RB2;
    if (a == b) {
        return b;      
    } else {
        return 0xFF;    
    }
}

void display_write(unsigned char digit) {
    if (digit > 9) return;  
    unsigned char pattern_cc = DISPLAY[digit];      
    unsigned char pattern_ca = (~pattern_cc) & 0x7F; 
    PORTAbits.RA1 = (pattern_ca >> 0) & 1;
    PORTAbits.RA2 = (pattern_ca >> 1) & 1;
    PORTAbits.RA3 = (pattern_ca >> 2) & 1;
    PORTAbits.RA4 = (pattern_ca >> 3) & 1;  
    PORTAbits.RA5 = (pattern_ca >> 4) & 1;
    PORTEbits.RE0 = (pattern_ca >> 5) & 1;
    PORTEbits.RE1 = (pattern_ca >> 6) & 1;
}

void main(void) {
    ADCON1 = 0x07;
    TRISBbits.TRISB2 = 1;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    unsigned char counter = 0;
    unsigned char prev = 0;
    display_write(counter);
    while (1) {
        unsigned char stable = get_input_debounced(); 
        if (stable != 0xFF) {                 
            if (prev == 0 && stable == 1) {   
                counter++;
                if (counter == 10) {          
                    counter = 0;
                }
                display_write(counter);
            }
            prev = stable;                    
        }
    }
}