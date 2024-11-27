#include <avr/io.h>
#include <uart_soft_RVV.h>
#include <util/delay.h>

int main(void){
  suartInit(9600);
  _delay_ms(50);
  while (1){
    unsigned char res = suartRx();
    if (res != 0) 
      suartTx(res + 1);
  }
  return 0;
}