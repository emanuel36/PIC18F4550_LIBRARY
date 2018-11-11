#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pic18f4550.h>
#include "../inc/configuration.h"
#include "../inc/lcd16x2.h"
#include "../inc/interrupt.h"
#include "../inc/pwm.h"

int main(){
    OSCCON = 0x72; //Internal Oscilator - 8MHz
    return (EXIT_SUCCESS);
}
