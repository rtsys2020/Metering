/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               app_cfg.h
** Descriptions:            ucosii configuration
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-9
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__
					  
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/
#define  DEF_ENABLED    1

#define  OS_VIEW_MODULE                  DEF_DISABLED	     	/* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */

#define  APP_CFG_DEBUG_ON_UART0					DEF_DISABLED					/* Uart0 is configured for debug*/


/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/






/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_DISABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED


//<o> Timer Task Priority
#define  	OS_TASK_TMR_PRIO                ( 2)
//<o> Application task Priority
#define  	APP_TASK_START_PRIO             (30) 
//<o> Application Stack Size
#define  APP_TASK_START_STK_SIZE                        1024


#endif
