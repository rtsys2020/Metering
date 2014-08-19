/**********************************************************************
* $Id$		applicationtask.h			2013-12-15
*//**
* @file		applicationtask.h
* @brief	
* @version	1.0
* @date		28. Decm. 2013
* @author	s.rezaee
**********************************************************************/


#ifndef __APPLICATIONTASK_H__
#define __APPLICATIONTASK_H__


/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
 
 /*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


#include "autenticationTask.h"
#include "irqhandlertask.h"

//<o> Application task Priority
#define  	APP_TASK_START_PRIO             (30) 
//<o> Application Stack Size
#define  APP_TASK_START_STK_SIZE                        1024

static  void  App_TaskCreate		(void);
static  void  App_TaskStart			(void		*p_arg); 
static  void  App_ObjectCreate		(void);


/*
EOF
*/

#endif//__APPLICATIONTASK_H__
