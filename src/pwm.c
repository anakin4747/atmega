#include <avr/io.h>

void setup_PWM(void){
    OCR0A = 191;
}
