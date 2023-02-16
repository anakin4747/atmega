#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/timer.h"
#include "../include/adc.h"
#include "../include/uart.h"
#include "../include/pwm.h"


int main(void){

    DDRB |= (1 << PB5);
    // Set port B5 as output

    setupADC();
    setupPWM();
    setupUART();
    setupTimer1();


    while (1) {
    }
    return 0;
}
