/**********************************************************************
* $Id$		memory.c			2013-10
*//**
* @file		memory.c
* @brief	
*			
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
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


OS_MEM *IHD_msg_mem;
INT8U IHD_msg_mem_Buff[10][64];

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

	IHD_msg_mem = OSMemCreate(&IHD_msg_mem_Buff[0][0], 10,64, &err);
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

