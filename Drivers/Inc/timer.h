#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f401xx.h"

#define CR1_CEN          (1U << 0)
#define SR_UIF           (1U << 0)

void tim2_1hz_init(void);

#endif