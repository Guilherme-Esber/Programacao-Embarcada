#include "config.h"
#include "pic18f4520.h"
#include "lcd.h"
#include "stdio.h"
//inicio do programa
void main(void) {
    lcdInit();
    printf("ecop\nunifei");
 while(1);
}

\\

#ifndef STDIO_H
#define STDIO_H

void printf(char str[32]);

#endif

\\

#include "stdio.h"
#include "lcd.h"

void printf(char str[32]){
    
    lcdCommand(0x80);
    
    char i = 0;
    
    while(i <= 32){
        if (str[i] == '\0'){
            return;
        }
        else if (str[i] == '\n'){
            lcdCommand(0xC0);
        }
        else{
            lcdData(str[i]);
        }
        i++;
    }
}
