/**********************************************************************
* $Id$		flash_rtc.h			2013-10
*//**
* @file		flash_rtc.h
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/

#ifndef __FLASH_RTC_H__
#define __FLASH_RTC_H__

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#include "record.h"
#include "user_bsp.h"
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

/*
*********************************************************************************************************
*                                          GPIO PIN DEFINITIONS
*********************************************************************************************************
*/
// DataFlash.h




//Global status register flags

#define T1_OVF  0x01
#define CLEARED 0x02

// DataFlash reset port pin (PB 0)
#define DF_RESET 0x01
         
// DataFlash ready/busy status port pin (PB 1)
#define DF_RDY_BUSY 0x02

// DataFlash boot sector write protection (PB 2)
#define DF_WRITE_PROTECT 0x04

// DataFlash chip select port pin (PB 4)
#define DF_CHIP_SELECT 0x10

// buffer 1 
#define BUFFER_1 0x00

// buffer 2
#define BUFFER_2 0x01


// defines for all opcodes

// buffer 1 write 
#define BUFFER_1_WRITE 0x84

// buffer 2 write 
#define BUFFER_2_WRITE 0x87

// buffer 1 read
#define BUFFER_1_READ 0x54

// buffer 2 read
#define BUFFER_2_READ 0x56

// buffer 1 to main memory page program with built-in erase
#define B1_TO_MM_PAGE_PROG_WITH_ERASE 0x83

// buffer 2 to main memory page program with built-in erase
#define B2_TO_MM_PAGE_PROG_WITH_ERASE 0x86

// buffer 1 to main memory page program without built-in erase
#define B1_TO_MM_PAGE_PROG_WITHOUT_ERASE 0x88

// buffer 2 to main memory page program without built-in erase
#define B2_TO_MM_PAGE_PROG_WITHOUT_ERASE 0x89

// main memory page program through buffer 1
#define MM_PAGE_PROG_THROUGH_B1 0x82
 
// main memory page program through buffer 2
#define MM_PAGE_PROG_THROUGH_B2 0x85
 
// auto page rewrite through buffer 1
#define AUTO_PAGE_REWRITE_THROUGH_B1 0x58
 
// auto page rewrite through buffer 2
#define AUTO_PAGE_REWRITE_THROUGH_B2 0x59
 
// main memory page compare to buffer 1
#define MM_PAGE_TO_B1_COMP 0x60

// main memory page compare to buffer 2
#define MM_PAGE_TO_B2_COMP 0x61
 
// main memory page to buffer 1 transfer
#define MM_PAGE_TO_B1_XFER 0x53

// main memory page to buffer 2 transfer
#define MM_PAGE_TO_B2_XFER 0x55

// DataFlash status register for reading density, compare status, 
// and ready/busy status
#define STATUS_REGISTER 0x57

// main memory page read
#define MAIN_MEMORY_PAGE_READ 0x52

// erase a 528 byte page
#define PAGE_ERASE 0x81

// erase 512 pages
#define BLOCK_ERASE 0x50

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

void RTC_TimeToStr(RTC_TIME_Type *pTime,char* str);

void WaitBusy(void);
void SFlash_Write_Enable(void);
void SFlash_Write_Disable(void);
uint32_t SFlash_Read_ID(IDtype_t IDType);
uint8_t SFlash_Read_Status_Register(void);
void SFlash_Enable_Write_Status_Register(void);

void SFlash_Write_Status_Rregister(uint8_t statusByte);
void SFlash_Write_Byte(uint8_t writeByte, uint32_t address);

void SFlash_Write_Data(uint8_t *writeBuffer, uint32_t len, uint32_t address);


void SFlash_Sector_Erase_4KB(uint32_t sectorAddress);

uint32_t Flash_test(void);


void AT45DBXX_Init(void);
uint8_t AT45DBXX_ReadSecProtReg(void);
uint32_t AT45DBXX_ReadManDevice(void);

/*
EOF
*/

#endif
