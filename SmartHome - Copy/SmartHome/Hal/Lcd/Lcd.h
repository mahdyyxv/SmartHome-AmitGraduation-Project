/*
 * Lcd.h
*/ 


#ifndef LCD_H_
#define LCD_H_

/*************************************************_INCLUDES_********************************************/

#include "LcdCfg.h"
#include "Dio.h"
#include "StdTypes.h"
#define F_CPU 16000000UL
#include <util/delay.h>

/**************************************************_MACROS_*********************************************/

#define LCD_4_BIT_MODE_1                0x33
#define LCD_4_BIT_MODE_2                0x32
#define LCD_4_BIT_MODE_3                0x28
#define LCD_DISPLAY_ON_CURSUR_OFF       0x0C
#define LCD_CLEAR                       0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_SHIFT_RIGHT                 0x1C
#define LCD_SHIFT_LEFT                  0x18
#define NULL_                           '\0'

/************************************************_PROTOTYPES_********************************************/

void H_Lcd_Init(void);
void H_Lcd_WriteCharacter(u8);
void H_Lcd_WriteCommand(u8);
void H_Lcd_WriteString(u8*);
void H_Lcd_WriteNumber(s32);
void H_Lcd_Clr(void);
void H_Lcd_GoTo(u8,u8);
void H_Lcd_ShiftRight(void);
void H_Lcd_ShiftLeft(void);

#endif /* LCD_H_ */