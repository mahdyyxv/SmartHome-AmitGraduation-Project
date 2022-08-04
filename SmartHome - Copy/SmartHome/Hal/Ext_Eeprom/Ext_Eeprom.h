/*
 * Ext_Eeprom.h
 *
 * Created: 7/9/2022 12:49:26 AM
 *  Author: mahdy
 */ 


#ifndef EXT_EEPROM_H_
#define EXT_EEPROM_H_

/**************************** _INCLUDES_ ****************************/

#include "Twi.h"
#include "StdTypes.h"
#include <string.h>

/**************************** _MACROS_ ****************************/

/**************************** _PROTO_TYPES_ ****************************/
void H_Ext_Eeprom_Init(void);
void H_Ext_Eeprom_Write(u8, u8, u8); /*page, byte, data*/
u8   H_Ext_Eeprom_Read(u8, u8);  /* page, byte*/
void H_Ext_Eeprom_MultiByteWrite(u8, u8, u8*); /*page, byte, data(More than one byte)*/
void H_Ext_Eeprom_MultiByteRead(u8, u8, u8*); /* page, byte, address to save in*/



#endif /* EXT_EEPROM_H_ */