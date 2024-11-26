#define __AVR_ATmega168__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect){
  PORTD ^= 1 << 7;
}

int main(void){
  DDRD = 1 << PD7; // pin output
  PORTD = 1 << PD2; // pin interrupt input_pullup

  EICRA = 1 << ISC00; //any logical changes on INT0
  EIMSK = 1 << INT0; //enable INT0

  sei();          // enable interruprts globally
  while (1)
  {
    _delay_ms(5000);
  }
  
}