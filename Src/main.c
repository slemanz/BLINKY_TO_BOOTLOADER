#include "stm32f401xx.h"


// Function prototype
void delay(volatile uint32_t count);
uint32_t teste;

int main(void) {
    uint32_t teste_data;
    teste_data = 12;
    (void)teste_data;
    // Enable GPIOA clock
    teste = 12;
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    (void)teste;

    // Set GPIOA pin 3 as output
    GPIOA_MODER &= ~(3U << (3 * 2)); // Clear MODER3
    GPIOA_MODER |= GPIO_MODER_MODER3_OUTPUT; // Set MODER3 to 01 (output)

    // Main loop
    while (1) {
        // Toggle GPIOA pin 3
        GPIOA_ODR ^= GPIO_ODR_ODR3;

        // Delay
        delay(4000000); // Adjust the delay value as necessary
    }
}

void delay(volatile uint32_t count) {
    while (count-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

void reset_handler(void) {
    // Initialization code
    while (1) {
        // Main loop
    }
}
