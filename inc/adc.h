#ifndef ADC_H
#define	ADC_H

void ADC_Init(){    
    TRISAbits.RA0 = 1;       /*set as input port*/
    ADCON1 = 0x0e;      /*ref vtg is VDD and Configure pin as analog pin*/    
    ADCON2 = 0x92;      /*Right Justified, 4Tad and Fosc/32. */
    ADRESH = 0;           /*Flush ADC output Register*/
    ADRESL = 0;   
}

int ADC_Read(int channel){
    int digital;
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100);      /*channel 0 is selected i.e (CHS3CHS2CHS1CHS0=0000) 
                                                                      and ADC is disabled i.e ADON=0*/
    ADCON0 |= ((1<<ADON)|(1<<GO));                   /*Enable ADC and start conversion*/
    while(ADCON0bits.GO_nDONE==1);                  /*wait for End of conversion i.e. Go/done'=0 conversion completed*/        
    digital = (ADRESH*256) | (ADRESL);              /*Combine 8-bit LSB and 2-bit MSB*/
    return (digital);
}

#endif	/* ADC_H */