/* 
 * File:   lcd16x2.h
 * Author: emanuel
 *
 * Created on 31 de Maio de 2017, 16:35
 */

#ifndef LCD16X2_H
#define	LCD16X2_H
    
#include <xc.h>
#include <pic18f4550.h>

void enableLCD();
void sendCMD(int value);
void sendASCII(char letra);
void writeLCD(char *frase);
void shiftRight();
void shiftLeft();
void selectLine(int line, int position);
void clear_lcd();
void initLCD();
void waitPassLCD();
void passLCD();
void digitoLCD();
void wrongPassLCD(int tentativas);
void correctPassLCD();

#endif	/* LCD16X2_H */