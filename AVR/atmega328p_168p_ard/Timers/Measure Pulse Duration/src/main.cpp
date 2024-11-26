#define __AVR_ATmega168__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define CLOCK_PERIOD (1 / F_CPU)
#define TIM0_PERIOD (CLOCK_PERIOD * 256U)
#define TIM1_PERIOD (CLOCK_PERIOD * 65536U)
#define TIM2_PERIOD (CLOCK_PERIOD * 256U)

int16_t period;

ISR(PCINT2_vect){
  if (PIND & (1 << PD2)){
    period = TCNT1 * TIM1_PERIOD * 1024;
  }
  else
    TCNT1 = 0; // хранится значение таймера
}


int main(void){
  PORTD |= 1 << PD7; // set pin pull-up
  
  PCICR |= 1 << PCIE2;
  PCMSK2 |= 1 << PCINT18;
  
  sei();

  TCCR1A = 0x00;  // set normal state tim1
  TCCR1B |= 1 << CS12 | 1 << CS10; // set presceller 1/1024
  while(1){

  }
  return 0;
}