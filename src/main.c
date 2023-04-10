#define F_CPU 16000000UL
#include <stdint.h>
#include <avr/io.h>
#include "../include/adc.h"
#include "../include/mppt.h"
#include "../include/pwm.h"
#include "../include/timer.h"
#include "../include/uart.h"


int main(void){

    static uint32_t inputVoltageX100, inputCurrentX100, battVoltageX100;
    inputVoltageX100 = inputCurrentX100 = battVoltageX100 = 0;
    // Are these the default values we want?

    DDRB |= (1 << DDB5);
    // Sign of life LED

    setupADC();
    setupPWM();
    setupUART();
    setupTimer0();
    // Initialization
    

    while(1){
        while(interruptOccured()){

            PORTB ^= (1 << PORTB5);
            // Just for sign of life in arduino version

            sendOverUART("Channel 0", inputVoltageX100 = adc_read(CH0), CH0);
            sendOverUART("Channel 1", inputCurrentX100 = adc_read(CH1), CH1);
            sendOverUART("Channel 2", battVoltageX100 = adc_read(CH2), CH2);
            // Read all ADCs and print to UART
            // Measurements are all x100 to account for a lack of floats

            // mppt(inputVoltageX100, inputCurrentX100, battVoltageX100);
            updatePWM(50);

        }
    }
    return 0;

}

