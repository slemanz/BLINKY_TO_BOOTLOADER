#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_

// this header file describes the microcontroller
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#define __vo volatile


/*******************START: Processor Specific Details *************************/
/*
 * 	ARM-Cortex Mx Processor NVIC ISERx register addresses
 */

#define NVIC_ISER0 						((__vo uint32_t*)0xE000E100UL)
#define NVIC_ISER1 						((__vo uint32_t*)0xE000E104UL)
#define NVIC_ISER2 						((__vo uint32_t*)0xE000E108UL)
#define NVIC_ISER3 						((__vo uint32_t*)0xE000E10CUL)

/*
 * 	ARM-Cortex Mx Processor NVIC ISERx register addresses
 */

#define NVIC_ICER0 						((__vo uint32_t*)0xE000E180UL)
#define NVIC_ICER1 						((__vo uint32_t*)0xE000E184UL)
#define NVIC_ICER2 						((__vo uint32_t*)0xE000E188UL)
#define NVIC_ICER3 						((__vo uint32_t*)0xE000E18CUL)

/*
 * ARm Cortex Mx Processor Priority Regesiter Address Calculation
 */

#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE000E400UL)

#define NO_PR_BITS_IMPLEMENTED 		4



/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR						0x08000000U
#define SRAM1_BASEADDR						0x20000000U
#define ROM_BASEADDR						0x1FFF 0000 	/* system memory */
#define SRAM1 								SRAM1_BASEADDR

/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASE							0x40000000U
#define APB1PERIPH_BASE						PERIPH_BASE
#define APB2PERIPH_BASE						0x40010000U
#define AHB1PERIPH_BASE						0x40020000U
#define AHB2PERIPH_BASE						0x50000000U


/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 */

#define GPIOA_BASEADDR						(AHB1PERIPH_BASE + 0x0000U)
#define GPIOB_BASEADDR						(AHB1PERIPH_BASE + 0x0400U)
#define GPIOC_BASEADDR						(AHB1PERIPH_BASE + 0x0800U)
#define GPIOD_BASEADDR						(AHB1PERIPH_BASE + 0x0C00U)
#define GPIOE_BASEADDR						(AHB1PERIPH_BASE + 0x1000U)
#define GPIOH_BASEADDR						(AHB1PERIPH_BASE + 0x1C00U)

#define RCC_BASEADDR						(AHB1PERIPH_BASE + 0x3800U)


/*
 * Base addresses of peripherals which are hanging on APB1 bus
 */

#define I2C1_BASEADDR						(APB1PERIPH_BASE + 0x5400U)
#define I2C2_BASEADDR						(APB1PERIPH_BASE + 0x5800U)
#define I2C3_BASEADDR						(APB1PERIPH_BASE + 0x5C00U)

#define SPI1_BASEADDR						(APB2PERIPH_BASE + 0x3000U)
#define SPI2_BASEADDR						(APB1PERIPH_BASE + 0x3800U)
#define SPI3_BASEADDR						(APB1PERIPH_BASE + 0x3C00U)

#define USART2_BASEADDR						(APB1PERIPH_BASE + 0x4400U)


/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */

#define EXTI_BASEADDR						(APB2PERIPH_BASE + 0x3C00U)
#define SYSCFG_BASEADDR						(APB2PERIPH_BASE + 0x3800U)
#define PWR_BASEADDR                        (APB1PERIPH_BASE + 0x7000UL)

#define SPI1_BASEADDR						(APB2PERIPH_BASE + 0x3000U)
#define SPI4_BASEADDR						(APB2PERIPH_BASE + 0x3400U)

#define USART1_BASEADDR						(APB2PERIPH_BASE + 0x1000U)
#define USART6_BASEADDR						(APB2PERIPH_BASE + 0x1400U)

/*
 *  Base adress of systick	and timers
 */

#define SCS_BASE            				(0xE000E000UL)
#define SYSTICK_BASEADDR					(SCS_BASE + 0x0010UL)

#define TIM2_BASEADDR						(APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASEADDR						(APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASEADDR						(APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASEADDR						(APB1PERIPH_BASE + 0x0C00UL)
#define RTC_BASEADDR                        (APB1PERIPH_BASE + 0x2800UL)

