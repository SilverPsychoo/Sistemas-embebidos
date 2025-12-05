#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definición de pines para LCD
#define LCD_DATA_PORT PORTD
#define LCD_DATA_DDR  DDRD
#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_DDR  DDRB
#define RS PB0  // Pin 8 Arduino
#define EN PB1  // Pin 9 Arduino

void lcdCommand(unsigned char cmd);
void lcd_init(void);
void lcdSendDataByte(unsigned char data);
void lcdSendString(char *addr);
void adc_init(void);
uint16_t adc_read_channel(uint8_t channel);

void lcdCommand(unsigned char cmd) {
    // Enviar comandos
    LCD_CTRL_PORT &= ~(1 << RS);  // RS = 0 (comando)
    LCD_DATA_PORT = cmd;          // Enviar comando al puerto de datos
    LCD_CTRL_PORT |= (1 << EN);   // EN = 1
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1 << EN);  // EN = 0
    _delay_ms(1);
}

void lcd_init(void) {
    // Configurar puertos como salida
    LCD_DATA_DDR = 0xFF;   // Puerto D completo como salida
    LCD_CTRL_DDR |= (1 << RS) | (1 << EN);  // RS y EN como salidas
    
    _delay_ms(20);  // Espera inicial para que el LCD se inicialice
    
    lcdCommand(0x38);  // Configura display: 2 líneas, matriz 5x8
    lcdCommand(0x06);  // Incrementar cursor automáticamente
    lcdCommand(0x0F);  // Display ON, cursor parpadeando
    lcdCommand(0x01);  // Limpiar pantalla
    _delay_ms(2);
    lcdCommand(0x80);  // Mover cursor a primera línea
}

void lcdSendDataByte(unsigned char data) {
    // Enviar datos
    LCD_CTRL_PORT |= (1 << RS);   // RS = 1 (datos)
    LCD_DATA_PORT = data;         // Enviar dato al puerto de datos
    LCD_CTRL_PORT |= (1 << EN);   // EN = 1
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1 << EN);  // EN = 0
    _delay_ms(1);
}

void lcdSendString(char *addr) {
    while(*addr) {
        lcdSendDataByte(*addr);
        addr++;
    }
}

void adc_init(void) {
    // Referencia AVcc
    ADMUX = (1 << REFS0);

    // Habilitar ADC + prescaler 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}


uint16_t adc_read_channel(uint8_t channel) {
    // Mantener referencia, limpiar solo MUX bits
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Iniciar conversión
    ADCSRA |= (1 << ADSC);

    // Esperar fin de conversión
    while (ADCSRA & (1 << ADSC));

    return ADC;
}


int main(void) {
    char buffer[16];
    uint16_t prev_mv = 0xFFFF;
    uint16_t raw, mV;
    
    // Inicializar periféricos
    lcd_init();
    adc_init();
    
    while(1) {
        raw = adc_read_channel(0);  // Leer canal ADC0 (A0)
        mV = (uint16_t)((uint32_t)raw * 5000UL / 1023UL);
        
        if(mV != prev_mv) {
            // Mostrar valor RAW
            lcdCommand(0x80);  // Primera línea
            sprintf(buffer, "RAW:%4u", raw);
            lcdSendString(buffer);
            
            // Mostrar valor en mV
            lcdCommand(0xC0);  // Segunda línea
            sprintf(buffer, "mV:%4u", mV);
            lcdSendString(buffer);
            
            prev_mv = mV;
        }
        
        _delay_ms(100);
    }
    
    return 0;
}
