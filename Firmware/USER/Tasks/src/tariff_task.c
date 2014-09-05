/**********************************************************************
* $Id$		tariff_task.c				
*//**
* @file		tariff_task.c
* @brief	
* @version	2.0
* @date		
* @author	
*/
#include "applicationtask.h"
#include "includes.h"
#include "tariff_task.h" 
#include "alarmmangment.h"
#include "inc\rtc_bsp.h"
#include "osinit.h"
#include "list.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/



static uint8_t TOU_current_index=0;
static uint8_t Active_Current_Index=0;
static uint32_t Current_Tariff;
static TOU_date_t TimeActivate;
//active_t DefaultActiveItems[]={{0x0000,0x0700,1},{0x0701,0x0A00,2},{0x0A01,0x0d00,3},{0x0D01,0x1400,4},{0x1401,0x1701,5}};

active_t ActiveListBackup[8][8],ActiveListUsed[8][8];

TOU_Session_t TOU_TableUsed[8],TOU_TableBackup[8];


static  void  Tariff_TaskStart (void *p_arg);


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

//OS_EVENT *dailyMeterSem;

OS_STK        Tariff_TaskStartStk[TARIFF_STK_SIZE];
/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 
/*********************************************************************//**
 * @author   
 * @brief 	
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				                                 
 **********************************************************************/
void Get_TOU_WillBeActiveONTime(TOU_date_t *date)
{
	if(date!=NULL)
		*date = TimeActivate;
}
/*********************************************************************//**
 * @author   
 * @brief 	
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				                                 
 **********************************************************************/
void Set_TOU_WillBeActiveONTime(TOU_date_t *date)
{
	if(date!=NULL)
		TimeActivate = *date ;
}
/*********************************************************************//**
 * @author   
 * @brief 	
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				                                 
 **********************************************************************/
