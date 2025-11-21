/*
 * File:   led_boton_tarea.c
 * Author: jonat
 *
 * Created on 21 de noviembre de 2025, 11:15 AM
 */
#include <xc.h>
#define _XTAL_FREQ 20000000
#include "PIC16F877A.h"


void main(void)  {
     TRISB = 0b11111111;
     TRISC = 0b00000000;
    
    while (1){
         if (PORTBbits.RB1 == 1) {
             PORTC = 0b11111111;
            __delay_ms(1000);
        } 
         
          if (PORTBbits.RB1 == 0) {
             PORTC = 0b00000000;
            __delay_ms(1000);
        }           
    }
    return;
}