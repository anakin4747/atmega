#include "../include/uart.h"
#include "../include/adc.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void setupUART(void){
    // Setting Baud Rate
    UBRR0H = (BAUD_RATE >> 8);
    UBRR0L = (BAUD_RATE);

    // Set frame rate
    UCSR0C = 0x06;     
    // Enable transmitter
    UCSR0B = (1 << TXEN0);

}

void sendOverUART(const char *message, uint16_t adcRead, uint8_t channel){
    char data[255];

    switch(channel){
        case CH0:
        case CH1:
            sprintf(data, "%10s %d.%-4d Volts\n\r\0", message, adcRead / 100, adcRead % 100);
            break;
        case CH2:
            sprintf(data, "%10s %d.%-4d Amps\n\r\0", message, adcRead / 100, adcRead % 100); // To Do, add conversion to mAmps 
            break;
        default:
            sprintf(data, "\033[2J\033[H");
            break;
    }

    int i = 0;
    while(data[i] != 0){
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = data[i];
        i++;          
    }
}
