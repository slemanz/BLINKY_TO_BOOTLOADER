#include "stm32f401xx.h"

void systickDelayMs(int delay)
{
    // reload with number of clocks per ms
    SysTick->LOAD = SYSTICK_LOAD_VAL;

    // Clear systick current value register
    SysTick->VAL = 0;

    // Enable systick and select inter clksrc
    SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

    for(int i = 0; i < delay; i++)
    {
        // wait until the COUNTFLAG is set
        while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
    }

    SysTick->CTRL = 0;
}