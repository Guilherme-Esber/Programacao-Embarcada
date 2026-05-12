#include "config.h"
#include "pic18f4520.h"

void main(void) {
    //configuração do sistema
    TRISA = 0x00; //configura porta A como saída
    TRISD = 0x00; //configura porta D como saída
    TRISE = 0x00; //configura porta E como saída
    BitClr(INTCON2, 7); //liga pull up
    ADCON1 = 0x0E; //config AD
    BitSet(PORTA, 5); //ativa o 1o display
    BitSet(PORTA, 2); //ativa o 2o display
    BitSet(PORTE, 0); //ativa o 3o display
    BitSet(PORTE, 2); //ativa o 4o display
    
    BitClr(INTCON2, 7); //liga pull up
    ADCON1 = 0x0E; //config AD
    TRISB = 0xFE; //config porta para ler teclas A e B
    PORTB = 0x00; //config porta para ler teclas A e B
    
    while(1){
        BitSet(PORTD,0);
        BitSet(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitSet(PORTD,1);
        BitClr(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitSet(PORTD,2);
        BitSet(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitSet(PORTD,3);
        BitClr(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitSet(PORTD,4);
        BitSet(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitSet(PORTD,5);
        BitClr(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitSet(PORTD,6);
        BitSet(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitClr(PORTD,6);
        BitClr(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitClr(PORTD,5);
        BitSet(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitClr(PORTD,4);
        BitClr(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitClr(PORTD,3);
        BitSet(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitClr(PORTD,2);
        BitClr(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitClr(PORTD,1);
        BitSet(PORTD,7);
        for(long i=0; i<=25000; i++){};
        BitClr(PORTD,0);
        BitClr(PORTD,7);
        for(long i=0; i<=25000; i++){};
        }
        
//    while(1){
//        if(!BitTst(PORTB, 4)){
//            PORTD = 0x77;
//        }
//        else if(!BitTst(PORTB, 5)){
//            PORTD = 0x7C;
//        }
//        else{
//            PORTD = 0x00;
//        }
//    }
}
