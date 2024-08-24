#include "stm32f401xx.h"

void tim2_1hz_init(void)
{
    // enable clock acess
    TIM2_PCLK_EN();

    // set prescaler value
    TIM2->PSC = 1600 - 1; // 16 000 000 / 16000 = 10 000

    // set autoload value
    TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1 hz

    // clear counter
    TIM2->CNT = 0;

    // enable timer
    TIM2->CR1 = CR1_CEN;
}


