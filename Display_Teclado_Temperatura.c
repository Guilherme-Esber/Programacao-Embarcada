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


//

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
        ssdDigit(kpRead(), 0);
        ssdDigit((temp % 10), 1);
        ssdDigit((temp / 10) % 10, 2);
        ssdDigit((temp / 100) % 10, 3);
    }
}



// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de operação de um teclado matricial
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
//   Modificações: Placa PICGenius por Décio Rennó de M. Faria
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

//#define PICGENIUS

#include "keypad.h"
#include "pic18f4520.h"


static unsigned char valor = 0x00;

unsigned char kpRead(void) {
    switch (valor) {
        case 1:
            return 0x0A;
        case 64:
            return 1;
        case 16:
            return 2;
        case 4:
            return 3;
        case 128:
            return 4;
        case 32:
            return 5;
        case 8:
            return 6;
        case 2:
            return 0x0B;
        default:
            return 0;

    }
}

void kpDebounce(void) {
#ifdef PICGENIUS
    if (!BitTst(PORTB, 0)) valor = 1;
    if (!BitTst(PORTB, 1)) valor = 64;
    if (!BitTst(PORTB, 2)) valor = 16;
    if (!BitTst(PORTB, 3)) valor = 4;
    if (!BitTst(PORTB, 4)) valor = 128;
    if (!BitTst(PORTB, 5)) valor = 32;
#else 
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned char valorNovo = 0x0000;
    static unsigned char valorAntigo = 0x0000;

    for (i = 0; i < 4; i++) {
        TRISB = ~((unsigned char) 1 << i);
        PORTB = ~((unsigned char) 1 << i);

        //realiza o teste para cada bit e atualiza a variável
        for (j = 0; j < 2; j++) {
            if (!BitTst(PORTB, j + 4)) {
                BitSet(valorNovo, (i * 2) + j);
            } else {
                BitClr(valorNovo, (i * 2) + j);
            }
        }
    }
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }
#endif
}

void kpInit(void) {
    TRISB = 0xFF; //quatro entradas e quatro saidas
    BitClr(INTCON2, 7); //liga pull up
    ADCON1 = 0b00001110; //apenas AN0 é analogico, a referencia é baseada na fonte

#ifdef PIC18F4550
    SPPCFG = 0x00; // SFR nao presente no PIC18F4520
#endif
}
