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
#include "NRI_Billing_Rst_Task.h" 
#include "inc\rtc_bsp.h"
#include "alarmmangment.h"
#include "osinit.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/

uint8_t NRI_DEAULT_RESET_WEEK=1,every_day_noday=15;
uint16_t Count_Day=0;

uint8_t NRI_Rst_Day[12];
RTC_TIME_Type NRI_Rst_Date[12];
uint8_t NRI_Rst_Date_MaxIndex=6;

static  void  NRI_RST_TaskStart (void *p_arg);

Period_Model_t NRI_Reset_Mode=EVERY_WEEK;


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;


OS_STK        NRI_RST_TaskStartStk[NRI_RST_TASK_START_STK_SIZE];
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
void NRI_Billing_Reset_Setting(Period_Model_t type,NRI_Reset_Time_t t)
{
	uint8_t i;
	RTC_TIME_Type time;
	switch(type)
	{
		case EVERY_WEEK:
		{
			NRI_DEAULT_RESET_WEEK = t.every_week_soday;
			break;
		}
		case EVERY_DAY:
		{
			every_day_noday = t.every_day_noday;
			Count_Day=0;
			break;
		}				
		case EVERY_MONTH_FIRST_DAY:
		{
			for(i=0;i<12;i++)
				NRI_Rst_Day[i]=1;
			break;
		}		
		case EVERY_MONTH_ON_DAY:
		{
			for(i=0;i<12;i++)
				NRI_Rst_Day[i]=t.every_month_firt_days[i];
			break;
		}						
		case ERLY_ON_DAY:
		{
			if(t.NRI_Rst_Date_maxindex>12)
			{
				NRI_Rst_Date_MaxIndex=12;
			}
			else
			{
				NRI_Rst_Date_MaxIndex = t.NRI_Rst_Date_maxindex;
			}
			for(i=0;i<(NRI_Rst_Date_MaxIndex);i++)
			{
				memcpy(&NRI_Rst_Date[i],&t.NRI_Rst_Date[i],sizeof(RTC_TIME_Type));
			}
			break;
		}	
	}	
	time.MIN = t.min;
	time.HOUR = t.hour;
	NRI_RST_SetAlarmTime(&time);

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
void NRI_RST_SendSignal(void)
{
	uint8_t err;
	OSSemPost(NRI_RST_Sem);
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
void NRI_RST_PendSignal(void)
{
	uint8_t err;
	OSSemPend(NRI_RST_Sem,0,&err);
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
static Status NRI_RST_SetAlarmTime(RTC_TIME_Type* fulltime)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF00;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = NRI_RST_SendSignal;
		Alarm_MGN(&alarm,ALARM_BILLING_RST);
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
void NRI_RST__initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 23;
	time.MIN = 59;
	
//	dailyMeterSem = OSSemCreate(0);
	

	
	os_err = OSTaskCreateExt((void (*)(void *)) NRI_RST_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&NRI_RST_TaskStartStk[NRI_RST_TASK_START_STK_SIZE - 1],
                             (INT8U           ) NRI_RST_TASK_START_PRIO,
                             (INT16U          ) NRI_RST_TASK_START_PRIO,
                             (OS_STK        * )&NRI_RST_TaskStartStk[0],
                             (INT32U          ) NRI_RST_TASK_START_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(NRI_RST_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  NRI_RST_TaskStart (void *p_arg)
{   
	uint8_t err,index,i;
	uint8_t prevMonth=20;
	/***************  Init hardware ***************/
	RTC_TIME_Type time;
																							/*Initialize user defined BSP functions*/
	RTC_GetFullTime(LPC_RTC,&time);
	prevMonth=time.MONTH;
	if(prevMonth>1)
		prevMonth--;
	else
		prevMonth=12;
	for(;;)
   	{
			NRI_RST_PendSignal();
			RTC_GetFullTime(LPC_RTC,&time);
			switch(NRI_Reset_Mode)
			{
				case EVERY_WEEK:
				{
					if(time.DOW == NRI_DEAULT_RESET_WEEK)
					{
						//reset billing
					}
					break;
				}
				case EVERY_DAY:
				{
					Count_Day++;
					if(Count_Day==(every_day_noday-1))
					{
						//reset billing
						Count_Day=0;
					}
					break;
				}				
				case EVERY_MONTH_FIRST_DAY:
				{
					if(time.MONTH!=prevMonth)
					{
						//reset billing
						prevMonth=time.MONTH;
					}
					break;
				}		
				case EVERY_MONTH_ON_DAY:
				{
					index = time.MONTH;
					if(NRI_Rst_Day[index]==time.DOM)
					{
						//reset billing
					}
					break;
				}						
				case ERLY_ON_DAY:
				{
					for(i=0;i<NRI_Rst_Date_MaxIndex;i++)
					{
						if(NRI_Rst_Date[i].DOM== time.DOM)
							if(NRI_Rst_Date[i].MONTH==time.MONTH)
								if(NRI_Rst_Date[i].YEAR==time.YEAR)
								{

									//reset billing

								}
					}
					break;
				}	
			}
      OSTimeDlyHMSM(0, 1, 0, 0);							 /* Delay One minute */
    }	
}
/**
 * @}
*/
