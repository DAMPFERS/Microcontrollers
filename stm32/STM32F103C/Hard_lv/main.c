#include "stm32f1xx_hal_conf.h"
#include <stdint.h>

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_gpio.h"
#include  "stm32f1xx_hal_cec.h"

void delay_RVV(uint32_t count);

int main(void){
    // Включаем тактирование порта C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Настраиваем PC13 как выход
    GPIOC->CRH &= ~GPIO_CRH_MODE13;  // Сбрасываем MODE13
    GPIOC->CRH |= GPIO_CRH_MODE13_1; // Устанавливаем MODE13 в "Output 2 MHz"
    GPIOC->CRH &= ~GPIO_CRH_CNF13;   // Устанавливаем CNF13 в "Push-pull"

    while (1){
        GPIOC->ODR ^= GPIO_ODR_ODR13; // Инвертируем состояние пина PC13
        delay_RVV(100000);
    }

    return 0;
}

void delay_RVV(uint32_t count){
    while (count--)
    {
        __asm("NOP");
    }
}
