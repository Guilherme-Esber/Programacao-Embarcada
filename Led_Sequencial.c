#include "led.h"

#define TRISD (*(volatile __near unsigned char*) 0xF95)
#define PORTD (*(volatile __near unsigned char*) 0xF83)

void ConfigurarLed(void){
    TRISD = 0x00;
    PORTD = 0xFF;
}

void LigarLed(unsigned char num){
    unsigned char mascara;
    
    mascara = 1 << num;
    PORTD = PORTD & (~mascara);
    
}

void DesligarLed(unsigned char num){
    unsigned char mascara;
    
    mascara = 1 << num;
    PORTD = PORTD | mascara;
    
}

//

#ifndef LED_H
#define	LED_H

void ConfigurarLed(void);
void LigarLed(unsigned char num);
void DesligarLed(unsigned char num);

#endif

//

#include "config.h"
#include "led.h"

void main(void) {
    unsigned char i = 0;
    
    ConfigurarLed();
    
    while(1){
        for(i=0; i<= 7;){
            LigarLed(i);
            for(long i = 0; i < 10000; i++);
            DesligarLed(i);
            for(long j = 0; j < 10000; j++);
            i++;
        }    
    }
}
