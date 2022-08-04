/*
 * TempSensor.c
 *
 * Created: 7/21/2022 11:54:28 PM
 *  Author: Hany
 */ 

#include "TempSensor.h"

void H_TempSensor_Init(void)
{
	M_Adc_Init();
}


u8 H_TempSensor_Read(void)
{
	
	u16 Local_u16_AdcVal =	M_Adc_Read();
	u8 Local_u8_Temp = ((u32)Local_u16_AdcVal*510)/1023; //u32 casting 3shan Value could be more than 2 bytes
	return Local_u8_Temp;
}
