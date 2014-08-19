/****************************************Copyright (c)****************************************************
**                                      
**                               
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               RTC_CFG.h
** Descriptions:            ucosii configuration
**
**--------------------------------------------------------------------------------------------------------
** Created by:              
** Created date:            
** Version:                
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __RTC_CFG_H__
#define  __RTC_CFG_H__
					  
#include "includes.h"

/* LPC Definitions */
#define _LPC_RTC		(LPC_RTC)
/* Get RTC time */
void rtc_gettime (RTC_TIME_Type *rtc);
/* Set RTC time */
void rtc_settime (const RTC_TIME_Type *rtc);
/*return serial number as string*/
uint16_t getSerialNumber(uint8_t* serial);
/*return current time as string*/ 
uint16_t getCurrTime(uint8_t* serial);
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

