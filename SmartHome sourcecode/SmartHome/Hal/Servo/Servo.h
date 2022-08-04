/*
 * SERVO.h
 *
 * Created: 7/23/2022 4:23:46 PM
 *  Author: Ahmed
 */ 


#ifndef SERVO_H_
#define SERVO_H_


/***************************_INCLUDES_***************************/
#include "Servo_Cfg.h"
#include "Timer_1_.h"


/**************************************************_MACROS_*********************************************/
#define OPEN           1
#define CLOSE          2
//#define  Control       3
/************************************************_PROTOTYPES_********************************************/
void H_ServoMotor_Init(void);
void H_ServoMotor_SetPosition(u8);
void H_ServoMotor_Start(void);
void H_ServoMotor_Stop(void);





#endif /* SERVO_H_ */