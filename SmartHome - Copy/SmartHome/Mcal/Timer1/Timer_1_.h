/*
 * Timer_1_.h
 *
 * Created: 7/23/2022 9:49:30 PM
 *  Author: Ahmed
 */ 


#ifndef TIMER_1__H_
#define TIMER_1__H_



/***************************_INCLUDES_***************************/
#include "Timer_1_Cfg_.h"
#include "BitMath.h"
#include  "Reg.h"


/***************************_MACROS_***************************/
#define _NULL   '\0'
#define Fast_PWM   2
#define  Phase_Correct_PWM       1
#define NON_Inverted  1
#define  Inverted  2

/******************************************_SELECT_WHAT_TO_CONTROL_********************************************/
// option 1 -> [ DOOR ]
// option 2 -> [ DIMMER_LIGHT ]
#define DOOR     2
#define DIMMER_LIGHT     1
/*********************************Prototypes***************************************/

void M_Timer1_Start(void);
void M_Timer1_Stop(void);
void M_Timer1_PWM_Control_Mode(u8 );
void M_Timer1_PWMInit(void);
void M_Timer1_PWM_SetDutyCycle(u8 Local_u8_DutyCycle);
void M_Timer1_Pwm_Start(void);
void M_Timer1_Pwm_Stop(void);
void M_Timer1_PWM_SetFrequency(u32 Local_u32_Frequency);

void M_Timer1_PwmReset(void);


#endif /* TIMER_1__H_ */