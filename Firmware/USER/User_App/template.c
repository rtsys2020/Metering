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
#include "includes.h"
#include "template.h"

//#define  APP_TASK_TEST_STK_SIZE                        32
///* Private Variables ---------------------------------------------------------- */
///** @defgroup Private Variable
// * @{
// */
// 
//static  OS_STK         App_TaskTestStk[APP_TASK_TEST_STK_SIZE];

///**
// * @}
// */
///* End of Private Variables ----------------------------------------------------*/ 




///*********************************************************************//**
// * @author             
// * @brief 	
// * @date 
// * @version  
// * @description 
// * @param[in]		None.
// * @param[out]		None.
// * @return 				             
// *                         
// **********************************************************************/
//void  App_MMcTestTaskCreat (void)
//{
//	    CPU_INT08U  os_err;

//	os_err = os_err; /**< Comment on variable . */


//	os_err = OSTaskCreate((void (*)(void *)) test_moudule /**< pointer of function */,				
//                          (void          * ) 0/**< pointer of input argument. */,							
//                          (OS_STK        * )&App_TaskTestStk[APP_TASK_TEST_STK_SIZE - 1]/**< pointer of stak */,		
//                          (INT8U           ) APP_TASK_TEST_PRIO  )/**< task priority : big number les priority . */;							

//	#if OS_TASK_NAME_EN > 0
//    	OSTaskNameSet(APP_TASK_TEST_PRIO, "Task Test MMC FatFs", &os_err);
//	#endif
//}


/*
EOF
*/

/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void test_moudule(void)
{

	while(1)
	{

	}
}
