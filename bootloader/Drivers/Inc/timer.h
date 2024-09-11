#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f401xx.h"

// freq = system_freq / ((prescaler + 1) * (arr + 1))
#define PRESCALER           (10-1)
#define ARR_VALUE           (26667 - 1)

#define CR1_CEN          (1U << 0)
#define SR_UIF           (1U << 0)

#define OC4_TOGGLE       ((1U << 13) | (1U << 12))
#define OC4_PWM          (0x6 << 12)
#define CCER_CC4E        (1U << 12)


typedef struct
{
	uint32_t prescaler; 
    uint32_t auto_reload;
    uint8_t channel;  		/*!< possible modes from @TIM_CHANNEL >*/
	float initialDuty;
}TIM_Config_t;



/*
 * This is a Handle structure for a Timer
 */

typedef struct
{
	TIM_RegDef_t *pTIMx; 
	TIM_Config_t TIM_Config; 
}TIM_Handle_t;

/*
 * @TIM_CHANNEL
 * Timer possible channels
 */


#define TIM_CHANNEL1                0
#define TIM_CHANNEL2                1
#define TIM_CHANNEL3                2
#define TIM_CHANNEL4                3


void timer_PeriClockControl(TIM_RegDef_t *pTIMx, uint8_t EnorDi);

void timer_pwm_init(TIM_Handle_t *pTIMHandle);
void timer_pwm_set_duty_cycle(TIM_Handle_t *pTIMHandle, float duty_cycle);

void tim2_1hz_init(void);
void tim2_pa3_out_compare(void);
void tim2_pa3_pwm(void);

#endif