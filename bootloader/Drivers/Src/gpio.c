#include "stm32f401xx.h"

/**************************************************************************
 * @fn				- GPIO_PeriClockControl
 *
 * @brief			- this functions enable and disables peripheral clock
 * 					  for the given GPIO port
 *
 * @param[in]		- base address of the gpio peripheral
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @Note			- none
 *
 */


void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if		(pGPIOx == GPIOA) GPIOA_PCLK_EN();
		else if	(pGPIOx == GPIOB) GPIOB_PCLK_EN();
		else if	(pGPIOx == GPIOC) GPIOC_PCLK_EN();
		else if	(pGPIOx == GPIOD) GPIOD_PCLK_EN();
		else if	(pGPIOx == GPIOE) GPIOE_PCLK_EN();
		else if	(pGPIOx == GPIOH) GPIOH_PCLK_EN();
	}else
	{
		if		(pGPIOx == GPIOA) GPIOA_PCLK_DI();
		else if	(pGPIOx == GPIOB) GPIOB_PCLK_DI();
		else if	(pGPIOx == GPIOC) GPIOC_PCLK_DI();
		else if	(pGPIOx == GPIOD) GPIOD_PCLK_DI();
		else if	(pGPIOx == GPIOE) GPIOE_PCLK_DI();
		else if	(pGPIOx == GPIOH) GPIOH_PCLK_DI();
	}
}

/**************************************************************************
 * @fn				- GPIO_Init
 *
 * @brief			- this function config the given GPIO pin handle
 *
 * @param[in]		- GPIO handle struct
 *
 * @return			- none
 *
 * @Note			- none
 *
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    // enable clock to the port
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	uint32_t temp = 0; // temporary register

	// 1. configure the mode of the gpio pin
	
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
		pGPIOHandle->pGPIOx->MODER |= temp; // setting
	}else
	{
		//1. configure interrupt mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// configure the FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			// good practice: clear corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			// configure the RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			// good practice: clear corresponding FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);


		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// configure both (FTSR and RTSR)
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		// 2. configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;

		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = (portcode << (temp2*4));


		// 3. enable the exti interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	// 2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;


	// 3. configure the pupd settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;


	// 4. configure the output type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;


	// 5. configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint32_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0x0F << (4*temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2));
	}
}

/**************************************************************************
 * @fn				- GPIO_DeInit
 *
 * @brief			- de init a port of GPIO
 *
 * @param[in]		- base address of gpio peripheral
 *
 * @return			- none
 *
 * @Note			- none
 *
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if		(pGPIOx == GPIOA) GPIOA_REG_RESET();
	else if	(pGPIOx == GPIOB) GPIOB_REG_RESET();
	else if	(pGPIOx == GPIOC) GPIOC_REG_RESET();
	else if	(pGPIOx == GPIOD) GPIOD_REG_RESET();
	else if	(pGPIOx == GPIOE) GPIOE_REG_RESET();
	else if	(pGPIOx == GPIOH) GPIOH_REG_RESET();
}




/**************************************************************************
 * @fn				- GPIO_ReadFromInputPin
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 *
 */

uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x01);

	return value;
}



/**************************************************************************
 * @fn				- GPIO_ReadFromInputPort
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 *
 */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);

	return value;
}

/**************************************************************************
 * @fn				- GPIO_WriteToOutputPin
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 *
 */

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// write 1 to the output data register at the bitfield corresponding to the pin number
		pGPIOx->ODR |= (1 << PinNumber);
	}else
	{
		// write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

/**************************************************************************
 * @fn				- GPIO_ToggleOutputPin
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 *
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}