#ifndef __LED_H__
#define __LED_H__

void led_set_output(void);

void led_update(unsigned int reading, unsigned int last_reading);

extern const int pins[5];

#endif // __LED_H__
