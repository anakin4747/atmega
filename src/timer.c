#include "../include/timer.h"
#include "../include/adc.h"
#include "../include/uart.h"
#include <avr/interrupt.h>

static char timerInterrupt = 0;

// Timer1 Compare Interrupt Service Routine
ISR(TIMER0_COMPA_vect){
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
    // TCCR0A |= (1 << WGM01);
    //
    // // Set prescaler to 1024
    // TCCR0B |= (1 << CS01) | (1 << CS00);
    //
    // // Calculate compare value for 20ms
    // OCR0A = 155;
    //
    // // Enable compare match interrupt
    // TIMSK0 |= (1 << OCIE0A);
    //
    // // Enable global interrupts
    // sei();
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
 * OCRnx = (f_clk_IO * T_s / N) - 1
 * OCRnx = (16M * 1s / 1024) - 1
 * OCRnx = 15624
 *
 */
