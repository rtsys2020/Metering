/**********************************************************************
* $Id$		template.c			2013-10
*//**
* @file		template.c
* @brief	Use as Template
*			
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee ElmoSanaat Reasearch And Development Team
* 
* Copyright(C) 2013, ElmoSanaat.co
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
* documentation is hereby granted, under ElmoSanaat '
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with ElmoSanaat  .  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/
#ifndef STUFFINGTASK_H
#define STUFFINGTASK_H
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


#include "includes.h"



//<o> Stuffing Message Size
#define STUFFING_MSG_SIZE 4
//<o> Stuffing Task Priority
#define STUFFING_TASK_PRIO 12
//<o> Stuffing Task Stack Size
#define STUFFING_TASK_STK_SIZE 64


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/
extern OS_EVENT *StuffingQ;


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
void App_StuffingQueueCreate (void);
void App_StuffingTaskCreate (void);
void StuffingTask (void *pdata);

/*
EOF
*/
#endif