/*
 *  Base adress of UART
 */

#define UART2_BASEADDR						(APB1PERIPH_BASE + 0x4400U)

/*
 *  Base adress of ADC
 */

#define ADC1_BASEADDR                       (APB2PERIPH_BASE + 0x2000U)

/*******************peripheral register definition structures*******************/

typedef struct
{
	__vo uint32_t MODER; /* configure the mode of pin 			address offset: 0x00 */
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

typedef struct
{
	__vo uint32_t CR; 			// 0x00
	__vo uint32_t PLLCFGR;		// 0x04
	__vo uint32_t CFGR;			//0x08
	__vo uint32_t CIR;			// 0x0C
	__vo uint32_t AHB1RSTR;		// 0x10
	__vo uint32_t AHB2RSTR;		// 0x14
	__vo uint32_t reserved[2];
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t reserved1[2];
	__vo uint32_t AHB1ENR;		//
	__vo uint32_t AHB2ENR;
	__vo uint32_t reserved2[2];
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t reserved3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t reserved4[2];
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	__vo uint32_t reserved5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t reserved6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	__vo uint32_t DCKCFGR;
}RCC_RegDef_t;

typedef struct{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	__vo uint32_t reserved[2];
	__vo uint32_t CMPCR;
}SYSCFG_RegDef_t;

typedef struct
{
    __vo uint32_t CR;           /*!< PWR power control register,        Address offset 0x00 */
    __vo uint32_t CSR;          /*!< PWR power control/status register, Address offset 0x04 */
} PWR_TypeDef;

typedef struct{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

typedef struct
{
  __vo uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __vo uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __vo uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __vo uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
}SysTick_RegDef_t;

typedef struct
{
	__vo uint32_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
  	__vo uint32_t CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
	__vo uint32_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
	__vo uint32_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
	__vo uint32_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
	__vo uint32_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
	__vo uint32_t CCMR[2];     /*!< TIM capture/compare mode register,   Address offset: 0x18 */
	__vo uint32_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
	__vo uint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
	__vo uint32_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
	__vo uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
	__vo uint32_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
	__vo uint32_t CCR[4];      /*!< TIM capture/compare register,        Address offset: 0x34 */
	__vo uint32_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
	__vo uint32_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
	__vo uint32_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
	__vo uint32_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
}TIM_RegDef_t;

typedef struct
{
  __vo uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  __vo uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  __vo uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  __vo uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  __vo uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  __vo uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  __vo uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
}UART_RegDef_t;

typedef struct
{
    __vo uint32_t SR;     /*!< ADC status register,                         Address offset: 0x00 */
    __vo uint32_t CR1;    /*!< ADC control register 1,                      Address offset: 0x04 */
    __vo uint32_t CR2;    /*!< ADC control register 2,                      Address offset: 0x08 */
    __vo uint32_t SMPR1;  /*!< ADC sample time register 1,                  Address offset: 0x0C */
    __vo uint32_t SMPR2;  /*!< ADC sample time register 2,                  Address offset: 0x10 */
    __vo uint32_t JOFR1;  /*!< ADC injected channel data offset register 1, Address offset: 0x14 */
    __vo uint32_t JOFR2;  /*!< ADC injected channel data offset register 2, Address offset: 0x18 */
    __vo uint32_t JOFR3;  /*!< ADC injected channel data offset register 3, Address offset: 0x1C */
    __vo uint32_t JOFR4;  /*!< ADC injected channel data offset register 4, Address offset: 0x20 */
    __vo uint32_t HTR;    /*!< ADC watchdog higher threshold register,      Address offset: 0x24 */
    __vo uint32_t LTR;    /*!< ADC watchdog lower threshold register,       Address offset: 0x28 */
    __vo uint32_t SQR1;   /*!< ADC regular sequence register 1,             Address offset: 0x2C */
    __vo uint32_t SQR2;   /*!< ADC regular sequence register 2,             Address offset: 0x30 */
    __vo uint32_t SQR3;   /*!< ADC regular sequence register 3,             Address offset: 0x34 */
    __vo uint32_t JSQR;   /*!< ADC injected sequence register,              Address offset: 0x38*/
    __vo uint32_t JDR1;   /*!< ADC injected data register 1,                Address offset: 0x3C */
    __vo uint32_t JDR2;   /*!< ADC injected data register 2,                Address offset: 0x40 */
    __vo uint32_t JDR3;   /*!< ADC injected data register 3,                Address offset: 0x44 */
    __vo uint32_t JDR4;   /*!< ADC injected data register 4,                Address offset: 0x48 */
    __vo uint32_t DR;     /*!< ADC regular data register,                   Address offset: 0x4C */
} ADC_RegDef_t;

typedef struct
{
    __vo uint32_t CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
    __vo uint32_t CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
    __vo uint32_t SR;         /*!< SPI status register,                                Address offset: 0x08 */
    __vo uint32_t DR;         /*!< SPI data register,                                  Address offset: 0x0C */
    __vo uint32_t CRCPR;      /*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
    __vo uint32_t RXCRCR;     /*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
    __vo uint32_t TXCRCR;     /*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
    __vo uint32_t I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
    __vo uint32_t I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
} SPI_RegDef_t;

typedef struct
{
    __vo uint32_t CR1;        /*!< I2C Control register 1,     Address offset: 0x00 */
    __vo uint32_t CR2;        /*!< I2C Control register 2,     Address offset: 0x04 */
    __vo uint32_t OAR1;       /*!< I2C Own address register 1, Address offset: 0x08 */
    __vo uint32_t OAR2;       /*!< I2C Own address register 2, Address offset: 0x0C */
    __vo uint32_t DR;         /*!< I2C Data register,          Address offset: 0x10 */
    __vo uint32_t SR1;        /*!< I2C Status register 1,      Address offset: 0x14 */
    __vo uint32_t SR2;        /*!< I2C Status register 2,      Address offset: 0x18 */
    __vo uint32_t CCR;        /*!< I2C Clock control register, Address offset: 0x1C */
    __vo uint32_t TRISE;      /*!< I2C TRISE register,         Address offset: 0x20 */
    __vo uint32_t FLTR;       /*!< I2C FLTR register,          Address offset: 0x24 */
} I2C_RegDef_t;

typedef struct
{
    __vo uint32_t TR;         /*!< RTC time register,                                        Address offset: 0x00 */
    __vo uint32_t DR;         /*!< RTC date register,                                        Address offset: 0x04 */
    __vo uint32_t CR;         /*!< RTC control register,                                     Address offset: 0x08 */
    __vo uint32_t ISR;        /*!< RTC initialization and status register,                   Address offset: 0x0C */
    __vo uint32_t PRER;       /*!< RTC prescaler register,                                   Address offset: 0x10 */
    __vo uint32_t WUTR;       /*!< RTC wakeup timer register,                                Address offset: 0x14 */
    __vo uint32_t CALIBR;     /*!< RTC calibration register,                                 Address offset: 0x18 */
    __vo uint32_t ALRMAR;     /*!< RTC alarm A register,                                     Address offset: 0x1C */
    __vo uint32_t ALRMBR;     /*!< RTC alarm B register,                                     Address offset: 0x20 */
    __vo uint32_t WPR;        /*!< RTC write protection register,                            Address offset: 0x24 */
    __vo uint32_t SSR;        /*!< RTC sub second register,                                  Address offset: 0x28 */
    __vo uint32_t SHIFTR;     /*!< RTC shift control register,                               Address offset: 0x2C */
    __vo uint32_t TSTR;       /*!< RTC time stamp time register,                             Address offset: 0x30 */
    __vo uint32_t TSDR;       /*!< RTC time stamp date register,                             Address offset: 0x34 */
    __vo uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                       Address offset: 0x38 */
    __vo uint32_t CALR;       /*!< RTC calibration register,                                 Address offset: 0x3C */
    __vo uint32_t TAFCR;      /*!< RTC tamper and alternate function configuration register, Address offset: 0x40 */
    __vo uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                          Address offset: 0x44 */
    __vo uint32_t ALRMBSSR;   /*!< RTC alarm B sub second register,                          Address offset: 0x48 */
    uint32_t RESERVED7;       /*!< Reserved, 0x4C                                                                 */
    __vo uint32_t BKP0R;      /*!< RTC backup register 1,                                    Address offset: 0x50 */
    __vo uint32_t BKP1R;      /*!< RTC backup register 1,                                    Address offset: 0x54 */
    __vo uint32_t BKP2R;      /*!< RTC backup register 2,                                    Address offset: 0x58 */
    __vo uint32_t BKP3R;      /*!< RTC backup register 3,                                    Address offset: 0x5C */
    __vo uint32_t BKP4R;      /*!< RTC backup register 4,                                    Address offset: 0x60 */
    __vo uint32_t BKP5R;      /*!< RTC backup register 5,                                    Address offset: 0x64 */
    __vo uint32_t BKP6R;      /*!< RTC backup register 6,                                    Address offset: 0x68 */
    __vo uint32_t BKP7R;      /*!< RTC backup register 7,                                    Address offset: 0x6C */
    __vo uint32_t BKP8R;      /*!< RTC backup register 8,                                    Address offset: 0x70 */
    __vo uint32_t BKP9R;      /*!< RTC backup register 9,                                    Address offset: 0x74 */
    __vo uint32_t BKP10R;     /*!< RTC backup register 10,                                   Address offset: 0x78 */
    __vo uint32_t BKP11R;     /*!< RTC backup register 11,                                   Address offset: 0x7C */
    __vo uint32_t BKP12R;     /*!< RTC backup register 12,                                   Address offset: 0x80 */
    __vo uint32_t BKP13R;     /*!< RTC backup register 13,                                   Address offset: 0x84 */
    __vo uint32_t BKP14R;     /*!< RTC backup register 14,                                   Address offset: 0x88 */
    __vo uint32_t BKP15R;     /*!< RTC backup register 15,                                   Address offset: 0x8C */
    __vo uint32_t BKP16R;     /*!< RTC backup register 16,                                   Address offset: 0x90 */
    __vo uint32_t BKP17R;     /*!< RTC backup register 17,                                   Address offset: 0x94 */
    __vo uint32_t BKP18R;     /*!< RTC backup register 18,                                   Address offset: 0x98 */
    __vo uint32_t BKP19R;     /*!< RTC backup register 19,                                   Address offset: 0x9C */
} RTC_TypeDef;

/*
 * 	peripheral definitions (Peripheral base address typecasted to xxx_RegDef_t)
 */

#define GPIOA			((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB			((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC			((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD			((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE			((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH			((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC				((RCC_RegDef_t*)RCC_BASEADDR)

#define SYSCFG			((SYSCFG_RegDef_t*)SYSCFG_BASEADDR	)
#define PWR             ((PWR_TypeDef *)PWR_BASEADDR)

#define EXTI			((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSTICK         ((SysTick_RegDef_t*)SYSTICK_BASEADDR) 

#define TIM2			((TIM_RegDef_t*)TIM2_BASEADDR)
#define TIM3			((TIM_RegDef_t*)TIM3_BASEADDR)
#define TIM4			((TIM_RegDef_t*)TIM4_BASEADDR)
#define TIM5			((TIM_RegDef_t*)TIM5_BASEADDR)
#define RTC             ((RTC_TypeDef *)RTC_BASEADDR)

#define UART2 			((UART_RegDef_t*)UART2_BASEADDR)

#define ADC1            ((ADC_RegDef_t *)ADC1_BASEADDR)

#define SPI1            ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2            ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3            ((SPI_RegDef_t*)SPI3_BASEADDR)

#define I2C1            ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2            ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3            ((I2C_RegDef_t*)I2C3_BASEADDR)


/*
 * Clock enable macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1 << 7))


/*
 * Clock enable macros for I2Cx peripherals
 */

#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 << 23))


/*
 * Clock enable macros for SPIx peripherals
 */

#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()		(RCC->APB2ENR |= (1 << 13))

/*
 * Clock enable macros for USARTx peripherals
 */

#define UART1_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define UART2_PCLK_EN()		(RCC->APB1ENR |= (1 << 17))
#define UART6_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))


/*
 * Clock enable macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))

/*
 * Clock enable macros for TIMx peripherals
 */

#define TIM2_PCLK_EN()		(RCC->APB1ENR |= (1 << 0))
#define TIM3_PCLK_EN()		(RCC->APB1ENR |= (1 << 1))
#define TIM4_PCLK_EN()		(RCC->APB1ENR |= (1 << 2))
#define TIM5_PCLK_EN()		(RCC->APB1ENR |= (1 << 3))

/*
 * Clock enable macros for ADC peripherals
 */

#define ADC1_PCLK_EN()		(RCC->APB2ENR |= (1 << 8))


/*
 * Clock disable macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 7))


/*
 * Clock disable macros for I2Cx peripherals
 */

#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 23))


/*
 * Clock disable macros for SPIx peripherals
 */

#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 13))

/*
 * Clock disable macros for USARTx peripherals
 */

#define UART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define UART2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 17))
#define UART6_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 5))


/*
 * Clock disable macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))

/*
 * Clock disable macros for TIMx peripherals
 */

#define TIM2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 0))
#define TIM3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 1))
#define TIM4_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 2))
#define TIM5_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 3))

/*
 * Clock disable macros for ADC peripherals
 */

#define ADC1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 8))

/*
 * 	Macros to reset GPIOx peripherals
 */

#define GPIOA_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);}while(0)
#define GPIOB_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);}while(0)
#define GPIOC_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);}while(0)
#define GPIOD_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);}while(0)
#define GPIOE_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);}while(0)
#define GPIOH_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);}while(0)


/*
 *  Macro to give the code of a port
 */

#define GPIO_BASEADDR_TO_CODE(x)	  ( (x == GPIOA) ? 0 :\
										(x == GPIOB) ? 1 :\
										(x == GPIOC) ? 2 :\
										(x == GPIOD) ? 3 :\
										(x == GPIOE) ? 4 :\
										(x == GPIOH) ? 7 : 0 )



/*
 * some generic macros
 */

#define ENABLE 						1
#define	DISABLE 					0
#define _SET						ENABLE
#define _RESET						DISABLE
#define GPIO_PIN_SET				_SET
#define GPIO_PIN_RESET				_RESET
#define FLAG_SET					_SET
#define FLAG_RESET					_RESET


/*
 * IRQ numbers macros - the positions
 * IRQ (Interrupt Request)
 */

#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI3 		8
#define IRQ_NO_EXTI4 		9
#define IRQ_NO_EXTI5 		10
#define IRQ_NO_EXTI9_5 		23
#define IRQ_NO_EXTI15_10 	40

/*
 * IRQ Priority levels
 */

#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI15		15


#define MMIO32(addr) (*(volatile uint32_t *)(addr))

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


/*
 *		SCB
 */

#define SCB_BASE (0xE000ED00UL)
#define VTOR_OFFSET       MMIO32(SCB_BASE + 0x08U)

typedef struct
{
    __vo uint32_t CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
    __vo uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
    __vo uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
    __vo uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
    __vo uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
    __vo uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
    __vo uint8_t  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    __vo uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
    __vo uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
    __vo uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
    __vo uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
    __vo uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
    __vo uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
    __vo uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
    __vo uint32_t PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
    __vo uint32_t DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
    __vo uint32_t ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
    __vo uint32_t MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
    __vo uint32_t ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
    __vo uint32_t RESERVED0[5];
    __vo uint32_t CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
}SCB_RegDef_t;  

#define SCB                 ((SCB_RegDef_t*)SCB_BASE)

#define INTERRUPT_ENABLE()          do{__asm volatile ("MOV R0, #0x0"); __asm volatile("MSR PRIMASK, R0");}while(0)
#define INTERRUPT_DISABLE()         do{__asm volatile ("MOV R0, #0x1"); __asm volatile("MSR PRIMASK, R0");}while(0)
// #define STACK_RESET()               (__asm volatile("MSR MSP, %0": : "r" (STACK_START): ))


#define HSI_CLOCK				16000000U

#endif