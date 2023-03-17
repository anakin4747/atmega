#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/adc.h"
#include "../include/mppt.h"
#include "../include/pwm.h"
#include "../include/timer.h"
#include "../include/uart.h"


int main(void){

    setupADC();
    setupPWM();
    setupUART();
    setupTimer1();

    int inputVoltage;
    int inputCurrent;
    int battVoltage;

    while(1){
        while(!timerInterrupt){

            sendOverUART("Channel 0", inputVoltage = adc_read(CH0), CH0);
            sendOverUART("Channel 1", inputCurrent = adc_read(CH1), CH1);
            sendOverUART("Channel 2", battVoltage = adc_read(CH2), CH2);
            // Read all ADCs and print to UART

            mppt(inputVoltage, inputCurrent, battVoltage);
            

            timerInterrupt = 0;

        }
    }
    return 0;
}
