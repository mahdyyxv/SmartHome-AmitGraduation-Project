/*
 * SmartHome.c
 *
 * Created: 7/8/2022 11:32:27 PM
 * Author : mahdy
 */ 


/**************************** _INCLUDES_ ****************************/
#include <avr/io.h>
#include "Ext_Eeprom.h"
#include "Uart.h"
#include "Lcd.h"
#include "Reg.h"
#include "Relay.h"
#include "Timer_1_.h"
#include "Servo.h"
#include "Timer0.h"
#include "DcMotor.h"
#include "TempSensor.h"
#include "Buzzer.h"
#include "KeyPad.h"
#include "Dimmer_Light.h"
#include <string.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

/**************************** _MACROS_ ****************************/

#define    MAX_USER_NUMBER              7  //Without Admin
#define    MAX_USERNAME_LENGTH          16
#define    MAX_PASSWORD_LENGTH          16

/**************************** _PROTO_TYPES_ ****************************/

void    A_EnterNewData(u8 *, u8 *); /*User Name, Password*/
u8      A_RetreiveData(u8 *); /*User Name,*/
void    A_UartRxInerrupt_Task(void);
void    A_TimerCtc_Interrupt_Task(void);
void    A_Alarm(void);
void    A_Show_Status(void);

/**************************** _GLOBAL_VAR_ ****************************/

u8  id = 1;
u8 admin_username [6]= "Mahdy\0";
u8 admin_password [5]= "1234\0";

u8 ordinary_password [5]= "5432\0";

u8 user1_id[2] = "1\0";
u8 user2_id[2] = "2\0";
u8 user3_id[2] = "3\0";
u8 user4_id[2] = "4\0";
u8 user5_id[2] = "5\0";
u8 user6_id[2] = "6\0";
u8 user7_id[2] = "7\0";

u8  retreived_username[] = "";
u8  retreived_password[] = "";

u8  username[17] = "";
u8  password[16] = "";
volatile u8 x;
u8	flag = 0; //
/*
bit 0 -> if 1 Admin mode ,, 0 for user
bit 1 -> if 1 receive username And Password for admin or any user ;
bit 2 -> for checking if any one logged or not -> if 1 -> there is at least one user ,, 0 no users
bit 3 -> 1 to start receive Username ,, 0 to start receive Password
bit 4 -> to indicate That program will receive 1byte
bit 7 -> to indicate receiveng pwm for dimming 
*/
u8 A_Cnt;
u8 control_flag = 0;
u8 user_flag = 0;
u8 Status_flag = 0;
u8 light_intensity = 100;
/**************************** _MAIN_ ****************************/

