#include <stm32f1xx.h>


void delay(uint32_t count){
    while (count--)
    {
        __asm("NOP");
    }
    
}


int main(void){
    // Включаем тактирование порта C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Настраиваем PC13 как выход
    GPIOC->CRH &= ~GPIO_CRH_MODE13;  // Сбрасываем MODE13
    GPIOC->CRH |= GPIO_CRH_MODE13_1; // Устанавливаем MODE13 в "Output 2 MHz"
    GPIOC->CRH &= ~GPIO_CRH_CNF13;   // Устанавливаем CNF13 в "Push-pull"

    while (1){
        GPIOC->ODR ^= GPIO_ODR_ODR13; // Инвертируем состояние пина PC13
        delay(1000000);
    }
    
    
    return 0;
}