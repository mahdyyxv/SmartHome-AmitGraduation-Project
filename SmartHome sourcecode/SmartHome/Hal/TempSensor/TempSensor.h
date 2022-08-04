/*
 * TempSensor.h
 *
 * Created: 7/21/2022 11:54:38 PM
 *  Author: Hany
 */ 


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_


/*************************************************_INCLUDES_********************************************/
#include "BitMath.h"
#include "Reg.h"
#include "Adc.h"
#include "StdTypes.h"
#include "TempSensorCfg.h"
/*************************************************_MACROS_********************************************/

/*************************************************_PROTOTYPE_********************************************/
void H_TempSensor_Init(void);
u8 H_TempSensor_Read(void);






#endif /* TEMPSENSOR_H_ */