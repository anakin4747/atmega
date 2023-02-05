#include <avr/io.h>
#include "../include/led.h"

const int pins[] = {PD3, PD4, PD5, PD6, PD7};


void led_set_output(void){
    DDRD |= (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);

}

void led_update(unsigned int reading, unsigned int last_reading){
    if(reading > 4 || last_reading > 4){
        return;
    }

    if(reading > last_reading){
        for(unsigned int i = reading; i > last_reading; i--){
            PORTD |= (1 << pins[i]);
        }
    } else { // reading < last_reading
        for(unsigned int i = last_reading; i > reading; i--){
            PORTD &= ~(1 << pins[i]);
        }
    }
}
