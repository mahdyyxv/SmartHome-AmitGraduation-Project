/*
 * Ext_Eeprom.c
 *
 * Created: 7/9/2022 12:49:43 AM
 *  Author: mahdy
 */ 
#include "Ext_Eeprom.h"

void H_Ext_Eeprom_Init(void)
{
	M_Twi_Init();
}
void H_Ext_Eeprom_Write(u8 Local_u8_Page, u8 Local_u8_Byte, u8 Local_u8_Data)
{
	M_Twi_StartCondition();
	M_Twi_SlaveAddressWrite(((0xA0 >> 1) | Local_u8_Page));
	M_Twi_SendByte(Local_u8_Byte);
	M_Twi_SendByte(Local_u8_Data);
	M_Twi_StopCondition();
}
u8 H_Ext_Eeprom_Read(u8 Local_u8_Page, u8 Local_u8_Byte)
{
	u8 Local_u8_Data = 0;
	M_Twi_StartCondition();
	M_Twi_SlaveAddressWrite(((0xA0 >> 1) | Local_u8_Page));
	M_Twi_SendByte(Local_u8_Byte);
	
	M_Twi_ReapeatedStart();
	M_Twi_SlaveAddressRead(((0xA0 >> 1) | Local_u8_Page));
	Local_u8_Data = M_Twi_ReadByte(ACK);
	M_Twi_StopCondition();
	
	return Local_u8_Data;
}


void H_Ext_Eeprom_MultiByteWrite(u8 Local_u8_Page, u8 Local_u8_Byte, u8 *Local_u8_Data)
{
	u8 Cnt = 0;
	M_Twi_StartCondition();
	M_Twi_SlaveAddressWrite(((0xA0 >> 1) | Local_u8_Page));
	M_Twi_SendByte(Local_u8_Byte);
	for(Cnt = 0; Cnt < strlen(Local_u8_Data); Cnt++)
	{
		M_Twi_SendByte(Local_u8_Data[Cnt]);	
	}
	M_Twi_StopCondition();
} 

void H_Ext_Eeprom_MultiByteRead(u8 Local_u8_Page, u8 Local_u8_Byte, u8 *Local_u8_Data)
{
	u8 Cnt = 0;

 	M_Twi_StartCondition();
	M_Twi_SlaveAddressWrite(((0xA0 >> 1) | Local_u8_Page));
	M_Twi_SendByte(Local_u8_Byte);
	
	M_Twi_ReapeatedStart();	
	M_Twi_SlaveAddressRead(((0xA0 >> 1) | Local_u8_Page));
	
	for (Cnt = 0; Cnt < 16/*Max user or password length*/; Cnt++)
	{
		Local_u8_Data[Cnt] = M_Twi_ReadByte(ACK);
		if(Local_u8_Data[Cnt] == '\0') break; 
	}
	Local_u8_Data[Cnt+1] = M_Twi_ReadByte(NACK);
	M_Twi_StopCondition();
}