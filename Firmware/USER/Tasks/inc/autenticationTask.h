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
#ifndef _AUTENTICATIONTASK_H_
#define  _AUTENTICATIONTASK_H_
 /*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


#include "includes.h"

//<o> Autentication Task Stack Size
#define  APP_TASK_AUTEN_STK_SIZE					256u
//<o> Autentication Task Priority Size
#define   APP_TASK_AUTEN_PRIO							(13)
//<o> Autentication Task Message Size
#define AUTEN_MSGQ_SIZE 5

typedef struct
{
	uint64_t UserID;
	uint8_t type;
}autentication_t;



extern OS_EVENT *AutenQ;
extern void *AutenListQ[AUTEN_MSGQ_SIZE];


void  App_AutenticationkTaskCreate (void);
static void AutenticationTask (void) ;

#endif



