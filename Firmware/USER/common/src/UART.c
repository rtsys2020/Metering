/**********************************************************************
* $Id$		Uart_Interrupt.c			2011-06-02
*//**
* @file		Uart_Interrupt.c
* @brief	This example describes how to using UART in interrupt mode
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
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
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

#include "uart.h"
#include "DMA_Handeler.h"

/** @defgroup UART_Interrupt	UART Interrupt
 * @ingroup UART_Examples
 * @{
 */


	
IRQn_Type UARTS_IRQn[5] = {UART0_IRQn,UART1_IRQn,UART2_IRQn,UART3_IRQn,UART4_IRQn};

uint32_t GPDMA_CONN_UART_Tx[5]={GPDMA_CONN_UART0_Tx,\
																GPDMA_CONN_UART1_Tx,\
																GPDMA_CONN_UART2_Tx,\
																GPDMA_CONN_UART3_Tx,\
																GPDMA_CONN_UART4_Tx,};

/************************** PRIVATE TYPES *************************/



/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/

OS_EVENT *UartDMAQ[5];
void *UartDMABuffQ[5][UDMA_MSG_SIZE];

uint8_t UartDMABuffDataQ[5];
OS_EVENT *UART_DMA_Semaphore[5];


/********************************************************************//**
 * @brief 		 UART_WaitDMAcomplete wait for dma transfer data complete
 * @param[in]	uart port number
 * @return 		None
 *********************************************************************/
void UART_WaitDMAcomplete(uint8_t uart_id)
{
	INT8U err;
	OSSemPend(UART_DMA_Semaphore[uart_id], 0, &err);
}
/********************************************************************//**
 * @brief 		UART_SendDMAcompleted send signal for dma sed data function to relese
 * @param[in]	uart port number
 * @return 		None
 *********************************************************************/
void UART_SendDMAcompleted(uint8_t uart_id)
{
	INT8U err;
	err = OSSemPost(UART_DMA_Semaphore[uart_id]);
}
/********************************************************************//**
 * @brief 		UART receive function (ring buffer used)
 * @param[in]	None
 * @return 		None
 *********************************************************************/
void UART_IntReceive(UART_ID_Type UartID,UART_ISR_Fun_t function)
{
	uint8_t tmpc[5];
	uint32_t rLen;

	while(1){
		// Call UART read function in UART driver
		rLen = UART_Receive(UartID, tmpc, 1, NONE_BLOCKING);
		// If data received
		if (rLen){
			/* Check if buffer is more space
			 * If no more space, remaining character will be trimmed out
			 */
			function(UartID,tmpc[0]);
		}
		// no more data
		else {
			break;
		}
	}
}

/********************************************************************//**
 * @brief 		UART Interrupt receive Disable (ring buffer used)
 * @param[in]	None
 * @return 		None
 *********************************************************************/
void UART_RecvDisable(UART_ID_Type UartID)
{
    /* Enable UART Rx interrupt */
	UART_IntConfig(UartID, UART_INTCFG_RBR, DISABLE);
	/* Enable UART line status interrupt */
	UART_IntConfig(UartID, UART_INTCFG_RLS, DISABLE);
}

/********************************************************************//**
 * @brief 		UART Interrupt receive Enable (ring buffer used)
 * @param[in]	None
 * @return 		None
 *********************************************************************/
