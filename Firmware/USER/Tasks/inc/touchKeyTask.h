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
#ifndef TOUCHKEYTASK_H
#define TOUCHKEYTASK_H
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
 
 /*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#include "includes.h"

//<o> TouchKey Task Stack Size
#define	 APP_TASK_TOUCHKEY_STK_SIZE											256u
//<o> TouchKey Task Priority
#define		APP_TASK_TOUCHKEY_PRIO					(10)


extern OS_EVENT *TouchKeySem;


typedef enum {
	KeyVACATION = 0x4000,KeyMISSION = 0x0040,KeyEXIT = 0x000A,KeyENTER = 0x0100,
	
	KEY1 = 0x0200,			KEY2 = 0x000B,			KEY3 = 0x00002,		KEYESC = 0x0000,
	
	KEY4=  0x0400,			KEY5 = 0x000c,			KEY6 = 0x0004,		KEYMENU = 0x0001,
	
	KEY7 = 0x000D,			KEY8 = 0x800,				KEY9 = 0x0008,		KEYUP = 0x2000,
	
	KEYC = 0x000E,			KEY0 = 0x0010,			KEYOK = 0x1000,		KEYDOWN = 0x0020
}KeyEnum_t;

void  App_TouchKeyTaskCreate (void);
uint8_t TouchKey_Get(void);

/*
EOF
*/
#endif

