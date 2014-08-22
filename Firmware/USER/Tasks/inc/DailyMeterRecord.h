/**********************************************************************
* $Id$		dailymeterrecord.h			2013-12-15
*//**
* @file		dailymeterrecord.h
* @brief	
* @version	1.0
* @date		28. Decm. 2013
* @author	
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#ifndef DAILYMETERRECORDTASK_H_
#define  DAILYMETERRECORDTASK_H_

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#include "includes.h"


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/

//<o> Daily Meter Task Priority
#define DAILYM_TASK_START_PRIO 11
//<o> Daily Meter TaskStack Size
#define DAILYM_TASK_START_STK_SIZE 64



/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
typedef enum
{
	GAZ,
	WATER,
	ELECTRICITY
}DialyMeterSource_t;
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
void DailyMeterTask_initial(void);
static DialyMeterSource_t DailyMeterWaitForSignal(uint8_t *err);
uint8_t DailyMeterSendSignal(RTC_TIME_Type* fulltime,DialyMeterSource_t src);
Status DailyMeterSetAlarmTime(RTC_TIME_Type* fulltime,DialyMeterSource_t src);
void DailyMeterSendSignalGaz(void);
void DailyMeterSendSignalWater(void);
void DailyMeterSendSignalElec(void);
/*
EOF
*/

#endif

/*
EOF
*/

