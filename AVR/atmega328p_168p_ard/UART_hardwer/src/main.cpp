#define __AVR_ATmega168__
#define F_CPU 16000000UL


#include <avr/io.h>
#include <ctype.h>
#include <util/delay.h>
#include <test.h>


#define ASYNCHRONOUS_NORMAL_MODE 16
#define ASYNCHRONOUS_DOUBLE_SPEED_MODE 8
#define SYNCHRONOUS_MASTER_MODE 2

#define HEX 16
#define DEC 10
#define OCT 8
#define BIN 2


void UART_Init(unsigned long baud = 9600, unsigned char OPERATING_MODE = ASYNCHRONOUS_NORMAL_MODE);
void UART_SendByte(unsigned char data);
void UART_SendString(const char* str, char end = '\0');
void UART_SendUInt(unsigned long value, char base = DEC);
void UART_SendSInt(unsigned long value, char base = DEC);
void UART_SendFloat(unsigned long value, char base = DEC);

unsigned char UART_ReceiveByte(void);
void UART_ReceiveString(char* str, unsigned char max_lenght);
void UART_ReceiveInt(char* str, unsigned char max_lenght);
void UART_ReceiveFloat(char* str, unsigned char max_lenght);


void intInStrTranslate(unsigned long value, char* str, char base = DEC);
void StrInIntTranslate(unsigned long value, char* str, char base = DEC);

int main(void){
  UART_Init(9600);
  int a = RVVres();
  while(1){
    char buf[32];
    UART_ReceiveString(buf, sizeof(buf));
    UART_SendString(buf);
  }
  return 0;
}


void UART_Init(unsigned long baud, unsigned char OPERATING_MODE){
  uint16_t ubrl_value = (F_CPU/(baud * OPERATING_MODE))-1;
  UBRR0L = (unsigned char) ubrl_value;
  UBRR0H = (unsigned char)(ubrl_value >> 8);
  //UBRR0L = UBRL_value;
  //UBRR0H = UBRL_value >> 8;

  UCSR0B |= 1 << TXEN0 | 1 << RXEN0; // Enable reciever and transmitter | 1 << RXEN0;
  //UCSR0C = 1 << USBS0 | 3 << UCSZ00; // Set frame format: 8data, 2stop bit
  UCSR0C |= 1 << UCSZ00 | 1 << UCSZ01; // Set frame format: 8data
  UCSR0C &= ~(1 << USBS0);             // 2stop bit
  if(OPERATING_MODE == SYNCHRONOUS_MASTER_MODE)
    UCSR0C |= 1 << UMSEL00;
  return;
}


void UART_SendByte(unsigned char data){
  while(!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = data;
  return;
}


void UART_SendString(const char* str, char end){
  while(*str)
    UART_SendByte(*str++);
  if (end != '\0') UART_SendByte(end);
  return;
}


void UART_SendUInt(unsigned long value, char base){
  char buf[33];
  intInStrTranslate(value, buf, base);
  UART_SendString(buf);
  UART_SendByte('\r');
  UART_SendByte('\n');
}


void intInStrTranslate(unsigned long value, char* str, char base){
  char buf[33];
  char* ptr = &buf[sizeof(buf) - 1];
  *ptr = '\0';
  do{
    unsigned long m = value;
    value /= base;
    char c = m - base * value;
    *--ptr = c < 10 ? c + '0' : c - 10 + 'A' ;
  } while (value);

  while(*ptr)
    *str++ = *ptr++; 
  *str = '\0';
  return;
}


unsigned char UART_ReceiveByte(void){
  while(!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

void UART_ReceiveString(char* str, unsigned char max_lenght){
  for(unsigned char i = 0; i < max_lenght - 1; i++){
    unsigned char receivedChar = UART_ReceiveByte();
    if (receivedChar == '\r' || receivedChar == '\n'){
      *str = '\0';
      break;
    }
    *str++ = receivedChar;
  }
  *str = '\0';
  return;
}