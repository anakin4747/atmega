#ifndef __PWM_HEADER__
#define __PWM_HEADER__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif // F_CPU

void setupPWM(void);
void updatePWM(uint8_t dutyCycle);

#endif // __PWM_HEADER__
