/**********************************************************************
* $Id$		tariff_task.c				
*//**
* @file		tariff_task.c
* @brief	
* @version	2.0
* @date		
* @author	
*/
#include "applicationtask.h"
#include "includes.h"
#include "tariff_task.h" 
#include "alarmmangment.h"
#include "inc\rtc_bsp.h"
#include "osinit.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/




static  void  Tariff_TaskStart (void *p_arg);


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;

OS_STK        Tariff_TaskStartStk[TARIFF_STK_SIZE];
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
uint8_t Tariff_SendSignal(uint8_t *msg)
{
	uint8_t err;
	OSQPost(Tariff_Q,&msg);
	return err;
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
void Tariff_RTC_SendSignal(void)
{
	uint8_t err;
	static uint8_t msg[]="message";
	OSQPost(Tariff_Q,msg);
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
Status Tariff_SetAlarmTime(RTC_TIME_Type* fulltime)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF00;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = Tariff_RTC_SendSignal;
		Alarm_MGN(&alarm,ALARM_TARIFF);
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
uint8_t Tariff_WaitForSignal(uint8_t *msg)
{
	uint8_t err;
	uint8_t *buff;
	//OSSemPend(dailyMeterSem,0,&err);
	buff = (uint8_t*)OSQPend(Tariff_Q,0,&err);
	//memcpy();
	return err;
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
void Tariff_Table_Update(tariff_t* table)
{

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
void Tariff_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 00;
	time.MIN = 00;
	
//	dailyMeterSem = OSSemCreate(0);

	
	Tariff_SetAlarmTime(&time);
	
	os_err = OSTaskCreateExt((void (*)(void *)) Tariff_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&Tariff_TaskStartStk[TARIFF_STK_SIZE - 1],
                             (INT8U           ) TARIFF_TASK_PRIO,
                             (INT16U          ) TARIFF_TASK_PRIO,
                             (OS_STK        * )&Tariff_TaskStartStk[0],
                             (INT32U          ) TARIFF_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(TARIFF_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  Tariff_TaskStart (void *p_arg)
{   
	uint8_t err;
	uint8_t index;
	for(;;)
   	{
			//wait for signal to start calculate avarage load
			index = Tariff_WaitForSignal(&err);

    }	
}


/**
 * @}
*/
