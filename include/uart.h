#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#define BAUD_RATE 103

void setupUART(void);

void sendOverUART(const char *message, uint16_t adcRead, uint8_t channel);


#endif //  __UART_H__
