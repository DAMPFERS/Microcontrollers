#define F_CPU 16000000UL
#define __AVR_ATmega168__

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRB |= 1 << PB5;
    while (1)
    {
        PORTB ^= 1 << PB5;
        _delay_ms(250.0);
    }
    
}