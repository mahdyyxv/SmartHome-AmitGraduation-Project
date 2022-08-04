/*
 * Reg.h
 *
 * Created: 5/13/2022 9:53:29 PM
 *  Author: mahdy
 */ 


#ifndef REG_H_
#define REG_H_
/***************************_INCLUDES_***************************/

#include "StdTypes.h"

/***************************_DIO_REGISTERS_***************************/
#define _DDRA         *(volatile u8*)0x3A
#define _PORTA        *(volatile u8*)0x3B
#define _PINA         *(volatile u8*)0x39
					 
#define _DDRB         *(volatile u8*)0x37
#define _PORTB        *(volatile u8*)0x38
#define _PINB         *(volatile u8*)0x36
			 
#define _DDRC         *(volatile u8*)0x34
#define _PORTC        *(volatile u8*)0x35
#define _PINC         *(volatile u8*)0x33
					 
#define _DDRD         *(volatile u8*)0x31
#define _PORTD        *(volatile u8*)0x32
#define _PIND         *(volatile u8*)0x30
					 
					 
/***************************_SREG_REGISTERS_***************************/
#define _SREG         *(volatile u8*)0x5F 
					 
/***************************_EXT_INT_REGISTERS_***************************/
#define _MCUCR        *(volatile u8*)0x55
#define _GICR         *(volatile u8*)0x5B
					 
/***************************_ADC_REGISTERS_***************************/
					 
#define _ADMUX        *(volatile u8*)0x27
#define _ADCSRA       *(volatile u8*)0x26
#define _ADCH         *(volatile u8*)0x25
#define _ADCL         *(volatile u8*)0x24
#define ADC_VALUE    *(volatile u16*)0x24
#define _SFIOR         *(volatile u8*)0x50
					 
/***************************_TIMER0_REGISTERS_***************************/
					 
#define _TCNT0        *(volatile u8*)0x52
#define _TCCR0        *(volatile u8*)0x53
#define _TIMSK        *(volatile u8*)0x59
#define _OCR0         *(volatile u8*)0x5C


/***************************_TIMER1_REGISTERS_***************************/

#define _TCNT1        *(volatile u16*)0x4C
#define _TCCR1A       *(volatile u8*)0x4F
#define _TCCR1B       *(volatile u8*)0x4E
#define _OCR1A        *(volatile u16*)0x4A
#define _OCR1B        *(volatile u16*)0x48
#define _ICR1         *(volatile u16*)0x46

/***************************_WDT_REGISTERS_***************************/

#define _WDTCR        *(volatile u8*)0x41

/***************************_UART_REGISTERS_***************************/

#define _UDR          *(volatile u8*)0x2C
#define _UCSRA        *(volatile u8*)0x2B
#define _UCSRB        *(volatile u8*)0x2A
#define _UCSRC        *(volatile u8*)0x40
#define _UBRRL        *(volatile u8*)0x29
#define _UBRRH        *(volatile u8*)0x40

/***************************_SPI_REGISTERS_***************************/

#define _SPCR          *(volatile u8*)0x2D
#define _SPDR          *(volatile u8*)0x2F
#define _SPSR          *(volatile u8*)0x2E

/***************************_TWI_REGISTERS_***************************/

#define _TWBR          *(volatile u8*)0x20
#define _TWSR          *(volatile u8*)0x21
#define _TWAR          *(volatile u8*)0x22
#define _TWDR          *(volatile u8*)0x23
#define _TWCR          *(volatile u8*)0x56
#endif /* REG_H_ */