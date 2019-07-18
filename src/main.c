#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pic18f4550.h>
#include "../inc/configuration.h"
#include "../inc/lcd16x2.h"
#include "../inc/interrupt.h"
#include "../inc/pwm.h"
#include "../inc/usart.h"
#include "../inc/adc.h"
#include "../inc/tcs3200.h"
#include "../inc/i2c.h"
    
int main(){
    OSCCON = 0x72; //Internal Oscilator - 8MHz
    
    LCD_Init();
    
    char msb_byte = 0, lsb_byte = 0;
    char display[16];
    
    LCD_Init();
    I2C_Init();    
    while(1){
//      BH1750 Code
        I2C_Start(0xB8);
        I2C_Write(0x13);
        I2C_Stop();
        
        I2C_Start(0xB9);
        msb_byte = I2C_Read(0);
        lsb_byte = I2C_Read(1);
        I2C_Stop();
        
        int data = 0;
        data = (int) lsb_byte;
        data |= (int) msb_byte << 8;
        
        sprintf(display, "lx: %d", data);
        LCD_String_xy(1, 0, display);
        
        __delay_ms(250);
        LCD_Clear();
        __delay_ms(250);
    } 
    
    return 0;

}
//      SHT3x Code
//        I2C_Start(0x88);
//        I2C_Write(0x24);
//        I2C_Write(0x00);
//        //I2C_Stop();
//        
//        I2C_Start(0x89);
//        msb_byte = I2C_Read(0);
//        lsb_byte = I2C_Read(1);
//        //I2C_Stop();
//        
//        unsigned int data = 0;
//        data = (int) lsb_byte;
//        data |= (int) msb_byte << 8;
//        
//        int temp = 10 * data;
//        
//        sprintf(display, "Data: %d", data);
//        LCD_String_xy(1, 0, display);
//        sprintf(display, "Temp: %d", temp);
//        LCD_String_xy(2, 0, display);
//        
//        __delay_ms(200);
//        //LCD_Clear();
//        __delay_ms(200);