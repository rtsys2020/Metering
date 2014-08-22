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
#ifndef I3C_H
#define I3C_H
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

#include "includes.h"


#define I3C_SDA_GPIO	LPC_GPIO5
#define I3C_SDA_PIN	2

#define I3C_SCL_GPIO	LPC_GPIO5
#define I3C_SCL_PIN	3
/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
typedef struct 
{
	uint8_t SlaveAddress;
	uint8_t Data[10];
	uint8_t Count;
}PIIC_IO_DESC;

/*
*********************************************************************************************************
*                                               DEFINIATION
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
*                                           DEFINITIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void makeOutputSDA(void);
void makeInputSDA(void);
void changeStateSDA(uint8_t bitVal);
void changeStateSCL(uint8_t bitVal);
uint8_t readSDA(void);
uint8_t HW_Write (PIIC_IO_DESC* pInData);
uint8_t HW_Read (PIIC_IO_DESC* pInData ,PIIC_IO_DESC* pOutData);
/*
EOF
*/
#endif

