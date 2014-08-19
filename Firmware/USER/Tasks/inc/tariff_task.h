//
/**********************************************************************
* $Id$		tariff_task.h			2013-12-15
*//**
* @file		tariff_task.h
* @brief	Contains the defines and function prototypes for finger reader
* @version	1.0
* @date		28. Decm. 2013
* @author	
* 
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#ifndef  TARIFF_TASK_H
#define  TARIFF_TASK_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#include "includes.h"


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/

//<o> Limit and manage load Task Priority
#define TARIFF_TASK_PRIO 12
//<o> Daily Meter TaskStack Size
#define TARIFF_STK_SIZE 64

#define TARIFF_QEUEU_SIZE	5

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

typedef struct
{
	uint8_t flag;
}tariff_t;
/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GPIO PIN DEFINITIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
uint8_t Tariff_WaitForSignal(uint8_t *msg);
Status Tariff_SetAlarmTime(RTC_TIME_Type* fulltime);
void Tariff_Table_Update(tariff_t* table);
#endif

/*
EOF
*/

