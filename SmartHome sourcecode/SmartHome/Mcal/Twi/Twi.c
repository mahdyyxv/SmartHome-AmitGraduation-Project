/*
 * Twi.c
 *
 * Created: 7/8/2022 11:43:30 PM
 *  Author: mahdy
 */ 
#include "Twi.h"


void M_Twi_Init(void)
{
	_TWBR = 3; //To Get Frequency 400Khz
	SetBit(_TWCR, 2); // To Enable Twi Cirvuit	
}

void M_Twi_StartCondition(void)
{
	_TWCR = 0xA4; //to clear interrupt flag and Set StartCondition Bit
	//wait until finish
	while( !(GetBit(_TWCR, 7)) ); 
	while( (_TWSR & 0xF8) != 0x08);
	
}

void M_Twi_SlaveAddressWrite(u8 Local_u8_Address)
{
	_TWDR = (Local_u8_Address << 1);
	_TWCR = 0x84; // to clear interrupt flag
	//wait until finish
	while( !(GetBit(_TWCR, 7)) );
	while( (_TWSR & 0xF8) != 0x18);
}

void M_Twi_SlaveAddressRead(u8 Local_u8_Address)
{
	_TWDR = (Local_u8_Address << 1) | 1;
	_TWCR = 0x84; // to clear interrupt flag
	//wait until finish
	while( !(GetBit(_TWCR, 7)) );
	while( (_TWSR & 0xF8) != 0x40);
}

void M_Twi_SendByte(u8 Local_u8_Data)
{
	_TWDR = Local_u8_Data;
	_TWCR = 0x84; // to clear interrupt flag
	//wait until finish
	while( !(GetBit(_TWCR, 7)) );
	while( (_TWSR & 0xF8) != 0x28);
}

u8   M_Twi_ReadByte(u8 Local_u8_Ack) /*ARGUMENT --> ACK OR NACK TO Send ACK OR NOT*/
{
	if (Local_u8_Ack == ACK)
	{
		_TWCR = 0xC4; // to clear interrupt flag and Set Ack Bit
		//wait until finish
		while( !(GetBit(_TWCR, 7)) );
		while( (_TWSR & 0xF8) != 0x50);
		
	}
	else if (Local_u8_Ack == NACK)
	{
		_TWCR = 0x84; // to clear interrupt flag
		//wait until finish
		while( !(GetBit(_TWCR, 7)) );
	}	
	return _TWDR;
}

void M_Twi_ReapeatedStart(void)
{
	_TWCR = 0xA4; //to clear interrupt flag and Set StartCondition Bit
	//wait until finish
	while( !(GetBit(_TWCR, 7)) );
	while( (_TWSR & 0xF8) != 0x10);
}

void M_Twi_StopCondition(void)
{
	_TWCR = 0x94; //to clear interrupt flag and Set StopCondition Bit
}
