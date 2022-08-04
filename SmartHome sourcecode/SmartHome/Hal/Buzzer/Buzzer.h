/*
 * Buzzer.h
*/ 


#ifndef BUZZER_H_
#define BUZZER_H_

/*************************************************_INCLUDES_********************************************/

#include "BuzzerCfg.h"
#include "Dio.h"
#define F_CPU 16000000UL
#include <util/delay.h>

/************************************************_PROTOTYPES_********************************************/

void H_Buzzer_Init(void);
void H_Buzzer_On(void);
void H_Buzzer_Off(void);
void H_Buzzer_Tog(void);
void H_Buzzer_Alarm(void);

#endif /* BUZZER_H_ */