/*
 * File:   counter_7seg_tarea.c
 * Author: jonat
 *
 * Created on 21 de noviembre de 2025, 11:29 AM
 */
#include <xc.h>
#define _XTAL_FREQ 20000000
#define DEBOUNCE_MS 20

const unsigned char DISPLAY[10] = {
    0b11111111,
    0b00001100, 
    0b00110111,
    0b00011111,
    0b00001100, 
    0b00011011,
    0b00111011,
    0b00001110,
    0b11111111,
    0b00011110 
};
const unsigned char DISPLAYE[10] = {
    0b00000001,
    0b00000000, 
    0b00000010, 
    0b00000010,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000000,
    0b11111111,
    0b00000011
};

unsigned char get_input_debounced(void) {
    unsigned char a = PORTBbits.RB2;
    __delay_ms(DEBOUNCE_MS);
    unsigned char b = PORTBbits.RB2;

    if (a == b) return b;
    else return 0xFF; 
}

void main(void) {
    TRISA = 0b00000000;  
    TRISB = 0b11111111;
    TRISE = 0b00000000;

    unsigned char counter = 0;
    unsigned char prev = 0;

    PORTA = DISPLAY[counter];
    PORTE = DISPLAYE[counter];
    while(1){

        unsigned char stable = get_input_debounced();

        if(stable != 0xFF){       
            if(prev == 0 && stable == 1){

                counter++;
                if(counter == 10) counter = 0;

                PORTA = DISPLAY[counter];
                PORTE = DISPLAYE[counter];
            }

            prev = stable;
        }
    }
}