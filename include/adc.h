#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>

#define CH0 0
#define CH1 1
#define CH2 2

#define FLOATFACTOR 100


void setupADC(void);
uint32_t adc_conversion(void);
uint32_t adc_read(uint8_t channel);

#endif // __ADC_H__
