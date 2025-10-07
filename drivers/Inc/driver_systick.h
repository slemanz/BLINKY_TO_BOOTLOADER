#ifndef DRIVER_SYSTICK_H_
#define DRIVER_SYSTICK_H_

#include "stm32f411xx.h"

#define TICK_HZ                 1000U
#define SYSTICK_TIM_CLK			HSI_CLOCK

void systick_init(uint32_t tick_hz);
uint64_t ticks_get(void);
void ticks_delay(uint64_t delay);

#define MAX_DELAY   0xFFFFFFFF

#endif