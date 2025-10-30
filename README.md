# Blinky to Bootloader

This project began as a simple LED blinky example and has evolved into a robust
STM32F411 application with a complete layered architecture. It now features a
UART-based bootloader with full Device Firmware Update (DFU) capabilities. The
entire codebase is developed for a bare-metal environment, providing deep
control over the hardware without relying on any IDE.

Every module is accompanied by clear documentation to demonstrate essential
embedded systems concepts and direct microcontroller interaction. This
repository serves as a practical reference for implementing a well-structured,
maintainable, and scalable embedded system on an STM32.

Inspired by [Low Byte Productions](https://www.youtube.com/@LowByteProductions) Youtube series.

---

## Achitecture

This embedded project follows a layered architecture divided into 5 distinct layers:

┌────────────────┐
│      APP       │  
├────────────────┤
│     COMMON     │  
├────────────────┤
│   INTERFACE    │  
├────────────────┤
│    DRIVERS     │  
├────────────────┤
│    HARDWARE    │  
└────────────────┘
