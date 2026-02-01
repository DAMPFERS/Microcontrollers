#include "rs_485_RVV.h"


/*
-------------------------- ПЕРЕДАТЧИК: начало ------------------------------------
*/


// Формирование пакета
size_t build_Packet(uint8_t addr, const uint8_t *data, size_len_word len, uint8_t *out_buf) {
    
    /* размер out_buf не должен превышать TX_BUF_SIZE */

    size_t  bias = 0;
    out_buf[bias++] = HEAD_0_BYTE;
    out_buf[bias++] = HEAD_1_BYTE;
    out_buf[bias++] = addr;
    if (sizeof(size_len_word) == 1)
        out_buf[bias++] = len;
    else {
        out_buf[bias++] = len >> 8;
        out_buf[bias++] = len & 0x00ff;
    }
    memcpy(&out_buf[bias], data, len);
    bias += len;

    // CRC по ADDR|LEN|PAYLOAD
    uint16_t crc = calculate_CRC16(&out_buf[2], 2 + len); // bytes: ADDR, LEN, Data
    out_buf[bias++] = (uint8_t)(crc & 0xFF); // LSB
    out_buf[bias++] = (uint8_t)((crc >> 8) & 0xFF); // MSB
    return bias;
}


// Хэш функция CRC-16
uint16_t calculate_CRC16(const uint8_t * buf, size_t len) {
    uint16_t crc = 0xffff;
    for (size_t i = 0; i < len; ++i) {
        crc ^= buf[i];
        for (int k = 0; k < 8; ++k) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001; // Полином
            else
                crc = (crc >> 1);
        }
    }
    return crc;
}



extern UART_HandleTypeDef huart2; // инициализированный UART для трансивера
#define RS485_DE_HIGH() HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_SET)
#define RS485_DE_LOW()  HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET)


// Отправка пакета байт по tx
void rs485_send_blocking(uint8_t *buf, size_t len) {
    RS485_DE_HIGH();
    HAL_UART_Transmit(&huart2, buf, (uint16_t)len, HAL_MAX_DELAY);   // Передача блокирующая
    while (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC) == RESET) { ; }  // Проверка флага, чтобы гарантировать, что последний бит "ушёл"
    RS485_DE_LOW();
}


/*
-------------------------- ПЕРЕДАТЧИК: конец ------------------------------------
*/







/*
-------------------------- ПРИЕМНИК: начало ------------------------------------
*/
enum rx_state_t { 
    WAIT_H1, 
    WAIT_H2,
    ADDR, 
    LEN, 
    DATA, 
    CRC1, 
    CRC2 
};

static enum rx_state_t rx_state = WAIT_H1;
static uint8_t rx_addr;
static uint8_t rx_len;
static uint8_t rx_buf[MAX_PAYLOAD];
static uint16_t rx_crc_calc;
static uint8_t rx_idx;



// Вспомогательная функция для парсера: обновляет текущее значение CRC по одному принятому байту
static inline uint16_t update_CRC16_Byte(uint16_t crc, uint8_t data) {
    crc ^= data;
    for (int i = 0; i < 8; i++) 
        if (crc & 0x0001)
            crc = (crc >> 1) ^ 0xA001; // полином 
        else 
            crc = (crc >> 1);
    
    return crc;
}



// Парсер принятых байт (для размера LEN в 1 байт)
void rx_Pars_Feed(uint8_t byte) {
    
    switch (rx_state) {
    case WAIT_H1:
        if (byte == HEAD_0_BYTE) rx_state = WAIT_H2;
        break;
    case WAIT_H2:
        if (byte == HEAD_1_BYTE)
            rx_state = ADDR;
        else 
            // возможная перекрывающаяся синхронизация
            rx_state = (byte == HEAD_0_BYTE) ? WAIT_H2 : WAIT_H1;       
        break;
    case ADDR:
        rx_addr = byte;
        rx_crc_calc = 0xFFFF;
        // включить addr в CRC
        rx_crc_calc = update_CRC16_Byte(rx_crc_calc, byte);
        rx_state = LEN;
        break;
    case LEN:
        rx_len = byte;
        if (rx_len > MAX_PAYLOAD) { rx_state = WAIT_H1; break; }
        rx_idx = 0;
        rx_state = (rx_len == 0) ? CRC1 : DATA;
        // включить len в CRC
        rx_crc_calc = update_CRC16_Byte(rx_crc_calc, byte);
        break;
    case DATA:
        rx_buf[rx_idx++] = byte;
        rx_crc_calc = update_CRC16_Byte(rx_crc_calc, byte);
        if (rx_idx >= rx_len) rx_state = CRC1;
        break;
    case CRC1: {
        uint8_t lsb = (uint8_t)(rx_crc_calc & 0xFF);
        if (byte != lsb) { rx_state = WAIT_H1; /* CRC error */ }
        else rx_state = CRC2;
        } break;
    case CRC2: {
        uint8_t msb = (uint8_t)((rx_crc_calc >> 8) & 0xFF);
        if (byte != msb) { /* CRC error */ }
        else {
            /*
            Корректный пакет
            Далее вызывается обработчмк данных пакета
            handle_packet(rx_addr, rx_buf, rx_len);
            */         
        }
        rx_state = WAIT_H1;
        } break;
    }
}



/*
-------------------------- ПРИЕМНИК: конец ------------------------------------
*/