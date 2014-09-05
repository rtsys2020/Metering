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
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "memory.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


//OS_MEM *HDLCmem;
//INT8U HDLCmemBuff[MY_SHARED_BUF_NUM_BLKS][MY_SHARED_BUF_BLK_SIZE];

//OS_MEM *ZKFINGERmem;
//INT8U ZKFINGERmemBuff[MY_SHARED_BUF_NUM_BLKS][MY_SHARED_BUF_BLK_SIZE];
/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void memoryInit(void)
{
	INT8U err;

//	HDLCmem = OSMemCreate(&HDLCmemBuff[0][0], MY_SHARED_BUF_NUM_BLKS,
//	                          MY_SHARED_BUF_BLK_SIZE, &err);
//	
//	ZKFINGERmem = OSMemCreate(&ZKFINGERmemBuff[0][0], MY_SHARED_BUF_NUM_BLKS,
//	                          MY_SHARED_BUF_BLK_SIZE, &err);
	/* The second argument is the number of available blocks within a 
	partition. This number must at least be two                         */
	
	/* The third argument specifies the size (in byte) of each memory
	block within the partition. A memory block must be large enough to
	hold at least a pointer                                             */
		
	/* err values could be:
	OS_NO_ERR
	OS_MEM_INVALID_ADDR --> It means the specified address is a NULL
	                        pointer.
	OS_MEM_INVALID_PART	--> It means the memory partition is not free
	                        (it is in use by other Mem managers
	OS_MEM_INVALID_BLKS --> It means there isn't at least two blocks
	                        per partition
	OS_MEM_INVALID_SIZE --> It means the block size is not even enough
	                        for storing a pointer variable              */
}


/*
EOF
*/

