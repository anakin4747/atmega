#include <avr/io.h>
#include <util/delay.h>
#include "../include/pwm.h"


int main(void){
    DDRB |= (1 << DDB5);

    setup_PWM();

    while(1){
        PORTB |= 1 << PORTB5;

        _delay_ms(3000);

        PORTB &= ~(1 << PORTB5);

        _delay_ms(3000);
    }
}
