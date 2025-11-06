/*
 * File:   ADC.c
 * Author: jonat
 *
 * Created on 5 de noviembre de 2025, 07:32 AM
 */

#include <xc.h>
#define _XTAL_FREQ 20000000

void adc_init(void){
    TRISA = 0b00000001;
    ADCON1 = 0b1101110;
    ADCON0 = 0b1000001;
    __delay_us(20);
}

unsigned int adc_read_an0(void){
    __delay_us(20);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((unsigned int)ADRESH <<8|ADRESL);
}

void main(void) {
    adc_init();
    
    while(1){
       uint16_t raw = adc_read_an0();
       uint16_t mv = (uint16_t)raw*5000L/1023U;
   }
    
}
