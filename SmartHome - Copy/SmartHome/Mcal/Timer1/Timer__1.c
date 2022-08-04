/*
 * Timer0.c
 *
 * Created: 6/10/2022 9:06:02 PM
 *  Author: Ahmed
 */ 


#include "Timer_1_.h"
u8 Timer1_Prescaler=64;
u8 Choose_Control_Mode=0;  //Choose Either "1" FOR Door_Mode Or "2" FOR DIMMER_LIGHT_Mode//
//u16 Choice=0;   //Ocr1a if Door_Mode & Ocr1B if DIMMER_LIGHT_Mode//

void M_Timer1_PWM_Control_Mode(u8 H_Control_Mode)
{
	    //Choose Either From MAIN.c//
		
	    //{ "1" FOR Door_Mode} // 
		//{ "2" FOR DIMMER_LIGHT_Mode}//
			
		Choose_Control_Mode = H_Control_Mode; 
		
		
}

void M_Timer1_PWMInit(void)
{	
	
ClrBit(_TCCR1A,0);
SetBit(_TCCR1A,1);

SetBit(_TCCR1B,3);
SetBit(_TCCR1B,4);

//SetBit(_DDRD,5); //To make PD5 Output//

if (Choose_Control_Mode == 1)  //Door_Mode//
{
	SetBit(_DDRD,5);
	
// 	Timer1_Prescaler=64;   //Prescaler is 8 in Door_Mode//
	SetBit(_TCCR1A,7);
	ClrBit(_TCCR1A,6);

}

else if  (Choose_Control_Mode ==2)   //DIMMER_LIGHT_Mode//
 {//To make PD5 Output//
	
	SetBit(_DDRD,4);
	
//	Timer1_Prescaler=64; //Prescaler is 64 in DIMMER_LIGHT_Mode//
	 //To make PD4 Output//
	   
	   //To select mode OCR1B//
	   // option 2 -> [ DIMMER_LIGHT ]
	   SetBit(_TCCR1A,5);
	   ClrBit(_TCCR1A,4);
}
}

void M_Timer1_PWM_SetFrequency(u32 Local_u32_Frequency)
{
	_ICR1	=( ( ( F_OSC * 1000000 )/ Timer1_Prescaler ) / Local_u32_Frequency );
}

void M_Timer1_PWM_SetDutyCycle(u8 Local_u8_DutyCycle)
{
	 	
		if (Choose_Control_Mode == 1)  //Door_Mode//
		{
			_OCR1A= (u16)(Local_u8_DutyCycle * (_ICR1/100));
		}
		else if (Choose_Control_Mode == 2)   //DIMMER_LIGHT_Mode//
		{
			//_OCR1A = 0;
			_OCR1B = (Local_u8_DutyCycle * (_ICR1/100)) ;
		}	
	
}

void M_Timer1_Start(void)
{

			//To set Prescaler 64 //
			SetBit(_TCCR1B,1);
			SetBit(_TCCR1B,0);
			ClrBit(_TCCR1B,2);
}

void M_Timer1_Stop(void)
{
	ClrBit(_TCCR1B,0);
	ClrBit(_TCCR1B,1);
	ClrBit(_TCCR1B,2);
	
	
}

void M_Timer1_Pwm_Start(void)
{
	M_Timer1_Start();
}

void M_Timer1_Pwm_Stop(void)
{
	M_Timer1_Stop();
}

void M_Timer1_PwmReset(void)
{
	M_Timer1_Pwm_Stop();
	_ICR1 = 0;
}