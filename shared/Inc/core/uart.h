#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f401xx.h"

/*
 *  it position definions Uart
 */

#define UART_CR1_M              12
#define UART_CR1_PCE            10
#define UART_CR1_TE              3
#define UART_CR1_RE              2

#define UART_CR2_STOP           12







/*
 *  Functions Prototypes
 */

void uart_setup(void);
void uart_write(uint8_t* data, const uint32_t lenght);
void uart_write_byte(uint8_t data);
uint32_t uart_read(uint8_t *data, const uint32_t length);
uint8_t uart_read_byte(void);
bool uart_data_available(void);

#endif /* INC_UART_H_ */
