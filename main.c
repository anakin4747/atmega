#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

int main(void){
    DDRB |= (1 << DDB5);
    OCR0A = 191;

    while(1){
        PORTB |= 1 << PORTB5;

        _delay_ms(3000);

        PORTB &= ~(1 << PORTB5);

        _delay_ms(3000);
    }
}
