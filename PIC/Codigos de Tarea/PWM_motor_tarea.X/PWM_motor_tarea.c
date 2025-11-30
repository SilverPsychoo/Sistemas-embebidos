/*
 * File:   PWM_motor_tarea.c
 * Author: jonat
 *
 * Created on 25 de noviembre de 2025, 10:58 PM
 */
#pragma config FOSC = XT       // Oscilador externo XT (20 MHz)
#pragma config WDTE = OFF      // Watchdog deshabilitado
#pragma config PWRTE = OFF     // Power-up Timer deshabilitado
#pragma config BOREN = ON      // Brown-out Reset habilitado
#pragma config LVP = OFF       // Programación de bajo voltaje deshabilitada
#pragma config CPD = OFF       // Protección EEPROM off
#pragma config WRT = OFF       // Escritura en Flash permitida
#pragma config CP = OFF        // Protección de código off
#include <xc.h>
#include "PIC16F877A.h"
#define _XTAL_FREQ 20000000

void pwm_init(void){
    TRISCbits.TRISC2 = 0;       // RC2 como salida PWM
    CCP1CON = 0b00001100;       // Modo PWM

    PR2 = 249;                  // Frecuencia ~1 kHz con prescaler 4
    T2CON = 0b00000101;         // Timer2 ON, prescaler 4
    
    CCPR1L = 0;                 // Duty inicial en 0%
}
void set_percent(unsigned char percent){
    if(percent > 100) percent = 100;

    unsigned int max_counts = 4 * (PR2 + 1);
    unsigned long dc = ((unsigned long)percent * max_counts) / 100;

    CCPR1L = (unsigned char)(dc >> 2);  // Parte alta del duty
    CCP1CONbits.CCP1X = (dc >> 1) & 1;  // Bits LSB
    CCP1CONbits.CCP1Y = dc & 1;
}
void main(void){
    TRISB = 0xFF;       // Botones en RB
    TRISA = 0x00;       // Control de motor o LEDs en RA

    pwm_init();
    unsigned char velocity = 0;

    while(1){
        // Aumentar PWM
        if(PORTBbits.RB1){
            if(velocity < 100) velocity++;
            set_percent(velocity);
            __delay_ms(20);
        }
        // Disminuir PWM
        if(PORTBbits.RB2){
            if(velocity > 0) velocity--;
            set_percent(velocity);
            __delay_ms(20);
        }
        // Direcciones o funciones en RA
        if(PORTBbits.RB3){
            PORTA = 0x01;
        }
        if(PORTBbits.RB4){
            PORTA = 0x02;
        }
        // Apagar salida
        if(PORTBbits.RB5){
            PORTA = 0x00;
            velocity = 0;
            set_percent(0);
        }
    }
}
