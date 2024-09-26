/**************************************************************************************************
 * @file    uart.h
 * @brief   UART Driver Header for STM32F401xx
 * @details This header file provides definitions, macros, and function prototypes for
 *          configuring and using the UART peripheral in STM32F401xx microcontroller.
 * 
 *          - Bit position definitions for UART control and status registers.
 *          - Status flag definitions for UART operations.
 *          - Function prototypes for UART setup, data transmission, and reception.
 * 
 *          For more details, please check the equivalent .c file.
 * 
 * Author:  William Sleman (www.slemanz.com)
 **************************************************************************************************/
#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f401xx.h"

/*
 *  Bit position definions Uart
 */

#define UART_CR1_UE                 13
#define UART_CR1_M                  12
#define UART_CR1_PCE                10
#define UART_CR1_RXNEIE             5
#define UART_CR1_TE                 3
#define UART_CR1_RE                 2

#define UART_CR2_STOP               12

#define UART_SR_CTS                 9
#define UART_SR_TXE                 7
#define UART_SR_TC                  6
#define UART_SR_RXNE                5
#define UART_SR_ORE                 3




#define UART_CR1_UE_SHIFT             (1 << UART_CR1_UE)
#define UART_CR1_M_SHIFT              (1 << UART_CR1_M)
#define UART_CR1_PCE_SHIFT            (1 << UART_CR1_PCE)
#define UART_CR1_RXNEIE_SHIFT         (1 << UART_CR1_RXNEIE)
#define UART_CR1_TE_SHIFT             (1 << UART_CR1_TE)
#define UART_CR1_RE_SHIFT             (1 << UART_CR1_RE)

#define UART_CR2_STOP_SHIFT           (1 << UART_CR2_STOP)

#define UART_SR_CTS_SHIFT             (1 << UART_SR_CTS)
#define UART_SR_TXE_SHIFT             (1 << UART_SR_TXE)
#define UART_SR_TC_SHIFT              (1 << UART_SR_TC)
#define UART_SR_RXNE_SHIFT            (1 << UART_SR_RXNE)
#define UART_SR_ORE_SHIFT             (1 << UART_SR_ORE)

/*
 *  UART related status flags definitions
 */


#define UART_FLAG_CTS	                (UART_SR_TXE_CTS)
#define UART_FLAG_TXE	                (UART_SR_TXE_SHIFT)
#define UART_FLAG_TC                 	(UART_SR_TC_SHIFT)
#define UART_FLAG_RXNE              	(UART_SR_RXNE_SHIFT)
#define UART_FLAG_ORE                 	(UART_SR_ORE_SHIFT)

/*
 *  Functions Prototypes
 */

void uart_setup(void);
void uart_write(uint8_t* data, const uint32_t lenght);
void uart_write_byte(uint8_t data);
uint8_t uart_recv(UART_RegDef_t *pUARTx);
uint32_t uart_read(uint8_t *data, const uint32_t length);
uint8_t uart_read_byte(void);
bool uart_data_available(void);

bool UART_GetFlagStatus(UART_RegDef_t *pUARTx, uint32_t FlagName);



void UART_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);

#endif /* INC_UART_H_ */
