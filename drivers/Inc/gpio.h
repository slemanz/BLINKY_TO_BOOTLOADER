#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f401xx.h"



/*
 * This is a configuration structure for a GPIO pin
 */

typedef struct
{
	uint8_t GPIO_PinNumber; 	/*!< possible modes from @GPIO_PIN_NUMBER >*/
	uint8_t GPIO_PinMode;		/*!< possible modes from @GPIO_PIN_MODES >*/
	uint8_t	GPIO_PinSpeed; 		/*!< possible modes from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinPuPdControl;/*!< possible modes from @GPIO_PIN_PUPD >*/
	uint8_t GPIO_PinOPType;		/*!< possible modes from @GPIO_PIN_OP_TYPE >*/
	uint8_t GPIO_PinAltFunMode;	/*!< possible modes from @GPIO_PIN_ >*/
}GPIO_PinConfig_t;


/*
 * This is a Handle structure for a GPIO pin
 */

typedef struct
{
	GPIO_RegDef_t *pGPIOx; /* hold the base address of the GPIO port which the pin belongs */
	GPIO_PinConfig_t GPIO_PinConfig; /* this holds GPIO pin configuration settings */
}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBER
 * GPIO pin possible number
 */

#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15


/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */

#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4 // input type falling
#define GPIO_MODE_IT_RT		5 // input type rising
#define GPIO_MODE_IT_RFT	6 // input type rising and falling


/* 
 * @GPIO_PIN_SPEED
 * GPIO pin possible output speeds
 */

#define GPIO_SPEED_LOW		0
#define	GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3


/*
 * @GPIO_PIN_SPEED
 * GPIO pin possible output types
 */

#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1


/*
 * @GPIO_PIN_PUPD
 * GPIO pin pull up and pull down configuration
 */

#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

/*
 * @GPIO_PIN_ALTFN
 * GPIO alternate functions
 */

#define GPIO_PIN_ALTFN_0            0
#define GPIO_PIN_ALTFN_1            1
#define GPIO_PIN_ALTFN_2            2
#define GPIO_PIN_ALTFN_3            3
#define GPIO_PIN_ALTFN_4            4
#define GPIO_PIN_ALTFN_5            5
#define GPIO_PIN_ALTFN_6            6
#define GPIO_PIN_ALTFN_7            7


// GPIO_PIN_ALTFN_SPECIF_FUNCTION

#define PA5_ALTFN_TIM2_CH1			GPIO_PIN_ALTFN_1
#define PA2_ALTFN_UART2_TX			GPIO_PIN_ALTFN_7
#define PA3_ALTFN_UART2_RX			GPIO_PIN_ALTFN_7



/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

/*
 *  Peripheral clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);


/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


/*
 * Data read and write
 */
uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);


/*
 * IRQ configuration and ISR handling
 */

// implement later

/*
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);
*/


















#endif /* INC_GPIO_H_ */