#include <stdint.h>

// Base address definitions
#define RCC_BASE         (0x40023800UL)
#define GPIOA_BASE       (0x40020000UL)

// RCC registers
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))

// GPIOA registers
#define GPIOA_MODER      (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR        (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

// Bit definitions
#define RCC_AHB1ENR_GPIOAEN (1U << 0)  // Enable GPIOA clock
#define GPIO_MODER_MODER3_OUTPUT (1U << (3 * 2)) // Pin 3 as output
#define GPIO_ODR_ODR3 (1U << 3)         // Bit for output on pin 3

// Function prototype
void delay(volatile uint32_t count);

int main(void) {
    // Enable GPIOA clock
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set GPIOA pin 3 as output
    GPIOA_MODER &= ~(3U << (3 * 2)); // Clear MODER3
    GPIOA_MODER |= GPIO_MODER_MODER3_OUTPUT; // Set MODER3 to 01 (output)

    // Main loop
    while (1) {
        // Toggle GPIOA pin 3
        GPIOA_ODR ^= GPIO_ODR_ODR3;

        // Delay
        delay(1000000); // Adjust the delay value as necessary
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
