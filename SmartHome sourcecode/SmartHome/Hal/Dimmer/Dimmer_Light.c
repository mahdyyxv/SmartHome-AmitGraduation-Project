/*
 * Dimmer_Light.c
 *
 * Created: 7/23/2022 9:31:38 PM
 *  Author: Ahmed
 */ 

#include "Dimmer_Light.h"

void H_Dimmer_Light_Init(void)
{
 M_Timer1_PWMInit();                    //Turn on Dimmer_Light//
M_Timer1_PWM_SetFrequency(50);
}



void H_Dimmer_Light_SetLight_Intense(u16 Local_u8_Intensity)     //Control Dimmer Light Intensity// 
{
	M_Timer1_PWM_SetDutyCycle(Local_u8_Intensity);
}
void H_Dimmer_Light_Start(void)
{
	M_Timer1_Pwm_Start();
}
void H_Dimmer_Light_Stop(void)
{
	M_Timer1_Pwm_Stop();
}