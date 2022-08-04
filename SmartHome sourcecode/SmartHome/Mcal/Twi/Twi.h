/*
 * Twi.h
 *
 * Created: 7/8/2022 11:43:10 PM
 *  Author: mahdy
 */ 


#ifndef TWI_H_
#define TWI_H_

/**************************** _INCLUDES_ ****************************/

#include "Reg.h"
#include "StdTypes.h"
#include "BitMath.h"

/**************************** _MACROS_ ****************************/


#define    ACK       1
#define    NACK      0


/**************************** _PROTO_TYPES_ ****************************/
void M_Twi_Init(void);
void M_Twi_StartCondition(void);
void M_Twi_SlaveAddressWrite(u8);
void M_Twi_SlaveAddressRead(u8);

void M_Twi_SendByte(u8);
u8   M_Twi_ReadByte(u8); /*ARGUMENT --> ACK OR NACK TO Send ACK OR NOT*/

void M_Twi_ReapeatedStart(void);
void M_Twi_StopCondition(void);
#endif /* TWI_H_ */