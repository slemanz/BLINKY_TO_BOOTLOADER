# Drivers

This directory contains all the bare-metal drivers developed for the STM32F401 microcontroller. Each driver is crafted from the ground up, providing direct access and control over the hardware. 

All functions within each driver are documented in their respective `.c` files, allowing you to understand their usage and functionalities. Additionally, the `.h` files contain the main macros for configuration and utilization of the drivers.

Feel free to explore the drivers below, which are well-documented and designed to facilitate your understanding of low-level programming and hardware interaction:

**GPIO Driver**

This driver provides a simple interface for configuring and controlling General-Purpose Input/Output (GPIO) pins.

- [driver_gpio.h](Inc/driver_gpio.h)
- [driver_gpio.c](Src/driver_gpio.c)

**Clock Driver**

- [driver_clock.h](Inc/driver_clock.h)
- [driver_clock.c](Src/driver_clock.c)

**Flash Driver**

- [driver_flash.h](Inc/driver_flash.h)
- [driver_flash.c](Src/driver_flash.c)

**Interrupt Driver**

- [driver_interrupt.h](Inc/driver_interrupt.h)
- [driver_interrupt.c](Src/driver_interrupt.c)

**Systick Driver**

- [driver_systick.h](Inc/driver_systick.h)
- [driver_systick.c](Src/driver_systick.c)

**Uart Driver**

- [driver_uart.h](Inc/driver_uart.h)
- [driver_uart.c](Src/driver_uart.c)



**Timer Driver**

This driver manages the Timer peripherals of the microcontroller.