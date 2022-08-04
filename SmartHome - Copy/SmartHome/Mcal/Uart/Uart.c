/*
 * Uart.c
 *
 * Created: 6/17/2022 9:03:01 PM
 *  Author: mahdy
 */ 

#include "Uart.h"
void (*Callback)(void) = _NULL;

void M_Uart_Init(void)
{
	ClrBit(_DDRD, 0); // to enable INPUT  circuit for Rx Pin
	SetBit(_DDRD, 1); // to enable OUTPUT circuit for Tx Pin
	
	u8 Local_u8_UCSRC = 0;
	u16 Local_u16_UBRR= ( F_OSCC / ((u32) 16 * BAUD_RATE )) - 1;
	
	// to select character size = 8bits
	SetBit(Local_u8_UCSRC, 7); // Already Set   
	SetBit(Local_u8_UCSRC, 1);      

	SetBit(Local_u8_UCSRC, 2);
	ClrBit(_UCSRB, 2);
	
	//to select Async. mode
	ClrBit(Local_u8_UCSRC, 6);
	
	#if PARITY_MODE  == PARITY_DISABLE
	
	ClrBit(Local_u8_UCSRC, 4);
	ClrBit(Local_u8_UCSRC, 5);
	
	#elif PARITY_MODE  == PARITY_ODD
	
	SetBit(Local_u8_UCSRC, 4);
	SetBit(Local_u8_UCSRC, 5);
	
	#elif PARITY_MODE  == PARITY_DISABLE
	
	ClrBit(Local_u8_UCSRC, 4);
	SetBit(Local_u8_UCSRC, 5);
	
	#endif
	ClrBit(Local_u8_UCSRC, 3); // to select stop bit  = 1bit
	
	
	
	//UBRRL =  103;
	_UCSRC = Local_u8_UCSRC;
	
	_UBRRL = Local_u16_UBRR;
	_UBRRH = 0x00 | (Local_u16_UBRR >> 8);
	
	SetBit(_UCSRB, 7);  //to enable Rx interrupt
	SetBit(_UCSRB, 4);  //to enable Rx Circuit
	SetBit(_UCSRB, 3);  //to enable Tx Circuit
	sei();
	_delay_ms(10);	
}

void M_Uart_Transmit(u8 Local_u8_data)
{
	ClrBit(_UCSRB, 4);  //to Disable Rx Circuit
	while(GetBit(_UCSRA, 5) == 0);
	_UDR = Local_u8_data;
	SetBit(_UCSRB, 4);  //to enable Rx Circuit
}

void M_Uart_SendString(u8 *Local_u8_Ptr)
{
	
	u8 Local_u8_Cnt = 0;
	while(Local_u8_Ptr[Local_u8_Cnt] != '\0')
	{
		M_Uart_Transmit(Local_u8_Ptr[Local_u8_Cnt]);
		Local_u8_Cnt++;
		_delay_ms(1);
	}
	M_Uart_Transmit('\n');
	M_Uart_Transmit('\r');
}

u8 M_Uart_Receive(void)
{
	while(!GetBit(_UCSRA, 7) == 0) ;
	return _UDR;
}

// void M_Uart_ReceiveString(u8 *Local_u8_Ptr, u8 Local_u8_Size) /*Location yo save string, Max size of string*/
// {
// 	u8 Local_u8_Cnt = 0;
// 	//ClrBit(UCSRB, 3);  //to disable Tx Circuit
// 	while(Local_u8_Cnt < Local_u8_Size -1)
// 	{
// 		u8 c ;
// 		c = M_Uart_Receive();
// 		if (c == '\0'|| c == '\n' ||c == '\r') break;
// 		Local_u8_Ptr[Local_u8_Cnt] = c;
// 		Local_u8_Cnt++;
// 	}
// 	Local_u8_Ptr[Local_u8_Cnt] = '\0';
// 	//SetBit(UCSRB, 3);  //to enable Tx Circuit
// }

boolean M_Uart_Available(void)
{
	return GetBit(_UCSRA, 7);
}

void M_Uart_Stop(void)
{
	ClrBit(_UCSRB, 7);  //to enable Rx interrupt
	ClrBit(_UCSRB, 4);  //to enable Rx Circuit
	ClrBit(_UCSRB, 3);  //to enable Tx Circuit
}

void M_Uart_SetCallBack(void (*Ptr)(void))
{
	Callback = Ptr;
}

ISR(USART_RXC_vect)
{
	Callback();
}