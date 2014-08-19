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
#ifndef HDLCTASK_H
#define HDLCTASK_H
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
 
 /*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


#include "applicationtask.h"
#include "includes.h"
#include "user_bsp.h"
#include "hdlc.h"
#include "memory.h"
#include "ff.h"
#include "record.h"
#include "lpc177x_8x_crc.h"

#define HDLC_DATA	1
//<o> HDLC Stack Size
#define  APP_TASK_HDLC_STK_SIZE            256u
//<o> HDLC Task Priority
#define  	APP_TASK_HDLC_PRIO							(14)
//<o> HDLC Task Recive Frame Qeueu size
#define HDLC_RCV_MSGQ_SIZE	1

extern OS_EVENT *HDLC_RcvFrameQ;

void HDLC_Start(void);
void  App_HDLCTaskCreat (void);
void UartGetPacketMachin(UART_ID_Type UartID,uint8_t byte);
uint8_t  GetPacket(HDLC_packet_t *packet,uint32_t Timeout);
void HDLC_SendPacket(uint8_t ControlByte,uint8_t PCSendBuff[],unsigned int DataLenght);
/*
EOF
*/
#endif

