#include "stm32f401xx.h"


/**************************************************************************
 * @fn              - timer_PeriClockControl
 *
 * @brief           - This function enables or disables the peripheral clock
 *                    for the specified timer controller.
 *
 * @param[in]       - pTIMx: Base address of the TIM peripheral.
 * @param[in]       - EnorDi: ENABLE or DISABLE macro for clock control.
 *
 * @return          - none
 *
 * @Note            - none
 *
 **************************************************************************/

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



/**************************************************************************
 * @fn              - timer_pwm_init
 *
 * @brief           - This function initializes the PWM generation on the
 *                    specified timer. It configures the prescaler, autoreload,
 *                    and enables the timer.
 *
 * @param[in]       - pTIMHandle: Pointer to the structure that contains the
 *                    timer configurations and the address of the peripheral.
 *
 * @return          - none
 *
 * @Note            - none
 *
 **************************************************************************/

void timer_pwm_init(TIM_Handle_t *pTIMHandle)
{
    timer_PeriClockControl(pTIMHandle->pTIMx, ENABLE);

    pTIMHandle->pTIMx->PSC = pTIMHandle->TIM_Config.prescaler; 
    pTIMHandle->pTIMx->ARR = pTIMHandle->TIM_Config.auto_reload; 

    pTIMHandle->pTIMx->CNT = 0;  // clear counter
    pTIMHandle->pTIMx->CCMR[pTIMHandle->TIM_Config.channel/2] = (0x06 << (4 + 8*(pTIMHandle->TIM_Config.channel % 2))); // config mode (OCxM)
    pTIMHandle->pTIMx->CCER |= (0x1 << 4*(pTIMHandle->TIM_Config.channel)); // enable compare (CCxE)

    timer_pwm_set_duty_cycle(pTIMHandle, pTIMHandle->TIM_Config.initialDuty);
    //TIM2->CCR[0] = (26667/10) - 1; // 1/3 of period -> 33% duty cycle

    pTIMHandle->pTIMx->CR1 = CR1_CEN; // enable timer
}



/**************************************************************************
 * @fn              - timer_pwm_set_duty_cycle
 *
 * @brief           - This function sets the duty cycle of the PWM for the
 *                    specified timer.
 *
 * @param[in]       - pTIMHandle: Pointer to the structure that contains the
 *                    timer configurations and the address of the peripheral.
 * @param[in]       - duty_cycle: Desired duty cycle value (0 to 100).
 *
 * @return          - none
 *
 * @Note            - The duty cycle must be in the range of 0 to 100;
 *                    values outside this range will result in unexpected behavior.
 *
 **************************************************************************/

void timer_pwm_set_duty_cycle(TIM_Handle_t *pTIMHandle, float duty_cycle)
{
    // formula:
    //      duty cycle = (ccr / arr) * 100
    //      duty cycle / 100 = ccr / arr
    //      ccr = arr * (duty cycle / 100)
    const float raw_value = (float)(pTIMHandle->TIM_Config.auto_reload) * ( duty_cycle / 100.0f);
    pTIMHandle->pTIMx->CCR[pTIMHandle->TIM_Config.channel] = raw_value; 
}











/*
 *  FUNCTIONS CREATED TO TEST PERIPHERAL,
 *  in the future i'll delete
 */

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
    TIM2->CCMR[1] = OC4_TOGGLE;

    // enable tim2 ch4 in compare mode
    TIM2->CCER |= CCER_CC4E;


    // clear counter
    TIM2->CNT = 0;

    // enable timer
    TIM2->CR1 = CR1_CEN;
}

void tim2_pa3_pwm(void)
{
    // timer setup
    TIM2_PCLK_EN();

    //TIM2->PSC = 1600 - 1;
    //TIM2->ARR = 10000 - 1;
    TIM2->PSC = 10 - 1; // divided by 10
    TIM2->ARR = 26667 - 1; // divided by 26667 -> close to 60Hz

    TIM2->CNT = 0;  // clear counter
    TIM2->CCMR[1] = OC4_PWM;
    TIM2->CCER |= CCER_CC4E; // enable compare

    //TIM2->CCR4 = (10000/4) - 1; 
    TIM2->CCR[3] = (26667/100) - 1; // 1/3 of period -> 33% duty cycle

    // enable timer
    TIM2->CR1 = CR1_CEN;
}