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

## Achitecture

This embedded project follows a layered architecture divided into 5 distinct layers:

```
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
```

**[App](app/)** - The highest application layer containing the main function and
configuration files. This layer can implement either the main **[application](app/)** or
the **[bootloader](bootloader/)**, both of which are included in the project. It configures pinout
options and interfaces with the common modules.

**[Common](common/)** - An abstract framework layer that provides foundational services for the
application. It includes modules for "core" system functions, "comms"
communication protocols, "shared" utilities, and "bsp" (Board Support Package)
for hardware abstraction.

**[Interface](interface/)** - Acts as a bridge between the Common layer and Drivers layer,
facilitating easier microcontroller changes when needed. This abstraction layer
ensures that higher-level components remain independent of specific hardware
implementations.

**[Drivers](drivers/)** - Contains the hardware-specific driver implementations
that directly interact with microcontroller peripherals and external
components.

Hardware - The lowest layer representing the physical STM32F401 microcontroller and its peripherals.