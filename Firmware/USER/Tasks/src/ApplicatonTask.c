/**********************************************************************
* $Id$		applicationtask.c				2010-06-04
*//**
* @file		applicationtask.c
* @brief	
* @version	2.0
* @date		04. June. 2010
* @author	
**********************************************************************/
#include "applicationtask.h"
#include "includes.h"
#include "DailyMeterRecord.h" 
#include "LimitAndManageBar.h" 
#include "IHD_Task.h" 
#include "alarmmangment.h" 
#include "loadprofil_task.h" 
#include "sourceonoff.h" 
#include "tariff_task.h" 
#include "osinit.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/

extern void User_BSP_Init(void);

#if (OS_VIEW_MODULE == DEF_ENABLED)
extern void  App_OSViewTaskCreate (void);
#endif



static  void  App_TaskStart (void *p_arg);

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
extern void Dummy_initial(void);


OS_STK        App_TaskStartStk[APP_TASK_START_STK_SIZE];
/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
static  void  App_TaskStart (void *p_arg);
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
void os_initial(void)
{
	CPU_INT08U  os_err;
	os_err = os_err; /* prevent warning... */
	//printErrorMsg	("salam\n");
	IntDisAll();                     /* Disable all ints until we are ready to accept them.  */

  OSInit();                        /* Initialize "uC/OS-II, The Real-Time Kernel".         */
	
	os_err = OSTaskCreateExt((void (*)(void *)) App_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                             (INT8U           ) APP_TASK_START_PRIO,
                             (INT16U          ) APP_TASK_START_PRIO,
                             (OS_STK        * )&App_TaskStartStk[0],
                             (INT32U          ) APP_TASK_START_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);
#endif

	OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */


}
/*********************************************************************//**
 * @author    سعيد رضايي         
 * @brief 	اجراي تمامي تسک هاو مقدار دهي اوليه و تنظيمات دستگاه
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/	  
static  void  App_TaskStart (void *p_arg)
{   
	(void)p_arg;
	
	/***************  Init hardware ***************/
	
																							/*Initialize user defined BSP functions*/

    OS_CPU_SysTickInit(SystemCoreClock/1000);                 /* Initialize the SysTick.                              */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                            /* Determine CPU capacity.                              */
#endif
		App_SignalQeueq_Init();
		User_BSP_Init();
    App_TaskCreate();                                        /* Create application tasks.                            */
	
//	for(;;)
//   	{
//				//MainTask();//////rezaee
//      	OSTimeDlyHMSM(0, 10, 0, 0);							 /* Delay One minute */
//    }	
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

static  void  App_TaskCreate (void)
{
#if (OS_VIEW_MODULE != OS_VIEW_MODULE)
	App_OSViewTaskCreate();
#endif	
	IRQ_Task_initial();//priority 15
	//DailyMeterTask_initial();//11
	//LimitAndManageBar_initial();//12
	//IHD_initial();//13
	ALARMMNGT_initial();//14
	//LoadProfilTask_initial();//15
	//SourceOnOff_initial();//16
	//Tariff_initial();//17
	Dummy_initial();//20
}



//add by rezaee
/*********************************************************************//**
 * @brief 			delay in micro seconds
 * @param[in]		delay    The delay required (in microseconds)
 * @return 		None.
 **********************************************************************/
void  delay_us (uint32_t  delay)
{
    volatile  uint32_t  i;


    for (i = 0; i < (100 * delay); i++) {    /* This logic was tested. It gives app. 1 micro sec delay        */
        ;
    }
}

/*********************************************************************//**
 * @brief 			delay in milli seconds
 * @param[in]		delay    The delay required (in milliseconds)
 * @return 		None.
 **********************************************************************/
 void  delay_ms (uint16_t dly)
{

    volatile  uint32_t  i;
    for (i = 0; i < dly; i++) {
        delay_us(100);
    }

}


/*********************************************************************//**
 * @brief 			delay in micro seconds
 * @param[in]		delay    The delay required (in microseconds)
 * @return 		None.
 **********************************************************************/
void  Delay_us (uint32_t  delay)
{
    volatile  uint32_t  i;


    for (i = 0; i < (100 * delay); i++) {    /* This logic was tested. It gives app. 1 micro sec delay        */
        ;
    }
}

/*********************************************************************//**
 * @brief 			delay in milli seconds
 * @param[in]		delay    The delay required (in milliseconds)
 * @return 		None.
 **********************************************************************/
 void  Delay_ms (uint16_t dly)
{

    volatile  uint32_t  i;
#ifndef _UCOS_
    for (i = 0; i < dly; i++) {
        delay_us(100);
    }
#else
	uint8_t sec = dly/1000;
	uint16_t mil = dly%1000;	
	OSTimeDlyHMSM(0, 0, sec, mil);							 /* Delay One minute */
#endif	
}

void FaultCode(uint8_t fault)
{
	//Fault_g;
	//RTC_FLASH_INIT_FAULT
	fault++;
	//while(1);

}
/**
 * @}
*/
