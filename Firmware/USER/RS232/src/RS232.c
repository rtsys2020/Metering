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
#include "rs232.h"
#include "DMA_Handeler.h"
extern  void  delay_ms (uint16_t dly);
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 
// Receive buffer
__IO uint8_t rx_buf[RX_BUF_SIZE];

// Terminal Counter flag for Channel 0
__IO uint32_t Channel0_TC;

// Error Counter flag for Channel 0
__IO uint32_t Channel0_Err;

// Terminal Counter flag for Channel 1
__IO uint32_t Channel1_TC;

// Error Counter flag for Channel 1
__IO uint32_t Channel1_Err;
/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/

/*-------------------------MAIN FUNCTION------------------------------*/
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
void RS232Config(void)
{
	uint8_t *rx_char;
	volatile uint32_t idx;
	uint8_t  stop = 0;
	// UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;
	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	GPDMA_Channel_CFG_Type GPDMACfg;

#if (RS232_UART_NUM == 0)
	/*
	 * Initialize UART0 pin connect
	 * P0.2: U0_TXD
	 * P0.3: U0_RXD
	 */
	PINSEL_ConfigPin(0,2,1);
	PINSEL_ConfigPin(0,3,1);
#elif (RS232_UART_NUM == 1)
	/*
	 * Initialize UART1 pin connect
	 * P0.15: U1_TXD
	 * P0.16: U1_RXD
	 */
	PINSEL_ConfigPin(0,15,1);
	PINSEL_ConfigPin(0,16,1);
#elif (RS232_UART_NUM == 2)
	/*
	 * Initialize UART2 pin connect
	 * P0.10: U2_TXD
	 * P0.11: U2_RXD
	 */
	PINSEL_ConfigPin(0,10,1);
	PINSEL_ConfigPin(0,11,1);
#elif (RS232_UART_NUM == 3)
	/*
	 * Initialize UART2 pin connect
	 * P0.2: U3_TXD
	 * P0.3: U3_RXD
	 */
	PINSEL_ConfigPin(0,2,2);
	PINSEL_ConfigPin(0,3,2);
#elif (RS232_UART_NUM == 4)
	/*
	 * Initialize UART2 pin connect
	 * P0.22: U4_TXD
	 * P2.9: U4_RXD
	 */
	PINSEL_ConfigPin(0,22,3);
	PINSEL_ConfigPin(2,9,3);
#endif
	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 115200 bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UARTConfigStruct.Baud_rate = RS232_BAUDRATE;
	UARTConfigStruct.Databits = UART_DATABIT_8;
	UARTConfigStruct.Parity = UART_PARITY_NONE;
	UARTConfigStruct.Stopbits = UART_STOPBIT_1;
	// Initialize UART0 peripheral with given to corresponding parameter
	UART_Init(_LPC_UART, &UARTConfigStruct);


	/* Initialize FIFOConfigStruct to default state:
	 * 				- FIFO_DMAMode = DISABLE
	 * 				- FIFO_Level = UART_FIFO_TRGLEV0 ???????????
	 * 				- FIFO_ResetRxBuf = ENABLE
	 * 				- FIFO_ResetTxBuf = ENABLE
	 * 				- FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	// Enable DMA mode in UART
	UARTFIFOConfigStruct.FIFO_DMAMode = ENABLE;

	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig(_LPC_UART, &UARTFIFOConfigStruct);

//	// Enable UART Transmit
//	UART_TxCmd(_LPC_UART, ENABLE);


//	/* GPDMA Interrupt configuration section ------------------------------------------------- */

//    /* Initialize GPDMA controller */
//	GPDMA_Init();
////	/* preemption = 1, sub-priority = 1 */
//	NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));//???????????????
}
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
uint8_t RS232Send(uint8_t *buff,uint16_t len)
{
	GPDMA_Channel_CFG_Type GPDMACfg;
	uint16_t dly;
	dly = (len*8000)/RS232_BAUDRATE;
	delay_ms(dly);
	//
	UART_TxCmd(_LPC_UART, ENABLE);
		/* Wait for GPDMA on UART0 Tx processing complete */
//	if ((Channel0_TC == 0) ){//&& (Channel0_Err == 1)
	/* Setting GPDMA interrupt */
    // Disable interrupt for DMA
    NVIC_DisableIRQ (DMA_IRQn);
//    /* preemption = 1, sub-priority = 1 */
//    NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));//???????????????

	// Setup GPDMA channel --------------------------------
	// channel 0
	GPDMACfg.ChannelNum = RS232_DMA_TX_CH;
	// Source memory
	GPDMACfg.SrcMemAddr = (uint32_t) buff;
	// Destination memory - don't care
	GPDMACfg.DstMemAddr = 0;
	// Transfer size
	GPDMACfg.TransferSize = len;
	// Transfer width - don't care
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	// Source connection - don't care
	GPDMACfg.SrcConn = 0;
	// Destination connection
	GPDMACfg.DstConn = _GPDMA_CONN_UART_Tx;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);
	/* Reset terminal counter */
	Channel0_TC = 0;
	/* Reset Error counter */
	Channel0_Err = 0;

    // Enable interrupt for DMA
  NVIC_EnableIRQ (DMA_IRQn);
	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(RS232_DMA_TX_CH, ENABLE);	
	//return 0;	//send data sucess
//}
//else
//{
//	//LPC_GPDMACH0->CSrcAddr
	while((Channel0_TC == 0) );
	return 0; //send error
//}
}
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
uint8_t RS232Recev(uint8_t *buff,uint16_t len)
{
	GPDMA_Channel_CFG_Type GPDMACfg;
	uint16_t dly;
	dly = (len*8000)/RS232_BAUDRATE;

	/* Setting GPDMA interrupt */
//    // Disable interrupt for DMA
//  NVIC_DisableIRQ (DMA_IRQn);
//    /* preemption = 1, sub-priority = 1 */
//  NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));//???????????????
		// Setup GPDMA channel --------------------------------
	// channel 1
	GPDMACfg.ChannelNum = RS232_DMA_RX_CH;
	// Source memory - don't care
	GPDMACfg.SrcMemAddr = 0;
	// Destination memory
	GPDMACfg.DstMemAddr = (uint32_t )buff;
	// Transfer size
	GPDMACfg.TransferSize = len;
	// Transfer width - don't care
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
	// Source connection
	GPDMACfg.SrcConn = _GPDMA_CONN_UART_Rx;
	// Destination connection - don't care
	GPDMACfg.DstConn = 0;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	//////////////////////////////
	GPDMA_Setup(&GPDMACfg);
		/* Reset terminal counter */
	Channel1_TC = 0;
	/* Reset Error counter */
	Channel1_Err = 0;

    // Enable interrupt for DMA
  NVIC_EnableIRQ (DMA_IRQn);
	// Make sure GPDMA channel 1 is disabled
	GPDMA_ChannelCmd(RS232_DMA_RX_CH, ENABLE);	
	/* Wait for GPDMA on UART0 Tx processing complete */
		
  while ((Channel1_TC == 0) ){//&& (Channel1_Err == 0)
		//return 1;//receve data
		delay_ms(dly+1);
	}
//	else
//	{
		return 0;//receve error
//	}
}
