/**********************************************************************
* $Id$		SourceOnOff.c				2010-06-04
*//**
* @file		SourceOnOff.c
* @brief	
* @version	2.0
* @date		04. June. 2010
* @author	
*/
#include "applicationtask.h"
#include "includes.h"
#include "sourceonoff.h" 
#include "alarmmangment.h"
#include "inc\rtc_bsp.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/




static  void  SourceOnOff_TaskStart (void *p_arg);



/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;
OS_EVENT *srcOnOffQ; 
void *srcOnOffQList[SRC_ON_OFF_QEUEU_SIZE];

OS_STK        Src_On_Off_TaskStartStk[SRC_ON_OFF_STK_SIZE];
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
Status SrcOnOff_SetOnTime(RTC_TIME_Type* fulltime)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF00;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = SrcOnOff_SendOn;
		Alarm_MGN(&alarm,ALARM_SRC_ON);
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
Status SrcOnOff_SetOffTime(RTC_TIME_Type* fulltime)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF00;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = SrcOnOff_SendOff;
		Alarm_MGN(&alarm,ALARM_SRC_OFF);
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
void SrcOnOff_SendOn(void)
{
	uint8_t err;
	static uint8_t msg;
	msg = 1;
	err = OSQPost(srcOnOffQ,&msg);
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
void SrcOnOff_SendOff(void)
{
	uint8_t err;
	static uint8_t msg;
	msg = 0;
	err = OSQPost(srcOnOffQ,&msg);
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
uint8_t SrcOnOff_WaitForSignal(void)
{
	uint8_t err;
	uint8_t *msg;
	msg = (uint8_t*)OSQPend(srcOnOffQ,0,&err);
	return *msg;
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
void SourceOnOff_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 23;
	time.MIN = 59;
	
//	dailyMeterSem = OSSemCreate(0);
	srcOnOffQ = OSQCreate(srcOnOffQList,SRC_ON_OFF_QEUEU_SIZE);
	

	
	os_err = OSTaskCreateExt((void (*)(void *)) SourceOnOff_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&Src_On_Off_TaskStartStk[SRC_ON_OFF_STK_SIZE - 1],
                             (INT8U           ) SRC_ON_OFF_TASK_PRIO,
                             (INT16U          ) SRC_ON_OFF_TASK_PRIO,
                             (OS_STK        * )&Src_On_Off_TaskStartStk[0],
                             (INT32U          ) SRC_ON_OFF_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(SRC_ON_OFF_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  SourceOnOff_TaskStart (void *p_arg)
{   
	uint8_t err;
	uint8_t index;
	uint8_t mode;
	for(;;)
   	{
			mode = SrcOnOff_WaitForSignal();
			if(mode == 1)
			{
				//power on source routin
			}
			else
			{
				////power off source routin
			}
			
    }	
}
/**
 * @}
*/
