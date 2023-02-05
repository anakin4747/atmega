#include <avr/io.h>
#include "../include/adc.h"
#include "../include/led.h"
#include <util/delay.h>


int main(void){

    unsigned int last_reading = 0, reading = 0;
    led_set_output();

    while(1){

        led_update(reading, last_reading);
        last_reading = reading++;

        _delay_ms(100);

        if(reading > 4){
            reading = 0;
        }
    }
}
