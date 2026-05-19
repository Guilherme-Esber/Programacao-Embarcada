#include "config.h"
#include "pic18f4520.h"
#include "lcd.h"
#include "keypad.h"

void lcdPosition(unsigned char linha, unsigned char coluna) {
    if (linha == 0) {
        lcdCommand(0x80 + coluna);
    } else if (linha == 1) {
        lcdCommand(0xC0 + coluna);
    } else {
        return;
    }
}

//void main(void) {
//    unsigned int tecla = 16;
//    unsigned char coluna = 0, linha = 0;
//    lcdInit();
//    kpInit();
//    lcdCommand(0x80);
//    for (;;) {
//        kpDebounce();
//        if (kpRead() != tecla) {
//            tecla = kpRead();
//            if (BitTst(tecla, 2)) linha = 0; //tecla 3
//            if (BitTst(tecla, 3)) linha = 1; //tecla 6
//            if (BitTst(tecla, 1)) coluna++; //tecla B
//            if (BitTst(tecla, 5)) coluna--; //tecla 5
//            lcdPosition(linha, coluna);
//        }
//    }
//}

void main(void) {
    kpInit();
    lcdInit();
    unsigned int tecla = 16;
    unsigned long int cont = 0;
    
    for (;;) { 
        cont++;
        
        lcdPosition(1, 0);
        
        lcdData((((cont / 360000) % 24) / 10) + 48);
        lcdData((((cont / 360000) % 24) % 10) + 48);
        lcdData(':');
        lcdData((cont / 60000) % 6 + 48);
        lcdData((cont / 6000) % 10 + 48);
        lcdData(':');
        lcdData((cont / 1000) % 6 + 48);
        lcdData((cont / 100) % 10 + 48);
        //ciclo de 10ms +-.
        
        kpDebounce();

        if (kpRead() != tecla) {
            tecla = kpRead();

        if (BitTst(tecla, 6)) {
            cont += 360000;
        }
        if (BitTst(tecla, 7)) {
            cont -= 360000;
        }

        if (BitTst(tecla, 4)) {
            cont += 6000;
        }
        if (BitTst(tecla, 5)) {
            cont -= 6000;
        }

        if (BitTst(tecla, 2)) {
            cont += 100;
        }
        if (BitTst(tecla, 3)) {
            cont -= 100;
        }

        }
    }

}
