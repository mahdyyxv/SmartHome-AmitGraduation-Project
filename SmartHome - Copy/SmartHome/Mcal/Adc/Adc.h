/*
 * Adc.h
 *
 * Created: 7/17/2022 3:04:05 PM
 *  Author: Hany
 */ 


#ifndef ADC_H_
#define ADC_H_
// ADC drivers works as Polling not Intrrupt 

/*************************************************_INCLUDES_********************************************/
#include "BitMath.h"
#include "Reg.h"
#include "AdcCfg.h"
#include "StdTypes.h"
/*************************************************_MACROS_********************************************/
#define VREF		AVCC
/*************************************************_PROTOTYPE_********************************************/

void M_Adc_Init(void); 
u16 M_Adc_Read(void);



#endif /* ADC_H_ */ 