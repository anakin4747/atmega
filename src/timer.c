#include "../include/timer.h"
#include "../include/adc.h"
#include "../include/uart.h"
#include <avr/interrupt.h>

static char timerInterrupt = 0;

// Timer1 Compare Interrupt Service Routine
ISR(TIMER1_COMPA_vect){
    timerInterrupt = 1;
}

int interruptOccured(void){
    if(timerInterrupt){
        timerInterrupt = 0;
        return 1;
    } else {
        return 0;
    }
}

void setupTimer1(void){
    // Set to CTC mode
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12);

    // Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Calculate compare value for 20ms
    OCR1A = 3905;

    // Enable compare match interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Enable global interrupts
    sei();
}

/*
 * f_OCnx = f_clk_IO / (N * (1 + OCRnx))
 *
 * N = 1 || 8 || 64 || 256 || 1024
 *
 * OCRnx = (f_clk_IO * T_s / N) - 1
 * OCRnx = (16M * 20ms / 1024) - 1
 * OCRnx = 311.5
 *
 * OCRnx = (f_clk_IO * T_s / N) - 1
 * OCRnx = (16M * 250ms / 1024) - 1
 * OCRnx = 3905.25
 *
 */
