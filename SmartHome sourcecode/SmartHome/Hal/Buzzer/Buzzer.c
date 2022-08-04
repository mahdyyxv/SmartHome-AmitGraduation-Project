/*
 * Buzzer.c
*/ 

#include "Buzzer.h"

void H_Buzzer_Init(void)
{
	M_Dio_PinMode(BUZZER_PIN,OUTPUT);
}

void H_Buzzer_On(void)
{
	M_Dio_PinWrite(BUZZER_PIN,HIGH);
}

void H_Buzzer_Off(void)
{
	M_Dio_PinWrite(BUZZER_PIN,LOW);
}

void H_Buzzer_Tog(void)
{
	M_Dio_PinTog(BUZZER_PIN);
}

void H_Buzzer_Alarm(void)
{
		H_Buzzer_On();
		_delay_ms(BUZZER_DELAY);
		H_Buzzer_Off();
		_delay_ms(BUZZER_DELAY);
}