/*
 * Timer_1_Cfg_.h
 *
 * Created: 7/23/2022 9:48:59 PM
 *  Author: Ahmed
 */ 


#ifndef TIMER_1_CFG__H_
#define TIMER_1_CFG__H_
/******************************************_SELECT_PWM_MODE_********************************************/
// option 1 -> [ NON_Inverted ]
// option 2 -> [ Inverted   ]
#define PWM_MODE           NON_Inverted
/******************************************_SELECT_TIMER1_PWM_MODE_********************************************/
// option 1 -> [ Phase_Correct_PWM ]
// option 2 -> [ Fast_PWM   ]
#define TIMER1_PWM_MODE           Fast_PWM

/*********************************************_SELECT_F_OSC_********************************************/
#define F_OSC                   16
/***************************************_SELECT_TIMER1_PRESCALER_********************************************/
// option 1 -> [ 8]
// option 2 -> [ 64 ]
// option 3 -> [ 256  ]
/*#define Timer1_Prescaler     64*/




#endif /* TIMER_1_CFG__H_ */