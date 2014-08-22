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

#include "EXTIT_Handeler.h"
#include "osinit.h"
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

IRQ_msg_t EINT0_msg_p;
IRQ_msg_t EINT1_msg_p;
IRQ_msg_t EINT2_msg_p;
IRQ_msg_t EINT3_msg_p;
/*********************************************************************//**
 * @brief		EINT0 Interrupt Handler
 * @param[in]	None
 *
 * @return 		None
 **********************************************************************/
void EINT0_IRQHandler(void) 
{
	uint8_t i;
	//TP_PIN_SET();
	OSQPost(IRQ_Q,&EINT0_msg_p);
	LPC_SC->EXTINT = 0x00000001;		/* clear interrupt */
	
}
/*********************************************************************//**
 * @brief		EINT0 Interrupt Handler
 * @param[in]	None
 *
 * @return 		None
 **********************************************************************/
void EINT1_IRQHandler(void)
{
 //LPC_GPIO1->SET = 0x8;//pin p1.3
	OSQPost(IRQ_Q,&EINT1_msg_p);
	LPC_SC->EXTINT |= 0x00000002;		/* clear interrupt */

//LPC_GPIO1->CLR = 0x8;//pin p1.3	

}
/*********************************************************************//**
 * @brief		EINT0 Interrupt Handler
 * @param[in]	None
 *
 * @return 		None
 **********************************************************************/
void EINT2_IRQHandler(void)
{
	OSQPost(IRQ_Q,&EINT2_msg_p);
	LPC_SC->EXTINT |= 0x00000004;		/* clear interrupt */

}
/*********************************************************************//**
 * @brief		EINT0 Interrupt Handler
 * @param[in]	None
 *
 * @return 		None
 **********************************************************************/
void EINT3_IRQHandler(void)
{
	////handel camera hsync and increment row
	OSQPost(IRQ_Q,&EINT3_msg_p);
	LPC_SC->EXTINT |= 0x00000008;		/* clear interrupt */
}
/*********************************************************************//**
 * @brief		EINT0 Interrupt Handler
 * @param[in]	None
 *
 * @return 		None
 **********************************************************************/
void EINT_BSP_Init(EINT_init_t *eint)
{
	//EXTI_InitTypeDef exti_cfg;
	if(eint == NULL)
		return;
	PINSEL_ConfigPin (eint->port, eint->pin, eint->func_num);
	PINSEL_SetPinMode(eint->port,eint->pin,IOCON_MODE_PLAIN);
	GPIO_SetDir(eint->port,1<<eint->pin,0);
	
		
//	exti_cfg.EXTI_Line = EXTI_EINT0;
//	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
//	exti_cfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
	if(eint->exti_cfg == NULL)
		return;
	EXTI_Config(eint->exti_cfg);
	if(eint->irq_msg == NULL)
		return;
	if(eint->eint_num == 0)
	{
		//EINT0_msg_p = eint->irq_msg;
		memcpy(&EINT0_msg_p,eint->irq_msg,sizeof(IRQ_msg_t));
		NVIC_EnableIRQ(EINT0_IRQn);
	}
	else if(eint->eint_num == 1)
	{
		memcpy(&EINT1_msg_p,eint->irq_msg,sizeof(IRQ_msg_t));
		NVIC_EnableIRQ(EINT1_IRQn);
	}
	else if(eint->eint_num == 2)
	{
		memcpy(&EINT2_msg_p,eint->irq_msg,sizeof(IRQ_msg_t));
		NVIC_EnableIRQ(EINT2_IRQn);
	}
	else if(eint->eint_num == 3)
	{
		memcpy(&EINT3_msg_p,eint->irq_msg,sizeof(IRQ_msg_t));
		NVIC_EnableIRQ(EINT3_IRQn);
	}
}





