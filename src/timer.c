#include "../include/timer.h"
#include <avr/interrupt.h>

static int timerIntCount = 0;

// Timer0 OVerFlow Interrupt Service Routine
ISR(TIMER0_COMPA_vect){

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

    TCCR0A = (1 << WGM01);
    // CTC Mode is WGM02:0 = 2 so WGM02 = 0, WGM01 = 1, and WGM00 = 0;
    // COM0A1:0 is 00 so that OC0A is disconnected

    TCCR0B = (1 << CS02) | (1 << CS00);
    // Prescaler is 1024
    
    OCR0A = 15;
    // OCR0A = f_CLK / (N * f_INT) - 1
    // OCR0A = ((f_CLK * T_INT) / N) - 1, T_INT being the period of interrupts
    //                                    and N is the prescalar
    // OCR0A = ((16MHz * 1ms) / 1024) - 1 = 14.65
    
    TIMSK0 = (1 << OCIE0A);
    // Enable timer compare match A interrupt

    sei();
    // Enable global interrupts
}

