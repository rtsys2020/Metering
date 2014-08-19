/**********************************************************************
* $Id$		DMA_Handeler.h			2013-06-21
*//**
* @file		Handeler.h
* @brief	Contains DMA Interrupt Handeler  
*			
* @version	1.0
* @date		21. Decem. 2011
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

#ifndef EXTI_HANDELER_H
#define EXTI_HANDELER_H
#include "includes.h"
#include "irqhandlertask.h"

#define ADE7953_IRQA_PORT	2
#define ADE7953_IRQA_PIN	10
#define ADE7953_IRQA_FUNC_NUM	1

typedef struct
{
	uint8_t port;
	uint8_t pin;
	uint8_t func_num;
	EXTI_InitTypeDef *exti_cfg;
	uint8_t eint_num;
	IRQ_msg_t *irq_msg;
}EINT_init_t;

void EINT_BSP_Init(EINT_init_t *eint);

#endif
