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
#include "inc\rtc_bsp.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/




static  void  Dummy_TaskStart (void *p_arg);

#define DUMMY_QEUEU_SIZE	5
#define DUMMY_STK_SIZE	128
#define DUMMY_TASK_PRIO	15
/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;
OS_EVENT *Dummy_Q; 
void *Dummy_QList[DUMMY_QEUEU_SIZE];

OS_STK        Dummy_TaskStartStk[DUMMY_STK_SIZE];
/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */


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
void Dummy_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 00;
	time.MIN = 00;
	
//	dailyMeterSem = OSSemCreate(0);
	Dummy_Q = OSQCreate(Dummy_QList,DUMMY_QEUEU_SIZE);
	
	
	os_err = OSTaskCreateExt((void (*)(void *)) Dummy_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&Dummy_TaskStartStk[DUMMY_STK_SIZE - 1],
                             (INT8U           ) DUMMY_TASK_PRIO,
                             (INT16U          ) DUMMY_TASK_PRIO,
                             (OS_STK        * )&Dummy_TaskStartStk[0],
                             (INT32U          ) DUMMY_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(DUMMY_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  Dummy_TaskStart (void *p_arg)
{   
	uint8_t err;
	uint8_t index;
	for(;;)
   	{
			//wait for signal to start calculate avarage load
			

    }	
}


/**
 * @}
*/
