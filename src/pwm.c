#include <avr/io.h>
#include "../include/pwm.h"

void setupPWM(void){
    DDRD = (1 << PD3);
    // Set PB6 to output (OC0A)

    OCR2A = 255;
    // Set a duty cycle of 0% in output control register 0A

    TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2B1);
    // Set WGM to Fast PWM mode 3

    TCCR2B = (1 << WGM22) | (1 << CS20);
    // No prescaling

}

void updatePWM(uint8_t dutyCycle){
    if(dutyCycle > 0 || dutyCycle < 100){
        // Check if duty cycle is appropriate

        OCR2B = (256 * dutyCycle / 100) - 1;
        /* This is how to set the PWM duty cycle
         * OCR2B = 256*D/100 - 1
         * D = 50
         * OCR2B = 127
         *
         */
    } 
}

