#include <avr/io.h>
#include "../include/pwm.h"

void setup_PWM(void){
    OCR0A = 191;
}
