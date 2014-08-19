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

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

#include "includes.h"
#include "DMA_Handeler.h"
#include "adc.h"


/* Example group ----------------------------------------------------------- */
/** @defgroup Adc_Burst		ADC Burst
 * @ingroup 
 * @{
 */

/************************** PRIVATE DEFINITIONS ***********************/
#if (ADC_DMA_EN == 1 )
uint32_t ADC_buf[20];		
uint8_t ADCNumOfEnCh = 0;

// Terminal Counter flag for Channel 0
__IO uint32_t DMA_ADC_TC;
// Error Counter flag for Channel 0
__IO uint32_t DMA_ADC_Err;
#endif /*__DMA_USED__*/

/************************** PRIVATE FUNCTION *************************/


/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/


/*-------------------------PRIVATE FUNCTIONS------------------------------*/


/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main ADC program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void BSP_ADC_Init(void)
{
	volatile uint32_t tmp;

  GPDMA_Channel_CFG_Type GPDMACfg;


/* Configuration for ADC:
*  select: ADC channel 2
*  		ADC channel 3
*  ADC conversion rate = 400KHz
*/
	ADC_Init(LPC_ADC, ADC_FREQ);	
	
#if (ADC_IN0_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.0 on P0.23
	*/
	PINSEL_ConfigPin(0, 23, 1);
  PINSEL_SetAnalogPinMode(0,23,ENABLE);
	ADC_ChannelCmd(LPC_ADC,0,ENABLE);
//	ADCNumOfEnCh++;
#endif
	
#if (ADC_IN1_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.1 on P0.24
	*/
	PINSEL_ConfigPin(0, 24, 1);
  PINSEL_SetAnalogPinMode(0,24,ENABLE);
	ADC_ChannelCmd(LPC_ADC,1,ENABLE);
	ADCNumOfEnCh++;
#endif

#if (ADC_IN2_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.2 on P0.25
	*/
	PINSEL_ConfigPin(0, 25, 1);
  PINSEL_SetAnalogPinMode(0,25,ENABLE);
	ADC_ChannelCmd(LPC_ADC,2,ENABLE);
	//ADCNumOfEnCh++;
#endif
#if (ADC_IN3_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.3 on P0.26
	*/
	PINSEL_ConfigPin(0, 26, 1);
  PINSEL_SetAnalogPinMode(0,26,ENABLE);
	ADC_ChannelCmd(LPC_ADC,3,ENABLE);
	ADCNumOfEnCh++;
#endif
#if (ADC_IN4_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.4 on P1.30
	*/
	PINSEL_ConfigPin(1, 30, 3);
  PINSEL_SetAnalogPinMode(1,30,ENABLE);
	ADC_ChannelCmd(LPC_ADC,4,ENABLE);
	ADCNumOfEnCh++;
#endif

#if (ADC_IN5_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.5 on P1.31
	*/
	PINSEL_ConfigPin(1, 31, 3);
  PINSEL_SetAnalogPinMode(1,31,ENABLE);
	ADC_ChannelCmd(LPC_ADC,5,ENABLE);
	ADCNumOfEnCh++;
#endif

#if (ADC_IN6_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.6 on P0.12
	*/
	PINSEL_ConfigPin(0, 12, 3);
  PINSEL_SetAnalogPinMode(0,12,ENABLE);
	ADC_ChannelCmd(LPC_ADC,6,ENABLE);
	ADCNumOfEnCh++;
#endif

#if (ADC_IN7_EN == 1)
	/*
	* Init ADC pin connect
	* AD0.7 on P0.12
	*/
	PINSEL_ConfigPin(0, 13, 3);
  PINSEL_SetAnalogPinMode(0,13,ENABLE);
	ADC_ChannelCmd(LPC_ADC,7,ENABLE);
	ADCNumOfEnCh++;
#endif


#if (ADC_DMA_EN == 1)
     /* Initialize GPDMA controller */
	//NVIC_DisableIRQ(DMA_IRQn);	 
	//GPDMA_Init();
	// Setup GPDMA channel --------------------------------
	// channel 0
	GPDMACfg.ChannelNum = ADC_DMA_CHANNEL;
	// Source memory - unused
	GPDMACfg.SrcMemAddr = 0;
	// Destination memory
	GPDMACfg.DstMemAddr = (uint32_t)ADC_buf;
	// Transfer size
	GPDMACfg.TransferSize = ADCNumOfEnCh*NUM_OF_SAMPLE;
	// Transfer width - unused
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
	// Source connection
	GPDMACfg.SrcConn = GPDMA_CONN_ADC;
	// Destination connection - unused
	GPDMACfg.DstConn = 0;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	/* Enable GPDMA interrupt */
	GPDMA_Setup(&GPDMACfg);
	//NVIC_EnableIRQ(DMA_IRQn);
		// Enable GPDMA channel 1
	GPDMA_ChannelCmd(ADC_DMA_CHANNEL, ENABLE);
		//Start burst conversion
	ADC_BurstCmd(LPC_ADC,ENABLE);

#endif
	
}
