/*
 * Dimmer_Light.h
 *
 * Created: 7/23/2022 9:31:47 PM
 *  Author: Ahmed
 */ 


#ifndef DIMMER_LIGHT_H_
#define DIMMER_LIGHT_H_

/***************************_INCLUDES_***************************/
#include "Dimmer_Light_Cfg.h"
#include "Timer_1_.h"
#define F_CPU 16000000UL
#include <util/delay.h>

/**************************************************_MACROS_*********************************************/
// #define NORMAL          1
// #define MED        2
// #define LOW        3
#define  Control        4
/************************************************_PROTOTYPES_********************************************/
void H_Dimmer_Light_Init(void);
void H_Dimmer_Light_SetLight_Intense(u16);
void H_Dimmer_Light_Start(void);
void H_Dimmer_Light_Stop(void);




#endif /* DIMMER_LIGHT_H_ */