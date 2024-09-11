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


void systick_1hz_interrupt(void)
{
    // reload with number of clocks persecond
    SysTick->LOAD   = ONE_SEC_LOAD - 1;

    // clear systick current value register
    SysTick->VAL = 0;


    // Enable systick and select internal clk src
    SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

    // enable systick interrupt
    SysTick->CTRL |= CTRL_TICKINT;


}

void systick_set_frequency(uint32_t freq, uint32_t cpu_freq)
{
    // reload with number of clocks persecond
    SysTick->LOAD   = (cpu_freq/freq) - 1;

    // clear systick current value register
    SysTick->VAL = 0;
}

void systick_counter_enable(void)
{
    // Enable systick and select internal clk src
    SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
}

void systick_interrupt_enable(void)
{
    // enable systick interrupt
    SysTick->CTRL |= CTRL_TICKINT;
}