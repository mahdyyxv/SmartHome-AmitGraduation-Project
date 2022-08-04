/*
 * DcMotor.c
 *
 * Created: 6/10/2022 10:16:27 PM
 *  Author: mahdy
 */ 

#include "DcMotor.h"

void H_DcMotor_Init(void)
{
	M_Dio_PinMode(MOTOR_PIN, OUTPUT);
}

void H_DcMotor_Stop(void)
{
	M_Dio_PinWrite(MOTOR_PIN, LOW);
}
void H_DcMotor_Start(void)
{
	M_Dio_PinWrite(MOTOR_PIN, HIGH);
}