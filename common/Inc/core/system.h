/**************************************************************************************************
 * @file    system.h
 * @brief   System Driver Header for STM32F401xx
 * @details This header file provides function prototypes, macro definitions, and configurations
 *          for the bare metal system drivers, including GPIO setup for LEDs and others.
 *          
 *          For more details, please check the equivalent .c file.
 * 
 * @author  William Sleman (www.slemanz.com)
 **************************************************************************************************/
#ifndef INC_SYSTEM_H_
#define INC_SYSTEM_H_

#include "stm32f411xx.h"

#define BOOTLOADER_SIZE (0x8000U)

#define CPU_FREQ        (16000000)
#define SYSTICK_FREQ    (1000) // in hz (1000hz == every 1 ms)

// Define led
#define LED_PORT        GPIOA
#define LED_PIN         GPIO_PIN_NO_5

// define uart pins

#define PORT_UART       (GPIOA)
#define PIN_TX          (GPIO_PIN_NO_3)
#define PIN_RX          (GPIO_PIN_NO_2)

void system_setup(void);

void systick_setup(void);
uint64_t system_get_ticks(void);
void gpio_setup(void);
void uart_pin_setup(void);



#endif