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

#ifdef EINT0_EN
#define EINT0_PORT	LPC_GPIO2
#define EINT0_PIN	10
#define EINT0_FUNC_NUM	2
#endif

#ifdef EINT1_EN
#define EINT1_PORT	LPC_GPIO2
#define EINT1_PIN	10
#define EINT1_FUNC_NUM	2
#endif

#ifdef EINT2_EN
#define EINT2_PORT	LPC_GPIO2
#define EINT2_PIN	10
#define EINT2_FUNC_NUM	2
#endif

#ifdef EINT3_EN
#define EINT3_PORT	LPC_GPIO2
#define EINT3_PIN	10
#define EINT3_FUNC_NUM	2
#endif
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 
 /*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
//extern volatile uint32_t CamRowIndex,CamDataIndex;
//extern volatile uint8_t Cam_Start_cap,*pCambuf;
//extern volatile uint32_t row;

/*********************************************************************//**
 * @brief		EINT0 Interrupt Handler
 * @param[in]	None
 *
 * @return 		None
 **********************************************************************/
void EINT0_IRQHandler(void) //p2.10  irq
{
//	LPC_GPIO1->SET = 0x4;//pin p1.2
	LPC_SC->EXTINT = 0x00000001;		/* clear interrupt */
	
}
/*********************************************************************//**
 * @brief		EINT0 Interrupt Handler
 * @param[in]	None
 *
 * @return 		None
 **********************************************************************/
void EINT1_IRQHandler(void)//p2.11  irqb
{
 //LPC_GPIO1->SET = 0x8;//pin p1.3
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
	LPC_SC->EXTINT |= 0x00000008;		/* clear interrupt */
}


void Eint_init(void)
{
#ifdef EINT0_EN	
	PINSEL_ConfigPin (EINT0_PORT, EINT0_PIN,EINT0_FUNC_NUM);
	PINSEL_SetPinMode(EINT0_PORT,EINT0_PIN,IOCON_MODE_PLAIN);
	GPIO_SetDir(EINT0_PORT,1<<EINT0_PIN,0);
#endif	
#ifdef EINT1_EN	
	PINSEL_ConfigPin (EINT1_PORT, EINT1_PIN, EINT1_FUNC_NUM);
	PINSEL_SetPinMode(EINT1_PORT,EINT1_PIN,IOCON_MODE_PLAIN);
	GPIO_SetDir(EINT1_PORT,1<<EINT1_PIN,0);
#endif	
#ifdef EINT2_EN	
	PINSEL_ConfigPin (EINT2_PORT, EINT2_PIN, EINT2_FUNC_NUM);
	PINSEL_SetPinMode(EINT2_PORT,EINT2_PIN,IOCON_MODE_PLAIN);
	GPIO_SetDir(EINT2_PORT,1<<EINT2_PIN,0);
#endif	
#ifdef EINT3_EN	
	PINSEL_ConfigPin (EINT3_PORT, EINT3_PIN, EINT3_FUNC_NUM);
	PINSEL_SetPinMode(EINT3_PORT,EINT3_PIN,IOCON_MODE_PLAIN);
	GPIO_SetDir(EINT3_PORT,1<<EINT3_PIN,0);
#endif		
	EXTI_Init();
#ifdef EINT0_EN	
	exti_cfg.EXTI_Line = EXTI_EINT0;
	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	exti_cfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
	EXTI_Config(&exti_cfg);
	NVIC_EnableIRQ(EINT0_IRQn);
#endif

#ifdef EINT1_EN	
	exti_cfg.EXTI_Line = EXTI_EINT1;
	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	exti_cfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
	EXTI_Config(&exti_cfg);
	NVIC_EnableIRQ(EINT1_IRQn);
#endif

#ifdef EINT2_EN	
	exti_cfg.EXTI_Line = EXTI_EINT1;
	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	exti_cfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
	EXTI_Config(&exti_cfg);
	NVIC_EnableIRQ(EINT2_IRQn);
#endif

#ifdef EINT3_EN	
	exti_cfg.EXTI_Line = EXTI_EINT1;
	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	exti_cfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
	EXTI_Config(&exti_cfg);
	NVIC_EnableIRQ(EINT3_IRQn);
#endif

	return;
}



