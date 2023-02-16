#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>

#define CH0 0
#define CH1 1
#define CH2 2

extern unsigned char adcIndex;
extern uint16_t rawBatteryReading;
extern uint16_t rawVoltReading;
extern uint16_t rawCurrReading;

void setupADC(void);
void rotateADC(void);
void saveResult(uint16_t result);
uint16_t adc_read(void);

#endif // __ADC_H__