int main(void)
{
	M_Timer0_Init();
	M_Timer0_SetCallBack(A_TimerCtc_Interrupt_Task);
	H_KeyPad_Init();	                ////
    M_Uart_Init();
	M_Uart_SetCallBack(A_UartRxInerrupt_Task);
	
	H_Lcd_Init();	  
	H_Buzzer_Init();
 	H_ServoMotor_Init(); 
	H_TempSensor_Init();
// 	H_Ext_Eeprom_Init();
// 	_delay_ms(100);
// 	H_Ext_Eeprom_MultiByteWrite(0,4, admin_username);
// 	H_Lcd_WriteString("Done adding");
// 	_delay_ms(1000);
// 	H_Lcd_Clr();
// 	H_Ext_Eeprom_MultiByteRead(0,4, retreived_username);
// 	H_Lcd_WriteString(retreived_username);
// 	M_Uart_SendString(retreived_username);
// 	_delay_ms(1000);
// 	H_Lcd_Clr();
	H_Relay_Init(RELAY_PIN1);
	H_Relay_Init(RELAY_PIN2);
	H_Relay_Init(RELAY_PIN3);
	H_Relay_Init(RELAY_PIN4);
	H_Relay_Init(RELAY_PIN5);
	ClrBit(flag, 2);
	SetBit(flag, 4);
//    id = H_Ext_Eeprom_Read(7, 255);
	M_Timer1_PWM_Control_Mode(1);
	H_ServoMotor_Init();
	H_ServoMotor_SetPosition(2); // to close the door 
	H_ServoMotor_Start();

	H_DcMotor_Init();
	sei();
	while (1)
	{
		if(GetBit(flag, 2) == 0)
		{			
			H_Lcd_GoTo(0,0);
			H_Lcd_WriteString("To Admin enter:1");
			M_Uart_SendString("To Admin enter:1");
			H_Lcd_GoTo(1,0);
			H_Lcd_WriteString("To User  enter:2");
			M_Uart_SendString("To User  enter:2");
			while(GetBit(flag, 2) == 0)
			{
				x = H_TempSensor_Read();
			}
			H_Lcd_Clr();
		}
		else if(GetBit(flag, 1) == 1)
		{
			H_Lcd_GoTo(0,0);
			H_Lcd_WriteString("Enter Username");
			H_Lcd_GoTo(1,0);
			H_Lcd_WriteString("Enter Password");
			M_Uart_SendString("Please enter User \n and Password");
			
			volatile u8 user[16] = "";
			volatile u8 pass[16] = "";
			volatile u8 Local_u8_UserCnt = 0;
			volatile u8 Local_u8_PassCnt = 0;
			
			while(GetBit(flag, 1) == 1)
			{	
				x = H_TempSensor_Read();			
				if(GetBit(flag, 0) == 0)
				{
					if ((GetBit(flag, 3) == 1) && (user_flag == 0))
					{
						memset(username, 0, 17);
						u8 c ;
						c = H_KeyPad_Read();				
						M_Uart_Transmit(c);
						if (c == 'A')
						{
						
							user[Local_u8_UserCnt] = '\0';
							Local_u8_UserCnt = 0;
							strcat(username, user);
							memset(user, 0, 16);
							memset(pass, 0, 16);
							ClrBit(flag, 3);
							user_flag = 1;
						}
						else if(c == 0) _delay_us(10);
						else
						{
							user[Local_u8_UserCnt] = c;
							Local_u8_UserCnt++;
						}
					}
				
					else if ((GetBit(flag, 3) == 0) && (user_flag == 1))
					{
						memset(password, 0, 16);
					
						u8 c ;
						c = H_KeyPad_Read();
						if ( c == 'A')
						{
							pass[Local_u8_PassCnt] = '\0';
							Local_u8_PassCnt = 0;
							strcat(password, pass);
							memset(pass, 0, 16);
							memset(user, 0, 16);
							SetBit(flag, 3);
							A_Cnt++;
							user_flag = 0;
						}
						else if(c == 0) _delay_us(10);
						else
						{
							pass[Local_u8_PassCnt] = c;
							Local_u8_PassCnt++;
						}
					
					}
				}
				if (strcmp(username, "")!=0 && strcmp(password, "") !=0)
				{
					if(GetBit(flag, 0) == 1)
					{
						if(( strcmp(username, admin_username) == 0 ) && ( strcmp(password, admin_password) == 0 ))
						{
							ClrBit(flag, 1);
							A_Cnt = 0;
						}
						else A_Alarm();
					}
					else
					{
						if(((  strcmp(username, user1_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 ))  ||
						    (( strcmp(username, user2_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
							(( strcmp(username, user3_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
							(( strcmp(username, user4_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
							(( strcmp(username, user5_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
							(( strcmp(username, user6_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
							(( strcmp(username, user7_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 ))
							 )
						{
							ClrBit(flag, 1);
							A_Cnt = 0;
						}
						else A_Alarm();
						
					}
					
				}
			}
			H_Lcd_Clr();
		}
		
		if(GetBit(flag, 0) == 1)
		{
			if(strcmp(username, admin_username) == 0)
			{
				
				if( ( strcmp(username, admin_username) == 0 ) && ( strcmp(password, admin_password) == 0 ) )
				{	
						SetBit(flag, 5);
											
						M_Uart_SendString("/*****************************************************/");
						M_Uart_SendString("1- open door \n\r2- close door \n\r3- add new user\n\r");
						M_Uart_SendString("4- remove old user \n\r5- turn 1st on \n\r6- turn 1st off\n\r");
						M_Uart_SendString("7- turn 2nd on \n\r8- turn 2nd off \n\r9- turn 3rd on\n\r");
						M_Uart_SendString("A- turn 3rd off \n\rB- turn 4th on \n\rC- turn 4th off\n\r");
						M_Uart_SendString("D- turn 5th on \n\rE- turn 5th off \n\rF- control dimming\n\r");
						M_Uart_SendString("/*****************************************************/");
						while(1)
						{
							
							if(GetBit(flag, 7) == 1)
							{
								if( (light_intensity == 100) )
								{
									M_Uart_SendString("Enter Intensity \r\n From 0 to 9 ");
								}
								else
								{
									H_Lcd_Clr();
									M_Timer1_PWM_Control_Mode(2);
									H_Dimmer_Light_Init();
									H_Dimmer_Light_SetLight_Intense( (light_intensity/9.0) * 100.0  );
									H_Dimmer_Light_Start();
									ClrBit(flag, 7);
									SetBit(flag, 5);
										
								}
								_delay_ms(10);
								light_intensity = 100;
							}
							x = H_TempSensor_Read();
							A_Show_Status();
							
						}
										

				}
			}
			
		}
		else if (GetBit(flag, 0) == 0)
		{
			
			if(((  strcmp(username, user1_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 ))  ||
				(( strcmp(username, user2_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
				(( strcmp(username, user3_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
				(( strcmp(username, user4_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
				(( strcmp(username, user5_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
				(( strcmp(username, user6_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
				(( strcmp(username, user7_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 ))
				)
			{
				
				while(((  strcmp(username, user1_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 ))  ||
					(( strcmp(username, user2_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
					(( strcmp(username, user3_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
					(( strcmp(username, user4_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
					(( strcmp(username, user5_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
					(( strcmp(username, user6_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 )) ||
					(( strcmp(username, user7_id) == 0 ) && ( strcmp(password, ordinary_password) == 0 ))
					)
				{	
					SetBit(flag, 5);
					x = H_TempSensor_Read();
					H_Lcd_GoTo(0,0);
					H_Lcd_WriteString("1- close door");
					H_Lcd_GoTo(1,0);
					H_Lcd_WriteString("2-on 1st 3-off 1st");
					_delay_ms(1000);
					H_Lcd_Clr();
				
					H_Lcd_GoTo(0,0);
					H_Lcd_WriteString("4-on 2nd 5-off 2nd");
					H_Lcd_GoTo(1,0);
					H_Lcd_WriteString("6-on 3rd 7-off 3rd");
					_delay_ms(1000);
					H_Lcd_Clr();
				
					H_Lcd_GoTo(0,0);
					H_Lcd_WriteString("8-on 4th 9-off 4th");
					H_Lcd_GoTo(1,0);
					H_Lcd_WriteString("A-on 5th B-off 5th");
					_delay_ms(1000);
					H_Lcd_Clr();
				
					H_Lcd_GoTo(0,0);
					H_Lcd_WriteString("C- control dimming");
					_delay_ms(1000);
					H_Lcd_Clr();
					if(GetBit(flag, 7) == 1)
					{
						
						H_Lcd_WriteString("Enter Intensity ");
						H_Lcd_GoTo(1,0);
						H_Lcd_WriteString("From 0 to 9 ");
							
						while( (light_intensity == 100) || (light_intensity == '\0'))
						{
							light_intensity = H_KeyPad_Read();
						}
						
						ClrBit(flag, 7);
						SetBit(flag, 5);
						M_Timer1_PWM_Control_Mode(2);
						H_Dimmer_Light_Init();
						H_Dimmer_Light_SetLight_Intense( ((light_intensity-48)/9.0) * 100.0);						
						H_Dimmer_Light_Start();
						light_intensity = 100;
						
					}
				}
			}
		}
		
	}
}


/**************************** _UART_ISR_ ****************************/

void A_UartRxInerrupt_Task(void)
{
	static volatile u8 Local_u8_UserCnt = 0;
	static volatile u8 Local_u8_PassCnt = 0;
	static u8 user[16] = "";
	static u8 pass[16] = "";
	static volatile u8  temp = 0;
	
	
	
	if((GetBit(flag, 5) == 1) && (GetBit(flag, 0) == 1))
	{
		control_flag = _UDR;	
	}
	
	else if(GetBit(flag, 7) == 1)
	{
		u8 c = _UDR;
		
		
		if( c == '\n' || c == '\r')
		{
			light_intensity = temp-48;
		
		}
		temp = c; 
		
	}
	if(GetBit(flag, 4) == 1)
	{
		u8 c = _UDR;
		if(c == '1')
		{
			SetBit(flag, 2);
			ClrBit(flag, 4);
			SetBit(flag, 3);
			SetBit(flag, 1);
			SetBit(flag, 0);
			
		}
		else if( c == '2')
		{
			SetBit(flag, 2);
			ClrBit(flag, 4);
			SetBit(flag, 3);
			SetBit(flag, 1);
			ClrBit(flag, 0);
		}
		else return;
	}
	
	
	else if (GetBit(flag, 3) == 1)
	{
		memset(username, 0, 16);
		if(Local_u8_UserCnt < MAX_USERNAME_LENGTH -1)
		{
			u8 c ;
			c = _UDR;
			if (c == '\0' || c == '\n' || c == '\r')
			{
				
				user[Local_u8_UserCnt] = '\0';
				Local_u8_UserCnt = 0;
				strcat(username, user);
				memset(user, 0, 16);
				memset(pass, 0, 16);
				ClrBit(flag, 3);
				return;
			}
			user[Local_u8_UserCnt] = c;
			
			Local_u8_UserCnt++;
		}
	}
	
	else if (GetBit(flag, 3) == 0)
	{
		memset(password, 0, 16);
		if(Local_u8_PassCnt < MAX_PASSWORD_LENGTH -1)
		{
			u8 c ;
			c = _UDR;
			if ( c == '\0' || c == '\n' ||c == '\r')
			{
				pass[Local_u8_PassCnt] = '\0';
				Local_u8_PassCnt = 0;
				strcat(password, pass);
				memset(pass, 0, 16);
				memset(user, 0, 16);
				SetBit(flag, 3);
				A_Cnt++;
				return;
			}
			pass[Local_u8_PassCnt] = c;
			Local_u8_PassCnt++;
		}
		
	}
}

/**************************** _CTC_ISR_ ****************************/

void A_TimerCtc_Interrupt_Task(void)
{
	if((GetBit(flag, 5) == 1) && (GetBit(flag, 0) == 0))
	{
		control_flag = 0;
		u8 c = H_KeyPad_Read();
		control_flag = c ;
		
	}
	else if(GetBit(flag, 4) == 1) 
	{
		u8 c = H_KeyPad_Read();
		if(c == '1')
		{
			SetBit(flag, 2);
			ClrBit(flag, 4);
			SetBit(flag, 3);
			SetBit(flag, 1);
			SetBit(flag, 0);
			
		}
		else if( c == '2')
		{
			SetBit(flag, 2);
			ClrBit(flag, 4);
			SetBit(flag, 3);
			SetBit(flag, 1);
			ClrBit(flag, 0);
		}
		else return;
	}
	
	
	if(x > 28)
	{
		 H_DcMotor_Start();
	}
	else if( x < 21)
	{
		 H_DcMotor_Stop();
	}
	
	if(GetBit(flag, 0) == 1)
	{
		switch (control_flag)
		{
			
			case '1':
			// Servo set position to 90;
			M_Timer1_PWM_Control_Mode(1);
			H_ServoMotor_Init();
			H_ServoMotor_SetPosition(1);
			H_ServoMotor_Start();
			SetBit(Status_flag, 0);
			break;
			case '2':
			// Servo set position to 0;
			M_Timer1_PWM_Control_Mode(1);
			H_ServoMotor_Init();
			H_ServoMotor_SetPosition(2);
			H_ServoMotor_Start();
			ClrBit(Status_flag, 0);
			break;
			case '3':
		
			SetBit(Status_flag, 1);
		
			break;
			case '4':
		
			ClrBit(Status_flag, 1);
			break;
			case '5':
			// Turn on relay1;
			H_Relay_On(RELAY_PIN1);
			SetBit(Status_flag, 2);
			break;
			case '6':
			// Turn off relay1;
			H_Relay_Off(RELAY_PIN1);
			ClrBit(Status_flag, 2);
			break;
			case '7':
			// Turn on relay2;
			H_Relay_On(RELAY_PIN2);
			SetBit(Status_flag, 3);
			break;
			case '8':
			// Turn off relay2;
			H_Relay_Off(RELAY_PIN2);
			ClrBit(Status_flag, 3);
			break;
			case '9':
			// Turn on relay3;
			H_Relay_On(RELAY_PIN3);
			SetBit(Status_flag, 4);
			break;
			case 'A':
			// Turn off relay3;
			H_Relay_Off(RELAY_PIN3);
			ClrBit(Status_flag, 4);
		
			break;
			case 'B':
			// Turn on relay4;
			H_Relay_On(RELAY_PIN4);
			SetBit(Status_flag, 5);
			break;
			case 'C':
			// Turn off relay4;
			H_Relay_Off(RELAY_PIN4);
			ClrBit(Status_flag, 5);
			break;
			case 'D':
			// Turn on relay5;
			H_Relay_On(RELAY_PIN5);
			SetBit(Status_flag, 6);
			break;
			case 'E':
			// Turn off relay5;
			H_Relay_Off(RELAY_PIN5);
			ClrBit(Status_flag, 6);
			break;
			case 'F':
			ClrBit(flag, 5);
			control_flag = 0;
			SetBit(flag, 7);
			break;
				
			default: break;
		}
	}
	else
	{
		switch (control_flag)
		{
			case '1':
			// Servo set position to 90;
			M_Timer1_PWM_Control_Mode(1);
			H_ServoMotor_Init();
			H_ServoMotor_SetPosition(2);
			H_ServoMotor_Start();
			ClrBit(Status_flag, 0);
			break;
			case '2':
			// Turn on relay1;
			H_Relay_On(RELAY_PIN1);
			SetBit(Status_flag, 2);
			break;
			case '3':
			// Turn off relay1;
			H_Relay_Off(RELAY_PIN1);
			ClrBit(Status_flag, 2);
			break;
			case '4':
			// Turn on relay2;
			H_Relay_On(RELAY_PIN2);
			SetBit(Status_flag, 3);
			break;
			case '5':
			// Turn off relay2;
			H_Relay_Off(RELAY_PIN2);
			ClrBit(Status_flag, 3);
			break;
			case '6':
			// Turn on relay3;
			H_Relay_On(RELAY_PIN3);
			SetBit(Status_flag, 4);
			break;
			case '7':
			// Turn off relay3;
			H_Relay_Off(RELAY_PIN3);
			ClrBit(Status_flag, 4);
			
			break;
			case '8':
			// Turn on relay4;
			H_Relay_On(RELAY_PIN4);
			SetBit(Status_flag, 5);
			break;
			case '9':
			// Turn off relay4;
			H_Relay_Off(RELAY_PIN4);
			ClrBit(Status_flag, 5);
			break;
			case 'A':
			// Turn on relay5;
			H_Relay_On(RELAY_PIN5);
			SetBit(Status_flag, 6);
			break;
			case 'B':
			// Turn off relay5;
			H_Relay_Off(RELAY_PIN5);
			ClrBit(Status_flag, 6);
			break;
			case 'C':
			H_Lcd_Clr();
			H_Lcd_WriteString("Wait");
			SetBit(flag, 7);
			ClrBit(flag, 5);
			control_flag = 0;		
			break;
			
			default: break;
		}
	}
}

void A_EnterNewData(u8 *Local_u8_User, u8 *Local_u8_Password) /*User Name, Password*/
{
	H_Ext_Eeprom_MultiByteWrite(id/*pointing to next page to write in*/,4, Local_u8_User );
	H_Ext_Eeprom_MultiByteWrite(id/*pointing to next page to write in*/,24, Local_u8_Password );
}
u8 A_RetreiveData(u8 *Local_u8_User) /*User Name, Password*/
{
	H_Ext_Eeprom_MultiByteWrite(Local_u8_User[0], 24, password);
}
void A_Alarm(void)
{
	H_Lcd_Clr();
	H_Lcd_WriteString("Error in user or");
	H_Lcd_GoTo(1,0);
	H_Lcd_WriteString("password");
	_delay_ms(1000);
	H_Lcd_Clr();
	H_Lcd_WriteString("Try Again");
	_delay_ms(1000);
	while(A_Cnt >= 3)
	{
		H_Buzzer_On();
	}
}

void A_Show_Status(void)
{
	u8 cnt = 0;
	
	
	H_Lcd_Clr();
	_delay_ms(10);
	H_Lcd_GoTo(0,0);
	H_Lcd_WriteString("L1 L2 L3 L4 L5 AC Dimming Door");
	H_Lcd_GoTo(1,0);
	if(GetBit(Status_flag, 2) == 1)H_Lcd_WriteString("On ");
	else H_Lcd_WriteString("Off");
	
	if(GetBit(Status_flag, 3) == 1)H_Lcd_WriteString("On ");
	else H_Lcd_WriteString("Off");
	
	if(GetBit(Status_flag, 4) == 1)H_Lcd_WriteString("On ");
	else H_Lcd_WriteString("Off");
	
	if(GetBit(Status_flag, 4) == 1)H_Lcd_WriteString("On ");
	else H_Lcd_WriteString("Off");
	
	if(GetBit(Status_flag, 6) == 1)H_Lcd_WriteString("On ");
	else H_Lcd_WriteString("Off");
	
	if(M_Dio_PinRead(MOTOR_PIN) == 1) H_Lcd_WriteString("On "); 
	else H_Lcd_WriteString("Off");
	
	H_Lcd_WriteString("Off     ");
	
	if(GetBit(Status_flag, 0) == 1)H_Lcd_WriteString("OPENED");
	else H_Lcd_WriteString("CLOSED");
	for(cnt = 0; cnt < 15; cnt++)
	{
		H_Lcd_ShiftLeft();
		_delay_ms(100);
	}
}

















/*

	Enter Admin Data Routine 

// Id -> 0
// username -> mahdy
// password -> 12345
// Location at eeprom || Page -> 0
Every User Will be the same But difference in Page Number
// username bytes -> from 4 to 20;  
// Password bytes -> from 24 to 40;
*/

// 
// H_Ext_Eeprom_Write(7, 255, id);
// strcat(username, "mahdy");
// strcat(password, "12345");
// 
// A_EnterNewData(username, password);
/*
Dimming control 
H_Lcd_Clr();
H_Lcd_WriteString("Enter Intensity ");
H_Lcd_GoTo(1,0);
H_Lcd_WriteString("From 0 to 9 ");
SetBit(flag, 7);
ClrBit(flag, 5);
M_Timer1_PWM_Control_Mode(2);
H_Dimmer_Light_Init();
H_Dimmer_Light_SetLight_Intense((light_intensity+1)*10);
H_Dimmer_Light_Start();
*/