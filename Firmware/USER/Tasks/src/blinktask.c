/**********************************************************************
* $Id$		dac_sinewave_test.c				2010-06-04
*//**
* @file		dac_sinewave_test.c
* @brief	This example describes how to use DAC to generate a sine wave
* 			using DMA to transfer data
* @version	2.0
* @date		04. June. 2010
* @author	NXP MCU SW Application Team
*
* Copyright(C) 2010, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/
#include "applicationtask.h"
#include "includes.h"
#include "lpc177x_8x_clkpwr.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/




/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

//<o> Blink task Priority
#define  	APP_TASK_BLINK_PRIO          	 	(20) 
//<o> Blink Task Stack Size
#define  APP_TASK_BLINK_STK_SIZE           64u

OS_STK        App_TaskBlinkStk[APP_TASK_BLINK_STK_SIZE];

static void uctsk_Blink (void);
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
void  App_BlinkTaskCreate (void)
{
    CPU_INT08U  os_err;

	os_err = os_err; /* prevent warning... */

	os_err = OSTaskCreate((void (*)(void *)) uctsk_Blink,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_TaskBlinkStk[APP_TASK_BLINK_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_BLINK_PRIO  );							

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task LED Blink", &os_err);
	#endif
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
static void uctsk_Blink (void) 
{   
	OS_STK_DATA stk_data;
	int paly =0;
	uint8_t ls=0;
		//add by rezaee
	OSTimeDlyHMSM(0, 0, 0, 50);	 /* 500 MS  */
	
	GPIO_SetDir(LED1_CORE_PORT,LED1_CORE_PIN,0);
	PINSEL_ConfigPin(LED1_CORE_PORT,LED1_CORE_PIN,0);
//	GPIO_IntCmd(2, 1<<11, 1);	
//	NVIC_SetPriority(GPIO_IRQn, GPIO_IRQ_PRIORITY);
//	NVIC_EnableIRQ(GPIO_IRQn);
	
	GPIO_SetDir(LED1_CORE_PORT,1<<LED1_CORE_PIN,1);
   	for(;;)
   	{   
			//OSTaskStkChk(APP_TASK_AUDIO_PRIO, &stk_data);
			//OSTaskStkChk(APP_TASK_HDLC_PRIO, &stk_data);
	  /*====LED-ON=======*/
			GPIO_ClearValue( LED1_CORE_PORT, 1<<LED1_CORE_PIN ); 
			OSTimeDlyHMSM(0, 0, 0, 500);	 /* 500 MS  */ 
		/*====LED-OFF=======*/
			GPIO_SetValue( LED1_CORE_PORT, 1<<LED1_CORE_PIN );
			OSTimeDlyHMSM(0, 0, 0, 500);	 /* 500 MS  */
			
   }
}



/**
 * @}
*/
