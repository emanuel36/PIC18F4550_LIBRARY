#ifndef USART_H
#define	USART_H

#include "configuration.h"

#define F_CPU _XTAL_FREQ/64
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)

void USART_Init(long baud_rate){
    float temp;
    TRISCbits.RC6 = 0;                     
    TRISCbits.RC7 = 1;                    
    temp = Baud_value;     
    SPBRG=(int)temp;                
    TXSTAbits.TXEN = 1;                   
    RCSTAbits.SPEN = 1;                  
    RCSTAbits.CREN = 1;
}

void USART_TransmitChar(char out){        
        while(TXIF==0);           
        TXREG=out;                                         
}

char USART_ReceiveChar(){
    while(RCIF==0);                 
    return(RCREG);              
}

void USART_SendString(const char *out){
   while(*out!='\0'){            
        USART_TransmitChar(*out);
        out++;
   }
}

#endif	/* USART_H */
#endif	/* USART_H */