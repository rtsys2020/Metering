/**
 * @file
 * @author  John Doe <jdoe@example.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The time class represents a moment of time.
 */

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"
#include "rtc_cfg.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
 /*
*********************************************************************************************************
*                                               template()
*
* Description : Get RTC time
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : 
*
* Note(s)     : 
*
*********************************************************************************************************
*/
void rtc_gettime (RTC_TIME_Type *rtc)
{
	RTC_GetFullTime( _LPC_RTC, rtc);	
}

 /*
*********************************************************************************************************
*                                               template()
*
* Description : Set RTC time
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : 
*
* Note(s)     : 
*
*********************************************************************************************************
*/
void rtc_settime (const RTC_TIME_Type *rtc)
{
	/* Stop RTC */
	RTC_Cmd(_LPC_RTC, DISABLE);

	/* Update RTC registers */
	RTC_SetFullTime (_LPC_RTC, (RTC_TIME_Type *)rtc);

	/* Start RTC */
	RTC_Cmd(_LPC_RTC, ENABLE);
}

 /*
*********************************************************************************************************
*                                               template()
*
* Brief  Description : return serial number as string
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : 
*
* Note(s)     : 
*
*********************************************************************************************************
*/
uint16_t getSerialNumber(uint8_t* serial)
{
	memcpy(serial,"12345",5);
	return 5;
}
 /*
*********************************************************************************************************
*                                               template()
*
* Description : return current time as string
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : 
*
* Note(s)     : 
*
*********************************************************************************************************
*/

uint16_t getCurrTime(uint8_t* serial)
{
	memcpy(serial,"13920107",8);
	return 8;
}

/*
EOF
*/

