#include <stdint.h>

/* Function prototypes */
extern int main(void);
void Reset_Handler(void);
void sys_tick_handler(void);
void Default_Handler(void);

/* Symbols defined in the linker script */
extern uint32_t _data_loadaddr;  // Load address of .data section in flash
extern uint32_t _data;           // Start of .data section in RAM
extern uint32_t _edata;          // End of .data section in RAM
extern uint32_t _sbss;           // Start of .bss section in RAM (you need to define this symbol in linker)
extern uint32_t _ebss;           // End of .bss section in RAM
extern uint32_t _stack;          // Initial stack pointer

/* Vector table in .isr_vector section */
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))(&_stack),    // Initial stack pointer
    Reset_Handler,                // Reset handler
    Default_Handler,              // NMI handler
    Default_Handler,              // HardFault handler
    Default_Handler,              // MemManage handler
    Default_Handler,              // BusFault handler
    Default_Handler,              // UsageFault handler
    0, 0, 0, 0,                  // Reserved
    Default_Handler,              // SVCall handler
    Default_Handler,              // DebugMonitor handler
    0,                           // Reserved
    Default_Handler,              // PendSV handler
    sys_tick_handler             // SysTick handler
};

/* Default handler implementation */
void Default_Handler(void) {
    while (1);
}

/* Reset handler implementation */
void Reset_Handler(void) {
    uint32_t *src, *dst;

    // Copy initialized data from flash to RAM
    src = &_data_loadaddr;
    dst = &_data;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    // Zero initialize .bss section
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    // Call the main function
    main();

    // Infinite loop if main returns
    while (1);
}
