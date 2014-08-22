#ifndef __FLASH_RTC_H__
#define __FLASH_RTC_H__

/**********************************************************************
* $Id$		FlashRtc.h			2013-12-15
*//**
* @file		FlashRtc.h
* @brief	Contains the defines and function prototypes for Flash and RTC
* @version	1.0
* @date		15. Decm. 2013
* @author	Amin Ezhdehakosh
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

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#include "bsp.h"


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
#define MAX_ADDR		0x1FFFFF	/* Maximum address */
#define	SEC_MAX     	511         /* Maximum sectors */
#define SEC_SIZE		0x1000      /* Sector size */
/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/
#define FROM_BCD(n)     ((((n) >> 4) * 10) + ((n) & 0xf))
#define TO_BCD(n)       ((((n) / 10) << 4) | ((n) % 10))
#define RTC_YEAR_DATUM  2000

// SST Flash Defines
#define READ_OPCODE					0x03		// Read memory
#define ERASE_SECTOR_OPCODE			0x20		// Erase 4KByte of memory array
#define ERASE_BLOCK_32KB_OPCODE		0x52		// Erase 32KByte block of memory array
#define ERASE_BLOCK_64KB_OPCODE		0xD8		// Erase 64KByte block of memory array
#define ERASE_CHIP_OPCODE			0x60		// Erase Full Memory Array
#define PROGRAM_BYTE_OPCODE			0x02		// To program one data byte
#define PROGRAM_AAI_OPCODE			0xAD		// Auto address increment programming
#define RDSR_OPCODE					0x05		// Read status register
#define EWSR_OPCODE					0x50		// Enable write status register
#define WRSR_OPCODE					0x01		// Write status register
#define WREN_OPCODE					0x06		// Write enable
#define WRDI_OPCODE					0x04		// Write disable
#define RDID_OPCODE					0x90		// Read ID

#define SFLASH_SIZE_4MB				0x400000
#define SFLASH_SECTOR_SIZE			4096
#define SFLASH_READ_SIZE			4096

// RTC Defines
#define GET_TIME_OPCODE				0xA3
#define SET_TIME_OPCODE				0x23


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/
typedef enum IDTYPE_t{ Manufacturer_ID, Device_ID, JEDEC_ID } IDtype_t;

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif
typedef struct
{
	uint32_t Sector;
	uint32_t Addr;
	uint8_t data[1024];
	uint16_t chksum;
	//uint16_t RESERVD;
}Record_t;
/*
*********************************************************************************************************
*                                          GPIO PIN DEFINITIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/


//BOOL_8 SFlash_Write(uint8_t *writeBuffer, uint32_t len, uint32_t address, BOOL_8 preserve);
void FlashRTC_Init(void);
uint32_t SFlash_Size(void);
void SFlash_Chip_Erase(void);

BOOL_8 SFlash_Read(uint8_t *readBuffer, uint32_t len, uint32_t address);
int SFlash_Write_Data_Record(Record_t *writeBuffer, uint32_t address);
uint8_t SFlash_Read_Record(Record_t *readBuffer, uint32_t address);


void WaitBusy(void);
void SFlash_Write_Enable(void);
void SFlash_Write_Disable(void);
uint32_t SFlash_Read_ID(IDtype_t IDType);
uint8_t SFlash_Read_Status_Register(void);
void SFlash_Enable_Write_Status_Register(void);

void SFlash_Write_Status_Rregister(uint8_t statusByte);
void SFlash_Write_Byte(uint8_t writeByte, uint32_t address);


void SFlash_Sector_Erase_4KB(uint32_t sectorAddress);

uint32_t Flash_test(void);
/*
EOF
*/

#endif
