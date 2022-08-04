/*
 * SERVO.c
 *
 * Created: 7/23/2022 4:23:35 PM
 *  Author: Ahmed
 */ 
#include "Servo.h"


void H_ServoMotor_Init(void)
{	
	M_Timer1_PWMInit();                  //Turn on Door//
	M_Timer1_PWM_SetFrequency(50);
}




void H_ServoMotor_SetPosition(u8 Local_u8_Direction)
{
	switch(Local_u8_Direction)
	{
		case OPEN:
		
		
		M_Timer1_PWM_SetDutyCycle(5);  //Door is Opened in 90 degree//
		
		
		
		break;
		
		case CLOSE:
		
		M_Timer1_PWM_SetDutyCycle(10);   //Door is Closed in -90 degree//
		
		break;
		
		default:                    break;
	}
	
}
void H_ServoMotor_Start(void)
{
	M_Timer1_Pwm_Start();  
}
void H_ServoMotor_Stop(void)
{
	M_Timer1_Pwm_Stop();
}