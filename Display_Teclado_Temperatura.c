#include "pic18f4520.h"
#include "config.h"
#include "ssd.h"
#include "timer.h"
#include "keypad.h"
#include "adc.h"

char flag = 0;
unsigned int ADvalor = 0;

void Int(void) __interrupt() {

    if (BitTst(INTCON, 2)) {
        timerReset(1000);
        BitClr(INTCON, 2);
        flag = 1;
    }
    
    if (BitTst(PIR1, 6)) { //Rotina para interrupção (fim de conversão AD)
        ADvalor = ADRESH;
        ADvalor <<= 8;
        ADvalor += ADRESL;
        BitClr(PIR1, 6); //limpa a flag
    }
}

unsigned char tecla(void) {

    // Testa qual bit está ativo e retorna o valor correspondente ao SSD
    // Assumindo que A = 10 e B = 11 no mapeamento do display ssd.h
    if (BitTst(kpRead(), 0)) return 10; // Tecla A
    if (BitTst(kpRead(), 1)) return 11; // Tecla B
    if (BitTst(kpRead(), 2)) return 3; // Tecla 1
    if (BitTst(kpRead(), 3)) return 6; // Tecla 2
    if (BitTst(kpRead(), 4)) return 2; // Tecla 3
    if (BitTst(kpRead(), 5)) return 5; // Tecla 4
    if (BitTst(kpRead(), 6)) return 1; // Tecla 5
    if (BitTst(kpRead(), 7)) return 4; // Tecla 6

    return 255; // Nenhuma tecla pressionada
}

void main(void) {
    unsigned int temp = 0;
    ssdInit();
    timerInit();
    kpInit();
    adcInit();

    BitClr(RCON, 7);
    BitSet(INTCON, 7);
    BitSet(INTCON, 6);
    BitSet(INTCON, 5);
    BitSet(PIE1, 6);
    //PORTD = 0;


    for (;;) {
        while (!flag);
        flag = 0;

        kpDebounce();

        ADCON0 |= 0x02;
        
        //O passo ;
        temp = ADvalor / 2;

        ssdUpdate();
        ssdDigit(tecla(), 0);
        ssdDigit((temp % 10), 1);
        ssdDigit((temp / 10) % 10, 2);
        ssdDigit((temp / 100) % 10, 3);
    }
}
