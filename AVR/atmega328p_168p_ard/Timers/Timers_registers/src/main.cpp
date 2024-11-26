#define __AVR_ATmega168__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect){
  PORTD ^= 1 << PD2;
}

int main(void){
  DDRD |= 1 << PD2;

  TCCR1A = 0x00;                    // tim1,  state, (WGM10, WGM11, WGM12, WGM13) = (0,0,(0)1,0)
  TCCR1B |= 1 << CS12 | 1 << CS10 | 1 << WGM12;  // presceler 1/1024 and set CTC ( top = OCR1A)
  OCR1A = 15624;                    // set output compare for interupt period of 1 second
  TIMSK1 = 1 << OCIE0A;             // enable interrupt or OCR1A

  sei();
  
  while (1){
    /* code */
  }
  return 0;
}
