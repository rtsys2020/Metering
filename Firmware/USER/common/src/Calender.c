/**********************************************************************
* $Id$		template.c			2013-10
*//**
* @file		template.c
* @brief	Use as Template
*			
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee ElmoSanaat Reasearch And Development Team
* 
* Copyright(C) 2013, ElmoSanaat.co
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
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under ElmoSanaat '
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with ElmoSanaat  .  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"
//add by rezaee
#include "rtc_cfg.h"
#include "sdram_config.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
//unsigned int  Year;   
//unsigned char Month, Day, DayOfWeek;

//unsigned int SolarYear;
//unsigned char SolarMonth, SolarDay;

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
 unsigned int  SolarLeapYears[16] = {1375, 1379, 1383, 1387, 1391, 1395, 1399, 1404, 1408, 1412, 1416, 1420, 1424, 1428, 1432, 0}; //solar range 1380,1430
 unsigned int  ChrisLeapYears[15] = {2000, 2004, 2008, 2012, 2016, 2020, 2024, 2028, 2032, 2036, 2040, 2044, 2048, 2052, 0}; //chris range 2000,2050
 unsigned char ChrisEndDay[51] = {20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21};
 unsigned char SolarEndDay[51] = {11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11};
 unsigned char ChrisMonthLen[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 unsigned char SolarMonthLen[13] = {0, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

//unsigned char Read_RTC(unsigned int Address);
//void CLS(unsigned char Data);
//void DispNum78(unsigned char Language,unsigned char DigitCount,unsigned long int n,unsigned char x, unsigned char y);
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
static unsigned int SolarLeapCount(unsigned int CurrentYear)
{
unsigned int RetValue = 343;
unsigned char i=0;

    do{
        if(CurrentYear <= SolarLeapYears[i])break;
        i += 1;
    }while(SolarLeapYears[i] != 0);
    RetValue += i;
    return RetValue;
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
static unsigned int ChrisLeapCount(unsigned int CurrentYear)
{
unsigned int RetValue = 499;
unsigned char i=0;

    do{
        if(CurrentYear <= ChrisLeapYears[i])break;
        i += 1;
    }while(ChrisLeapYears[i] != 0);
    RetValue += i;
    return RetValue;
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
static unsigned char ChrisLeapYear(unsigned int CurrentYear)
{
unsigned char i=0;

    do{
        if(CurrentYear == ChrisLeapYears[i])
            return 1;
        i += 1;
    }while(ChrisLeapYears[i] != 0);
    return 0;
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
static unsigned char SolarLeapYear(unsigned int CurrentYear)
{
unsigned char i=0;

    do{
        if(CurrentYear == SolarLeapYears[i])
            return 1;
        i += 1;
    }while(SolarLeapYears[i] != 0);
    return 0;
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
uint8_t  GetWeekday(unsigned int ChrisYear,unsigned char ChrisMonth,unsigned char ChrisDay)
{
unsigned long int NumDays=0;
unsigned char ChrisMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
unsigned char i;
    
    for(i = 1;i<ChrisMonth;i++){
        if(i==2 && ChrisLeapYear(ChrisYear)){
            NumDays += 1;
        }
        NumDays += ChrisMonths[i];
    }
    NumDays += ChrisDay;
    
    NumDays = (((long int)ChrisYear - 1) * 365) + NumDays + ChrisLeapCount(ChrisYear);    
    
    return NumDays%7;

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
void ChristianToSolar (uint16_t *Year,uint8_t *Month,uint8_t *Day)   
{
unsigned long int NumDays=0;
unsigned long int TotalDays;
unsigned char CriticalDay;
unsigned char ChrisMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
unsigned char SolarMonths[13] = {0, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
unsigned char i;
	uint16_t SolarYear;
  uint8_t SolarMonth,SolarDay;      
    for(i = 1;i<*Month;i++){
        if(i==2 && ChrisLeapYear(*Year)){
            NumDays += 1;
        }
        NumDays += ChrisMonths[i];
    }
    NumDays += *Day;
    
    NumDays = (((long int)*Year - 1) * 365) + NumDays + ChrisLeapCount(*Year);
    NumDays -= 226899;

    if(*Month < 3)
        SolarYear = *Year - 622;
    else if(*Month > 3)
        SolarYear = *Year - 621;
    else {
        CriticalDay = ChrisEndDay[*Year - 2000];
        if(*Day >= CriticalDay)
            SolarYear = *Year - 621;
        else
            SolarYear = *Year - 622;
    }

    NumDays -=  (((long int)SolarYear - 1) * 365 + SolarLeapCount(SolarYear));
    
    if(SolarLeapYear(SolarYear))
        SolarMonths[12] = 30;
    else
        SolarMonths[12] = 29;
    
    for(i=1;i<=12;i++){
        if(NumDays <= SolarMonths[i]){
            SolarMonth = i;
            break;
        }
        NumDays -= SolarMonths[i];
    }
    
    SolarDay = NumDays;  
    
		*Year = SolarYear;
		*Month = SolarMonth;
		*Day = SolarDay;
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
void SolarToChristian (uint16_t *SolarYear,uint8_t *SolarMonth,uint8_t *SolarDay)
{

unsigned long int NumDays=0;
unsigned char CriticalDay;
unsigned char ChrisMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
unsigned char SolarMonths[13] = {0, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
unsigned char i;
uint16_t Year;
uint8_t Month,Day;

    for(i=1;i<*SolarMonth;i++)
        NumDays += SolarMonths[i];
    
    NumDays += *SolarDay;
    NumDays = ((long int)*SolarYear - 1) * 365 + NumDays + SolarLeapCount(*SolarYear);
    NumDays += 226899;
    
    if(*SolarMonth < 10)
        Year = *SolarYear + 621;
    else if(*SolarMonth > 10)
        Year = *SolarYear + 622;
    else{
        CriticalDay = SolarEndDay[*SolarYear - 1380];
        if(*SolarDay >= CriticalDay)
            Year = *SolarYear + 622;
        else
            Year = *SolarYear + 621;
    }
    
    NumDays -=(((long int)Year - 1) * 365 + ChrisLeapCount(Year));
    
    if(ChrisLeapYear(Year))
        ChrisMonths[2] = 29;
    else
        ChrisMonths[2] = 28;

    for(i=1;i<=12;i++){
        if(NumDays <= ChrisMonths[i]){
            Month = i;
            break;
        }
        NumDays -= ChrisMonths[i];
    }

    Day = NumDays;        
		*SolarYear = Year ;
		*SolarMonth = Month;
		*SolarDay = Day;
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

void ChrisToSolar(unsigned char* y,unsigned char* m,unsigned char* d,uint8_t Month)   
{
unsigned long int NumDays=0;
unsigned long int TotalDays;
unsigned char CriticalDay;
unsigned char ChrisMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
unsigned char SolarMonths[13] = {0, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
unsigned char i;
unsigned int y1,y2;
unsigned char m1,d1,m2,d2;

        
    y1=*y+2000;
    m1=*m;
    d1=*d;
    
    
    for(i = 1;i<m1;i++){
        if(i==2 && ChrisLeapYear(y1)){
            NumDays += 1;
        }
        NumDays += ChrisMonths[i];
    }
    NumDays += d1;
    
    NumDays = (((long int)y1 - 1) * 365) + NumDays + ChrisLeapCount(y1);
    NumDays -= 226899;

    if(m1 < 3)
        y2 = y1 - 622;
    else if(Month > 3)
        y2 = y1 - 621;
    else {
        CriticalDay = ChrisEndDay[y1 - 2000];
        if(d1 >= CriticalDay)
            y2 = y1 - 621;
        else
            y2 = y1 - 622;
    }

    NumDays -=  (((long int)y2 - 1) * 365 + SolarLeapCount(y2));
    
    if(SolarLeapYear(y2))
        SolarMonths[12] = 30;
    else
        SolarMonths[12] = 29;
    
    for(i=1;i<=12;i++){
        if(NumDays <= SolarMonths[i]){
            m2 = i;
            break;
        }
        NumDays -= SolarMonths[i];
    } 
    
    d2 = NumDays;
    
//    CLS(0);
//    DispNum78(ENGLISH,2,y2,0,0);
//    DispNum78(ENGLISH,2,m2,1,0);
//    DispNum78(ENGLISH,2,d2,2,0);
//    delay_ms(5000);
     
    *y=y2-1300;
    *m=m2;
    *d=d2;   
}



/*
EOF
*/

