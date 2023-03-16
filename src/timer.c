#include "../include/timer.h"
#include "../include/adc.h"
#include "../include/uart.h"
#include <avr/interrupt.h>


// Timer1 Compare Interrupt Service Routine
ISR(TIMER1_COMPA_vect){
    // Code to be executed every 20ms
    PORTB ^= (1 << PB5);

    sendOverUART("Channel 0", adc_read(CH0), CH0);
    sendOverUART("Channel 1", adc_read(CH1), CH1);
    sendOverUART("Channel 2", adc_read(CH2), CH2);
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
