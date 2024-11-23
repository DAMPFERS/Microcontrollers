#define __AVR_ATmega168P__
#define F_CPU 16000000Ul
#define BAUD 9600UL
#define UBRL_value (F_CPU/(BAUD*16))-1

#define HEX 16
#define DEC 10
#define BIN 2

#include <avr/io.h>
#include <util/delay.h>

#define DT PD3
#define SCK PD2
#define GAIN 128

unsigned long readLoadCell_HX711();
void initUART(void);
void sendUART(char data);
void sendUART_String(const char* str);
void initPins_HX711(void);
void intInStrTranslate(unsigned long value, char* str, char base = DEC);
void uartPrintln_int(unsigned long value, char base = DEC);


int main(void){
  //DDRB = 1 << PB5;
  initPins_HX711();
  initUART();
  while (1)
  {
    uartPrintln_int(readLoadCell_HX711());
    //_delay_ms(150);
    //PORTB ^= 1 << PB5;
  }
  
  return 0;
}

unsigned long readLoadCell_HX711(){
  while (PIND & (1 << DT))
  ;
  unsigned long res = 0;

  for(char i = 0; i < 24; i++){
    PORTD |= 1 << SCK;
    _delay_us(1.0);
    PORTD &= ~(1 << SCK);
    _delay_us(1.0);
    res = (res << 1) | (0x01 & (PIND >> DT));
  }
  PORTD |= 1 << SCK;
  _delay_us(1.0);
  PORTD &= ~(1 << SCK);
  _delay_us(1.0);

  if(GAIN == 64){
    PORTD |= 1 << SCK;
    _delay_us(1.0);
    PORTD &= ~(1 << SCK);
    _delay_us(1.0);
    PORTD |= 1 << SCK;
    _delay_us(1.0);
    PORTD &= ~(1 << SCK);
    _delay_us(1.0);
  }
  else if (GAIN == 32){
    PORTD |= 1 << SCK;
    _delay_us(1.0);
    PORTD &= ~(1 << SCK);
    _delay_us(1.0);
  }
  return res ^ 0x800000;
}

void initUART(void){
  UBRR0L = UBRL_value;
  UBRR0H = UBRL_value >> 8;

  // Enable reciever and transmitter
  UCSR0B = 1 << TXEN0;
  // Set frame format: 8data, 2stop bit
  UCSR0C = 3 << UCSZ00;
  return;
}


void sendUART(char data){
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
  return;
}


void sendUART_String(const char* str){
  while (*str)
  {
    sendUART(*str++);
  }
  return;
}


void initPins_HX711(void){
  DDRD |= 1 << SCK;
  DDRD &= ~(1 << DT);
  PORTD &= ~(1 << SCK);
  return;
}


void intInStrTranslate(unsigned long value, char* str, char base){
  char buf[33];
  char* ptr = &buf[sizeof(buf) - 1];
  *ptr = '\0';

  do{
    unsigned long m = value;
    value /= base;
    char c = m - base * value;
    *--ptr = c < 10 ? c + '0' : c + 'A' - 10;
  } while (value);
  
  while (*ptr)
    *str++ = *ptr++;
  
  *str = '\0';
  return;
}


void uartPrintln_int(unsigned long value, char base){
  char buf[33];
  intInStrTranslate(value, buf, base);
  sendUART_String(buf);
  sendUART('\r');
  sendUART('\n');
  return;
}