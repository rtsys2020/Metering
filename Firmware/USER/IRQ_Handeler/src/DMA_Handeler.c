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


#include "DMA_Handeler.h"
#include "includes.h"
#include "rs232.h"
#include "adc.h"

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */

/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 
extern const LPC_GPDMACH_TypeDef *pGPDMACh[8];

/*********************************************************************//**
 * @author             
 * @brief 	
 * @date 
 * @version  
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		GPDMA interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void DMA_IRQHandler (void)
{
	uint32_t tmp;
	LPC_GPDMACH_TypeDef *pDMAch;
	
	// Get Channel pointer
		// Scan interrupt pending
	for (tmp = 0; tmp <= 7; tmp++) {
		pDMAch = (LPC_GPDMACH_TypeDef *) pGPDMACh[tmp];
		if (GPDMA_IntGetStatus(GPDMA_STAT_INT, tmp)){
			// Check counter terminal status
			if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, tmp)){
				// Clear terminate counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, tmp);

				switch (tmp){					
					case HDLC_DMA_TX_CH:
						UART_SendDMAcompleted(HDLC_UART_PORT);
						GPDMA_ChannelCmd(HDLC_DMA_TX_CH, DISABLE);
						break;	
#if MCI_DMA_ENABLED						
					case MCI_DMA_WRITE_CHANNEL:
            dmaWrCh_TermianalCnt++;
						break;
					case MCI_DMA_READ_CHANNEL:
            dmaRdCh_TermianalCnt++;
						break;	
#endif		
					//pGPDMACh[ADC_DMA_CHANNEL]
					default:
						break;
				}

			}
				// Check error terminal status
			if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, tmp)){
				// Clear error counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, tmp);
				switch (tmp){
					case HDLC_DMA_TX_CH:
						UART_SendDMAcompleted(HDLC_UART_PORT);
						GPDMA_ChannelCmd(HDLC_DMA_TX_CH, DISABLE);
						break;					
#if MCI_DMA_ENABLED					
					case MCI_DMA_WRITE_CHANNEL:
						dmaWrCh_ErrorCnt++;
						break;
					case MCI_DMA_READ_CHANNEL:
						dmaRdCh_ErrorCnt++;
						break;		
#endif	
					default:
						break;
				}
			}
		}
	}
}
/*
EOF
*/


