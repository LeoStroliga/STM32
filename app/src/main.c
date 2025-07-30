//#define STM32F4
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/scb.h>
#include "core/system.h"
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>


#define BOOTLOADER_SIZE (0x8000U)


void usart_setup(void) {
    // Enable clocks
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);

    // Setup GPIO pins for USART2 TX (PA2) and RX (PA3)
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);

    // Setup USART
    usart_set_baudrate(USART2, 115200);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_enable(USART2);
}

void usart_send_string(const char *str) {
    while (*str) {
        usart_send_blocking(USART2, *str++);
    }
}


static void gpio_setup(void){  
    rcc_periph_clock_enable(RCC_GPIOC);
   gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
}



int main(void)
{
   
    system_setup();
    gpio_setup();
    gpio_set(GPIOC, GPIO13);
  

  
    uint64_t start_time = system_get_ticks();
    
  
    
    while(1)
    {
     
      if(system_get_ticks()-start_time>=5000)
        {
        gpio_toggle(GPIOC, GPIO13);
        start_time=system_get_ticks();
        }

    }

    return 0;
}
/*
int main(void) {
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
    //gpio_toggle(GPIOC, GPIO13);   // toggle LED
    while (1) {
        gpio_toggle(GPIOC, GPIO13);   // toggle LED
        for (int i = 0; i < 5000000; ++i) 
        {
            __asm__("nop");
        }
    }
}
*/
