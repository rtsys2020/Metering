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
#include "lpc177x_8x_iap.h"
#include "lpc_types.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_eeprom.h"
/* LWIP Includes */


/* FatFs Includes */
//#include "diskio.h"
//#include "ff.h"
///* User Includes */
//#include "user_bsp.h"
//#include "record.h"

//#include "gui.h"

////////////////////////////
#define RTC_FLASH_INIT_FAULT 1
#define MMC_MOUNT_FAULT	2
///////////////////////////////
 #define RISING_EDGE	 	 0//: Rising edge
 #define FALLING_EDGE 1 //: Falling edge



#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


