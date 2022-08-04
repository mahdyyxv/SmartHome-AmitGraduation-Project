/*
 * Timer0.c
 *
 * Created: 6/4/2022 8:02:10 PM
 *  Author: mahdy
 */ 
#include "Timer0.h"

u32 Timer0_u32_NumOfOverFlows = 0;
u8 Timer0_u8_RemTicks = 0;
u32 Timer0_NumOfCompareMatch = 0;
void (*_Callback)(void) = _NULL ;

void  M_Timer0_Init(void)
{
	
	_OCR0 = 249;                 ////
	_TCCR0 = 0x28;				//
	_TCCR0 |= 0x03;				// -> TIMER0 INIT AS TEST (CTC INTERRUPT)
	_TIMSK |= (1<<1);		//
}

void M_Timer0_SetCallBack(void (*Ptr)(void))
{
	_Callback = Ptr;
}


ISR(TIMER0_COMP_vect)
{
	_Callback();
	
}