void TOU_BackupToUsedLoad(void)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		memcpy(&TOU_TableUsed[i],&TOU_TableBackup[i],sizeof(TOU_Session_t));
		memcpy(ActiveListUsed[i],ActiveListBackup[i],sizeof(active_t)*8);
	}

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
uint8_t TOU_LoadFromSD(void)
{
	

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
uint8_t TOU_StoreInSD()
{

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
void AddItemTo_TOU_List(TOU_Session_t *item,int index)
{
	if(index<8)
	{
		item->flag = 1;
	//TOU_TableBackup[index]=*item;
		memcpy(&TOU_TableBackup[index],item,sizeof(TOU_Session_t));
	}
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
int FindItemIn_TOU_List(TOU_date_t *date,TOU_Session_t* ret)
{
	uint8_t i;
	uint16_t t1,m1,m2;
	TOU_Session_t *itm;
	t1 = (date->month)<<8|(date->day);
	for(i=0;i<8;i++)
	{
		itm = &TOU_TableUsed[i];
		if(itm->flag)
		{
			m1 = (itm->start.month)<<8|(itm->start.day);
			m2 = (itm->end.month)<<8|(itm->end.day);
			if(t1>=m1 && t1<=m2)
			{
				memcpy(ret,itm,sizeof(active_t));
				return i;
			}
		}
	}
	return -1;
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
int GetItemIn_TOU_BackupList(TOU_Session_t *item,uint8_t index)
{
	if(TOU_TableBackup[index].flag)
	{
		memcpy(item,&TOU_TableBackup[index],sizeof(TOU_Session_t));
		return 1;
	}
	return 0;
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
int GetItemIn_TOU_UsedList(active_t *item,uint8_t index)
{
	if(TOU_TableUsed[index].flag)
	{
		memcpy(item,&TOU_TableUsed[index],sizeof(TOU_Session_t));
		return 1;
	}
	return 0;
}
//// /*********************************************************************//**
//// * @author   
//// * @brief 	
//// * @date 
//// * @version  1.0
//// * @description 
//// * @param[in]		None.
//// * @param[out]		None.
//// * @return 				             
//// *                         
//// **********************************************************************/
////int compareActiveItem(void *a,void *b)
////{
////	active_t *a1,*b1;
////	a1=(active_t*)a;
////	b1=(active_t*)b;
////	if(a1->t1>=b1->t1)
////		if(a1->t2<=b1->t2)
////			return 1;
////	return 0;
////}
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
void AddItemToActiveList(active_t *item,uint8_t activeNumber,int index)
{
	item->flag = 1;
	ActiveListBackup[activeNumber][index]=*item;
	
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
int FindItemInActiveList(active_t *item,uint8_t activeNumber,active_t* ret)
{
	uint8_t i;
	uint16_t t1,t2,m1,m2;
	active_t *itm;
	t1 = (item->t1.hour)<<8|(item->t1.min);
	t2 = (item->t2.hour)<<8|(item->t2.min);
	for(i=0;i<8;i++)
	{
		itm = &ActiveListUsed[activeNumber][i];
		if(itm->flag)
		{
			m1 = (itm->t1.hour)<<8|(itm->t1.min);
			m2 = (itm->t2.hour)<<8|(itm->t2.min);
			if(t1>=m1 && t2<=m2)
			{
				memcpy(ret,itm,sizeof(active_t));
				return i;
			}
		}
	}
	return -1;
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
int GetItemInActiveBackupList(active_t *item,uint8_t activeNumber,uint8_t index)
{
	if(ActiveListBackup[activeNumber][index].flag)
	{
		memcpy(item,&ActiveListBackup[activeNumber][index],sizeof(active_t));
		return 1;
	}
	return 0;
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
int GetItemInActiveUsedList(active_t *item,uint8_t activeNumber,uint8_t index)
{
	if(ActiveListUsed[activeNumber][index].flag)
	{
		memcpy(item,&ActiveListUsed[activeNumber][index],sizeof(active_t));
		return 1;
	}
	return 0;
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
uint8_t Tariff_SendSignal(uint8_t *msg)
{
	uint8_t err;
	OSQPost(Tariff_Q,&msg);
	return err;
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
void Tariff_RTC_SendSignal(void)
{
	uint8_t err;
	static uint8_t msg=2;
	OSQPost(Tariff_Q,&msg);
	return ;
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
void TOU_RTC_SendSignal(void)
{
	uint8_t err;
	static uint8_t msg=1;
	OSQPost(Tariff_Q,&msg);
	return ;
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
Status Tariff_SetAlarmTime(RTC_TIME_Type* fulltime)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x0000000000FFFF00;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.fun = Tariff_RTC_SendSignal;
		Alarm_MGN(&alarm,ALARM_TARIFF);
		//memcpy(&dailyMeterTime[src],fulltime,sizeof(RTC_TIME_Type));
		return SUCCESS;
	}
	return ERROR;
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
Status TOU_SetAlarmTime(RTC_TIME_Type* fulltime)
{
	alarm_t alarm;
	
	if(fulltime != NULL)
	{
		alarm.EnDis = ENABLE;
		alarm.mask = 0x00FFFFFFFF000000;
		alarm.t1.day = 0;
		alarm.t1.hour = fulltime->HOUR;
		alarm.t1.min = fulltime->MIN;
		alarm.t1.day = fulltime->DOM;
		alarm.t1.month = fulltime->MONTH;
		alarm.t1.year = fulltime->YEAR;
		alarm.fun = Tariff_RTC_SendSignal;
		Alarm_MGN(&alarm,ALARM_TOU);
		//memcpy(&dailyMeterTime[src],fulltime,sizeof(RTC_TIME_Type));
		return SUCCESS;
	}
	return ERROR;
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
uint8_t Tariff_WaitForSignal(uint8_t *msg)
{
	uint8_t err;
	//OSSemPend(dailyMeterSem,0,&err);
	*msg = *(uint8_t*)OSQPend(Tariff_Q,0,&err);
	//memcpy();
	return err;
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
void Tariff_Table_Update(tariff_t* table)
{

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
void Tariff_initial(void)
{
	CPU_INT08U  os_err;
	RTC_TIME_Type time;
	active_t itm,*itm2;
	int i;
	TOU_Session_t session;
	TOU_date_t date;
	os_err = os_err; /* prevent warning... */

	time.HOUR  = 00;
	time.MIN = 00;

//	dailyMeterSem = OSSemCreate(0);
	//TOU_LoadFromSD();
	//TOU_BackupToUsedLoad();
	//
	RTC_GetFullTime(LPC_RTC,&time);
	date.day = time.DOM;
	date.month = time.MONTH;	
	TOU_current_index = FindItemIn_TOU_List(&date,&session);
	Active_Current_Index = session.day_of_week[time.DOW];
	itm.t1.hour = time.HOUR;
	itm.t1.min  = time.MIN;
	i=FindItemInActiveList(&itm,Active_Current_Index,itm2);
	time.HOUR  = itm2->t2.hour;
	time.MIN = itm2->t2.min;
	Tariff_SetAlarmTime(&time);
	Current_Tariff = itm2->T;
	
	
	os_err = OSTaskCreateExt((void (*)(void *)) Tariff_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&Tariff_TaskStartStk[TARIFF_STK_SIZE - 1],
                             (INT8U           ) TARIFF_TASK_PRIO,
                             (INT16U          ) TARIFF_TASK_PRIO,
                             (OS_STK        * )&Tariff_TaskStartStk[0],
                             (INT32U          ) TARIFF_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(TARIFF_TASK_PRIO, (CPU_INT08U *)"Start Task", &os_err);
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
static  void  Tariff_TaskStart (void *p_arg)
{   
	uint8_t err;
	uint8_t index;
	for(;;)
   	{
			//wait for signal to start calculate avarage load
			err = Tariff_WaitForSignal(&index);
			if(err == OS_ERR_NONE)
			{
				if(index == 2)
				{
					//muset change tariff
				}
				else if(index==1)
				{
					//load TOU_Backup into TOU_used
				}
			}

    }	
}

/////*********************************************************************//**
//// * @author   
//// * @brief 	
//// * @date 
//// * @version  1.0
//// * @description 
//// * @param[in]		None.
//// * @param[out]		None.
//// * @return 				             
//// *                         
//// **********************************************************************/
////void AddItemToActiveList(active_t *item,uint8_t activeNumber)
////{
////	active_t *Act_node;
////	list_node_t *node;
////	if(ActiveList[activeNumber]==NULL)
////	{
////		ActiveList[activeNumber]  =list_new();
////		if(ActiveList[activeNumber]==NULL)
////			return;
////		ActiveList[activeNumber]->free = free;
////		ActiveList[activeNumber]->match = compareActiveItem;
////	}
////	Act_node = calloc(1,sizeof(active_t));
////	if(Act_node==NULL)
////		return;
////	*Act_node = *item;
////	node = list_node_new(Act_node);
////	list_rpush(ActiveList[activeNumber],node);
////}
/////*********************************************************************//**
//// * @author   
//// * @brief 	
//// * @date 
//// * @version  1.0
//// * @description 
//// * @param[in]		None.
//// * @param[out]		None.
//// * @return 				             
//// *                         
//// **********************************************************************/
////active_t* FindItemInActiveList(active_t *item,uint8_t activeNumber,int *index)
////{
////	active_t *Act_node;
////	list_node_t *node;
////	list_t	*list;
////	if(ActiveList[activeNumber]==NULL)
////	{
////		return NULL;
////		//ActiveList[index]->match = compare;
////	}
////	list=ActiveList[activeNumber];

////	node = list_find(list,item,index);
////	if(node!=NULL)
////		return node->val;
////	return NULL;
////}
/////*********************************************************************//**
//// * @author   
//// * @brief 	
//// * @date 
//// * @version  1.0
//// * @description 
//// * @param[in]		None.
//// * @param[out]		None.
//// * @return 				             
//// *                         
//// **********************************************************************/
////active_t* GetItemInActiveList(active_t *item,uint8_t activeNumber,uint8_t index)
////{
////	active_t *Act_node;
////	list_node_t *node;
////	list_t	*list;
////	int i=0;
////	if(ActiveList[activeNumber]==NULL)
////	{
////		return NULL;
////		//ActiveList[index]->match = compare;
////	}
////	list=ActiveList[activeNumber];
////	node = list_at(list,index);
////	//node = list_find(list,item,&i);
////	if(node!=NULL)
////		return node->val;
////	return NULL;
////}
/**
 * @}
*/
