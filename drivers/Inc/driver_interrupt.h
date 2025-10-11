#ifndef INC_DRIVER_INTERRUPT_H_
#define INC_DRIVER_INTERRUPT_H_

#include "stm32f411xx.h"

#define IRQ_NO_UART2            38

/********************************************************************************************
 *                              APIs supported by this driver                               *
 *                  for more information check the function definitions                     *
 ********************************************************************************************/

void interrupt_Config(uint8_t IRQNumber, uint8_t EnorDi);


#endif /* INC_DRIVER_INTERRUPT_H_ */