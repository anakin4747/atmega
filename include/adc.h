#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>

extern volatile uint16_t adc_result;

void adc_init(void);

#endif // __ADC_H__
