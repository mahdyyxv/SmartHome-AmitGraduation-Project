/*
 * Uart.h
 *
 * Created: 6/17/2022 9:03:15 PM
 *  Author: mahdy
 */ 


#ifndef UART_H_
#define UART_H_


/***************************_INCLUDES_***************************/

#include "UartCfg.h"
#include "StdTypes.h"
#include "BitMath.h"
#include "Reg.h"

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
/***************************_MACROS_***************************/
#define    PARITY_DISABLE     1
#define    PARITY_ODD         2
#define    PARITY_EVEN        3

#define _NULL                          '\0'
/***************************_PROTOTYPES_***************************/

void M_Uart_Init(void);
void M_Uart_Transmit(u8);
void M_Uart_SendString(u8 *);

u8   M_Uart_Receive(void);
void M_Uart_ReceiveString(u8 *, u8); /*Location yo save string, Max size of string*/
boolean M_Uart_Available(void);
void M_Uart_Stop(void);

void M_Uart_SetCallBack(void (*)(void));


#endif /* UART_H_ */