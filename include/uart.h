#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#define BAUD_RATE 103

void setupUART(void);

void sendOverUART(uint16_t adcRead);


#endif //  __UART_H__
