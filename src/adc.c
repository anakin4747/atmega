#include "../include/adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t adc_result;

ISR(ADC_vect){

    adc_result = ADCL;
    adc_result |= (ADCH << 8);

}

void adc_init(void){

    // Set the ADC prescaler to 128, to give a 125 kHz ADC clock frequency
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Set the voltage ref to internal 1.1V
    ADMUX |= (1 << REFS1) | (1 << REFS0);

    // Set ADC pin as input
    DDRC &= ~(1 << DDC0);

    // The power reduction bit must be set to 0 to enable 
    PRR &= ~(1 << PRADC);

    // ADC enable bit and interrupt bit
    ADCSRA |= (1 << ADEN) | (1 << ADIE);

    // Enable global interrupts
    sei();

    // Start the first conversion
    ADCSRA |= (1 << ADSC);
}
