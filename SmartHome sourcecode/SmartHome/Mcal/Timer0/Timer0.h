/*
 * Timer0.h
 *
 * Created: 6/4/2022 8:02:24 PM
 *  Author: mahdy
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_


/***************************_INCLUDES_***************************/
#include "Timer0Cfg.h"
#include "StdTypes.h"
#include "BitMath.h"
#include "Reg.h"
#include <avr/interrupt.h>

/***************************_MACROS_***************************/

#define _NULL              '\0'


/***************************_PROTOTYPES_***************************/

void  M_Timer0_Init(void);
void  M_Timer0_SetTime(u32);
void M_Timer0_Start();
void M_Timer0_Stop();
void M_Timer0_SetCallBack(void (*)(void));


#endif /* TIMER0_H_ */