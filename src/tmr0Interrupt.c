#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

void config_tmr0_interupt(){
    INTCON = 0x0;
    INTCONbits.GIE_GIEH = 1;
    INTCONbits.PEIE_GIEL = 1;
    INTCONbits.TMR0IE = 1;
    
    T0CON = 0x00;
    T0CONbits.TMR0ON = 1;
    T0CONbits.T0PS = 3;
}

void interrupt low_priority ISR(){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        PORTDbits.RD0 = ~PORTDbits.RD0;
    }
}
