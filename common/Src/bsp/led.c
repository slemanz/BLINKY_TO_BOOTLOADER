#include "bsp/led.h"

static led_t _leds[LED_NUM_MAX] = {0};

void led_setup(led_num_e led_num, IO_Interface_t *io)
{
    if(led_num >= LED_NUM_MAX || led_num < LED_NUM_1) return;

    _leds[led_num].set = io->write;
    _leds[led_num].toggle = io->toggle;
}

led_t *led_get(led_num_e led_num)
{
    if(led_num >= LED_NUM_MAX || led_num < LED_NUM_1) return NULL;

    return (led_t*)&_leds[led_num];
}