/*
 * UartCfg.h
 *
 * Created: 6/17/2022 9:03:32 PM
 *  Author: mahdy
 */ 


#ifndef UARTCFG_H_
#define UARTCFG_H_

/***************************_SELECT_PARITY_MODE_***************************/

//Option 1 -> [PARITY_DISABLE   ]
//Option 2 -> [PARITY_ODD       ]
//Option 3 -> [PARITY_EVEN      ]

#define  PARITY_MODE   PARITY_DISABLE

/***************************_SELECT_BAUD_RATE_***************************/

#define  BAUD_RATE     9600

/***************************_SELECT_F_OSC_***************************/

#define  F_OSCC         16000000

#endif /* UARTCFG_H_ */