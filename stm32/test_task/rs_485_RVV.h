#ifndef RVV_RS485_PROTOCOL
#define RVV_RS485_PROTOCOL


#include <stdint.h>
#include <string.h>

typedef uint8_t size_len_word; // размер блока LEN в 1 байт
// typedef uint16_t size_len_word; // размер блока LEN в 2 байта

// Константы
#define RS485_DE_Pin        GPIO_PIN_8   // Пин 
#define RS485_DE_GPIO_Port  GPIOA        // Порт
#define HEAD_0_BYTE 0xdd
#define HEAD_1_BYTE 0x99
#define MAX_PAYLOAD 200  // Максимальный размер блока данных
#define TX_BUF_SIZE (2 + 1 + sizeof(size_len_word) + MAX_PAYLOAD + 2) // размер буфера отправки данных


size_t build_Packet(uint8_t addr, const uint8_t *data, size_len_word len, uint8_t *out_buf);        // Формирование пакета
uint16_t calculate_CRC16(const uint8_t * buf, size_t len);                                          // Хэш функция CRC-16  
void rs485_send_blocking(uint8_t *buf, size_t len);                                                 // Отправка пакета байт по tx


void rx_Pars_Feed(uint8_t byte);                                                                    // Парсер принятых байт (для размера LEN в 1 байт)



#endif