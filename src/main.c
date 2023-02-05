#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>


int main(void){

    DDRB |= (1 << PB5);


    while(1){
        PORTB |= (1 << PB5);
        _delay_ms(100);
        PORTB &= ~(1 << PB5);
        _delay_ms(100);
    }
}
