/**********************************************************************
* $Id$		sdram_config.h			2011-06-02
*//**
* @file		sdram_config.h
* @brief	Contains all macro definitions for SAMSUNG K4S561632J
*			
* @version	1.0
* @date		02. June. 2013
* @author	ElmoSanat reashearch development Team
* 
* Copyright(C) 2013, ElmoSanat co
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
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup  Sdram_K4S561632J	Sdram_K4S561632J
 * @ingroup LPC177x_8xCMSIS_Board_Support
 * @{
 */

#ifndef __SDRAM_CONFIG_H_
#define __SDRAM_CONFIG_H_
#include "includes.h"

                        
#define MHZ           		*1000000
#define SYS_FREQ  			120000000
#if   SYS_FREQ == (120000000)
#define SDRAM_PERIOD          5.33  // 96MHz
#elif     SYS_FREQ == (96000000)
#define SDRAM_PERIOD          10.4  // 96MHz
#elif   SYS_FREQ == (72000000)
#define SDRAM_PERIOD          13.8  // 72MHz
#elif   SYS_FREQ == (60000000)
#define SDRAM_PERIOD          16.67  // 72MHz
#elif   SYS_FREQ == (57000000)
#define SDRAM_PERIOD          17.4  // 57.6MHz
#elif SYS_FREQ == (48000000)
#define SDRAM_PERIOD          20.8  // 48MHz
#elif SYS_FREQ == (36000000)
#define SDRAM_PERIOD          27.8  // 36MHz
#elif SYS_FREQ == (24000000)
#define SDRAM_PERIOD          41.7  // 24MHz
#elif SYS_FREQ == (12000000)
#define SDRAM_PERIOD          83.3  // 12MHz
#else
#error Frequency not defined
#endif

#define P2C(Period)           (((Period<SDRAM_PERIOD)?0:(uint32_t)((float)Period/SDRAM_PERIOD))+1)

#if SDRAM_MODEL == K4S561632C_32MB_16BIT
#define SDRAM_REFRESH         7813		  // 'tREFRESH = 64ms/8192'   7813 1456 748
#define SDRAM_TRP             (20)		  // 'tRP = 20ns' PrechargeCmdPeriod
#define SDRAM_TRAS            (45)		  // 'tRAS = 45ns' Active2PreChargeTime
#define SDRAM_TAPR            1			  // 'tAPR = 1CLK	DataOut2ActiveTime
#define SDRAM_TDAL            7			  // 'tDAL = 2CLK + tRP' DataIn2ActiveTime 3
#define SDRAM_TWR             3			  // 'tWR = 2CLK'	WriteRecoveryTime
#define SDRAM_TRC             (65)		  // 'tRC = 65'	Active2ActivePeriod 65
#define SDRAM_TRFC            (66)		  // 'tRFC = 65'  AutoRefrehPeriod 66
#define SDRAM_TXSR            (67)		  // 'tXSR = 1CLK' ExitSelfRefreshTime 67
#define SDRAM_TRRD            (14)		  // 'tRRD = 15'  ActiveBankLatency 14
#define SDRAM_TMRD            3			  // 'tMRD = 2CLK' LoadModeReg2Active
#define CASLATENCY			  3				//col latency
#define RASLATENCY	   		  3				//row latency
#define CHIPSIZE			  256			//size of singel cip
#define ADDRBUSWIDTH		  16			//address bus size
#define ADDRMAP	 			  EMC_ADD_MAP_ROW_BANK_COL
#define CHIPSELECTNUM		  0						//chip select
#define DATAWIDTH			  16					//data bus width
#define TOTALSIZE			  SDRAM_SIZE	//size of total memory

