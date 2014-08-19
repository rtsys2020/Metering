/**********************************************************************
* $Id$		applicationtask.h			2013-12-15
*//**
* @file		applicationtask.h
* @brief	
* @version	1.0
* @date		28. Decm. 2013
* @author	s.rezaee
**********************************************************************/


#ifndef IRQHANDLERTASK_H
#define IRQHANDLERTASK_H


/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
 


#include "includes.h"


static  void  IRQ_TaskStart (void *p_arg);

#define IRQ_QEUEU_SIZE	5
#define IRQ_STK_SIZE	128
#define IRQ_TASK_PRIO	15

extern OS_EVENT *IRQ_Q;

typedef enum
{
	ADE7953_IRQA_SRC
}IRQ_src_t;

typedef void (*irqfunp)(void);

typedef struct
{
	IRQ_src_t src;
	irqfunp fun;
}IRQ_msg_t;


void IRQ_Task_initial(void);
/*
EOF
*/

#endif//__APPLICATIONTASK_H__
