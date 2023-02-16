#include <avr/io.h>
#include "../include/pwm.h"

void setupPWM(void){
    DDRD |= (1 << PD6);
    // Set PB6 to output (OC0A)
    
    OCR0A = 127;
    // Set a duty cycle of 0% in output control register 0A

    TCCR0A |= (1 << COM0A1);
    // Set to non-inverting PWM

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // Set WGM to Fast PWM mode 3

    TCCR0B |= (1 << CS00);
}

/*
 * OCR0A = 256*D/100 - 1
 * D = 50
 * OCR0A = 127
 *
 */
