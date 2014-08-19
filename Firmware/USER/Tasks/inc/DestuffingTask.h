/**********************************************************************
* $Id$		Finger.h			2013-12-15
*//**
* @file		Finger.h
* @brief	Contains the defines and function prototypes for finger reader
* @version	1.0
* @date		28. Decm. 2013
* @author	Amin Ezhdehakosh
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#ifndef DESTUFFINGTASK_H_
#define  DESTUFFINGTASK_H_

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#include "includes.h"


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/
//<o> Destuffing message size
#define DESTUFFING_MSG_SIZE 4
//<o> Destuffing Task Priority
#define DESTUFFING_TASK_PRIO 11
//<o> Destuffing TaskStack Size
#define DESTUFFING_TASK_STK_SIZE 64


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
enum hdlc_communication_port {
  UART_PORT0,
  UART_PORT1,
	UART_PORT2,
	UART_PORT3,
	UART_PORT4,
	UART_PORT5,
  ETHERNET_PORT
};

//typedef struct 
//{
//	enum hdlc_communication_port port;
//	uint16_t len;
//	INT8S *dataframe;
//}comunication_t;

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/
extern OS_EVENT *RcvDestuffingQ;


/*
*********************************************************************************************************
*                                          GPIO PIN DEFINITIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void App_DestuffingQueueCreate (void);
void App_DestuffingTaskCreate (void);
void DestuffingTask (void *pdata);


/*
EOF
*/

#endif

/*
EOF
*/

