#include "bsp/button.h"

static button_t _buttons[BUTTON_NUM_MAX] = {0};

void button_setup(button_num_e button_num, IO_Interface_t *io)
{
    if(button_num >= BUTTON_NUM_MAX || button_num < BUTTON_NUM_1) return;

    _buttons[button_num].read = io->read;
}

button_t *button_get(button_num_e button_num)
{
    if(button_num >= BUTTON_NUM_MAX || button_num < BUTTON_NUM_1) return NULL;

    return (button_t*)&_buttons[button_num];
}