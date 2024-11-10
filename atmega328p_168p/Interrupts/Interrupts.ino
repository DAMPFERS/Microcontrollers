#define F_CPU 8000000L


// interrupt 2 pin arduino (INT0)
ISR(INT0_vect){
  PORTD ^= 1 << 7;
}




int main(void){
  DDRD = (1 << 7); // pin output
  PORTD = (1 << 2); // pin interrupt input_pullup

  EICRA = 1 << 0; // any logical changes on INT0
  EIMSK = 1 << 0; // enable INT0
  sei();          // enable interruprts globally

  while (1) {
  _delay_ms(5000);
  }
}