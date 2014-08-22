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
#ifndef UART_H
#define UART_H
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

#include "includes.h"


typedef void (*UART_ISR_Fun_t)(UART_ID_Type UartID,uint8_t c);
extern void ZKGetPacketMachin(UART_ID_Type UartID,uint8_t byte);
extern void MifareGetPacket(UART_ID_Type UartID,uint8_t byte);
//#define HDLC 0
//#define PLAIN 1
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/




/************************** PRIVATE DEFINTIONS *************************/
// <o> Buffer size
// <16=> 16 Byte
// <32=> 32 Byte
// <64=> 64 Byte
// <128=> 128 Byte
#define UART_RING_BUFSIZE 16

// <e> enable uart port number 0
// 	<o1> Initialize UART0 Port connect <0-4>
// 	<o2> Initialize UART0 TX pin connect <0-31>
// 	<o3> Initialize UART0 RX pin connect <0-31>
// 	<o4> Initialize UART0 Function Number <0-5>
// 	<o5> Initialize UART0 BaudRate 
//		<9600=> 9600 b/s
//		<19200=> 19200 b/s
//		<38400=> 38400 b/s
//		<57600=> 57600 b/s
//		<115200=> 115200 b/s
// </e>

#define UART_NUM0_EN		1
#define UART0_PORT	0
#define UART0_PIN_TX 2
#define UART0_PIN_RX	3
#define UART0_FUN_NUM	1
#define UART0_BAUDRATE	115200



// <e> Enable interrupt Port 0 
//</e>
#define UART_NUM0_INT_EN 1
#define UART0_ISR_HANDLER UartGetPacketMachin

// <e> enable uart port number 1
// 	<o1> Initialize UART1 Port connect <0-4>
// 	<o2> Initialize UART1 TX pin connect <0-31>
// 	<o3> Initialize UART1 RX pin connect <0-31>
// 	<o4> Initialize UART1 Function Number <0-5>
// 	<o5> Initialize UART1 BaudRate 
//		<9600=> 9600 b/s
//		<19200=> 19200 b/s
//		<38400=> 38400 b/s
//		<115200=> 115200 b/s
// </e>

#define UART_NUM1_EN		1
#define UART1_PORT	3
#define UART1_PIN_TX 16
#define UART1_PIN_RX	17
#define UART1_FUN_NUM	1
#define UART1_BAUDRATE	115200


// <e> Enable interrupt Port 1 
//</e>
#define UART_NUM1_INT_EN 0
#define UART1_ISR_HANDLER  //ZKGetPacketMachin

// <e> enable uart port number 2
// 	<o1> Initialize UART2 Port connect <0-4>
// 	<o2> Initialize UART2 TX pin connect <0-31>
// 	<o3> Initialize UART2 RX pin connect <0-31>
// 	<o4> Initialize UART2 Function Number <0-5>
// 	<o5> Initialize UART2 BaudRate 
//		<9600=> 9600 b/s
//		<19200=> 19200 b/s
//		<38400=> 38400 b/s
//		<115200=> 115200 b/s
// </e>

#define UART_NUM2_EN		1
#define UART2_PORT	0
#define UART2_PIN_TX 10
#define UART2_PIN_RX	11
#define UART2_FUN_NUM	1
#define UART2_BAUDRATE	115200 

// <e> Enable interrupt Port 2 
//</e>
#define UART_NUM2_INT_EN 1
#define UART2_ISR_HANDLER ZKGetPacketMachin

// <e> enable uart port number 3
// 	<o1> Initialize UART3 Port connect <0-4>
// 	<o2> Initialize UART3 TX pin connect <0-31>
// 	<o3> Initialize UART3 RX pin connect <0-31>
// 	<o4> Initialize UART3 Function Number <0-5>
// 	<o5> Initialize UART3 BaudRate 
//		<9600=> 9600 b/s
//		<19200=> 19200 b/s
//		<38400=> 38400 b/s
//		<115200=> 115200 b/s
// </e>

#define UART_NUM3_EN		1
#define UART3_PORT	0
#define UART3_PIN_TX 0
#define UART3_PIN_RX	1
#define UART3_FUN_NUM	1
#define UART3_BAUDRATE	19200

// <e> Enable interrupt Port 3 
//</e>
#define UART_NUM3_INT_EN 1
#define UART3_ISR_HANDLER MifareGetPacket

// <e> enable uart port number 4
// 	<o1> Initialize UART4 Port connect <0-4>
// 	<o2> Initialize UART4 TX pin connect <0-31>
// 	<o3> Initialize UART4 RX pin connect <0-31>
// 	<o4> Initialize UART4 Function Number <0-5>
// 	<o5> Initialize UART4 BaudRate 
//		<9600=> 9600 b/s
//		<19200=> 19200 b/s
//		<38400=> 38400 b/s
//		<115200=> 115200 b/s
#define UART_NUM4_EN		0
#define UART4_PORT	0
#define UART4_PIN_TX 2
#define UART4_PIN_RX	3
#define UART4_FUN_NUM	1
#define UART4_BAUDRATE	19200


// </e>
// <e> Enable interrupt Port 4
//</e>
#define UART_NUM4_INT_EN 0
#define UART4_ISR_HANDLER 


/* Buf mask */
#define __BUF_MASK (UART_RING_BUFSIZE-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(head, tail) ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail) ((head&__BUF_MASK)==(tail&__BUF_MASK))
/* Reset buf */
#define __BUF_RESET(bufidx)	(bufidx=0)
#define __BUF_INCR(bufidx)	(bufidx=(bufidx+1)&__BUF_MASK)

#define UDMA_MSG_SIZE	2


typedef struct 
{
	uint16_t port;
	uint16_t len;
	uint8_t *buff;
}comunication_t;

void UART_WaitDMAcomplete(uint8_t uart_id);
void UART_SendDMAcompleted(uint8_t uart_id);
void UART_IntReceive(UART_ID_Type UartID,UART_ISR_Fun_t function);
void UART_SendCahr(UART_ID_Type UartID, uint8_t txbuf);
void BSP_UART_Initial(UART_ID_Type UartID);
uint8_t BSP_UART_SendDMA(UART_ID_Type UartID,uint8_t dma_ch,uint8_t *buff,uint16_t len);
uint8_t BSP_MAIFER_SendDMA(comunication_t *uartq);
uint8_t BSP_HDLC_SendDMA(comunication_t *uartq);
uint8_t BSP_FINGER_SendDMA(comunication_t *uartq);


/*
EOF
*/

#endif
