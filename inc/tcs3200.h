#ifndef TCS3200_H
#define	TCS3200_H

#include "interrupt.h"

#define NO_COLOR 0
#define RED      1
#define BLUE     2
#define CLEAR    3
#define GREEN    4

#define S0  PORTDbits.RD0
#define S1  PORTDbits.RD1
#define S2  PORTDbits.RD2
#define S3  PORTDbits.RD3
#define OE  PORTDbits.RD4

void init_tcs3200(){
    TRISD = TRISD & 0xE0;
    S0 = 1;
    S1 = 0;
    OE = 1;
    config_tmr0();
    config_tmr1();
}

void select_photodiode(int diode){
    switch(diode){
        case RED:
            S2 = 0;
            S3 = 0;
            break;
            
        case BLUE:
            S2 = 0;
            S3 = 1;
            break;
            
        case CLEAR:
            S2 = 1;
            S3 = 0;
            break;
            
        case GREEN:
            S2 = 1;
            S3 = 1;
            break;
    }
}

int get_freq(){
    OE = 0;
    TMR0 = 0x00;
    TMR1 = 0xD8F0;
    T0CONbits.TMR0ON = 1;
    T1CONbits.TMR1ON = 1;
    while(!(interrupt_flag & TMR1_FLAG));
    T1CONbits.TMR1ON = 0;
    T0CONbits.TMR0ON = 0;
    interrupt_flag = interrupt_flag & !TMR1_FLAG;
    OE = 1;
    return TMR0;
}

int get_color(){
    int freq_red, freq_blue, freq_green;
    
    select_photodiode(RED);
    __delay_ms(10);
    freq_red = get_freq()/10;
    
    select_photodiode(GREEN);
    __delay_ms(10);
    freq_green = get_freq()/10;
    
    select_photodiode(BLUE);
    __delay_ms(10);
    freq_blue = get_freq()/10;
    
    if((freq_red > 5) || (freq_green > 5) || (freq_blue > 5)){
        if((freq_red > freq_blue) && (freq_red > freq_green))          return RED;
        else if((freq_green > freq_blue) && (freq_green > freq_red))   return GREEN;    
        else if((freq_blue > freq_red) && (freq_blue > freq_green))    return BLUE;
    }
    return NO_COLOR;
}

#endif	/* TCS3200_H */