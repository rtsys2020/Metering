/**********************************************************************
* $Id$		Handeler.c			2013-10
*//**
* @file		Handeler.c
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
#include "UART_Handeler.h"
#include "includes.h"
#include "uart.h"
#include "hdlc.h"

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private FUNCTIONS
 * @{
 */

/* Interrupt service routines */
extern void UART_IntErr(uint8_t bLSErrType);
extern void UART_IntTransmit(UART_ID_Type UartID,uint8_t mode);
extern void UART_IntReceive(UART_ID_Type UartID,UART_ISR_Fun_t);


/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 




/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
#if (UART_NUM0_INT_EN == 1)
void UART0_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
#ifdef _UCOS_	
	OSIntEnter();
#endif	
	

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(UART_0);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(UART_0);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}
	
	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){	
			UART_IntReceive(UART_0,UART0_ISR_HANDLER);
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			//UART_IntTransmit(UART_0,UARTS_MODE[UART_0]);
	}
#ifdef _UCOS_
	OSIntExit();
#endif	
}

#endif


/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
#if (UART_NUM1_INT_EN == 1)
void UART1_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
#ifdef _UCOS_	
	OSIntEnter();
#endif	
	

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(UART_1);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(UART_1);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			//UART_IntReceive(UART_1,UART1_ISR_HANDLER);
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			//UART_IntTransmit(UART_1,UARTS_MODE[UART_1]);
	}
#ifdef _UCOS_
	OSIntExit();
#endif	
}

#endif

/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
#if (UART_NUM2_INT_EN == 1)
void UART2_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
#ifdef _UCOS_	
	OSIntEnter();
#endif	
	
	/* Determine the interrupt source */
	intsrc = UART_GetIntId(UART_2);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(UART_2);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			//UART_IntReceive(UART_2,UART2_ISR_HANDLER);
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			//UART_IntTransmit(UART_2,UARTS_MODE[UART_2]);
	}
#ifdef _UCOS_
	OSIntExit();
#endif	
}

#endif

/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
#if (UART_NUM3_INT_EN == 1)
void UART3_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
#ifdef _UCOS_	
	OSIntEnter();
#endif	
	

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(UART_3);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(UART_3);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			//UART_IntReceive(UART_3,UART3_ISR_HANDLER);
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			//UART_IntTransmit(UART_3,UARTS_MODE[UART_3]);
	}
#ifdef _UCOS_
	OSIntExit();
#endif	
}

#endif

/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
#if (UART_NUM_INT_EN == 1)
void UART4_IRQHandler(void)
{
#ifdef _UCOS_	
	OSIntEnter();
#endif	
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(UART_4);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(UART_4);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			//UART_IntReceive(UART_4,UART4_ISR_HANDLER);
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			//UART_IntTransmit(UART_4,UARTS_MODE[UART_4]);
	}
#ifdef _UCOS_
	OSIntExit();
#endif	
}

#endif
