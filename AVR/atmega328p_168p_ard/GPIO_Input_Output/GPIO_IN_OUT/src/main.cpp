#define F_CPU 16000000
// #define __AVR_ATmega168__
 #define __AVR_ATmega328__



#include <avr/io.h>
#include <util/delay.h>

#define LOW_LEVEL 0
#define HIGH_LEVEL 1

int main(void){
  DDRB |= 1 << PB5;
  // DDRD |= 1 << PD2;
  // PORTD |= 1 << PD5;
  // char old_state_button = 0;
  while (1)  {
    // char new_state_button = (PIND & (1 << PD5)) == 0; 
    // if(new_state_button == LOW_LEVEL && old_state_button == HIGH_LEVEL)
      // PORTD ^= 1 << PD2;
    // old_state_button = new_state_button;   
    PORTB ^= 1 << PB2;
    _delay_ms(10);
  }

  
  return 0;
}