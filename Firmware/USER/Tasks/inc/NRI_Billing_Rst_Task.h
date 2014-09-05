/**********************************************************************
* $Id$		NRI_Billing_Rst_Task.h			2013-12-15
*//**
* @file		NRI_Billing_Rst_Task.h
* @brief	
* @version	1.0
* @date		28. Decm. 2013
* @author	
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#ifndef NRI_BILLING_RST_TASK_H
#define  NRI_BILLING_RST_TASK_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#include "includes.h"


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/

//<o> NRI Billing Reset  Task Priority
#define NRI_RST_TASK_START_PRIO 11
//<o> NRI Billing Reset TaskStack Size
#define NRI_RST_TASK_START_STK_SIZE 64



/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
typedef struct
{
	uint8_t every_week_soday;
	uint8_t every_day_noday;
	uint8_t every_month_firt_days[12];
	RTC_TIME_Type NRI_Rst_Date[12];
	uint8_t NRI_Rst_Date_maxindex;
	uint8_t hour;
	uint8_t min;
}NRI_Reset_Time_t;

typedef enum
{
	ON_TIME,
	EVERY_WEEK,
	EVERY_DAY,
	EVERY_MONTH_FIRST_DAY,
	EVERY_MONTH_ON_DAY,
	ERLY_ON_DAY
}Period_Model_t;
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
void NRI_Billing_Reset_Setting(Period_Model_t type,NRI_Reset_Time_t t);
void NRI_RST__initial(void);
static Status NRI_RST_SetAlarmTime(RTC_TIME_Type* fulltime);
/*
EOF
*/

#endif

/*
EOF
*/

