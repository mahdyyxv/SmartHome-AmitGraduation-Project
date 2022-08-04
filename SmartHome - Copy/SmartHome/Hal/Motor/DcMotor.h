/*
 * DcMotor.h
 *
 * Created: 6/10/2022 10:16:37 PM
 *  Author: mahdy
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_


/***************************_INCLUDES_***************************/
#include "Dio.h"
#include "DcMotorCfg.h"
#include "BitMath.h"
#include "Reg.h"
/***************************_MACROS_***************************/


/***************************_PROTOTYPES_***************************/

void H_DcMotor_Init(void);
void H_DcMotor_Stop(void);
void H_DcMotor_Start(void);


#endif /* DCMOTOR_H_ */