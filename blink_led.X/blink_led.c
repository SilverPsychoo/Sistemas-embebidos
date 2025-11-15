/*
 * File:   blink_led.c
 * Author: jonat
 *
 * Created on 23 de octubre de 2025, 07:50 AM
 */
#include <xc.h>
#define _XTAL_FREQ 20000000


void main(void) {
    
    TRISB = 0b00000000;
    
    while(1){
       
       PORTB = 0b00000000;
       __delay_ms(1000);
       PORTB = 0b11111111;
       __delay_ms(1000);
    }        
    return;
}
