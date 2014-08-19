/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               includes.h
** Descriptions:            includes.h for ucos
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


#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__


/* Includes ------------------------------------------------------------------*/
/* Standard C Libraries includes */
#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>

/* uC/OS-II Includes */
#if (_UC_OS_) 
#include  <uCOS-II\Source\ucos_ii.h>
#include  <uCOS-II\Ports\ARM-Cortex-M3\RealView\os_cpu.h>
#include  <uC-CPU\ARM-Cortex-M3\RealView\cpu.h>
#endif




/* CMSIS Includes */
#include "LPC177x_8x.h"
#include "lpc177x_8x_emac.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_mci.h"
#include "lpc177x_8x_gpdma.h"
#include "lpc177x_8x_rtc.h"
#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_i2c.h" 
#include "lpc177x_8x_exti.h" 
#include "lpc177x_8x_adc.h" 
#include "lpc177x_8x_dac.h"
#include "lpc177x_8x_timer.h" 
#include "lpc177x_8x_pwm.h" 
#include "lpc177x_8x_wwdt.h"
#include "lpc_types.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_eeprom.h"
/* LWIP Includes */
//#include  "lwip.h"


//add by rezaee
/* FatFs Includes */
#include "integer.h"
//#include "diskio.h"
//#include "ff.h"
///* User Includes */
//#include "user_bsp.h"
//#include "record.h"

//#include "gui.h"
typedef struct 
{
	uint16_t port;
	uint16_t len;
	uint8_t *dataframe;
}comunication_t;
////////////////////////////
#define RTC_FLASH_INIT_FAULT 1
#define MMC_MOUNT_FAULT	2
///////////////////////////////
 #define RISING_EDGE	 	 0//: Rising edge
 #define FALLING_EDGE 1 //: Falling edge


extern void  delay_ms (uint16_t dly);
extern void FaultCode(uint8_t fault);
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


