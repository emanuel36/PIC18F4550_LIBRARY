#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pic18f4550.h>
#include "../inc/main.h"
#include "../inc/lcd16x2.h"
#include "../inc/tmr0Interrupt.h"

#define _XTAL_FREQ  8000000

int main(){
    TRISD = 0x00;
    PORTD = 0x00;
    config_tmr0_interupt();
    while(1);
    return (EXIT_SUCCESS);
}