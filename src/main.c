#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/adc.h"


volatile uint16_t adc_result;

int main(void){
    // Initialize the ADC
    adc_init();

    // Set the LED pin as an output
    DDRB |= (1 << PB5);

    // Enable global interrupts
    sei();

    while (1) {
        // Wait for the ADC conversion to complete
        while (!(ADCSRA & (1 << ADIF)));

        uint16_t Vref = 5;

        uint16_t voltage = (adc_result * Vref) / 1024;

        // Turn on the LED if the ADC result is above a threshold
        if (voltage > 1) {
            PORTB |= (1 << PB5);
        } else {
            PORTB &= ~(1 << PB5);
        }

        // Clear the ADC interrupt flag
        ADCSRA |= (1 << ADIF);
    }

    return 0;
}
