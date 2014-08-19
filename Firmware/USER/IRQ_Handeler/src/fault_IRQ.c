/**********************************************************************
* $Id$		Handeler.c			2013-10
*//**
* @file		Handeler.c
* @brief	Use for rs232 functionality
*			
* @version	1.0
* @date		23. decm. 2013
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
#include "includes.h"
#include  "bsp.h"
#include <stdio.h>
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private FUNCTIONS
 * @{
 */
 
void printErrorMsg(const char * errMsg);
void printUsageErrorMsg(uint32_t CFSRValue);
void printBusFaultErrorMsg(uint32_t CFSRValue);
void printMemoryManagementErrorMsg(uint32_t CFSRValue);
void stackDump(uint32_t stack[]);
void Hard_Fault_Handler(uint32_t stack[]);
#define REGION_Enabled  (0x01)
#define REGION_32K      (14 << 1)      // 2**15 == 32k
#define NORMAL          (8 << 16)      // TEX:0b001 S:0b0 C:0b0 B:0b0
#define FULL_ACCESS     (0x03 << 24)   // Privileged Read Write, Unprivileged Read Write
#define NOT_EXEC        (0x01 << 28)   // All Instruction fetches abort

//Watchodog time out in 5 seconds
#define WDT_TIMEOUT 	5000000
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
void printErrorMsg(const char * errMsg)
{
   while(*errMsg != '\0'){
      ITM_SendChar(*errMsg);
      ++errMsg;
   }
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
void printUsageErrorMsg(uint32_t CFSRValue)
{
   printErrorMsg("Usage fault: ");
   CFSRValue >>= 16; // right shift to lsb
   
   if((CFSRValue & (1<<9)) != 0) {
      printErrorMsg("Divide by zero\n");
   }
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
void printBusFaultErrorMsg(uint32_t CFSRValue)
{
   printErrorMsg("Bus fault: ");
   CFSRValue = ((CFSRValue & 0x0000FF00) >> 8); // mask and right shift to lsb
}



enum { r0, r1, r2, r3, r12, lr, pc, psr};
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
void stackDump(uint32_t stack[])
{
   static char msg[80];
   sprintf(msg, "r0  = 0x%08x\n", stack[r0]);
   printErrorMsg(msg);
   sprintf(msg, "r1  = 0x%08x\n", stack[r1]);
   printErrorMsg(msg);
   sprintf(msg, "r2  = 0x%08x\n", stack[r2]);
   printErrorMsg(msg);
   sprintf(msg, "r3  = 0x%08x\n", stack[r3]);
   printErrorMsg(msg);
   sprintf(msg, "r12 = 0x%08x\n", stack[r12]);
   printErrorMsg(msg);
   sprintf(msg, "lr  = 0x%08x\n", stack[lr]);
   printErrorMsg(msg);
   sprintf(msg, "pc  = 0x%08x\n", stack[pc]);
   printErrorMsg(msg);
   sprintf(msg, "psr = 0x%08x\n", stack[psr]);
   printErrorMsg(msg);
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
void printMemoryManagementErrorMsg(uint32_t CFSRValue)
{
   printErrorMsg("Memory Management fault: ");
   CFSRValue &= 0x000000FF; // mask just mem faults
   if((CFSRValue & (1<<5)) != 0) {
      printErrorMsg("A MemManage fault occurred during FP lazy state preservation\n");
   }
   if((CFSRValue & (1<<4)) != 0) {
      printErrorMsg("A derived MemManage fault occurred on exception entry\n");
   }
   if((CFSRValue & (1<<3)) != 0) {
      printErrorMsg("A derived MemManage fault occurred on exception return.\n");
   }
   if((CFSRValue & (1<<1)) != 0) {
      printErrorMsg("Data access violation.\n");
   }
   if((CFSRValue & (1<<0)) != 0) {
      printErrorMsg("MPU or Execute Never (XN) default memory map access violation\n");
   }
   if((CFSRValue & (1<<7)) != 0) {
      static char msg[80];
      sprintf(msg, "SCB->MMFAR = 0x%08x\n", SCB->MMFAR );
      printErrorMsg(msg);
   }
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
void Hard_Fault_Handler(uint32_t stack[])
{
   static char msg[80];
	__ASM volatile("BKPT #01");
   //if((CoreDebug->DHCSR & 0x01) != 0) {
      printErrorMsg("In Hard Fault Handler\n");
      sprintf(msg, "SCB->HFSR = 0x%08x\n", SCB->HFSR);
      printErrorMsg(msg);
      if ((SCB->HFSR & (1 << 30)) != 0) {
         printErrorMsg("Forced Hard Fault\n");
         sprintf(msg, "SCB->CFSR = 0x%08x\n", SCB->CFSR );
         printErrorMsg(msg);
         if((SCB->CFSR & 0xFFFF0000) != 0) {
            printUsageErrorMsg(SCB->CFSR);
         } 
         if((SCB->CFSR & 0xFF00) != 0) {
            printBusFaultErrorMsg(SCB->CFSR);
         }
         if((SCB->CFSR & 0xFF) != 0) {
            printMemoryManagementErrorMsg(SCB->CFSR);
         }      
      }  
      stackDump(stack);
      
   //}
   while(1);
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

When the processor invokes an exception, it automatically stores the following eight 
registers to the SP in the following order: 
• Program Counter (PC) 
• Processor Status Register (xPSR) 
• r0-r3 
• r12 
• Link Register (LR).
 **********************************************************************/
void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
/* These are volatile to try and prevent the compiler/linker optimising them
away as the variables never actually get used.  If the debugger won't show the
values of the variables, make them global my moving their declaration outside
of this function. */
	volatile uint32_t r0;
	volatile uint32_t r1;
	volatile uint32_t r2;
	volatile uint32_t r3;
	volatile uint32_t r12;
	volatile uint32_t lr; /* Link register. */
	volatile uint32_t pc; /* Program counter. */
	volatile uint32_t psr;/* Program status register. */
	volatile uint32_t CFSR,HFSR,MMFAR,BFAR;/* Program status register. */
	volatile uint32_t arr[16];	
	arr[0] = r0 = pulFaultStackAddress[ 0 ];
	arr[1] = r1 = pulFaultStackAddress[ 1 ];
	arr[2] = r2 = pulFaultStackAddress[ 2 ];
	arr[3] = r3 = pulFaultStackAddress[ 3 ];

	arr[4] = r12 = pulFaultStackAddress[ 4 ];
	arr[5] = lr = pulFaultStackAddress[ 5 ];
	arr[6] = pc = pulFaultStackAddress[ 6 ];
	arr[7] = psr = pulFaultStackAddress[ 7 ];
	arr[8] = CFSR = *((volatile uint32_t *)(0xE000ED28));
	arr[9] = HFSR = *((volatile uint32_t *)(0xE000ED2C));
	arr[10] = MMFAR = *((volatile uint32_t *)(0xE000ED34));
	arr[11] = BFAR = *((volatile uint32_t *)(0xE000ED38));
	
//	EEPROM_Erase(0);
//	EEPROM_Write(0,0,(uint32_t*)arr,MODE_32_BIT,12);	
#if (WWDT_ENABLE==1) 	
	/* When the following line is hit, the variables contain the register values. */
	// Initialize WDT, IRC OSC, interrupt mode, timeout = 5000000us = 5s
	WWDT_Init(WDT_TIMEOUT);

	WWDT_Enable(ENABLE);

	WWDT_SetMode(WWDT_RESET_MODE, ENABLE);
	
	// Start watchdog with timeout given
	WWDT_Start(WDT_TIMEOUT);

	WWDT_Feed();	
#endif	
	for( ;; );
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
__asm void MemManage_Handler(void)
{
	 BKPT #01
   TST lr, #4
   ITE EQ
   MRSEQ r0, MSP
   MRSNE r0, PSP
	 LDR r1,[r0,#24]
   B __cpp(prvGetRegistersFromStack)
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
        " TST lr, #4                                                \n"
        " ITE eq                                                    \n"
        " MRSEQ r0, msp                                             \n"
        " MRSNE r0, psp                                             \n"
				" LDR r1,[r0,#24]																						\n"
        " LDR r2, handler2_address_const                            \n"
        " BX r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
 **********************************************************************/
__asm void BusFault_Handler(void)
{
	 BKPT #01
   TST lr, #4
   ITE EQ
   MRSEQ r0, MSP
   MRSNE r0, PSP
	 LDR r1,[r0,#24]
   B __cpp(prvGetRegistersFromStack)
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

__asm void UsageFault_Handler(void)
{
	 BKPT #01
   TST lr, #4
   ITE EQ
   MRSEQ r0, MSP
   MRSNE r0, PSP
	 LDR r1,[r0,#24]
   B __cpp(prvGetRegistersFromStack)
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
#if defined(__CC_ARM)
__asm void HardFault_Handler(void)
{
	 BKPT #01
   TST lr, #4
   ITE EQ
   MRSEQ r0, MSP
   MRSNE r0, PSP
	 LDR r1,[r0,#24]
   B __cpp(prvGetRegistersFromStack)
}
#elif defined(__ICCARM__)
void HardFault_Handler(void)
{
   __asm("TST lr, #4");
   __asm("ITE EQ");
   __asm("MRSEQ r0, MSP");
   __asm("MRSNE r0, PSP");
   __asm("B Hard_Fault_Handler");
}
#else
  #warning Not supported compiler type
#endif

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

//void lpc1768_mpu_config(void)
//{
//   /* Disable MPU */
//   MPU->CTRL = 0;
//   /* Configure region 0 to cover 512KB Flash (Normal, Non-Shared, Executable, Read-only) */
//   MPU->RBAR = 0x00000000 | REGION_Valid | 0;
//   MPU->RASR = REGION_Enabled | NORMAL | REGION_512K | RO;
//   /* Configure region 1 to cover CPU 32KB SRAM (Normal, Non-Shared, Executable, Full Access) */
//   MPU->RBAR = 0x10000000 | REGION_Valid | 1;
//   MPU->RASR = REGION_Enabled | NOT_EXEC | NORMAL | REGION_32K | FULL_ACCESS;
//   /* Configure region 2 to cover AHB 32KB SRAM (Normal, Non-Shared, Executable, Full Access) */
//   MPU->RBAR = 0x2007C000 | REGION_Valid | 2;
//   MPU->RASR = REGION_Enabled | NOT_EXEC | NORMAL | REGION_32K | FULL_ACCESS;
//   /* Configure region 3 to cover 16KB GPIO (Device, Non-Shared, Full Access Device, Full Access) */
//   MPU->RBAR = 0x2009C000 | REGION_Valid | 3;
//   MPU->RASR = REGION_Enabled |DEVICE_NON_SHAREABLE | REGION_16K | FULL_ACCESS;
//   /* Configure region 4 to cover 512KB APB Peripherials (Device, Non-Shared, Full Access Device, Full Access) */
//   MPU->RBAR = 0x40000000 | REGION_Valid | 4;
//   MPU->RASR = REGION_Enabled | DEVICE_NON_SHAREABLE | REGION_512K | FULL_ACCESS;
//   /* Configure region 5 to cover 2MB AHB Peripherials (Device, Non-Shared, Full Access Device, Full Access) */
//   MPU->RBAR = 0x50000000 | REGION_Valid | 5;
//   MPU->RASR = REGION_Enabled | DEVICE_NON_SHAREABLE | REGION_2M | FULL_ACCESS;
//   /* Configure region 6 to cover the 1MB PPB (Privileged, XN, Read-Write) */
//   MPU->RBAR = 0xE0000000 | REGION_Valid | 6;
//   MPU->RASR = REGION_Enabled |STRONGLY_ORDERED_SHAREABLE | REGION_1M | FULL_ACCESS;
//   /* Enable MPU */
//   MPU->CTRL = 1;
//   __ISB();
//   __DSB();
//}
