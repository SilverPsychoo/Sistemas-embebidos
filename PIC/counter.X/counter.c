/*
 * File:   counter.c
 * Author: jonat
 *
 * Created on 30 de octubre de 2025, 07:25 AM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000
#define DEBOUNCE_MS 20
unsigned char display[10] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b00000111,
    0b01111111,
    0b01101111,
};

unsigned char get_input_debounced(void) {
    unsigned char a = PORTAbits.RA0;
    __delay_ms(DEBOUNCE_MS);
    unsigned char b = PORTAbits.RA0;
    
    if (a==b){
        return b;
        }else {
            return 0xff;
        }
}
void main(void) {
    TRISB = 0b00000000;
    TRISA = 0b11111111;
    PORTB = display[0];
    
    unsigned char counter = 0;
    unsigned char prev = 0;
    
    while(1){
        unsigned char stable = get_input_debounced();
        
        if(stable!=0xff){
            if (prev == 0 && stable == 1){
                counter ++;
                PORTB = display[counter];  
            }
            prev = stable;
            if(counter == 10){
                counter = 0;
            }
        }
    }    
} 
  