//#elif SDRAM_MODEL == K4M563233G_32MB_32BIT
//#define SDRAM_REFRESH         7813		  // 'tREFRESH = 64ms/8192'
//#define SDRAM_TRP             20		  // 'tRP = 20ns' PrechargeCmdPeriod
//#define SDRAM_TRAS            45		  // 'tRAS = 45ns' Active2PreChargeTime
//#define SDRAM_TAPR            1			  // 'tAPR = 1CLK	DataOut2ActiveTime
//#define SDRAM_TDAL            3			  // 'tDAL = 2CLK + tRP' DataIn2ActiveTime
//#define SDRAM_TWR             3			  // 'tWR = 2CLK'	WriteRecoveryTime
//#define SDRAM_TRC             65		  // 'tRC = 65'	Active2ActivePeriod
//#define SDRAM_TRFC            66		  // 'tRFC = 65'  AutoRefrehPeriod
//#define SDRAM_TXSR            67		  // 'tXSR = 1CLK' ExitSelfRefreshTime
//#define SDRAM_TRRD            15		  // 'tRRD = 15'  ActiveBankLatency
//#define SDRAM_TMRD            3			  // 'tMRD = 2CLK' LoadModeReg2Active
//#define CASLATENCY						3				//col latency
//#define RASLATENCY						3				//row latency
//#define CHIPSIZE							128			//size of singel cip
//#define ADDRBUSWIDTH					15			//address bus size
//#define ADDRMAP	 							EMC_ADD_MAP_ROW_BANK_COL
//#define CHIPSELECTNUM					0						//chip select
//#define DATAWIDTH							16					//data bus width
//#define TOTALSIZE							SDRAM_SIZE	//size of total memory

//#elif SDRAM_MODEL == IS42S32800D_32MB_32BIT
//#define SDRAM_REFRESH         7813	  // 'tREFRESH = 64ms/8192'
//#define SDRAM_TRP             3		  // 'tRP = 20ns' PrechargeCmdPeriod
//#define SDRAM_TRAS            7		  // 'tRAS = 45ns' Active2PreChargeTime
//#define SDRAM_TAPR            5			// 'tAPR = 1CLK	DataOut2ActiveTime
//#define SDRAM_TDAL            3			// 'tDAL = 2CLK + tRP' DataIn2ActiveTime
//#define SDRAM_TWR             2			// 'tWR = 2CLK'	WriteRecoveryTime
//#define SDRAM_TRC             10		// 'tRC = 65'	Active2ActivePeriod
//#define SDRAM_TRFC            10		// 'tRFC = 65'  AutoRefrehPeriod
//#define SDRAM_TXSR            70		// 'tXSR = 1CLK' ExitSelfRefreshTime
//#define SDRAM_TRRD            2		  // 'tRRD = 15'  ActiveBankLatency
//#define SDRAM_TMRD            2			// 'tMRD = 2CLK' LoadModeReg2Active
//#define CASLATENCY						2			//col latency
//#define RASLATENCY						1			//row latency
//#define CHIPSIZE							256		//size of singel cip
//#define ADDRBUSWIDTH					32		//address bus size
//#define ADDRMAP	 							EMC_ADD_MAP_ROW_BANK_COL
//#define CHIPSELECTNUM					0						//chip select
//#define DATAWIDTH							16					//data bus width
//#define TOTALSIZE							0x10000000	//size of total memory

//#elif SDRAM_MODEL == MT48LC8M_32MB_32BIT
//#define SDRAM_REFRESH         7813	  // 'tREFRESH = 64ms/8192'
//#define SDRAM_TRP             0		  // 'tRP = 20ns' PrechargeCmdPeriod
//#define SDRAM_TRAS            2		  // 'tRAS = 45ns' Active2PreChargeTime
//#define SDRAM_TAPR            1			// 'tAPR = 1CLK	DataOut2ActiveTime
//#define SDRAM_TDAL            2			// 'tDAL = 2CLK + tRP' DataIn2ActiveTime
//#define SDRAM_TWR             1			// 'tWR = 2CLK'	WriteRecoveryTime
//#define SDRAM_TRC             3		  // 'tRC = 65'	Active2ActivePeriod
//#define SDRAM_TRFC            3		  // 'tRFC = 65'  AutoRefrehPeriod
//#define SDRAM_TXSR            3		  // 'tXSR = 1CLK' ExitSelfRefreshTime
//#define SDRAM_TRRD            0		  // 'tRRD = 15'  ActiveBankLatency
//#define SDRAM_TMRD            0			// 'tMRD = 2CLK' LoadModeReg2Active
//#define CASLATENCY						2			//col latency
//#define RASLATENCY						1			//row latency
//#define CHIPSIZE							256		//size of singel cip
//#define ADDRBUSWIDTH					32		//address bus size
//#define ADDRMAP	 							EMC_ADD_MAP_ROW_BANK_COL
//#define CHIPSELECTNUM					0						//chip select
//#define DATAWIDTH							16					//data bus width
//#define TOTALSIZE							0x10000000	//size of total memory

#endif

void SDRAMInit( void );

#endif

/**
 * @}
 */

/*****************************************************************************
**                            End Of File
******************************************************************************/
