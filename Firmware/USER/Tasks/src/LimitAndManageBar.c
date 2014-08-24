/**********************************************************************
* $Id$		LimitAndManageBar.c				2010-06-04
*//**
* @file		LimitAndManageBar.c
* @brief	
* @version	2.0
* @date		04. June. 2010
* @author	
*/
#include "applicationtask.h"
#include "includes.h"
#include "LimitAndManageBar.h" 
#include "alarmmangment.h"
#include "inc\rtc_bsp.h"
#include "osinit.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/




static  void  LimitAndManageBar_TaskStart (void *p_arg);

RTC_TIME_Type startTimes[NUM_OF_TIMES];
RTC_TIME_Type endTimes[NUM_OF_TIMES];

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;


OS_STK        LimitLouad_TaskStartStk[LIMIT_LOUAD_STK_SIZE];
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
Status LimitManageSetStartTime(RTC_TIME_Type* fulltime)
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
		alarm.fun = LimitManageSendStart;
		Alarm_MGN(&alarm,ALARM_LIMITMANAGE_START);
		//memcpy(&dailyMeterTime[src],fulltime,sizeof(RTC_TIME_Type));
		return SUCCESS;
	}
	return ERROR;
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
Status LimitManageSetEndTime(RTC_TIME_Type* fulltime)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF;
		alarm.t1.day = 0;
		alarm.t1.month = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = LimitManageSendEnd;
		Alarm_MGN(&alarm,ALARM_LIMITMANAGE_END);
		//memcpy(&dailyMeterTime[src],fulltime,sizeof(RTC_TIME_Type));
		return SUCCESS;
	}
	return ERROR;
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
//uint8_t LimitManageSendSignal(RTC_TIME_Type* fulltime)
//{
//	uint8_t err;
//	RTC_TIME_Type compTime;
//	uint8_t msg=0,i=0;
//	for(i=0;i<NUM_OF_TIMES;i++)
//	{
//		RTC_BSP_CompareTime(&compTime,&startTimes[i],fulltime);
//		if(compTime.MIN == 0 & compTime.HOUR == 0)
//		{
//			msg = i;
//			OSQPost(limitAndManageBarQ,&msg);
//			break;
//		}
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
void LimitManageSendStart(void)
{
	uint8_t err;
	//OSTaskResume(LIMIT_LOUAD_TASK_PRIO);
	LimitAndManageBar_taskCreate();
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
//uint8_t LimitManageWaitForSignal(uint8_t *err)
//{
//	uint8_t index;
//	//OSSemPend(dailyMeterSem,0,&err);
//	index = *(uint8_t*)OSQPend(limitAndManageBarQ,0,err);
//	return index;
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
void LimitManageSendEnd(void)
{
	uint8_t err;
	//OSTaskSuspend(LIMIT_LOUAD_TASK_PRIO);
	while (OSTaskDelReq(LIMIT_LOUAD_TASK_PRIO) != OS_ERR_TASK_NOT_EXIST) { 
		OSTimeDly(1)	;
	}
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
void LimitAndManageBar_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 0;
	time.MIN = 5;
	LimitManageSetStartTime(&time);
	
	time.HOUR  = 0;
	time.MIN = 10;
	LimitManageSetEndTime(&time);
//	
//	os_err = OSTaskCreateExt((void (*)(void *)) LimitAndManageBar_TaskStart,  /* Create the start task.                               */
//                             (void          * ) 0,
//                             (OS_STK        * )&LimitLouad_TaskStartStk[LIMIT_LOUAD_STK_SIZE - 1],
//                             (INT8U           ) LIMIT_LOUAD_TASK_PRIO,
//                             (INT16U          ) LIMIT_LOUAD_TASK_PRIO,
//                             (OS_STK        * )&LimitLouad_TaskStartStk[0],
//                             (INT32U          ) LIMIT_LOUAD_STK_SIZE,
//                             (void          * )0,
//                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
//	
//#if OS_TASK_NAME_EN > 0
//    OSTaskNameSet(LIMIT_LOUAD_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
//#endif



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
void LimitAndManageBar_taskCreate(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	os_err = OSTaskCreateExt((void (*)(void *)) LimitAndManageBar_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&LimitLouad_TaskStartStk[LIMIT_LOUAD_STK_SIZE - 1],
                             (INT8U           ) LIMIT_LOUAD_TASK_PRIO,
                             (INT16U          ) LIMIT_LOUAD_TASK_PRIO,
                             (OS_STK        * )&LimitLouad_TaskStartStk[0],
                             (INT32U          ) LIMIT_LOUAD_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(LIMIT_LOUAD_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  LimitAndManageBar_TaskStart (void *p_arg)
{   
	uint8_t err;
	uint8_t index;
	for(;;)
   	{
			/* Application code */
			 if (OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ)
				{ 
			//Release any owned resources; (2)
			//De-allocate any dynamic memory;
				OSTaskDel(OS_PRIO_SELF);
			} else
			{
				index++;
			/* Application code */
			}
			OSTimeDlyHMSM(0, 0, 100, 0);							 /* Delay One minute */
				//on relay after t time	
			
			//change time index
    }	
}
/**
 * @}
*/
