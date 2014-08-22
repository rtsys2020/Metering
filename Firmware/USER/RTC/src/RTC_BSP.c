/**********************************************************************
* $Id$		rtc_bsp.c			2013-10
*//**
* @file		rtc_bsp.c
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
#include "inc\rtc_bsp.h"
#include "DailyMeterRecord.h"
#include "alarmmangment.h" 
/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */


unsigned int  SolarLeapYears[16] = {1375, 1379, 1383, 1387, 1391, 1395, 1399, 1404, 1408, 1412, 1416, 1420, 1424, 1428, 1432, 0}; //solar range 1380,1430
unsigned int  ChrisLeapYears[15] = {2000, 2004, 2008, 2012, 2016, 2020, 2024, 2028, 2032, 2036, 2040, 2044, 2048, 2052, 0}; //chris range 2000,2050
unsigned char ChrisEndDay[51] = {20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21, 21, 20, 20, 21};
unsigned char SolarEndDay[51] = {11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 11, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11};
unsigned char ChrisMonthLen[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
unsigned char SolarMonthLen[13] = {0, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};

 
/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 

volatile RTC_ER_TIMESTAMP_Type FirstTimeStamp[3];
volatile RTC_ER_TIMESTAMP_Type LastTimeStamp[3];
volatile uint8_t evt_cnt[3];

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
void RTC_IRQHandler(void)
{
	uint32_t counterIncSt;
	RTC_TIME_Type fullTime;
	uint32_t er_status;
	
	/* This is increment counter interrupt*/
	if (RTC_GetIntPending(LPC_RTC, RTC_INT_COUNTER_INCREASE))
	{
		counterIncSt = LPC_RTC->CIIR;
		RTC_IRQ_SendSignal();
//		if(counterIncSt & RTC_CIIR_IMMIN)
//			funMinCounter();
//		RTC_GetFullTime(LPC_RTC,&fullTime);
//		DailyMeterSendSignal(&fullTime,GAZ);
//		DailyMeterSendSignal(&fullTime,WATER);
//		DailyMeterSendSignal(&fullTime,ELECTRICITY);
		
		// Clear pending interrupt
		RTC_ClearIntPending(LPC_RTC, RTC_INT_COUNTER_INCREASE);
	}

	/* Continue to check the Alarm match*/
	if (RTC_GetIntPending(LPC_RTC, RTC_INT_ALARM))
	{
		// Clear pending interrupt
		RTC_ClearIntPending(LPC_RTC, RTC_INT_ALARM);
	}
	
#if(EV0_ENABLE == 1)	
  // Get status
  er_status = RTC_ER_GetStatus(); 
  // Get events
  evt_cnt[0] =  RTC_ER_GetEventCount(0); 
  RTC_ER_GetFirstTimeStamp(0,(RTC_ER_TIMESTAMP_Type*) &FirstTimeStamp[0]);
  RTC_ER_GetLastTimeStamp(0, (RTC_ER_TIMESTAMP_Type*) &LastTimeStamp[0]);
#endif

#if(EV1_ENABLE == 1)
	// Get events
  evt_cnt[1] =  RTC_ER_GetEventCount(1); 
  RTC_ER_GetFirstTimeStamp(1,(RTC_ER_TIMESTAMP_Type*) &FirstTimeStamp[1]);
  RTC_ER_GetLastTimeStamp(1, (RTC_ER_TIMESTAMP_Type*) &LastTimeStamp[1]);
#endif	
	
#if(EV2_ENABLE == 1)	
	  // Get events
  evt_cnt[2] =  RTC_ER_GetEventCount(2); 
  RTC_ER_GetFirstTimeStamp(2,(RTC_ER_TIMESTAMP_Type*) &FirstTimeStamp[2]);
  RTC_ER_GetLastTimeStamp(2, (RTC_ER_TIMESTAMP_Type*) &LastTimeStamp[2]);
#endif	
  // Clear status
  RTC_ER_ClearStatus(er_status);	
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
void RTC_BSP_Init(RTC_TIME_Type* rtcFullTime)
{
	uint8_t i;
	
	
	
	if(!(LPC_RTC->CCR & 0x01))
	{
		RTC_Init(LPC_RTC);
		/* Disable RTC interrupt */
		NVIC_DisableIRQ(RTC_IRQn);
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(RTC_IRQn, ((0x01<<3)|0x01));
		RTC_ResetClockTickCounter(LPC_RTC);
		RTC_Cmd(LPC_RTC, ENABLE);
		RTC_CalibCounterCmd(LPC_RTC, DISABLE);

		/* Set current time for RTC */
		RTC_SetFullTime(LPC_RTC,rtcFullTime);
		EVR_initi();
    NVIC_EnableIRQ(RTC_IRQn);
	}
	else
	{
		NVIC_DisableIRQ(RTC_IRQn);
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(RTC_IRQn, ((0x01<<3)|0x01));
		    /* Enable RTC interrupt */
		for(i=0;i<3;i++)
		{
			evt_cnt[i] =  RTC_ER_GetEventCount(i); 
			RTC_ER_GetFirstTimeStamp(i,(RTC_ER_TIMESTAMP_Type*) &FirstTimeStamp[i]);
			RTC_ER_GetLastTimeStamp(i, (RTC_ER_TIMESTAMP_Type*) &LastTimeStamp[i]);
		}
		
    NVIC_EnableIRQ(RTC_IRQn);
		
	}
	//RTC_AlarmIntConfig(LPC_RTC,RTC_AMR_AMRSEC,ENABLE);
	//RTC_CntIncrIntConfig(LPC_RTC,RTC_TIMETYPE_SECOND,ENABLE);
	RTC_CntIncrIntConfig(LPC_RTC,RTC_TIMETYPE_MINUTE,ENABLE);
	//RTC_CntIncrIntConfig(LPC_RTC,RTC_TIMETYPE_HOUR,ENABLE);
}

/*********************************************************************//**
 * @brief		c_entry: Main RTC program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void EVR_initi(void)
{
	RTC_ER_CONFIG_Type	ErInit;
	uint8_t uart_in;
	uint32_t tmp = 0;
    // Init RTC_ER
	RTC_ER_InitConfigStruct(&ErInit);

	/* Pin Configuration for Event Monitor/Recoder */
#if(EV0_ENABLE == 1)	
	PINSEL_ConfigPin(EV0_PORT,EV0_PIN,EV0_FUNC_NUM);
  ErInit.InputChannel[0].EventOnPosEdge = TRUE;
	ErInit.InputChannel[0].IntWake= FALSE;
	if(RTC_ER_Init(&ErInit) == SUCCESS)
	{
        // Enable RTC_ER
		RTC_ER_Cmd(0,ENABLE);
		// Enable Interrupt
		//NVIC_EnableIRQ(RTC_IRQn);
	}	
#endif	
	
#if(EV1_ENABLE == 1)	
	////////////////////////////////////////////////
	PINSEL_ConfigPin(EV1_PORT,EV1_PIN,EV1_FUNC_NUM);
  ErInit.InputChannel[1].EventOnPosEdge = TRUE;
	ErInit.InputChannel[1].IntWake= FALSE;
	if(RTC_ER_Init(&ErInit) == SUCCESS)
	{
        // Enable RTC_ER
		RTC_ER_Cmd(1,ENABLE);
		// Enable Interrupt
		//NVIC_EnableIRQ(RTC_IRQn);
	}	
#endif
	
#if(EV2_ENABLE == 1)	
	///////////////////////////////////////////////////
	PINSEL_ConfigPin(EV2_PORT,EV2_PIN,EV2_FUNC_NUM);
  ErInit.InputChannel[2].EventOnPosEdge = TRUE;
	ErInit.InputChannel[2].IntWake= FALSE;
	if(RTC_ER_Init(&ErInit) == SUCCESS)
	{
        // Enable RTC_ER
		RTC_ER_Cmd(2,ENABLE);
		// Enable Interrupt
		//NVIC_EnableIRQ(RTC_IRQn);
	}
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
uint8_t RTC_BSP_CompareTime(RTC_TIME_Type* time,RTC_TIME_Type* t1,RTC_TIME_Type* t2)
{
	
	time->YEAR = t1->YEAR - t2->YEAR;
	time->MONTH = t1->MONTH - t2->MONTH;
	time->DOM = t1->DOM - t2->DOM;
	time->HOUR = t1->HOUR - t2->HOUR;
	time->MIN = t1->MIN - t2->MIN;	
	time->SEC = t1->SEC - t2->SEC;
	time->DOY = t1->DOY - t2->DOY;
	return 1;
}
