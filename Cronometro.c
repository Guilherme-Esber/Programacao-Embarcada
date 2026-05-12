//jeito do professor

#include "pic18f4520.h"
#include "config.h"
#include "ssd.h"

void main(void) {
    float tempo;
    unsigned char min=0, seg;
    int cont = 0;
    ssdInit();
    for (;;) {
        cont++;
        if(cont>99) { seg++; cont=0; }
        if(seg>59) { min++; seg=0; }
        ssdDigit(((seg / 1) % 10), 0); //0.1s
        ssdDigit(((seg / 10) % 10), 1); //0.1s
        ssdDigit(((min / 1) % 10), 2); //1s
        ssdDigit(((min / 10) % 10), 3); //10s
        for (tempo = 0; tempo < 50; tempo++) ssdUpdate();
    }
}

// meu jeito

#include "pic18f4520.h"
#include "config.h"
#include "ssd.h"

void main(void) {

    int segundos = 0;
    int minutos = 0;
    long int tempo;
    
    ssdInit();

    for(;;){

        ssdDigit(segundos % 10, 0);
        ssdDigit((segundos / 10) % 10, 1);
        ssdDigit(minutos % 10, 2);
        ssdDigit((minutos / 10) % 10, 3);
        
        for (tempo = 0; tempo < 50000; tempo++){
        ssdUpdate();
        }

        segundos++;

        if(segundos >= 60) {
            segundos = 0;
            minutos++;

            if(minutos >= 100) {
                minutos = 0;
            }
        }
    }
}
