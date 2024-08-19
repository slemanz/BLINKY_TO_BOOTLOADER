#include "stm32f401xx.h"


// Function prototype
void delay(volatile uint32_t count);

void gpio_setup(void)
{
    // Set GPIOA pin 3 as output


}


int main(void)
 {

    while (1) {

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
