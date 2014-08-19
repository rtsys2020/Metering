/**********************************************************************
* $Id$		template.c			2013-10
*//**
* @file		rs232.c
* @brief	Use for rs232 functionality
*			
* @version	1.0
* @date		23. decm. 2013
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
#include "GPIO_Handeler.h"

//#pragma o3



/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */



/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 
 /*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @author          Amin Ezhdehakosh
 * @brief 			ISR for handling GPIO interrupts
 * @date 			2014/01/08
 * @version  
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/


void GPIO_IRQHandler(void)
{
	//OSIntEnter();

// if(LPC_GPIOINT->IO0IntStatF & VSYNC_MASK)
//	{
//		//start of frame
//		LPC_GPIOINT->IO0IntClr = VSYNC_MASK;
//		
//	}	
	if(GPIO_GetIntStatus(0, 5, 1))
	{
		
		GPIO_ClearInt(0, 1<<5);
	}
		
	//OSIntExit();
}


