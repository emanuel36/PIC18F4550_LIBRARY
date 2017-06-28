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

#define _XTAL_FREQ  8000000
    
int main(){
    OSCCON = 0x72;
    TRISDbits.RD1 = 0;
    PORTDbits.RD1 = 0;
    config_int0();
    while(1){
        //
    }
    return (EXIT_SUCCESS);
}