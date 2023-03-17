#ifndef __MPPT_H__
#define __MPPT_H__

#define DELTA 2
// In percent of duty cycle
#define FLOATFACTOR 100
#define CHARGED_BATT_VOLTAGE 400
// 4.0 volts multiplied by float factor

#include <stdint.h>

void mppt(uint32_t inputVoltage, uint32_t inputCurrent, uint32_t battVoltage);

#endif // __MPPT_H__
