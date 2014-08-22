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
/* Includes ------------------------------------------------------------------*/
#include <includes.h>
#include "lpc17xx_sector.h"
void  delay_ms (uint16_t dly);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/
extern char Image$$ER_IROM1$$RO$$Base[];
extern char Image$$ER_IROM1$$RO$$Length[];
extern char Image$$RW_IRAM1$$RW$$Base[];
extern char Image$$RW_IRAM1$$RW$$Length[];
static UNS_32 bl_size, bl_sector_startidx, bl_sector_endidx;
#define DIV_0_TRP_BIT		4	
#define UNALIGN_TRP_BIT	3
#define MEMFAULTENA		16	
#define BUSFAULTENA		17
#define USGFAULTENA		18
	
#define BITBAND_SRAM_REF 0x20000000
#define BITBAND_SRAM_BASE 0x22000000
#define BITBAND_SRAM(a,b) ((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32 + (b*4))) // Convert SRAM address
#define BITBAND_PERI_REF 0x40000000
#define BITBAND_PERI_BASE 0x42000000
#define BITBAND_PERI(a,b) ((BITBAND_PERI_BASE + (a-BITBAND_PERI_REF)*32 + (b*4))) // Convert PERI address
#define MAILBOX 0x20004000

// Mailbox bit 0
#define MBX_B0 *((volatile unsigned int *)(BITBAND_SRAM(MAILBOX,0)))
// Mailbox bit 7
#define MBX_B7 *((volatile unsigned int *)(BITBAND_SRAM(MAILBOX,7)))


#define CRP 0x11223344
#define CRP1  0x12345678
#define CRP2  0x87654321
#define CRP3  0x43218765
#define NOCRP 0x11223344
#define DEFAULT_RUN_ADDR	0x2000
#define DEFAULT_PROG_ADDR 0x2000
#define INVALID_RESULT 0xFFFFFFFF
#define IAP_BUF_SIZE 1024

/* Read Part Identification number */
 void cmd_readid (char *par)
{
	UNS_32 id[1];

	//IRQDisable();
	ReadPartID((unsigned long*)&id[0]);
	//IRQEnable();

	//printf("\nPart ID: 0x%x.\n", id[0]);
}
/* Display info of bootloader */
 void cmd_bootinfo (char *par)
{
	printf("  Bootloader:\n");
	printf("             Entry:    0x%x\n", (UNS_32)Image$$ER_IROM1$$RO$$Base);
	printf("             Size:     0x%x bytes (%d)\n", bl_size, bl_size);
	printf("             Sectors:  %d to %d\n", bl_sector_startidx, bl_sector_endidx);
	printf("             Version:  %s\n", __DATE__);
}

 void init_bootpara(void)
{
	bl_size = (UNS_32)Image$$ER_IROM1$$RO$$Length + (UNS_32)Image$$RW_IRAM1$$RW$$Length;
	bl_sector_startidx = getSectorIndex((UNS_32)Image$$ER_IROM1$$RO$$Base);
	bl_sector_endidx = getEndSectorIndex(bl_size, bl_sector_startidx);
}


int main (void)
{
	//enable watchdog
	//read eeprom check for flag for program or start application
			//1.0 read firmware from spi flash and program flash
					//1.1 disable all interrupt and deinitial all configuration
					//1.2 run application or restart microontroller
			//2.0 run application
					//2.1 start application
	return (0);
}


//add by rezaee
/*********************************************************************//**
 * @brief 			delay in micro seconds
 * @param[in]		delay    The delay required (in microseconds)
 * @return 		None.
 **********************************************************************/
void  delay_us (uint32_t  delay)
{
    volatile  uint32_t  i;
    for (i = 0; i < (100 * delay); i++) {    /* This logic was tested. It gives app. 1 micro sec delay        */
        ;
    }
}

/*********************************************************************//**
 * @brief 			delay in milli seconds
 * @param[in]		delay    The delay required (in milliseconds)
 * @return 		None.
 **********************************************************************/
 void  delay_ms (uint16_t dly)
{
    volatile  uint32_t  i;
    for (i = 0; i < dly; i++) {
        delay_us(100);
    }
}


void FaultCode(uint8_t fault)
{


}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
