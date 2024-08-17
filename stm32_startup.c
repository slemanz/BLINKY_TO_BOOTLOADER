#include <stdint.h>

#define SRAM_START      0x20000000U
#define SRAM_SIZE       (96 * 1024) // 96K bytes
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))

#define STACK_START     (SRAM_END)

void Reset_handler(void);
void NMI_Handler(void)          __attribute__((section("Default_Handler"))); 
void HardFault_Handler(void)          __attribute__((section("Default_Handler"))); 

uint32_t vectors[] __attribute__((section(".isr_vector")))= {
    STACK_START,
    (uint32_t)(&Reset_Handler),
    (uint32_t)(&NMI_Handler)
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{

}
