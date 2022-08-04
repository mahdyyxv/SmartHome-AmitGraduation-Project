/*
 * Dio.c
*/ 

#include "Dio.h"

void M_Dio_PinMode(u8 Local_u8_Num,u8 Local_u8_Mode)   
{ 
	u8 Local_u8_Pin  = Local_u8_Num % 10;
	u8 Local_u8_Port = Local_u8_Num / 10;
	switch(Local_u8_Mode)
	{
		case OUTPUT:
		switch(Local_u8_Port)
		{
			case 1: SetBit(_DDRA,Local_u8_Pin); break;
			case 2: SetBit(_DDRB,Local_u8_Pin); break;
			case 3: SetBit(_DDRC,Local_u8_Pin); break;
			case 4: SetBit(_DDRD,Local_u8_Pin); break;
			default:                           break;
		}
		break;
		case INPUT:
		switch(Local_u8_Port)
		{
			case 1: ClrBit(_DDRA,Local_u8_Pin); break;
			case 2: ClrBit(_DDRB,Local_u8_Pin); break;
			case 3: ClrBit(_DDRC,Local_u8_Pin); break;
			case 4: ClrBit(_DDRD,Local_u8_Pin); break;
			default:                           break;
		}	
		break;
		default:
		break;
	}
}

void M_Dio_PinWrite(u8 Local_u8_Num,u8 Local_u8_Mode)
{
	u8 Local_u8_Pin  = Local_u8_Num % 10;
	u8 Local_u8_Port = Local_u8_Num / 10;
	switch(Local_u8_Mode)
	{
		case HIGH:
		switch(Local_u8_Port)
		{
			case 1: SetBit(_PORTA,Local_u8_Pin); break;
			case 2: SetBit(_PORTB,Local_u8_Pin); break;
			case 3: SetBit(_PORTC,Local_u8_Pin); break;
			case 4: SetBit(_PORTD,Local_u8_Pin); break;
			default:                           break;
		}
		break;
		case LOW:
		switch(Local_u8_Port)
		{
			case 1: ClrBit(_PORTA,Local_u8_Pin); break;
			case 2: ClrBit(_PORTB,Local_u8_Pin); break;
			case 3: ClrBit(_PORTC,Local_u8_Pin); break;
			case 4: ClrBit(_PORTD,Local_u8_Pin); break;
			default:                           break;
		}
		break;
		default:
		break;
	}	
}

void M_Dio_PinTog(u8 Local_u8_Num)
{
	u8 Local_u8_Pin  = Local_u8_Num % 10;
	u8 Local_u8_Port = Local_u8_Num / 10;
	switch(Local_u8_Port)
	{
		case 1: TogBit(_PORTA,Local_u8_Pin); break;
		case 2: TogBit(_PORTB,Local_u8_Pin); break;
		case 3: TogBit(_PORTC,Local_u8_Pin); break;
		case 4: TogBit(_PORTD,Local_u8_Pin); break;
		default:                            break;	
	}
}

u8   M_Dio_PinRead(u8 Local_u8_Num)
{
	u8 Local_u8_Pin  = Local_u8_Num % 10;
	u8 Local_u8_Port = Local_u8_Num / 10;
	u8 Local_u8_PinReading = 0;
	switch(Local_u8_Port)
	{ 
		case 1: Local_u8_PinReading = GetBit(_PINA,Local_u8_Pin); break;
		case 2: Local_u8_PinReading = GetBit(_PINB,Local_u8_Pin); break;
		case 3: Local_u8_PinReading = GetBit(_PINC,Local_u8_Pin); break;
		case 4: Local_u8_PinReading = GetBit(_PIND,Local_u8_Pin); break;
		default:                                                 break;
		
	}
	return Local_u8_PinReading;
}

void M_Dio_PinPullUpRes(u8 Local_u8_Num,u8 Local_u8_Mode)
{
	u8 Local_u8_Pin  = Local_u8_Num % 10;
	u8 Local_u8_Port = Local_u8_Num / 10;
	switch(Local_u8_Mode)
	{
		case ENABLE:
		switch(Local_u8_Port)
		{
			case 1: SetBit(_PORTA,Local_u8_Pin); break;
			case 2: SetBit(_PORTB,Local_u8_Pin); break;
			case 3: SetBit(_PORTC,Local_u8_Pin); break;
			case 4: SetBit(_PORTD,Local_u8_Pin); break;
			default:                            break;
		}
		break;
		case DISABLE:
		switch(Local_u8_Port)
		{
			case 1: ClrBit(_PORTA,Local_u8_Pin); break;
			case 2: ClrBit(_PORTB,Local_u8_Pin); break;
			case 3: ClrBit(_PORTC,Local_u8_Pin); break;
			case 4: ClrBit(_PORTD,Local_u8_Pin); break;
			default:                            break;
		}
		break;
		default:
		break;
	}
}

void M_Dio_PortMode(u8 Local_u8_Port,u8 Local_u8_Mode)
{
	switch(Local_u8_Mode)
	{
		case OUTPUT:
		switch(Local_u8_Port)
		{
			case A: _DDRA = 0xFF; break;
			case B: _DDRB = 0xFF; break;
			case C: _DDRC = 0xFF; break;
			case D: _DDRD = 0xFF; break;
			default:             break;
		}
		break;
		case INPUT:
		switch(Local_u8_Port)
		{
			case A: _DDRA = 0x00; break;
			case B: _DDRB = 0x00; break;
			case C: _DDRC = 0x00; break;
			case D: _DDRD = 0x00; break;
			default:             break;
		}
		break;
		default:                 break;
	}
}

void M_Dio_PortWrite(u8 Local_u8_Port,u8 Local_u8_Value)
{
	switch(Local_u8_Port)
	{
		case A: _PORTA = Local_u8_Value; break;
		case B: _PORTB = Local_u8_Value; break;
		case C: _PORTC = Local_u8_Value; break;
		case D: _PORTD = Local_u8_Value; break;
		default:                        break;
	}
}
