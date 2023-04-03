#include "../include/adc.h"
#include <avr/io.h>


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

    ADCSRA |= (1 << ADEN);
    // Enable ADC
}

int32_t adc_conversion(void){
    int32_t result;

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

uint32_t adc_read(uint8_t channel){
    // Accepts the channel to perform the read of and handles conversions
    // appropriately
    int32_t currentReading;

    switch(channel){
        case CH0:
            ADMUX = ADMUX & 0xF0; // Clear MUX0-MUX3 
            ADMUX |= CH0; // Set ADC to channel 0
            return (adc_conversion() * 2 * 5 * 100 / 1023);
            break;
        case CH1:
            ADMUX = ADMUX & 0xF0;
            ADMUX |= CH1;

            currentReading = ((adc_conversion() * 2500) - 1278750) / 1023;
            if(currentReading < 0){
                return 0;
            } else {
                return currentReading;
            }
            break;
        case CH2:
            ADMUX = ADMUX & 0xF0;
            ADMUX |= CH2;
            return (adc_conversion() * 4 * 5 * 100 / 1023);
            break;
        default:
            return -1;
            break;
    }
}
