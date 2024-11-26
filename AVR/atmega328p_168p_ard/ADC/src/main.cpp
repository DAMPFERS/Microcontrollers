#define __AVR_ATmega168__
#define F_CPU 16000000UL

#include <avr/io.h>

#define A0 0x00
#define A1 0x01
#define A2 0x02
#define A3 0x03
#define A4 0x04
#define A5 0x05
#define A6 0x06
#define A7 0x07


int main(void){
  ADMUX |= A4; // set 4 chanal MUX (bits MUX*)
  ADMUX |= 1 << REFS1 | 1 << REFS0; // (0,0)-AREF; (0,1)-VCC; (1,1)-1.1V
  
  ADCSRA |= 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0; // presceler (F_CPU/128(1,1,1) =125 kHz), max F_ADC = 200 kHz

  ADCSRA |=  1 << ADEN; // ADEN-on/off ADC (enable); 

  ADCSRA |= 1 << ADSC; // ADSC-initialization of the ADC (START)
  while(bit_is_set(ADCSRA, ADSC));  // пока бит ADSC=1 идет считывание, ADSC=0, считывание закончено
  
  uint16_t value = ADCL | (ADCH << 8); // result in HIGH and LOW Bytes

  while(1){

  }
  return 0;
}