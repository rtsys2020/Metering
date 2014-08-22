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
#include "filesystem.h"
//add by rezaee
#include "template.h"
#include "rs232.h"
#include "uart.h"
#include "touch.h"
#include "applicationtask.h"
STX_Sate_t g_State;
/* Private variables ---------------------------------------------------------*/

void os_initial(void);
void  delay_ms (uint16_t dly);
void  User_BSP_Init (void);
/* Private function prototypes -----------------------------------------------*/

extern void printErrorMsg(const char * errMsg);
extern void CAM_init(void) ;
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

uint8_t  arry[] __attribute__((section("GlobalVal")))={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

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

	
//extern  struct etharp_entry arp_table[];	
	
INT32S main (void)
{
	int i;
	SCB->SHCSR = 1<<MEMFAULTENA | 1<<BUSFAULTENA | 1<<USGFAULTENA;

//	//SCB->CCR |= 1<<DIV_0_TRP_BIT;
//	NVIC_SetPriority(BusFault_IRQn,2);
//	//NVIC_SystemReset();
	SCnSCB->ACTLR |= 3; 
//	for(i=0;i<10;i++)
//	{
//		arp_table[i].q = NULL;
//	}
	User_BSP_Init();
	EEPROM_Init();
#if (WWDT_ENABLE==1) 	
	// Read back TimeOut flag to determine previous timeout reset
	if (WWDT_GetStatus(WWDT_TIMEOUT_FLAG))
	{
		//_DBG_("Last MCU reset caused by WDT TimeOut!\n\r");
		// Clear WDT TimeOut
		WWDT_ClrTimeOutFlag();
	} 
	else
	{
		//_DBG_("Last MCU reset caused by External!\n\r");
	}	
#endif	
	//os_initial();
	
	return (0);
}





/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
