#include "../include/timer.h"
#include <avr/interrupt.h>

static int timerIntCount = 0;

// Timer0 OVerFlow Interrupt Service Routine
ISR(TIMER0_OVF_vect){

    timerIntCount++;
}

int interruptOccured(void){

    if(timerIntCount > 1000){
        timerIntCount = 0;
        return 1;
        // if 100 interrupts have occured return true
    } else {
        return 0;
    }
}

void setupTimer0(void){

    TCNT0 = 100;

    TCCR0B |= (1 << CS01) | (1 << CS00);
    // Set prescaler to 1024

    TIMSK0 |= (1 << TOIE0);
    // Enable compare match interrupt

    sei();
    // Enable global interrupts
}

