#ifndef INTERRUPT_H
#define INTERRUPT_H
    
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>
#include "configuration.h"
#include "lcd16x2.h"

#define INT0_FLAG 0x1
#define INT1_FLAG 0x2
#define INT2_FLAG 0x4
#define TMR0_FLAG 0x8
#define TMR1_FLAG 0x10
#define TMR2_FLAG 0x20
#define TMR3_FLAG 0x40

void disable_ext_int(){
    INTCONbits.INT0IE = 0;
    INTCON3bits.INT1IE = 0;
    INTCON3bits.INT2E = 0;
}

void enable_ext_int(){
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2E = 1;
}

void config_tmr0(){
    T0CONbits.PSA = 1;
    T0CONbits.T0SE = 0;
    T0CONbits.T0CS = 1;
    T0CONbits.T08BIT = 0;
    TMR0 = 0x00;
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IE = 0;
}

void config_tmr1(){
    T1CONbits.RD16 = 0;
    T1CONbits.T1CKPS = 0;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 1;
    TMR1 = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void config_int0(){
    TRISBbits.RB0 = 1;
    INTCON2bits.INTEDG0 = 1;
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;
    INTCONbits.GIE = 1;
}

void config_int1(){
    TRISBbits.RB1 = 1;
    INTCON3bits.INT1IE = 1;
    INTCON2bits.INTEDG2 = 1;
    INTCON3bits.INT2IF = 0;
    INTCONbits.GIE = 1;
}

void config_int2(){
    TRISBbits.RB2 = 1;
    INTCON3bits.INT2E = 1;
    INTCON2bits.INTEDG2 = 0;
    INTCON3bits.INT2IF = 0;
    INTCONbits.GIE = 1;
}

void interrupt ISR(){
    if(INTCONbits.INT0IF){      
        INTCONbits.INT0IF = 0;
        interrupt_flag = interrupt_flag | INT0_FLAG;
        DutyPWM1 += 0.1;
    }
    
    if(INTCON3bits.INT1IF){      
        INTCON3bits.INT1IF = 0;
        interrupt_flag = interrupt_flag | INT1_FLAG;
        DutyPWM1 -= 0.1;
    }
    
    if(INTCON3bits.INT2IF){   
        INTCON3bits.INT2F = 0; 
        interrupt_flag = interrupt_flag | INT2_FLAG;
    } 
    
    if(PIR1bits.TMR1IF){
        PIR1bits.TMR1IF = 0;
        interrupt_flag = interrupt_flag | TMR1_FLAG;
    }
}

#endif  /* INTERRUPT_H */