#define F_CPU 8000000L

int main(void){

  DDRD |= (1 << 7) | (1 << 3); // set 7 and 3 bit output
  PORTD |= (1 << 2);           // set 2 bit input_pullup



  while (1) {

    if (PIND & (1 << 2) == 0){
      PORTD |= (1 << 7); // set 7 high level
      _delay_ms(10);
    }
    else{
      PORTD ^= (1 << 7); // set 7 low level
      _delay_ms(10);
    }
    
  }

}