#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pic18f4550.h>
#include "../inc/lcd16x2.h"
#include "../inc/tmr0Interrupt.h"

#define _XTAL_FREQ  8000000

int main(){
    initLCD();
    writeLCD("PIC18F4550");
    selectLine(2, 0);
    writeLCD("QUIXADA");
    
    TRISD = 0;
    PORTD = 0;
    config_tmr0_interupt();
    
    while(1);
    
    return (EXIT_SUCCESS);
}