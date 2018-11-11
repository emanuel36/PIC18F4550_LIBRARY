#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pic18f4550.h>
#include "../inc/main.h"
#include "../inc/lcd16x2.h"
#include "../inc/interrupt.h"
#include "../inc/pwm.h"
 
void toogleLed0(){
    PORTDbits.RD0 = !PORTDbits.RD0;
}

void toogleLed1(){
    PORTDbits.RD1 = !PORTDbits.RD1;
}

void toogleLed2(){
    PORTDbits.RD2 = !PORTDbits.RD2;
}

void initPins(){
    TRISDbits.RD0 = 0;
    PORTDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    PORTDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    PORTDbits.RD2 = 0;
}

void scanButtons(){
    if(interrupt_flag & INT0){
        interrupt_flag = interrupt_flag ^ INT0;
        toogleLed0();
        __delay_ms(300);
    }
        
    if(interrupt_flag & INT1){
        interrupt_flag = interrupt_flag ^ INT1;
        toogleLed1();
        __delay_ms(300);
    }
        
    if(interrupt_flag & INT2){
        interrupt_flag = interrupt_flag ^ INT2;
        toogleLed2();
        __delay_ms(300);
    }
}

int main(){
    OSCCON = 0x72;
    initPins();
    config_int0();
    config_int1();
    config_int2();
    
    while(1){
        scanButtons();
    }
    return (EXIT_SUCCESS);
}
