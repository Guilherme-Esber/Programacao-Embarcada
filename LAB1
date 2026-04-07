#include "config.h"
#include "pic18f4520.h"
#include "delay.h"

//inicio do programa

void main(void) {
    unsigned char i, j;
    TRISD = 0x00;
    while (1) {
        PORTD = 0x00;
        for (i = 0; i < 100; i++){
            tempo(100);
        }
        PORTD = 0xFF;
        for (i = 0; i < 100; i++){
            tempo(100);
        }
    }
}

---

#ifndef DELAY_H
#define	DELAY_H

void tempo(unsigned char x);

#endif

---

#include "delay.h"

//este código gera um delay de aprox 1ms

void delay1ms(){
volatile unsigned char j, k;
for(j = 0; j < 41; j++) {
for(k = 0; k < 3; k++);
}
}

void tempo(unsigned char x){
    unsigned char i;
    for (i=0; i<x; i++){
        delay1ms();
    }
}

---

#include "config.h"
#include "pic18f4520.h"
#include "delay.h"

//inicio do programa

void main(void) {
    unsigned char i, j;
    TRISD = 0x00;
    while (1) {
        PORTD = 0xFE;
        for (i = 0; i < 50; i++){
            tempo(100);
        }
        PORTD = 0xFD;
        for (i = 0; i < 5; i++){
            tempo(100);
        }
        PORTD = 0xFB;
        for (i = 0; i < 40; i++){
            tempo(100);
        }
    }
}
