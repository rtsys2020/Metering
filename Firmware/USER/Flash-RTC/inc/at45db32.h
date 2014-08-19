/**********************************************************************
* $Id$		at45db32.h			2013-10
*//**
* @file		at45db32.h
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/

#ifndef AT45DB32_H
#define AT45DB32_H

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

typedef enum
{
	BUFFER_ONE,
	BUFFER_TOW
}buff_num_t;


#define AT45DB32_MAX_ADDR		0x1FFFFF	/* Maximum address */
#define	AT45DB32_SEC_MAX     	511         /* Maximum sectors */
#define AT45DB32_SEC_SIZE		0x1000      /* Sector size */

/// AT45DBXX

// Flash pin	Config
#define AT45DBXX_EN	1
#define AT45DBXX_SSP_NUM			0


#define AT45DBXX_MOSI_PORT_NUM			2
#define AT45DBXX_MOSI_PIN_NUM			27
#define AT45DBXX_MOSI_FUN_NUM			2

#define AT45DBXX_MISO_PORT_NUM			2
#define AT45DBXX_MISO_PIN_NUM			26
#define AT45DBXX_MISO_FUN_NUM			2

#define AT45DBXX_SCK_PORT_NUM			2
#define AT45DBXX_SCK_PIN_NUM			22
#define AT45DBXX_SCK_FUN_NUM			2

#define AT45DBXX_CS_PORT		2
#define AT45DBXX_CS_PIN		23

#define AT45DBXX_WP_PORT	2
#define AT45DBXX_WP_PIN	25

#define AT45DBXX_RESET_PORT	2
#define AT45DBXX_RESET_PIN	24

#if (AT45DBXX_SSP_NUM == 0)
#define AT45DBXX_SSP	LPC_SSP0
#elif (AT45DBXX_SSP_NUM == 1)
#define AT45DBXX_SSP	LPC_SSP1
#elif (AT45DBXX_SSP_NUM == 2)
#define AT45DBXX_SSP	LPC_SSP2
#endif

// AT45DBXX
#define AT45DBXX_CS_LOW()    GPIO_ClearValue( AT45DBXX_CS_PORT, (1<<AT45DBXX_CS_PIN) )  
#define AT45DBXX_CS_HIGH()   GPIO_SetValue( AT45DBXX_CS_PORT, (1<<AT45DBXX_CS_PIN) ) 

#define AT45DBXX_RESET_LOW()    GPIO_ClearValue( AT45DBXX_RESET_PORT, (1<<AT45DBXX_RESET_PIN) )  
#define AT45DBXX_RESET_HIGH()   GPIO_SetValue( AT45DBXX_RESET_PORT, (1<<AT45DBXX_RESET_PIN) ) 

#define AT45DBXX_WP_ENABLE()    GPIO_ClearValue( AT45DBXX_WP_PORT, (1<<AT45DBXX_WP_PIN) )  
#define AT45DBXX_WP_DISABLE()   GPIO_SetValue( AT45DBXX_WP_PORT, (1<<AT45DBXX_WP_PIN) ) 
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


void AT45DBXX_Init(void);
uint32_t AT45DBXX_ReadManDevice(void);
uint16_t AT45DBXX_ReadStatusReg(void);
uint8_t AT45DBXX_ReadSecurityReg(void);
void AT45DBXX_ReadProtectReg(uint8_t *data);
void AT45DBXX_Read528Page(uint16_t page_add,uint16_t byte_add,uint8_t *buff);
void AT45DBXX_ReadMemContinueArray(uint16_t page_add,uint16_t byte_add,uint8_t *buff,uint16_t len);
void AT45DBXX_ReadBufferContinue528(buff_num_t buffNum,uint16_t byte_add,uint8_t *buff,uint16_t len);
void AT45DBXX_WriteBuffer_528(buff_num_t buff_Num,uint16_t byte_add,uint8_t *buff,uint16_t len);
void AT45DBXX_WriteBuffToMem528(buff_num_t buff_Num,uint16_t page_add);
void AT45DBXX_ReadMemoryPageToBuff(buff_num_t buff_Num,uint16_t page_add);
void AT45DBXX_ErasePage528(uint16_t page_add);
void AT45DBXX_ChipErase(void);
void AT45DBXX_EnableSectorProtect(void);
void AT45DBXX_DisableSectorProtect(void);
void AT45DBXX_EraseSectorProtect(void);
void AT45DBXX_DisableAllProtect(void);

/*
EOF
*/

#endif
