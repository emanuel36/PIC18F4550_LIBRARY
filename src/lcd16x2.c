#include <stdio.h>
#include <string.h>
#include <pic18f4550.h>
#include <xc.h>
#include "../inc/lcd16x2.h"

#define _XTAL_FREQ 8000000

void enableLCD(){
    PORTEbits.RE1 = 1;
    __delay_ms(10);
    PORTEbits.RE1 = 0;
}

void sendASCII(char letra){
    PORTEbits.RE2 = 1;
    PORTD = letra;
    enableLCD();
}

void sendCMD(int value){
    PORTEbits.RE2 = 0;
    PORTD = value;
    enableLCD();
}

void writeLCD(char *frase){
    int i;
    for(i = 0; frase[i] != '\0'; i++){
        sendASCII(frase[i]);
    }
}

void shiftRight(){
    sendCMD(0x1C);
}

void shiftLeft(){
    sendCMD(0x18);
}

void selectLine(int line, int position){
    if(line == 1)   sendCMD(0x80 + position);
    if(line == 2)   sendCMD(0xC0 + position);
}

void clear_lcd(){
    sendCMD(0x1);
}

void initLCD(){
    TRISD = 0x0;
    TRISE = TRISE & 0b11111001;
    sendCMD(0x01);    
    sendCMD(0x38);
    sendCMD(0x80);    
    sendCMD(0xf);
    sendCMD(0x01);
}

void waitPassLCD(){
    selectLine(1, 1);
    writeLCD("Cofre Fechado");
    selectLine(2, 0);
    writeLCD("Aguardando Senha");
}

void passLCD(){
    writeLCD("Digitando Senha");
    selectLine(2,0);
    writeLCD("Senha:");
}

void digitoLCD(){
    writeLCD("*");
}

void wrongPassLCD(int tentativas){
    char msg_tentativas[16];
    writeLCD("Senha Incorreta");
    sprintf(msg_tentativas, "Tentativas = %d", tentativas);
    selectLine(2, 0);
    writeLCD(msg_tentativas);
}

void correctPassLCD(){
    writeLCD("Senha Correta");
    selectLine(2,0);
    writeLCD("Cofre Aberto");
}
