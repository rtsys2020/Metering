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
#ifndef CALENDER_H
#define CALENDER_H

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

#include "bsp.h"


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

/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GPIO PIN DEFINITIONS
*********************************************************************************************************
*/
//extern unsigned int  Year;   
//extern unsigned char Month, Day, DayOfWeek;

//extern unsigned int SolarYear;
//extern unsigned char SolarMonth, SolarDay;

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static unsigned int ChrisLeapCount(unsigned int CurrentYear);
static unsigned int SolarLeapCount(unsigned int CurrentYear);
static unsigned char ChrisLeapYear(unsigned int CurrentYear);
static unsigned char SolarLeapYear(unsigned int CurrentYear);
static void GetWeekday(unsigned int ChrisYear,unsigned char ChrisMonth,unsigned char ChrisDay);

void ChristianToSolar (uint16_t *Year,uint8_t *Month,uint8_t *Day);
void SolarToChristian (uint16_t *SolarYear,uint8_t *SolarMonth,uint8_t *SolarDay);

static void ChrisToSolar(unsigned char* y,unsigned char* m,unsigned char* d) ;

/*
EOF
*/

#endif
