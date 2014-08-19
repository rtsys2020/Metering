#ifndef __RECORD_H__
#define __RECORD_H__

/**********************************************************************
* $Id$		record.h			2013-12-15
*//**
* @file		record.h
* @brief	Contains the defines and function prototypes for Flash and RTC
* @version	1.0
* @date		15. Decm. 2013
* @author	saeed rezaei
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

//
#include "includes.h"

#define EMPTY	0
#define SOME	1
#define FULL	2
/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

typedef struct
{
	uint8_t GlobState;
	uint32_t RD_flash_index;
	uint32_t WR_flash_index;
	uint32_t BulkRD_index;
	
}STX_Sate_t;
//////////////////////////////
#if defined ( __CC_ARM   )
#pragma anon_unions
#endif
typedef struct
{
	uint8_t YEAR;
	uint8_t MONTH;
	uint8_t DOM;
	uint8_t HOUR;
	uint8_t MIN;
	uint8_t SEC;
}time_t;

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif
typedef struct
{
	uint8_t ID[5];
	time_t time;
	uint8_t record1;
	uint8_t record2;
	uint8_t chksum;
	uint16_t RESERVD;
}Record_t;
/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


extern STX_Sate_t g_State;
extern Record_t record_g;
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

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

uint8_t STX_GetRecord(uint8_t PCSendBuff[]);
uint8_t STX_GetRecordStatus(void);
uint8_t STX_IncGetRecord(uint8_t PCSendBuff[]);
uint8_t STX_BulkGetRec(uint32_t index,uint32_t count,uint8_t PCSendBuff[]);
uint8_t STX_PutRec(Record_t Record) ;
uint8_t STX_GetRec(Record_t *Record,uint16_t recNum);
void STX_CalcChksumRec(Record_t *Rec1);
/*
EOF
*/

#endif //__RECORD_H__

