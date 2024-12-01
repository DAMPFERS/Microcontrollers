volatile unsigned char  pcount = 0;
volatile unsigned char  suart_flags = 0;

#include <uart_soft_RVV.h>
#define SUART_WR_0_FLAG_TX()        (suart_flags &= ~(1 << SUART_FLAG_TX))
#define SUART_WR_1_FLAG_TX()        (suart_flags |= (1 << SUART_FLAG_TX))
#define SUART_WR_0_FLAG_RX()        (suart_flags &= ~(1 << SUART_FLAG_RX))
#define SUART_WR_1_FLAG_RX()        (suart_flags |= (1 << SUART_FLAG_RX))
#define SUART_WR_0_FLAG_CRR()       (suart_flags &= ~(1 << SUART_FLAG_CRR))
#define SUART_WR_1_FLAG_CRR()   	(suart_flags |= (1 << SUART_FLAG_CRR))
#define SUART_WR_0_FLAG_TIMOUT()    (suart_flags &= ~(1 << SUART_FLAG_TIMOUT))
#define SUART_WR_1_FLAG_TIMOUT()    (suart_flags |= (1 << SUART_FLAG_TIMOUT))

#define SUART_FLAG_READ(f)          (suart_flags & (1 << f) == 1)
#define SUART_FLAG_CLEAR()          (suart_flags = 0x00)

ISR(TIMER1_COMPA_vect){
    // сброс порта
    TCNT1 = 0x00;
    pcount++;
}



void suartDelay(unsigned char count){
    TCNT1 = 0x0000;
    pcount = 0x00;

    while(pcount < count)
        ;
    return;
}

void suartInit(unsigned long baud){
    TCCR1A = 0x00;
    TCCR1B |= 1 << CS10;

    OCR1A = ((F_CPU / baud) / 2) - DEAD_TIME_COM;
    TCNT1 = 0x0000;

    TIMSK1 |= 1 << OCIE1A;
    SUART_DDR_TX |= 1 << SURAT_PIN_TX;
    SUART_DDR_RX &= ~(1 << SURAT_PIN_RX);
    
    SURAT_PORT_TX |= 1 << SURAT_PIN_TX;
    return;
}


void suartTx(unsigned char data){
    sei();

    SURAT_PORT_TX &= ~(1 << SURAT_PIN_TX);
    suartDelay(2);
    
    for(unsigned char i = 0; i < 8; i++){
        if (((data >> i) & 0x01) == 1)
            SURAT_PORT_TX |= 1 << SURAT_PIN_TX;
        else
            SURAT_PORT_TX &= ~(1 << SURAT_PIN_TX);
        suartDelay(2);
    }
    SURAT_PORT_TX |= 1 << SURAT_PIN_TX;
    suartDelay(2);
    
    cli();
    return;
}


void suartTxStr(const char* str){
    while(*str)
        suartTx(*str++);
    return;
}

unsigned char suartRx(void){
    uint16_t count = 0;
    unsigned char data = 0;
    sei();
    while (count < 0xffff)
    {
        if(SURAT_PORT_RX & (1 << SURAT_PIN_RX))
            count++; 
        else{
            suartDelay(3);
            for(unsigned char i = 0; i < 8; i++){
                if (SURAT_PORT_RX & (1 << SURAT_PIN_RX))
                    data |= 1 << i;
                suartDelay(2);
            }
            suartDelay(1);
            if ((SURAT_PORT_RX & (1 << SURAT_PIN_RX)) == 0){
                SUART_WR_1_FLAG_RX();
                cli();
                return '>';
            }

            else{
                SUART_WR_0_FLAG_RX();
                cli();
                return data;
            }
        }      
    }
    SUART_WR_1_FLAG_TIMOUT();
    cli();
    return 0;  
}



unsigned char suartRxStr(unsigned char* str, unsigned char len){
    if (len <= 0){
        SUART_WR_1_FLAG_CRR();
        return 0;
    }
    else{
        for (unsigned char count = 0; count < len; count++){
            str[count] = suartRx();
            if (SUART_FLAG_READ(SUART_FLAG_RX) != 0)
                return 0;
        }
        
        return 1;
    }
}