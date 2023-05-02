#include "../include/uart.h"
#include "../include/adc.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

void setupUART(void){

    UBRR0H = (BAUD_RATE >> 8);
    UBRR0L = (BAUD_RATE);
    // Setting Baud Rate

    UCSR0C = 0x06;     
    // Set frame rate

    UCSR0B = (1 << TXEN0);
    // Enable transmitter

}

void sendOverUART(const char *message, uint16_t adcRead, uint8_t channel){
    char data[255];

    switch(channel){
        case CH0:
        case CH2:
            sprintf(data, "%10s %d.%-4d Volts\n\r", message, adcRead / 100, adcRead % 100);
            break;
        case CH1:
            sprintf(data, "%10s %d.%-4d Amps\n\r", message, adcRead / 100, adcRead % 100); // To Do, add conversion to mAmps 
            break;
        case 5:
            sprintf(data, "%s %d\n\r", message, adcRead);
            break;
        default:
            sprintf(data, "%s\n\r", message);
            break;
    }

    int i = 0;
    while(data[i] != 0){
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = data[i];
        i++;          
    }
}
