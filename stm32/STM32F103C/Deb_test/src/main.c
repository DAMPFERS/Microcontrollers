#include "stm32f1xx.h"

void delay(volatile uint32_t count);


int main(void) {
    char a = 31;
    char b = a - 10;
    // Включение тактирования порта GPIOC
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Настройка PC13 на выход
    GPIOC->CRH &= ~GPIO_CRH_MODE13;
    GPIOC->CRH |= GPIO_CRH_MODE13_0; // Output mode, max speed 10 MHz
    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // General purpose push-pull

    while (1) {
        GPIOC->BSRR = GPIO_BSRR_BR13; // Включить светодиод
        delay(500000);
        GPIOC->BSRR = GPIO_BSRR_BS13; // Выключить светодиод
        delay(500000);
        a++;
        b--;
    }
}

void delay(volatile uint32_t count) {
    while (count--) {}
    return;
}