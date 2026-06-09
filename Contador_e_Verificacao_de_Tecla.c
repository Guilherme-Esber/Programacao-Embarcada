#include "config.h"
#include "pic18f4520.h"
#include "ssd.h"
#include "keypad.h"

void main(void) {
    unsigned char teclaAnt = 0, tecla = 0, qt = 0;
    ssdInit();
    kpInit();
    for (;;) {
        ssdUpdate();
        kpDebounce();
        tecla = kpRead();


        if (tecla != 0 && teclaAnt == 0) {
            if (qt < 99) {
                qt++;
            } else {
                qt = 0;

            }
        }

        teclaAnt = tecla;
        
        ssdDigit(tecla, 0);
        ssdDigit((qt % 10), 2);
        ssdDigit(qt / 10, 3);
    }
}

//

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
