#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f401xx.h"

#define CR1_CEN          (1U << 0)
#define SR_UIF           (1U << 0)

#define OC4_TOGGLE       ((1U << 13) | (1U << 12))
#define OC4_PWM          (0x6 << 12)
#define CCER_CC4E        (1U << 12)

void timer_setup(void);
void timer_pwm_set_duty_cycle(float duty_cycle);

void tim2_1hz_init(void);
void tim2_pa3_out_compare(void);
void tim2_pa3_pwm(void);

#endif