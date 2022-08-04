/*
 * Adc.c
 *
 * Created: 7/17/2022 3:04:51 PM
 *  Author: Hany
 */ 

#include "Adc.h"

void M_Adc_Init()
{
	
//ADMUX Register Confg.	 
	// seting the source of V refrence for ADC circuit and conversion 
	#if		 VREF	==	AVCC
	SetBit(_ADMUX,6);
	ClrBit(_ADMUX,7);
	#elif	 VREF	==	AREF_PIN	
	ClrBit(_ADMUX,6);
	ClrBit(_ADMUX,7);
	#elif	 VREF	==	_2V56
	SetBit(_ADMUX,6);
	SetBit(_ADMUX,7);
	#endif
	ClrBit(_ADMUX,5); // Right Adjust   <<<<<< BIT5 control right or left adjust
	
	/*bits from 0 to 4 in ADMUX control which signal 
	to get from which Analog Pin PA0 > PA7*/
	// selecting Channel
	ClrBit(_ADMUX,0); //ADC1 PA0 will be the ADC Pin only // error??
	ClrBit(_ADMUX,1);
	ClrBit(_ADMUX,2);
	ClrBit(_ADMUX,3);
	ClrBit(_ADMUX,4);

//ADCSRA Config			
	//setting prescaller 128 
	//125 khzz	 , it should be done before enablling ADC
	SetBit(_ADCSRA,0);
	SetBit(_ADCSRA,1);
	SetBit(_ADCSRA,2);	
	//Auto Trigger Enable
	SetBit(_ADCSRA,5);
	// Free Running Mode for AutoTtigger
	//_SFIOR |= 0x60;
	/*ClrBit(SFIOR,7);
	ClrBit(SFIOR,6);
	ClrBit(SFIOR,5);*/
	
	//enable ADC Circuit
	SetBit(_ADCSRA,7);
	
	
}

u16 M_Adc_Read()
{
	SetBit(_ADCSRA,6); //start conversion
	
	while (GetBit(_ADCSRA,4) == 0);
	
	return ADC_VALUE;
}