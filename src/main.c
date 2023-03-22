#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/timer.h"
#include "../include/adc.h"
#include "../include/uart.h"
#include "../include/pwm.h"

int dc = 0;

int main(void){

    DDRB |= (1 << DDB5);


    setupADC();
    setupPWM();
    setupUART();
    setupTimer1();

    while(1){
        while(!timerInterrupt){

            sendOverUART("Channel 0", adc_read(CH0), CH0);
            sendOverUART("Channel 1", adc_read(CH1), CH1);
            sendOverUART("Channel 2", adc_read(CH2), CH2);
            // Read all ADCs and print to UART
            PORTB ^= (1 << PORTB5);


            if(dc > 100){
                dc = 0;
            }
            updatePWM(dc);
            dc++;

            timerInterrupt = 0;
        }
    }
    return 0;
}
