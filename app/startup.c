#include <stdint.h>

/* Function prototypes */
extern int main(void);
void Reset_Handler(void);
void sys_tick_handler(void);
void Default_Handler(void);
//void usart2_isr(void);
void usart2_isr(void);

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
    (void (*)(void))(&_stack),  // Stack pointer
    Reset_Handler,              // Reset
    Default_Handler,            // NMI
    Default_Handler,            // HardFault
    Default_Handler,            // MemManage
    Default_Handler,            // BusFault
    Default_Handler,            // UsageFault
    0,0,0,0,                    // Reserved
    Default_Handler,            // SVCall
    Default_Handler,            // DebugMonitor
    0,                           // Reserved
    Default_Handler,            // PendSV
    sys_tick_handler,            // SysTick
    Default_Handler,            // WWDG
    Default_Handler,            // PVD
    Default_Handler,            // TAMP_STAMP
    Default_Handler,            // RTC_WKUP
    Default_Handler,            // FLASH
    Default_Handler,            // RCC
    Default_Handler,            // EXTI0
    Default_Handler,            // EXTI1
    Default_Handler,            // EXTI2
    Default_Handler,            // EXTI3
    Default_Handler,            // EXTI4
    Default_Handler,            // DMA1_Stream0
    Default_Handler,            // DMA1_Stream1
    Default_Handler,            // DMA1_Stream2
    Default_Handler,            // DMA1_Stream3
    Default_Handler,            // DMA1_Stream4
    Default_Handler,            // DMA1_Stream5
    Default_Handler,            // DMA1_Stream6
    Default_Handler,            // ADC
    Default_Handler,            // CAN1_TX
    Default_Handler,            // CAN1_RX0
    Default_Handler,            // CAN1_RX1
    Default_Handler,            // CAN1_SCE
    Default_Handler,            // EXTI9_5
    Default_Handler,            // TIM1_BRK_TIM9
    Default_Handler,            // TIM1_UP_TIM10
    Default_Handler,            // TIM1_TRG_COM_TIM11
    Default_Handler,            // TIM1_CC
    Default_Handler,            // TIM2
    Default_Handler,            // TIM3
    Default_Handler,            // TIM4
    Default_Handler,            // I2C1_EV
    Default_Handler,            // I2C1_ER
    Default_Handler,            // I2C2_EV
    Default_Handler,            // I2C2_ER
    Default_Handler,            // SPI1
    Default_Handler,            // SPI2
    Default_Handler,            // USART1
    usart2_isr,                // USART2 <-- here!
    Default_Handler,            // USART3
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
