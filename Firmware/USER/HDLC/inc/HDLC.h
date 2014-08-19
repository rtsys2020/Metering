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
#ifndef HDLC_H
#define HDLC_H
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

#include "includes.h"
#include  "setting.h"
#include "uart.h"

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
typedef enum
{
	HDLC_START_OF_PACKET = 0,
	HDLC_SOURCE_ADD,
	HDLC_DEST_ADD,
	HDLC_DATA,
	HDLC_DUMMY
}HDLC_Packet_State_t;

/*
*********************************************************************************************************
*                                               DEFINIATION
*********************************************************************************************************
*/
#define HDLC_UART_PORT	0

#define START_FLAG        0x7e
#define ST_X_ADD 1
#define HDLC_BROADCAST_ADD 255

#define COMM_DEVINFO       0x01
#define COMM_GETSTATUS     0x02
#define COMM_GETTIME       0x03
#define COMM_SETTIME       0x04

#define COMM_GETRECORD     0x20
#define COMM_INCGETRECORD  0x21
#define COMM_GETRECORDBULK 0x22
#define COMM_INCPTR        0x23

#define COMM_GETIMAGE      0x30
#define COMM_CAPTUREIMG    0x31

#define COMM_SETPARAM      0x50
#define COMM_GETPARAM      0x51
#define COMM_DIRECTFPM     0x52
#define COMM_TOUCHKEY      0x55
#define COMM_PROGRAM       0xF0 


#define PARAM_LANG      0x01
#define PARAM_CALENDAR  0x02
#define PARAM_DAYLIGHT  0x03
#define PARAM_SPEAKER   0x04
#define PARAM_BACKLIGHT 0x05
#define PARAM_STANDBY   0x06
#define PARAM_ALARM     0x07
#define PARAM_SETUPPASS 0x08
#define PARAM_SN        0x1E
#define PARAM_FC        0x1F

#define PARAM_RDINDEX       0x20
#define PARAM_WRINDEX       0x21
#define PARAM_REPEATTIME    0x22
#define PARAM_VALIDITY      0x23
#define PARAM_F1            0x24
#define PARAM_F2            0x25
#define PARAM_MISSIONKEY    0x26
#define PARAM_VACATIONKEY   0x27
#define PARAM_MISSIONCARD   0x28
#define PARAM_VACATIONCARD  0x29
#define PARAM_READERSCH     0x2A
#define PARAM_INOUTSCH      0x2B

#define PARAM_TIMEOUT       0x40
#define PARAM_IPD           0x41
#define PARAM_TRTADDRESS    0x42
#define PARAM_IP            0x43
#define PARAM_SUBNET        0x44
#define PARAM_GETWAY        0x45
#define PARAM_SERVER        0x46
#define PARAM_BAUDRATE      0x47

#define PARAM_FINGER        0xA0
#define PARAM_MIFARE        0xA1
#define PARAM_MIFAREMODE    0xA2
#define PARAM_MIFARESECTOR  0xA3
#define PARAM_MIFAREBLOCK   0xA4
#define PARAM_PROXIMITY     0xA5
#define PARAM_PROXMODE      0xA6
#define PARAM_MAGNET        0xA7
#define PARAM_MAGNETMODE    0xA8
#define PARAM_BARCODE       0xA9
#define PARAM_BARCODEMODE   0xAA
#define PARAM_CAMERA        0xAB
#define PARAM_CAMERAMODE    0xAC
#define PARAM_NET           0xAD
#define PARAM_WIFI          0xAE
#define PARAM_GPRS          0xAF
#define PARAM_RESET					0xB0

#define CRISTIAN	0
#define SOLAR	1
#define COMM_SUCCESS        0x00
#define COMM_ERROR          0x01
#define COMM_NODATA         0x02


#define DATAOFFSET       7

#define HDLC_ABORT       50
#define HDLC_PROG        200
#define HDLC_REQHEX      201    // 201 Add Add 
#define HDLC_HEXBLOCK    202    // Status(one byte) --> data(512 byte) 
                                // C for initial and inner blocks,F for last block,A for abort  
    
#define HDLC_HEXINFO     203    // NOB(high) + NOB(low) + VER1 + VER 2
#define HDLC_REQINFO     204
#define HDLC_EOT 24

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/

extern void rtc_settime (const RTC_TIME_Type *rtc);
extern void rtc_gettime (RTC_TIME_Type *rtc);
/*
*********************************************************************************************************
*                                           DEFINITIONS
*********************************************************************************************************
*/
typedef struct 
{
	uint8_t Status;
	uint8_t DestAddress;
	uint16_t Timeout;
}Session_t;


typedef enum
{
	SESSION_CLOSE,
	SESSION_ALIVE,
}session_state_t;

typedef enum
{		
COM_ACK	,						
COM_NACK ,
COM_BUSY ,
COM_SESSION	
}command_pos_t;

typedef struct 
{
	uint8_t start_flag;
	uint8_t src;
	uint8_t dest;
	uint8_t cmd;
	uint16_t len;
	uint8_t *data;
	uint16_t crc;
	uint8_t end_flag;
	uint8_t *mem;
}HDLC_packet_t;

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
extern void UartGetPacketMachin(UART_ID_Type UartID,uint8_t byte);
uint8_t  GetPacket(HDLC_packet_t *packet,uint32_t Timeout);
uint16_t CRC16_update(uint16_t crc, uint16_t a);
void SendPacket(uint8_t ControlByte,uint8_t PCSendBuff[],unsigned int StartIndex,unsigned int DataLenght);
void ProcessPacket(HDLC_packet_t* packet);
/*
EOF
*/
#endif

