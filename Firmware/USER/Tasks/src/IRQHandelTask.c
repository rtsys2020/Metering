/**********************************************************************
* $Id$		irqhandlertask.c				
*//**
* @file		irqhandlertask.c
* @brief	
* @version	2.0
* @date		
* @author	
*/
#include "applicationtask.h"
#include "includes.h"
#include "inc\rtc_bsp.h"
#include "irqhandlertask.h"
#include "inc\ade7953_i2c_driver.h"
#include "osinit.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/




/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;


OS_STK        IRQ_TaskStartStk[IRQ_STK_SIZE];
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
void IRQ_Task_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	os_err = os_err; /* prevent warning... */
	
	
	time.HOUR  = 00;
	time.MIN = 00;
	
//	dailyMeterSem = OSSemCreate(0);
	
	if(IRQ_Q == NULL)
		return;
	
	os_err = OSTaskCreateExt((void (*)(void *)) IRQ_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&IRQ_TaskStartStk[IRQ_STK_SIZE - 1],
                             (INT8U           ) IRQ_TASK_PRIO,
                             (INT16U          ) IRQ_TASK_PRIO,
                             (OS_STK        * )&IRQ_TaskStartStk[0],
                             (INT32U          ) IRQ_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(IRQ_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  IRQ_TaskStart (void *p_arg)
{   
	IRQ_msg_t *msg;
	uint8_t err;
	ADE7953_Reset();
	for(;;)
   	{
			//wait for signal to start calculate avarage load
			msg = (IRQ_msg_t*)OSQPend(IRQ_Q,0,&err);
			if(err == OS_ERR_NONE)
			{
				if(msg!=NULL && msg->fun != NULL)
				{
					msg->fun();
				}
			}
    }	
}


/**
 * @}
*/
