#include "stm32f401xx.h"

void systickDelayMs(int n)
{
    // configure systick
    SysTick->LOAD = SYSTICK_LOAD_VAL;
}