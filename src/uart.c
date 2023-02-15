#include "../include/uart.h"
#include <avr/io.h>

void setupUART(void){
    // Setting Baud Rate
    UBRR0H = (BAUD_RATE >> 8);
    UBRR0L = (BAUD_RATE);

    // Set frame rate
    UCSR0C = 0x06;     
    // Enable transmitter
    UCSR0B = (1 << TXEN0);

}

void sendOverUART(void){
    unsigned char data[] = "Hello from ATmega328p\n\r";
    int i = 0;

    i = 0;
    while(data[i] != 0){
        while (!( UCSR0A & (1<<UDRE0)));
        UDR0 = data[i];
        i++;          
    }
}
