# Drivers

This directory contains all the bare-metal drivers developed for the STM32F401 microcontroller. Each driver is crafted from the ground up, providing direct access and control over the hardware. 

All functions within each driver are documented in their respective `.c` files, allowing you to understand their usage and functionalities. Additionally, the `.h` files contain the main macros for configuration and utilization of the drivers.

Feel free to explore the drivers below, which are well-documented and designed to facilitate your understanding of low-level programming and hardware interaction:

**GPIO Driver**

This driver provides a simple interface for configuring and controlling General-Purpose Input/Output (GPIO) pins.

- [gpio.h](Inc/gpio.h)
- [gpio.c](Src/gpio.c)

**Timer Driver**

This driver manages the Timer peripherals of the microcontroller.