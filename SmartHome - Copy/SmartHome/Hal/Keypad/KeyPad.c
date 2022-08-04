/*
 * KeyPad.c
*/ 

#include "KeyPad.h"

void H_KeyPad_Init(void)
{
	M_Dio_PinMode(KEYPAD_R0_PIN,OUTPUT);
	M_Dio_PinMode(KEYPAD_R1_PIN,OUTPUT);
	M_Dio_PinMode(KEYPAD_R2_PIN,OUTPUT);
	M_Dio_PinMode(KEYPAD_R3_PIN,OUTPUT);
	M_Dio_PinMode(KEYPAD_C0_PIN,INPUT);
	M_Dio_PinMode(KEYPAD_C1_PIN,INPUT);
	M_Dio_PinMode(KEYPAD_C2_PIN,INPUT);
	M_Dio_PinMode(KEYPAD_C3_PIN,INPUT);
	M_Dio_PinWrite(KEYPAD_R0_PIN,HIGH);
	M_Dio_PinWrite(KEYPAD_R1_PIN,HIGH);
	M_Dio_PinWrite(KEYPAD_R2_PIN,HIGH);
	M_Dio_PinWrite(KEYPAD_R3_PIN,HIGH);
	M_Dio_PinPullUpRes(KEYPAD_C0_PIN,ENABLE);
	M_Dio_PinPullUpRes(KEYPAD_C1_PIN,ENABLE);
	M_Dio_PinPullUpRes(KEYPAD_C2_PIN,ENABLE);
	M_Dio_PinPullUpRes(KEYPAD_C3_PIN,ENABLE);
}
u8   H_KeyPad_Read(void)
{
	u8 Local_u8_Arr[4][4] = { {'7', '8', '9', 'A'},
							  {'4', '5', '6', 'B'},
							  {'1', '2', '3', 'C'},
							  {'*', '0', '#', 'D'} };
	u8 Local_u8_Reading = KEYPAD_RELEASED;
	u8 Local_u8_Value = _NULL;
	u8 Local_u8_Row = 0;
	u8 Local_u8_Col = 0;
	
	
	for (Local_u8_Row = KEYPAD_R0_PIN; Local_u8_Row <= KEYPAD_R3_PIN; Local_u8_Row++ )
	{
		M_Dio_PinWrite(Local_u8_Row, LOW);
		
		for (Local_u8_Col = KEYPAD_C0_PIN; Local_u8_Col <= KEYPAD_C3_PIN; Local_u8_Col++)
		{
			Local_u8_Reading = M_Dio_PinRead(Local_u8_Col);
			if(Local_u8_Reading == KEYPAD_PRESSED)
			{
				_delay_ms(KEYPAD_DEBOUNCING_TIME);
				if ( M_Dio_PinRead(Local_u8_Col) == KEYPAD_PRESSED)
				{
					Local_u8_Value = Local_u8_Arr[Local_u8_Row - KEYPAD_R0_PIN ][Local_u8_Col - KEYPAD_C0_PIN];
					while (M_Dio_PinRead(Local_u8_Col) == KEYPAD_PRESSED);
				}
			}
			
		}
		
		M_Dio_PinWrite(Local_u8_Row, HIGH);
		/*_delay_ms(1);*/
	}
	
	return Local_u8_Value;
}

