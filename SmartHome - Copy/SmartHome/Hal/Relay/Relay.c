/*
 * Relay.c
*/ 

#include "Relay.h"

void H_Relay_Init(u8 channel)
{
	M_Dio_PinMode(channel, OUTPUT);
}

void H_Relay_On(u8 channel)
{
	M_Dio_PinWrite(channel, HIGH);
}

void H_Relay_Off(u8 channel)
{
	M_Dio_PinWrite(channel, LOW);
}

void H_Relay_Tog(u8 channel)
{
	M_Dio_PinTog(channel);
}