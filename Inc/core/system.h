#ifndef INC_SYSTEM_H_
#define INC_SYSTEM_H_

#include "stm32f401xx.h"

#define CPU_FREQ        (16000000)
#define SYSTICK_FREQ    (1000) // in hz (1000hz == every 1 ms)

void system_setup(void);

void systick_setup(void);
uint64_t system_get_ticks(void);

#endif