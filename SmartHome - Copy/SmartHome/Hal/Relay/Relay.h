/*
 * Relay.h
*/ 


#ifndef RELAY_H_
#define RELAY_H_

/*************************************************_INCLUDES_********************************************/

#include "RelayCfg.h"
#include "Dio.h"

/************************************************_PROTOTYPES_********************************************/

void H_Relay_Init(u8 channel);
void H_Relay_On(u8 channel);
void H_Relay_Off(u8 channel);
void H_Relay_Tog(u8 channel);



#endif /* RELAY_H_ */