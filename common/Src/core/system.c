#include "core/system.h"

static volatile uint64_t ticks = 0;

static void vector_setup(void)
{
    VTOR_OFFSET = BOOTLOADER_SIZE;
}

void systick_setup(void)
{
}

void system_setup(void)
{
    vector_setup();
    systick_setup();
}
