#ifndef INTERRUPT_H
#define	INTERRUPT_H
    
#include <xc.h>
#include <pic18f4550.h>
#define _XTAL_FREQ 16000000

void config_tmr0();
void config_int2();

#endif	/* INTERRUPT_H */