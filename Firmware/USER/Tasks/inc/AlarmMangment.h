/**********************************************************************
* $Id$		alarmmanagment.h			2013-12-15
*//**
* @file		alarmmanagment.h
* @brief	
* @version	1.0
* @date		28. Decm. 2013
* @author	
* 
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#ifndef  ALARMMANAGMENT_H
#define  ALARMMANAGMENT_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#include "includes.h"


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/
#define ALARM_TABLE_SIZE	20
//<o> Limit and manage load Task Priority
#define ALARMMNGT_TASK_PRIO 12
//<o> Daily Meter TaskStack Size
#define ALARMMNGT_STK_SIZE 64

#define ALARMMNGT_QEUEU_SIZE	5

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

typedef void (*CallFunAlarm)(void);

typedef struct
{
	uint8_t resrve;
	uint8_t src;
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}rtc_signal_t;

typedef struct
{
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
}time_t;

typedef struct
{
	time_t t1;//start time
	uint64_t mask;//mask time
	uint8_t EnDis;//enable or disable
	CallFunAlarm fun;
}alarm_t;

typedef enum
{
	ALARM_DAILY_METER_GAZ,
	ALARM_DAILY_METER_WATER,
	ALARM_DAILY_METER_ELEC,
	ALARM_MONTH_METER_GAZ,
	ALARM_MONTH_METER_WATER,
	ALARM_MONTH_METER_ELEC,
	ALARM_IHD,
	ALARM_LIMITMANAGE_START,
	ALARM_LIMITMANAGE_END,
	ALARM_LOAD_PROFIL_GAZ,
	ALARM_LOAD_PROFIL_WATER,
	ALARM_LOAD_PROFIL_ELEC,	
	ALARM_SRC_ON,
	ALARM_SRC_OFF,
	ALARM_TARIFF
}
alarm_index_t;


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

void RTC_IRQ_SendSignal(void);
static uint64_t ALARMMNGT_WaitForSignal_RTC(void);
void Alarm_MGN(alarm_t* alarm,alarm_index_t index);

#endif

/*
EOF
*/
