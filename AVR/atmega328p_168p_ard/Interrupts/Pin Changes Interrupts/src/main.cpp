#define __AVR_ATmega168__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(PCINT2_vect){
  PORTD ^= 1 << PD7;
}

int main(void){
  DDRD |= 1 << PD7;// set pin 7 as out 
  PORTD |= 1 << PD2 | 1 << PD3; //enable internal pull-up on pin 2

  PCICR |= 1 << PCIE2;    //  выбор пинов с 16 по 23 (PCINT...)
  PCMSK2 |= 1 << PCINT18 | 1 << PCINT19; //  прерывания на 2й и 3й пин

  sei();

  while(1){
    _delay_ms(5000);
  }
  return 0;
}