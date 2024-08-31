#include "stm32f401xx.h"

void timer_PeriClockControl(TIM_RegDef_t *pTIMx, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{
		if		(pTIMx == TIM2) TIM2_PCLK_EN();
	}else
	{
		if		(pTIMx == TIM2) TIM2_PCLK_DI();
	}
}

void timer_setup(void)
{
    timer_pwm_init(TIM2);

    // set mode (later todo an init function to timer)
    //TIM2->CR1 
}

void timer_pwm_set_duty_cycle(float duty_cycle)
{

}

void timer_pwm_init(TIM_RegDef_t *pTIMx)
{

}





















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

void tim2_pa3_out_compare(void)
{
    // config PA3
    GPIOA_PCLK_EN();
    GPIOA->MODER &= ~(1 << 6); 
    GPIOA->MODER |=  (1 << 7); // pa3 in altfn
    GPIOA->AFR[0] &= (0xF << 12);
    GPIOA->AFR[0] |= (0x1 << 12); // altfn tim2 ch4


    // enable clock acess
    TIM2_PCLK_EN();

    // set prescaler value
    TIM2->PSC = 1600 - 1; // 16 000 000 / 16000 = 10 000

    // set autoload value
    TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1 hz

    // set output compare toggle mode
    TIM2->CCMR2 = OC4_TOGGLE;

    // enable tim2 ch4 in compare mode
    TIM2->CCER |= CCER_CC4E;


    // clear counter
    TIM2->CNT = 0;

    // enable timer
    TIM2->CR1 = CR1_CEN;
}

void tim2_pa3_pwm(void)
{
    // config PA3
    GPIOA_PCLK_EN();
    GPIOA->MODER &= ~(1 << 6); 
    GPIOA->MODER |=  (1 << 7); // pa3 in altfn
    GPIOA->AFR[0] &= (0xF << 12);
    GPIOA->AFR[0] |= (0x1 << 12); // altfn tim2 ch4


    // timer setup
    TIM2_PCLK_EN();

    //TIM2->PSC = 1600 - 1;
    //TIM2->ARR = 10000 - 1;
    TIM2->PSC = 10 - 1; // divided by 10
    TIM2->ARR = 26667 - 1; // divided by 26667 -> close to 60Hz

    TIM2->CNT = 0;  // clear counter
    TIM2->CCMR2 = OC4_PWM;
    TIM2->CCER |= CCER_CC4E; // enable compare

    //TIM2->CCR4 = (10000/4) - 1; 
    TIM2->CCR4 = (26667/3) - 1; // 1/3 of period -> 33% duty cycle

    // enable timer
    TIM2->CR1 = CR1_CEN;
}