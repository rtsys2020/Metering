/**********************************************************************
* $Id$		rs232.h			2013-06-21
*//**
* @file		rs232.h
* @brief	Contains rs232 protocol 
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

#ifndef RS232_H
#define RS232_H
#include "bsp.h"
#include "includes.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
// <o> Initialize RS232 UART Number <0-4>
#define RS232_UART_NUM	0//2
// <o> Initialize PORT Port connect <0-4>
#define RS232_UART_PORT	0
// <o> Initialize RS232 PIN TX connect <0-31>
#define	RS232_UART_PIN_TX	10
// <o> Initialize RS232 PIN RX connect <0-31>
#define	RS232_UART_PIN_RX	11
// <o> Initialize RS232 BaudRate 
//	<9600=> 9600 b/s
//	<19200=> 19200 b/s
//	<38400=> 38400 b/s
//	<115200=> 115200 b/s
#define RS232_BAUDRATE	115200


/** @defgroup UART_Dma		UART DMA
 * @ingroup UART_Examples
 * @{
 */


/************************** PRIVATE DEFINITIONS *************************/
#if (RS232_UART_NUM == 0)
#define	_LPC_UART				UART_0
#define _GPDMA_CONN_UART_Tx		GPDMA_CONN_UART0_Tx
#define _GPDMA_CONN_UART_Rx		GPDMA_CONN_UART0_Rx
#elif (RS232_UART_NUM == 1)
#define _LPC_UART				UART_1
#define _GPDMA_CONN_UART_Tx		GPDMA_CONN_UART1_Tx
#define _GPDMA_CONN_UART_Rx		GPDMA_CONN_UART1_Rx
#elif (RS232_UART_NUM == 2)
#define _LPC_UART				UART_2
#define _GPDMA_CONN_UART_Tx		GPDMA_CONN_UART2_Tx
#define _GPDMA_CONN_UART_Rx		GPDMA_CONN_UART2_Rx
#elif (RS232_UART_NUM == 3)
#define _LPC_UART			    UART_3
#define _GPDMA_CONN_UART_Tx		GPDMA_CONN_UART3_Tx
#define _GPDMA_CONN_UART_Rx		GPDMA_CONN_UART3_Rx
#elif (RS232_UART_NUM == 4)
#define _LPC_UART			    UART_4
#define _GPDMA_CONN_UART_Tx		GPDMA_CONN_UART4_Tx
#define _GPDMA_CONN_UART_Rx		GPDMA_CONN_UART4_Rx
#endif
/* Receive buffer size */
#define RX_BUF_SIZE	0x10



// Receive buffer
extern __IO uint8_t rx_buf[RX_BUF_SIZE];

// Terminal Counter flag for Channel 0
extern __IO uint32_t Channel0_TC;

// Error Counter flag for Channel 0
extern __IO uint32_t Channel0_Err;

// Terminal Counter flag for Channel 1
extern __IO uint32_t Channel1_TC;

// Error Counter flag for Channel 1
extern __IO uint32_t Channel1_Err;
/************************** PRIVATE VARIABLES *************************/
 
 
/************************** PRIVATE FUNCTIONS *************************/

void RS232Config(void);
uint8_t RS232Send(uint8_t *buff,uint16_t len);
uint8_t RS232Recev(uint8_t *buff,uint16_t len);
/*
EOF
*/
#endif
