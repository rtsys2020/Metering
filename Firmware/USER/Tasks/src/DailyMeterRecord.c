/**********************************************************************
* $Id$		dailymeterrecord.c				2010-06-04
*//**
* @file		dailymeterrecord.c
* @brief	
* @version	2.0
* @date		04. June. 2010
* @author	
**********************************************************************/
#include "applicationtask.h"
#include "includes.h"
#include "DailyMeterRecord.h" 
#include "inc\rtc_bsp.h"
#include "alarmmangment.h"
#include "osinit.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/


static  void  DailyMeter_TaskStart (void *p_arg);

static RTC_TIME_Type dailyMeterTime[3];

static alarm_index_t srcIndex[]={ALARM_DAILY_METER_GAZ,ALARM_DAILY_METER_WATER,ALARM_DAILY_METER_ELEC};
static CallFunAlarm alarm_Func[]={DailyMeterSendSignalGaz,DailyMeterSendSignalWater,DailyMeterSendSignalElec};

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;


OS_STK        DAILYM_TaskStartStk[DAILYM_TASK_START_STK_SIZE];
/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */

/*********************************************************************//**
 * @author             
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
static DialyMeterSource_t DailyMeterWaitForSignal(uint8_t *err)
{
	DialyMeterSource_t *src;
	//OSSemPend(dailyMeterSem,0,&err);
	src = (DialyMeterSource_t*)OSQPend(dialyMeterQ,0,err);
	return *src;
}

///*********************************************************************//**
// * @author   
// * @brief 	
// * @date 
// * @version  1.0
// * @description 
// * @param[in]		None.
// * @param[out]		None.
// * @return 				             
// *                         
// **********************************************************************/
//uint8_t DailyMeterSendSignal(RTC_TIME_Type* fulltime,DialyMeterSource_t src)
//{
//	uint8_t err;
//	RTC_TIME_Type compTime;
//	static  DialyMeterSource_t msg;
//	RTC_BSP_CompareTime(&compTime,&dailyMeterTime[src],fulltime);
//	if(compTime.MIN == 0 & compTime.HOUR == 0)
//	{
//		msg = src;
//		OSQPost(dialyMeterQ,&msg);
//		//err = OSSemPost(dailyMeterSem);
//	}
//	return err;
//}

/*********************************************************************//**
 * @author   
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void DailyMeterSendSignalWater(void)
{
	uint8_t err;
	static DialyMeterSource_t msg=WATER;
	OSQPost(dialyMeterQ,&msg);
	return ;
}
/*********************************************************************//**
 * @author   
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void DailyMeterSendSignalGaz(void)
{
	uint8_t err;
	static DialyMeterSource_t msg=GAZ;
	OSQPost(dialyMeterQ,&msg);
	return ;
}
/*********************************************************************//**
 * @author   
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void DailyMeterSendSignalElec(void)
{
	uint8_t err;
	static DialyMeterSource_t msg=ELECTRICITY;
	OSQPost(dialyMeterQ,&msg);
	return ;
}

/*********************************************************************//**
 * @author             
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
Status DailyMeterSetAlarmTime(RTC_TIME_Type* fulltime,DialyMeterSource_t src)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF;
		alarm.t1.month = 0;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = alarm_Func[src];
		Alarm_MGN(&alarm,srcIndex[src]);
		//memcpy(&dailyMeterTime[src],fulltime,sizeof(RTC_TIME_Type));
		return SUCCESS;
	}
	return ERROR;
}
/*********************************************************************//**
 * @author             
 * @brief 	
 * @date 
 * @version  
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void DailyMeterTask_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 23;
	time.MIN = 59;
	
//	dailyMeterSem = OSSemCreate(0);
	
	
	DailyMeterSetAlarmTime(&time,GAZ);
	DailyMeterSetAlarmTime(&time,WATER);
	DailyMeterSetAlarmTime(&time,ELECTRICITY);
	
	os_err = OSTaskCreateExt((void (*)(void *)) DailyMeter_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&DAILYM_TaskStartStk[DAILYM_TASK_START_STK_SIZE - 1],
                             (INT8U           ) DAILYM_TASK_START_PRIO,
                             (INT16U          ) DAILYM_TASK_START_PRIO,
                             (OS_STK        * )&DAILYM_TaskStartStk[0],
                             (INT32U          ) DAILYM_TASK_START_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(DAILYM_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);
#endif



}
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/	  
static  void  DailyMeter_TaskStart (void *p_arg)
{   
	uint8_t err;
	DialyMeterSource_t src;
	/***************  Init hardware ***************/
	
																							/*Initialize user defined BSP functions*/

	for(;;)
   	{
			src = DailyMeterWaitForSignal(&err);
			if( err == OS_ERR_NONE)
			{
				switch(src)
				{
					case WATER:
					{
						//do daily water recording
						break;
					}
					case GAZ:
					{
						//do daily gaz recording
						break;
					}
					case ELECTRICITY:
					{
						//do daily electricity recording
						break;
					}					
				}
					//do work
			}
      OSTimeDlyHMSM(0, 1, 0, 0);							 /* Delay One minute */
    }	
}
/**
 * @}
*/
