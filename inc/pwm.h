#ifndef PWM_H
#define	PWM_H
    
#include <pic18f4550.h>
#include <stdio.h>
#include <math.h>

#define MINTHR              8000
#define RESOLUTION          488

#define InternalOsc_8MHz    8000000
#define InternalOsc_4MHz    4000000
#define InternalOsc_2MHz    2000000
#define InternalOsc_1MHz    1000000
#define InternalOsc_500KHz  500000
#define InternalOsc_250KHz  250000
#define InternalOsc_125KHz  125000
#define InternalOsc_31KHz   31000

#define Timer2Prescale_1    1
#define Timer2Prescale_4    4
#define Timer2Prescale_16   16

//The frequency of both PWMs have to be the same.

unsigned long frequencia_pwm;

void PWM1_config();
int setPWM1(unsigned long FPWM, float duty_cycle);
void SetDutyCyclePWM1(float Duty_cycle, int Period);

void PWM2_config();
int setPWM2(unsigned long FPWM, float duty_cycle);
void SetDutyCyclePWM2(float Duty_cycle, int Period);

void PWM1_config(){         
    TRISCbits.TRISC2 = 0; 
    CCP1CON = 0x0C;       
}

void PWM2_config(){         
    TRISCbits.TRISC1 = 0; 
    CCP2CON = 0x0C;       
}

int setPWM1(unsigned long FPWM, float duty_cycle){
    int clockSelectBits, TimerPrescaleBits;
    int TimerPrescaleValue;
    int PWM10BitValue;
    float period;
    unsigned long FOSC, _resolution = RESOLUTION;
    
    if(FPWM == frequencia_pwm){
        SetDutyCyclePWM1(duty_cycle, (int) period);
        return (EXIT_SUCCESS);
    }
    
    frequencia_pwm = FPWM;

    if (FPWM < MINTHR)    {TimerPrescaleBits = 2; TimerPrescaleValue = Timer2Prescale_16;}
    else                  {TimerPrescaleBits = 0; TimerPrescaleValue = Timer2Prescale_1;}

    if (FPWM > _resolution)               {clockSelectBits = 7; FOSC = InternalOsc_8MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 6; FOSC = InternalOsc_4MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 5; FOSC = InternalOsc_2MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 4; FOSC = InternalOsc_1MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 3; FOSC = InternalOsc_500KHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 2; FOSC = InternalOsc_250KHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 1; FOSC = InternalOsc_125KHz;}
    else                                  {clockSelectBits = 0; FOSC = InternalOsc_31KHz;}

    period = ((float)FOSC / (4.0 * (float)TimerPrescaleValue * (float)FPWM)) - 1.0;
    period = round(period);

    OSCCON = ((clockSelectBits & 0x07) << 4) | 0x02;
    PR2 = (int)period;
    T2CON = TimerPrescaleBits;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;  /* Turn ON Timer2 */
    
    
    PWM10BitValue = 4.0 * ((float)period + 1.0) * (duty_cycle/100.0);
    CCPR1L = (PWM10BitValue >> 2);
    CCP1CON = ((PWM10BitValue & 0x03) << 4) | 0x0C;
    
    SetDutyCyclePWM1(duty_cycle, (int) period);
    return (EXIT_SUCCESS);
}

int setPWM2(unsigned long FPWM, float duty_cycle){
    int clockSelectBits, TimerPrescaleBits;
    int TimerPrescaleValue;
    int PWM10BitValue;
    float period;
    unsigned long FOSC, _resolution = RESOLUTION;
    
    if(FPWM == frequencia_pwm){
        SetDutyCyclePWM2(duty_cycle, (int) period);
        return (EXIT_SUCCESS);
    }
    
    frequencia_pwm = FPWM;

    if (FPWM < MINTHR)    {TimerPrescaleBits = 2; TimerPrescaleValue = Timer2Prescale_16;}
    else                  {TimerPrescaleBits = 0; TimerPrescaleValue = Timer2Prescale_1;}

    if (FPWM > _resolution)               {clockSelectBits = 7; FOSC = InternalOsc_8MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 6; FOSC = InternalOsc_4MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 5; FOSC = InternalOsc_2MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 4; FOSC = InternalOsc_1MHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 3; FOSC = InternalOsc_500KHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 2; FOSC = InternalOsc_250KHz;}
    else if (FPWM > (_resolution >>= 1))  {clockSelectBits = 1; FOSC = InternalOsc_125KHz;}
    else                                  {clockSelectBits = 0; FOSC = InternalOsc_31KHz;}

    period = ((float)FOSC / (4.0 * (float)TimerPrescaleValue * (float)FPWM)) - 1.0;
    period = round(period);

    OSCCON = ((clockSelectBits & 0x07) << 4) | 0x02;
    PR2 = (int)period;
    T2CON = TimerPrescaleBits;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;  /* Turn ON Timer2 */
    
    
    PWM10BitValue = 4.0 * ((float)period + 1.0) * (duty_cycle/100.0);
    CCPR1L = (PWM10BitValue >> 2);
    CCP1CON = ((PWM10BitValue & 0x03) << 4) | 0x0C;
    
    SetDutyCyclePWM2(duty_cycle, (int) period);
    return (EXIT_SUCCESS);
}

void SetDutyCyclePWM1(float Duty_cycle, int Period){
    int PWM10BitValue;

    PWM10BitValue = 4.0 * ((float)Period + 1.0) * (Duty_cycle/100.0);
    CCPR1L = (PWM10BitValue >> 2);
    CCP1CON = ((PWM10BitValue & 0x03) << 4) | 0x0C;
}

void SetDutyCyclePWM2(float Duty_cycle, int Period){
    int PWM10BitValue;

    PWM10BitValue = 4.0 * ((float)Period + 1.0) * (Duty_cycle/100.0);
    CCPR2L = (PWM10BitValue >> 2);
    CCP2CON = ((PWM10BitValue & 0x03) << 4) | 0x0C;
}

#endif	/* PWM_H */