#include "keypad.h"
#include "lcd.h"
#include "pwm.h"
#include "serial.h"
#include "timer.h"
#include "ssd.h"
#include "adc.h"
#include "pic18f4520.h"
#include "config.h"


unsigned char nome[] = "Guilherme Esber";
unsigned char matricula[] = "2025019463";

void LeTeclado(void) {

    // Testa qual bit está ativo e retorna o valor correspondente ao SSD
    // Assumindo que A = 10 e B = 11 no mapeamento do display ssd.h

    if (BitTst(kpRead(), 0)) { // Tecla A Imprimir nome na 1a linha – A
        lcdCommand(0x80);
        for (int i = 0; i <= 14; i++) {
            lcdData(nome[i]);
        }
    }

    if (BitTst(kpRead(), 1)) { // Tecla B //Imprimir matricula na 2a linha – B
        lcdCommand(0xC0);
        for (int i = 0; i <= 9; i++) {
            lcdData(matricula[i]);
        }
    }

    if (BitTst(kpRead(), 2)) { // Tecla 3 //Ligar o cooler – C
        pwmSet1(100);
    }

    if (BitTst(kpRead(), 3)) { // Tecla 6 //Desligar o cooler – D
        pwmSet1(0);
    }

    if (BitTst(kpRead(), 4)) { // Tecla 2 //Limpar o LCD – 0

        lcdCommand(0x80);
        for (int i = 0; i <= 14; i++) {
            lcdData(' ');
        }

        lcdCommand(0xC0);
        for (int i = 0; i <= 9; i++) {
            lcdData(' ');
        }
    }
}

void Serial(void) {

    unsigned char dado;
    unsigned int temp;

    dado = serialRead();

    if (dado != 0) {

        switch (dado) {

            case 'A':
                lcdCommand(0x80);
                for (int i = 0; i <= 14; i++) {
                    lcdData(nome[i]);
                }
                break;

            case 'B':
                lcdCommand(0xC0);
                for (int i = 0; i <= 9; i++) {
                    lcdData(matricula[i]);
                }
                break;

            case 'C':
                pwmSet1(100);
                break;

            case 'D':
                pwmSet1(0);
                break;

            case '0':
                lcdCommand(0x80);
                for (int i = 0; i <= 14; i++) {
                    lcdData(' ');
                }

                lcdCommand(0xC0);
                for (int i = 0; i <= 9; i++) {
                    lcdData(' ');
                }
                break;
        }

        temp = adcRead() / 2;

        serialSend('T');
        serialSend(':');
        serialSend(((temp / 10) % 10) + 48);
        serialSend((temp % 10) + 48);
        serialSend(13);
    }
}

void MostraDisplay(void) {
    char temp = adcRead() / 2;

    ssdDigit((temp / 10) % 10, 1);
    ssdDigit(temp % 10, 0);
}

void main(void) {
    kpInit();
    lcdInit();
    pwmInit();
    serialInit();
    timerInit();
    ssdInit();
    adcInit();

    pwmFrequency(1000);
    pwmSet1(0);
    
    char slot;
    //inicializações
    for (;;) {
        timerReset(5000);
        ssdUpdate();
        switch (slot) {
            case 0:
                kpDebounce();
                LeTeclado();
                slot = 1;
                break;
            case 1:
                Serial();
                slot = 2;
                break;
            case 2:
                kpDebounce();
                slot = 3;
                break;
            case 3:
                MostraDisplay();
                slot = 0;
                break;
            default:
                slot = 0;
                break;
        }
        timerWait();
    }
}
