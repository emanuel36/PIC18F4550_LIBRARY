#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

void pwm_config(){
    PR2 = 255;
    CCPR1L = 0x4;
    CCP1CONbits.DC1B = 0b11;
    TRISCbits.RC2 = 0;
    T2CONbits.T2CKPS = 0b11;
    T2CONbits.TMR2ON = 1;
    CCP1CONbits.CCP1M = 0xF;
}