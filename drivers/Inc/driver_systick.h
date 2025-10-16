#ifndef DRIVER_SYSTICK_H_
#define DRIVER_SYSTICK_H_

#include "stm32f411xx.h"

#define TICK_HZ                 1000U
#define SYSTICK_TIM_CLK			HSI_CLOCK

#define SYSTICK_CTRL_ENABLE                 (1U << 0)
#define SYSTICK_CTRL_CLKSRC                 (1U << 2)
#define SYSTICK_CTRL_COUNTFLAG              (1U << 16)
#define SYSTICK_CTRL_TICKINT                (1U << 1)

void systick_init(uint32_t tick_hz);
uint64_t ticks_get(void);
void ticks_delay(uint64_t delay);

void systick_counter(uint8_t EnorDi);
void systick_interrupt(uint8_t EnorDi);
void systick_deinit(void);

#define MAX_DELAY   0xFFFFFFFF

#endif