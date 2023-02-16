#include "../include/uart.h"
#include <avr/io.h>
#include <stdlib.h>
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

void sendOverUART(uint16_t adcRead){
    char data[4 + 2 + 1];
    // 4 chars in a long, plus \n\r (2), plus null

    ultoa(adcRead, data, 10);
    // Convert to string in base 10

    strcat(data, "\n\r");
    // Newline and return

    int i = 0;

    while(data[i] != 0){
        while (!( UCSR0A & (1<<UDRE0)));
        UDR0 = data[i];
        i++;          
    }
}
