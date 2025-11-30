#include <avr/io.h>

void adc_init()
{
    ADMUX |= (1 << REFS0);       // Referencia AVcc
    ADCSRA |= (1 << ADEN);       // Habilitar ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // Prescaler 64
}

uint16_t adc_read()
{
    ADCSRA |= (1 << ADSC);            // Iniciar conversión
    while (ADCSRA & (1 << ADSC));     // Esperar a que termine
    return ADC;                       // Valor 0–1023
}

int main(void)
{
    // --- PWM en Timer1 ---
    DDRB |= (1 << DDB1); // PB1 (OC1A) salida, pin 9 Arduino

    ICR1 = 0xFFFF; // TOP = 16 bits

    TCCR1A |= (1 << COM1A1); // PWM no-invertido
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13); // Fast PWM ICR1 como TOP
    TCCR1B |= (1 << CS10); // Sin prescaler

    // --- ADC ---
    adc_init();

    while (1)
    {
        uint16_t pot = adc_read();    // 0–1023

        // Escalar pot → 0–65535 (16 bits)
        uint32_t pwm = (uint32_t)pot * 65535UL / 1023UL;
        OCR1A = pwm; // Actualizar PWM según pot
    }
}
