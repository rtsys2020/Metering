/**********************************************************************
* $Id$		loadprofil_task.c				
*//**
* @file		loadprofil_task.c
* @brief	
* 		
* @version	1.0
* @date		
* @author	
**********************************************************************/
#include "applicationtask.h"
#include "includes.h"
#include "loadprofil_task.h" 
#include "inc\rtc_bsp.h"
#include "alarmmangment.h"
#include "osinit.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/


static  void  LoadProfil_TaskStart (void *p_arg);

static RTC_TIME_Type LoadProfilTime[3];

static alarm_index_t srcIndex[]={ALARM_LOAD_PROFIL_GAZ,ALARM_LOAD_PROFIL_WATER,ALARM_LOAD_PROFIL_ELEC};
static CallFunAlarm alarm_Func[]={LoadProfilSendSignalGaz,LoadProfilSendSignalWater,LoadProfilSendSignalElec};

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *LoadProfilSem;

OS_STK        LOAD_PROFIL_TaskStartStk[LOAD_PROFIL_TASK_START_STK_SIZE];
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
void LoadProfilSendSignalWater(void)
{
	uint8_t err;
	static LoadProfilSource_t msg=LOAD_WATER;
	OSQPost(loadProfilQ,&msg);
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
void LoadProfilSendSignalGaz(void)
{
	uint8_t err;
	static LoadProfilSource_t msg=LOAD_GAZ;
	OSQPost(loadProfilQ,&msg);
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
void LoadProfilSendSignalElec(void)
{
	uint8_t err;
	static LoadProfilSource_t msg=LOAD_ELECTRICITY;
	OSQPost(loadProfilQ,&msg);
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
Status LoadProfilSetAlarmTime(RTC_TIME_Type* fulltime,LoadProfilSource_t src)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF00;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = alarm_Func[src];
		Alarm_MGN(&alarm,srcIndex[src]);
		//memcpy(&LoadProfilTime[src],fulltime,sizeof(RTC_TIME_Type));
		return SUCCESS;
	}
	return ERROR;
}

/*********************************************************************//**
 * @author    ???? ?????         
 * @brief 	????? ????? ??? ??? ????? ??? ????? ? ??????? ??????
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
static LoadProfilSource_t LoadProfilWaitForSignal(uint8_t *err)
{
	LoadProfilSource_t *src;
	//OSSemPend(dailyMeterSem,0,&err);
	src = (LoadProfilSource_t*)OSQPend(loadProfilQ,0,err);
	return *src;
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
void LoadProfilTask_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 23;
	time.MIN = 59;
	
//	LoadProfilSem = OSSemCreate(0);

	
	LoadProfilSetAlarmTime(&time,LOAD_GAZ);
	LoadProfilSetAlarmTime(&time,LOAD_WATER);
	LoadProfilSetAlarmTime(&time,LOAD_ELECTRICITY);
	
	os_err = OSTaskCreateExt((void (*)(void *)) LoadProfil_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&LOAD_PROFIL_TaskStartStk[LOAD_PROFIL_TASK_START_STK_SIZE - 1],
                             (INT8U           ) LOAD_PROFIL_TASK_START_PRIO,
                             (INT16U          ) LOAD_PROFIL_TASK_START_PRIO,
                             (OS_STK        * )&LOAD_PROFIL_TaskStartStk[0],
                             (INT32U          ) LOAD_PROFIL_TASK_START_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(LOAD_PROFIL_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  LoadProfil_TaskStart (void *p_arg)
{   
	uint8_t err;
	LoadProfilSource_t src;
	/***************  Init hardware ***************/
	
																							/*Initialize user defined BSP functions*/

	for(;;)
   	{
			src = LoadProfilWaitForSignal(&err);
			if( err == OS_ERR_NONE)
			{
					//do work
			}
      OSTimeDlyHMSM(0, 1, 0, 0);							 /* Delay One minute */
    }	
}
/**
 * @}
*/
