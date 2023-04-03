#ifndef __MPPT_H__
#define __MPPT_H__

#include <stdint.h>
#define CHARGED_BATT_VOLTAGE_X100 1260
#define DELTA 5

void mppt(uint32_t inputVoltage, 
	  uint32_t inputCurrent, 
	  uint32_t battVoltage);

#endif // __MPPT_H__
