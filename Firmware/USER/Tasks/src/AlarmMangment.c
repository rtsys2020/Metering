/**********************************************************************
* $Id$		alarmmangment.c				
*//**
* @file		alarmmangment.c
* @brief	
* @version	1.0
* @date		
* @author	
*/
#include "applicationtask.h"
#include "includes.h"
#include "alarmmangment.h" 
#include "inc\rtc_bsp.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/




static  void  ALARMMNGT_TaskStart (void *p_arg);


alarm_t alarmsTable[ALARM_TABLE_SIZE];

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;
OS_EVENT *ALARMMNGT_Q; 
void *ALARMMNGT_QList[ALARMMNGT_QEUEU_SIZE];

OS_EVENT *RTC_IRQ_Q; 
void *RTC_IRQ_QList[5];


OS_STK        ALARMMNGT_TaskStartStk[ALARMMNGT_STK_SIZE];


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
void RTC_IRQ_SendSignal(void)
{
	static RTC_TIME_Type time;
	static rtc_signal_t msg;//f y m d h m s
	RTC_GetFullTime(LPC_RTC,&time);
	msg.year = time.YEAR;
	msg.month = time.MONTH;
	msg.day = time.DOM;
	msg.hour = time.HOUR;
	msg.min = time.MIN;
	OSQPost(RTC_IRQ_Q,&msg);
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
static uint64_t ALARMMNGT_WaitForSignal_RTC(void)
{
	uint64_t *time;
	uint8_t err;
	time = (uint64_t*)OSQPend(RTC_IRQ_Q,0,&err);
	return *time;
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
void Alarm_MGN(alarm_t* alarm,alarm_index_t index)
{
	
	if((uint8_t)index < ALARM_TABLE_SIZE)
	{
		//alarmsTable[index] = alarm;
		memcpy(&alarmsTable[index],alarm,sizeof(alarm_t));
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
void ALARMMNGT_initial(void)
{
	CPU_INT08U  os_err;
	alarm_t alarm={{0,0,0,0},0,0,0};
	uint8_t i;
	
	os_err = os_err; /* prevent warning... */
	
	for(i=0;i<ALARM_TABLE_SIZE;i++)
	{
		alarmsTable[i]=alarm;
	}
	
//	dailyMeterSem = OSSemCreate(0);
	RTC_IRQ_Q = OSQCreate(RTC_IRQ_QList,5);
	ALARMMNGT_Q = OSQCreate(ALARMMNGT_QList,ALARMMNGT_QEUEU_SIZE);
	funMinCounter = RTC_IRQ_SendSignal;
	
	os_err = OSTaskCreateExt((void (*)(void *)) ALARMMNGT_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&ALARMMNGT_TaskStartStk[ALARMMNGT_STK_SIZE - 1],
                             (INT8U           ) ALARMMNGT_TASK_PRIO,
                             (INT16U          ) ALARMMNGT_TASK_PRIO,
                             (OS_STK        * )&ALARMMNGT_TaskStartStk[0],
                             (INT32U          ) ALARMMNGT_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(ALARMMNGT_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  ALARMMNGT_TaskStart (void *p_arg)
{   
	uint8_t err;
	uint8_t index;
	uint64_t timeSignal;
	uint8_t i=0;
	alarm_t alarm0;
	uint64_t mask;
	uint64_t *t0;
	for(;;)
   	{
			
			//wait for signal to start 
			timeSignal = ALARMMNGT_WaitForSignal_RTC();
			i=0;
			while(i<ALARM_TABLE_SIZE)//for n time
			{
				//get RTC time
				alarm0 = alarmsTable[i];
				if(alarm0.EnDis)
				{
					mask = alarm0.mask;
					t0 = (uint64_t *)&(alarm0.t1);
					if((*t0&mask)==(timeSignal&mask))
					{
						alarm0.fun();
					}
				}
				i++;
			}
    }	
}

/**
 * @}
*/
