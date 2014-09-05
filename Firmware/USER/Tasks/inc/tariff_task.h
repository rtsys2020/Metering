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
#define TARIFF_TASK_PRIO 17
//<o> Daily Meter TaskStack Size
#define TARIFF_STK_SIZE 64



/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
/////////////////////////////
typedef struct
{
	uint8_t flag;
}tariff_t;

/////////////////////////////

typedef struct
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
}TOU_date_t;
/////////////////////////////
typedef struct
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}TOU_time_t;
//////////////////////////////
typedef struct
{						
	TOU_time_t t1;
	TOU_time_t t2;
	uint32_t T;
	uint16_t flag;
}active_t;
/////////////////////////////
typedef struct
{
	uint8_t start_of_week;
	TOU_date_t start;
	TOU_date_t end;
	uint8_t day_of_week[7];
	uint8_t flag;
}TOU_Session_t;
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
void Tariff_initial(void);
uint8_t Tariff_WaitForSignal(uint8_t *msg);
Status Tariff_SetAlarmTime(RTC_TIME_Type* fulltime);
void Tariff_Table_Update(tariff_t* table);

#endif

/*
EOF
*/

