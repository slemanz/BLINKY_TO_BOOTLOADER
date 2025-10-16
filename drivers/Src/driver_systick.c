#include "driver_systick.h"
#include "driver_clock.h"

uint64_t g_ticks = 0;
uint64_t g_ticks_p = 0;

static void ticks_increment(void)
{
	g_ticks += 1;
}

void systick_init(uint32_t tick_hz)
{
    uint32_t count_value = clock_get()/tick_hz;

    // clear the value of SVR (value reload)
    SYSTICK->LOAD &= ~(0x00FFFFFFFF);
    
    // load the value
    SYSTICK->LOAD |= count_value;

    // setting and enable
    SYSTICK->CTRL |= (1 << 1);
    SYSTICK->CTRL |= (1 << 2);

    SYSTICK->CTRL |= (1 << 0);
}

uint64_t ticks_get(void)
{
    INTERRUPT_DISABLE();
	g_ticks_p = g_ticks;
	INTERRUPT_ENABLE();

	return g_ticks_p;
}

void ticks_delay(uint64_t delay)
{
    uint64_t ticks_start = ticks_get();
    uint64_t wait = delay;

	if(wait < MAX_DELAY)
	{
		wait += 1;
	}

    while((ticks_get() - ticks_start) < wait)
    {
        __asm("NOP");
    }
}

void systick_counter(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        SYSTICK->CTRL = (SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_CLKSRC);
    }else
    {
        SYSTICK->CTRL &= ~(SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_CLKSRC);
    }
}

void systick_interrupt(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        SYSTICK->CTRL |= SYSTICK_CTRL_TICKINT;
    }else
    {
        SYSTICK->CTRL &= ~SYSTICK_CTRL_TICKINT;
    }
}

void systick_deinit(void)
{
    systick_counter(DISABLE);
    systick_interrupt(DISABLE);
}

void SysTick_Handler(void)
{
    ticks_increment();
}