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

#ifndef UART_HANDELER_H
#define UART_HANDELER_H

 // Terminal Counter flag, Error Counter flag for Channel 0
//extern uint32_t dmaWrCh_TermianalCnt, dmaWrCh_ErrorCnt;
//extern uint32_t dmaRdCh_TermianalCnt, dmaRdCh_ErrorCnt;

#define DAC_DMA_CH												0
#define MCI_DMA_WRITE_CHANNEL            (2)//0
#define MCI_DMA_READ_CHANNEL             (3)//1
#define HDLC_DMA_TX_CH 										5
#define MIFARE_DMA_TX_CH 										6
#define ZKFINGER_DMA_TX_CH 									7
#define ADC_DMA_CHANNEL											4

#define HDLC_UART_PORT			0//?????????

//#define MIFARE_UART_PORT		2
//#define ZKFINGER_UART_PORT	2

void DMA_IRQHandler (void);
#endif
