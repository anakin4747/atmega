#include "../include/adc.h"
#include <avr/io.h>

unsigned char adcIndex;
uint16_t rawBatteryReading;
uint16_t rawVoltReading;
uint16_t rawCurrReading;

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

void rotateADC(void){
    switch(adcIndex){
        case CH0:
            ADMUX = ADMUX & 0xF0;
            // Clear MUX0-MUX3 

            ADMUX |= CH0;
            // Set ADC to channel 0

            break;
        case CH1:
            ADMUX = ADMUX & 0xF0;
            ADMUX |= CH1;
            break;
        case CH2:
            ADMUX = ADMUX & 0xF0;
            ADMUX |= CH2;
            break;
        default:
            ADMUX = ADMUX & 0xF0;
            ADMUX |= CH0;
            break;
    }
}

void saveResult(uint16_t result){
    switch(adcIndex){
        case CH0:
            rawBatteryReading = result;
            adcIndex = CH1;
            // Set the index to the next channel
            break;
        case CH1:
            rawVoltReading = result;
            adcIndex = CH2;
            break;
        case CH2:
            rawCurrReading = result;
            adcIndex = CH0;
            break;
        default:
            adcIndex = CH1;
            break;
    }
}

uint16_t adc_read(void){
    uint16_t result;

    rotateADC();

    ADCSRA |= (1 << ADSC);
    // Start adc conversion

    while(!(ADCSRA & (1 << ADIF)));
    // Wait for conversion to finish

    result = ADC;
    saveResult(result);
    // Save result

    ADCSRA |= (1 << ADIF);
    // Clear ADIF for next conversion
    
    return result;
}
