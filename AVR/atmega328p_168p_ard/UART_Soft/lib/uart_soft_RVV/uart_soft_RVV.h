#ifndef SUART_H
#define SUART_H

// Частота кварца
#define F_CPU 16000000UL
#define __AVR_ATmega168__
#include <avr/interrupt.h>
// deadTime
#define DEAD_TIME_COM 50

// Ports settings
#define SUART_DDR_TX DDRB
#define SUART_DDR_RX DDRB
#define SURAT_PORT_TX PORTB
#define SURAT_PORT_RX PINB
#define SURAT_PIN_TX 3
#define SURAT_PIN_RX 4

#define SUART_FLAG_TX     0
#define SUART_FLAG_RX     1
#define SUART_FLAG_CRR    3
#define SUART_FLAG_TIMOUT 4



void suartDelay(unsigned char count);
void suartInit(unsigned long baud);
void suartTx(unsigned char data);
void suartTxStr(const char* str);

unsigned char suartRx(void);
unsigned char suartRxStr(unsigned char* str, unsigned char len);
#endif /* SUART_H */
