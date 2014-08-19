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
#ifndef SETTING_H
#define SETTING_H

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */



#define ENGLISH	0
#define FARSI	1
#define ARABIC	3

#define SPEAKER_OFF 0
#define SPEAKER_ON	1

#define BACKLIGHT_OFF 0
#define BACKLIGHT_ON	1
/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
typedef struct
{
	uint8_t Language;
	uint8_t Calendar;
	uint8_t Daylight;
	uint8_t Speaker;
	uint8_t Backlight;
	uint8_t Standby;
	uint32_t Password;
	uint32_t SerialNumber;
	uint32_t FactoryCode;
	uint8_t RepeatTime;
	uint8_t ValidityCheck;
	uint8_t F1Key;
	uint8_t F2Key;	
	uint8_t MisionKey;
	uint8_t VacationKey;
	uint8_t MisionCard;
	uint8_t VacationCard;
	uint32_t SessionTimeout;
	uint8_t TRTAddress;
	uint8_t IP[4];
	uint8_t SUBNET[4];
	uint8_t GETWAY[4];
	uint8_t SERVER[4];
	uint8_t Baud;
	uint8_t Finger;
	uint8_t Mifare;
	uint8_t MifareSector;
	uint8_t MifareBlock;
	uint8_t ContactlessMode;
}setup_t;

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


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
uint8_t SetParameter(uint8_t ParameterIndex,uint8_t PCRecBuff[]);
uint8_t GetParameter(uint8_t ParameterIndex,uint8_t PCSendBuff[]);
/*
EOF
*/

#endif
