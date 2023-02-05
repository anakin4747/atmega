#include "../include/adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t adc_result;

ISR(ADC_vect){

    adc_result = ADC;

}

void adc_init(void){
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    ADCSRA |= (1 << ADEN) | (1 << ADIE);

    sei();

    ADCSRA |= (1 << ADSC);
}