void UART_RecvEnable(UART_ID_Type UartID)
{
    /* Enable UART Rx interrupt */
	UART_IntConfig(UartID, UART_INTCFG_RBR, ENABLE);
	/* Enable UART line status interrupt */
	UART_IntConfig(UartID, UART_INTCFG_RLS, ENABLE);
}
/*********************************************************************//**
 * @brief		Send a block of data via UART peripheral
 * @param[in]	UARTx	Selected UART peripheral used to send data, should be:
 *				- UART_0: UART0 peripheral
 *				- UART_1: UART1 peripheral
 *				- UART_2: UART2 peripheral
 *				- UART_3: UART3 peripheral
 *				- UART_4: UART4 peripheral
 * @param[in]	txbuf 	Pointer to Transmit buffer
 * @param[in]	buflen 	Length of Transmit buffer
 * @param[in] 	flag 	Flag used in  UART transfer, should be
 * 						NONE_BLOCKING or BLOCKING
 * @return 		Number of bytes sent.
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 **********************************************************************/
void UART_SendCahr(UART_ID_Type UartID, uint8_t txbuf)
{
	__IO uint32_t *LSR = NULL;

	switch (UartID)
	{
		case UART_0:
			LSR = (__IO uint32_t *)&LPC_UART0->LSR;
			break;
		case UART_1:
			LSR = (__IO uint32_t *)&LPC_UART1->LSR;
			break;
		case UART_2:
			LSR = (__IO uint32_t *)&LPC_UART2->LSR;
			break;
		case UART_3:
			LSR = (__IO uint32_t *)&LPC_UART3->LSR;
			break;
		case UART_4:
			LSR = (__IO uint32_t *)&LPC_UART4->LSR;
			break;
	}
	// Wait for THR empty with timeout
	while (!(*LSR & UART_LSR_THRE))
	{
	}
	UART_SendByte(UartID, txbuf);
	return;
}
/*********************************************************************//**
 * @brief		c_entry: Main UART program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void BSP_UART_Initial(UART_ID_Type UartID)
{
	// UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;
	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	//uint32_t idx, len;
	//FlagStatus exitflag;
	//uint8_t buffer[10];
	UART_DMA_Semaphore[UartID] = OSSemCreate(1);
	UartDMAQ[UartID] = OSQCreate(&UartDMABuffQ[UartID][0], UDMA_MSG_SIZE);
	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 115200 bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);	
if (UartID == 0)
	{
	PINSEL_ConfigPin(UART0_PORT,UART0_PIN_TX,1);
	PINSEL_ConfigPin(UART0_PORT,UART0_PIN_RX,1);
	UARTConfigStruct.Baud_rate = UART0_BAUDRATE;
	}
else if (UartID == 1)
{
	PINSEL_ConfigPin(UART1_PORT,UART1_PIN_TX,3);
	PINSEL_ConfigPin(UART1_PORT,UART1_PIN_RX,3);
	UARTConfigStruct.Baud_rate = UART1_BAUDRATE;
}
else if (UartID == 2)
{
	PINSEL_ConfigPin(UART2_PORT,UART2_PIN_TX,UART2_FUN_NUM);
	PINSEL_ConfigPin(UART2_PORT,UART2_PIN_RX,UART2_FUN_NUM);
	UARTConfigStruct.Baud_rate = UART2_BAUDRATE;
}
else if (UartID == 3)
{

	PINSEL_ConfigPin(UART3_PORT,UART3_PIN_TX,UART3_FUN_NUM);
	PINSEL_ConfigPin(UART3_PORT,UART3_PIN_RX,UART3_FUN_NUM);
	UARTConfigStruct.Baud_rate = UART3_BAUDRATE;
}
else if (UartID == 4)
{
	/*
	 * Initialize UART2 pin connect
	 * P0.22: U4_TXD
	 * P2.9: U4_RXD
	 */
	PINSEL_ConfigPin(0,UART4_PIN_TX,1);
	PINSEL_ConfigPin(2,UART4_PIN_RX,1);
	UARTConfigStruct.Baud_rate = UART4_BAUDRATE;
}
else 
{
	return;
}
	// Initialize UART0 peripheral with given to corresponding parameter
	UART_Init(UartID, &UARTConfigStruct);

	/* Initialize FIFOConfigStruct to default state:
	 * 				- FIFO_DMAMode = DISABLE
	 * 				- FIFO_Level = UART_FIFO_TRGLEV0 ??????
	 * 				- FIFO_ResetRxBuf = ENABLE
	 * 				- FIFO_ResetTxBuf = ENABLE
	 * 				- FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig(UartID, &UARTFIFOConfigStruct);

	UART_RecvEnable(UartID);
	/* Enable Interrupt for UART0 channel */
  NVIC_EnableIRQ(UARTS_IRQn[UartID]);//???????????????????????
	UART_TxCmd(UartID, ENABLE);

}
/*********************************************************************//**
 * @brief		c_entry: Main UART program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void BSP_UART_UnInitial(UART_ID_Type UartID)
{
	uint8_t err;
	// UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;
	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 115200 bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);	
if (UartID == 0)
	{
	PINSEL_ConfigPin(UART0_PORT,UART0_PIN_TX,0);
	PINSEL_ConfigPin(UART0_PORT,UART0_PIN_RX,0);
	}
else if (UartID == 1)
{
	PINSEL_ConfigPin(UART1_PORT,UART1_PIN_TX,0);
	PINSEL_ConfigPin(UART1_PORT,UART1_PIN_RX,0);
}
else if (UartID == 2)
{
	PINSEL_ConfigPin(UART2_PORT,UART2_PIN_TX,0);
	PINSEL_ConfigPin(UART2_PORT,UART2_PIN_RX,0);
}
else if (UartID == 3)
{

	PINSEL_ConfigPin(UART3_PORT,UART3_PIN_TX,0);
	PINSEL_ConfigPin(UART3_PORT,UART3_PIN_RX,0);
}
else if (UartID == 4)
{
	/*
	 * Initialize UART2 pin connect
	 * P0.22: U4_TXD
	 * P2.9: U4_RXD
	 */
	PINSEL_ConfigPin(0,UART4_PIN_TX,0);
	PINSEL_ConfigPin(2,UART4_PIN_RX,0);
}
else 
{
	return;
}
	// Initialize UART0 peripheral with given to corresponding parameter
	//UART_Init(UartID, &UARTConfigStruct);
	UART_DeInit(UartID);

	UART_RecvDisable(UartID);
	/* Enable Interrupt for UART0 channel */
  NVIC_DisableIRQ(UARTS_IRQn[UartID]);//???????????????????????
	UART_TxCmd(UartID, DISABLE);

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
uint8_t BSP_UART_SendDMA(UART_ID_Type UartID,uint8_t dma_ch,uint8_t *buff,uint16_t len)
{
	GPDMA_Channel_CFG_Type GPDMACfg;

	UART_TxCmd(UartID, ENABLE);
  //NVIC_DisableIRQ (DMA_IRQn);
	// Setup GPDMA channel --------------------------------
	GPDMACfg.ChannelNum = dma_ch;
	GPDMACfg.SrcMemAddr = (uint32_t) buff;
	GPDMACfg.DstMemAddr = 0;
	GPDMACfg.TransferSize = len;
	GPDMACfg.TransferWidth = 0;
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	GPDMACfg.SrcConn = 0;
	GPDMACfg.DstConn = GPDMA_CONN_UART_Tx[UartID];
	GPDMACfg.DMALLI = 0;
	GPDMA_Setup(&GPDMACfg);
  // Enable interrupt for DMA
  //NVIC_EnableIRQ (DMA_IRQn);
	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(dma_ch, ENABLE);	
	UART_WaitDMAcomplete(UartID);//wait for complete
	UART_TxCmd(UartID, DISABLE);
	return 0; //send error

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
uint8_t BSP_MAIFER_SendDMA(comunication_t *uartq)
{
	GPDMA_Channel_CFG_Type GPDMACfg;

	//UART_TxCmd(UartID, ENABLE);
  //NVIC_DisableIRQ (DMA_IRQn);
	// Setup GPDMA channel --------------------------------
	GPDMACfg.ChannelNum = MIFARE_DMA_TX_CH;
	GPDMACfg.SrcMemAddr = (uint32_t) uartq->dataframe;
	GPDMACfg.DstMemAddr = 0;
	GPDMACfg.TransferSize = uartq->len;
	GPDMACfg.TransferWidth = 0;
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	GPDMACfg.SrcConn = 0;
	GPDMACfg.DstConn = GPDMA_CONN_UART_Tx[uartq->port];
	GPDMACfg.DMALLI = 0;
	GPDMA_Setup(&GPDMACfg);
  // Enable interrupt for DMA
  //NVIC_EnableIRQ (DMA_IRQn);
	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(MIFARE_DMA_TX_CH, ENABLE);	
	UART_WaitDMAcomplete(uartq->port);//wait for complete
	//UART_TxCmd(UartID, DISABLE);
	return 0; //send error

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
uint8_t BSP_HDLC_SendDMA(comunication_t *uartq)
{
	GPDMA_Channel_CFG_Type GPDMACfg;

	//UART_TxCmd(UartID, ENABLE);
  //NVIC_DisableIRQ (DMA_IRQn);
	// Setup GPDMA channel --------------------------------
	GPDMACfg.ChannelNum = HDLC_DMA_TX_CH;
	GPDMACfg.SrcMemAddr = (uint32_t) uartq->dataframe;
	GPDMACfg.DstMemAddr = 0;
	GPDMACfg.TransferSize = uartq->len;
	GPDMACfg.TransferWidth = 0;
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	GPDMACfg.SrcConn = 0;
	GPDMACfg.DstConn = GPDMA_CONN_UART_Tx[uartq->port];
	GPDMACfg.DMALLI = 0;
	GPDMA_Setup(&GPDMACfg);
  // Enable interrupt for DMA
  //NVIC_EnableIRQ (DMA_IRQn);
	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(HDLC_DMA_TX_CH, ENABLE);	
	UART_WaitDMAcomplete(uartq->port);//wait for complete
	//UART_TxCmd(UartID, DISABLE);
	return 0; //send error

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
uint8_t BSP_FINGER_SendDMA(comunication_t *uartq)
{
	GPDMA_Channel_CFG_Type GPDMACfg;

	//UART_TxCmd(UartID, ENABLE);
  //NVIC_DisableIRQ (DMA_IRQn);
	// Setup GPDMA channel --------------------------------
	GPDMACfg.ChannelNum = ZKFINGER_DMA_TX_CH;
	GPDMACfg.SrcMemAddr = (uint32_t) uartq->dataframe;
	GPDMACfg.DstMemAddr = 0;
	GPDMACfg.TransferSize = uartq->len;
	GPDMACfg.TransferWidth = 0;
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	GPDMACfg.SrcConn = 0;
	GPDMACfg.DstConn = GPDMA_CONN_UART_Tx[uartq->port];
	GPDMACfg.DMALLI = 0;
	GPDMA_Setup(&GPDMACfg);
  // Enable interrupt for DMA
  //NVIC_EnableIRQ (DMA_IRQn);
	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(ZKFINGER_DMA_TX_CH, ENABLE);	
	UART_WaitDMAcomplete(uartq->port);//wait for complete
	//UART_TxCmd(UartID, DISABLE);
	//rx enable
	//UART_RecvEnable(uartq->port);
	return 0; //send error

}

/*********************************************************************//**
 * @brief		UART Line Status Error
 * @param[in]	bLSErrType	UART Line Status Error Type
 * @return		None
 **********************************************************************/
void UART_IntErr(uint8_t bLSErrType)
{
	// Loop forever
//	while (1){
//		// For testing purpose
//	}
}




/**
 * @}
 */
