#ifndef __PWM_HEADER__
#define __PWM_HEADER__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif // F_CPU

#include <stdint.h>

extern uint8_t duty;

void setupPWM(void);
void updatePWM(uint8_t dutyCycle);

#endif // __PWM_HEADER__
