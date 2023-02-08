#include "../include/timer.h"
#include <avr/interrupt.h>

// Timer0 Compare Interrupt Service Routine
ISR(TIMER0_COMPA_vect){
    // Code to be executed every 20ms
    PORTB ^= (1 << PB5);
}

void setupTimer0(void){
    // Set prescaler to 1024
    TCCR0B |= (1 << CS02) | (1 << CS00);

    // Calculate compare value for 20ms
    OCR0A = 156;

    /*
    // Settings for every 500ms
    // Set prescaler to 8
    TCCR0B |= (1 << CS01);

    // Calculate compare value for 500ms
    OCR0A = 199;
    */

    // Enable compare match interrupt
    TIMSK0 |= (1 << OCIE0A);

    // Enable global interrupts
    sei();
}
