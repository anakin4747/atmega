#include "../include/adc.h"
#include <avr/io.h>

unsigned char adcIndex;

void setupADC(void){
    // Select ADC Prescalar to 128
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // 16MHz/128 = 125kHz       50kHz < 125kHz < 200kHz

    ADMUX = ADMUX & 0xF0;
    // Clear MUX0-MUX3 Important in Multichannel conv

    ADMUX |= (1 << REFS0);
    // Select AVcc with capacitor on AREF pin

    ADMUX |= CH0;
    // Select fisrt channel

    adcIndex = CH0;
    // Set index to first channel at setup
    
    ADCSRA |= (1 << ADEN);
    // Enable ADC
}

uint16_t adc_read(void){
    uint16_t result;

    ADCSRA |= (1 << ADSC);
    // Start adc conversion

    while(!(ADCSRA & (1 << ADIF)));
    // Wait for conversion to finish

    result = ADC;
    // Save result

    ADCSRA |= (1 << ADIF);
    // Clear ADIF for next conversion
    
    return result;
}
