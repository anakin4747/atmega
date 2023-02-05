#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/adc.h"



#define LED_PIN PB5

volatile uint16_t adc_result;

int main(void){
    // Initialize the ADC
    adc_init();

    // Set the LED pin as an output
    DDRB |= (1 << LED_PIN);
    DDRC &= ~(1 << DDC0);

    // Enable global interrupts
    sei();

    while (1) {
        // Wait for the ADC conversion to complete
        while (!(ADCSRA & (1 << ADIF)));

        // Read the ADC result
        uint16_t adc_result = ADC;
        uint16_t Vref = 5;

        uint16_t voltage = (adc_result * Vref) / 1024;

        // Turn on the LED if the ADC result is above a threshold
        if (voltage > 1) {
            PORTB |= (1 << LED_PIN);
        } else {
            PORTB &= ~(1 << LED_PIN);
        }

        // Clear the ADC interrupt flag
        ADCSRA |= (1 << ADIF);
    }

    return 0;
}
