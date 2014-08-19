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
#include "record.h"
#include "FlashRTC.h"
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
uint8_t REC_storage_state;
Record_t record_g;

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 
extern const int NUM_OF_ALL_RECORD; 
//const int MAX_RECORD = NUM_OF_ALL_RECORD;
/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
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
uint8_t STX_IncGetRecord (uint8_t PCSendBuff[])//????????????????????????????
{
	uint8_t Li,i,j,Count;
	Record_t record;
	
	Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
	if(g_State.RD_flash_index != g_State.BulkRD_index){
			g_State.RD_flash_index = g_State.BulkRD_index;///???????????????????????????????????
			if (g_State.RD_flash_index == g_State.WR_flash_index)
			{
					REC_storage_state = EMPTY;
			}
			else
			{
					REC_storage_state = SOME;
			}
			//Write_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
			//Write_nv_pointers();       
	}			
	if(REC_storage_state==EMPTY){
			return 0;
	}		
	if(g_State.WR_flash_index >=g_State.RD_flash_index)
			Li = (g_State.WR_flash_index - g_State.RD_flash_index);
	else
			Li = NUM_OF_ALL_RECORD - g_State.RD_flash_index + g_State.WR_flash_index ;
	if(Li>18)Count=18;
	else Count=(unsigned char)Li; 		
	
	g_State.BulkRD_index = g_State.RD_flash_index;
	i=0;
	while(i<Count)
	{	
		if(SFlash_Read_Record(&record,g_State.BulkRD_index)==0)
		{
				break ;
		}
		else
		{
			PCSendBuff[i*14+0] = record.ID[0];
			PCSendBuff[i*14+1] = record.ID[1];
			PCSendBuff[i*14+2] = record.ID[2];
			PCSendBuff[i*14+3] = record.ID[3];
			PCSendBuff[i*14+4] = record.ID[4];
			PCSendBuff[i*14+5] = record.time.YEAR; 
			PCSendBuff[i*14+6] = record.time.MONTH;
			PCSendBuff[i*14+7] = record.time.DOM;
			PCSendBuff[i*14+8] = record.time.HOUR;
			PCSendBuff[i*14+9] = record.time.MIN;
			PCSendBuff[i*14+10] = record.time.SEC;
			PCSendBuff[i*14+11] = record.record1;
			PCSendBuff[i*14+12] = record.record2;
			PCSendBuff[i*14+13] = record.chksum;		
			++g_State.BulkRD_index;
			if (g_State.BulkRD_index >= NUM_OF_ALL_RECORD)
				g_State.BulkRD_index = 0; 		
			i++;
		}
	}			
	///add by rezaee
	g_State.RD_flash_index  = g_State.BulkRD_index;
	Write_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
	return i;
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
uint8_t STX_GetRecordStatus(void)
{

	Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
	if (g_State.RD_flash_index == g_State.WR_flash_index)
	{
			REC_storage_state = EMPTY;
		return EMPTY;
	}
	REC_storage_state = SOME;	
	return SOME;		
}
//COMM_INCGETRECORD
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
uint8_t STX_GetRecord(uint8_t PCSendBuff[])
{
	uint8_t Li,i,j,Count;
	Record_t record;
	
	if (STX_GetRecordStatus()== EMPTY)
	{
		return 0;
	}

	Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
	if(g_State.WR_flash_index >=g_State.RD_flash_index)
			Li = (g_State.WR_flash_index - g_State.RD_flash_index);
	else
			Li = NUM_OF_ALL_RECORD - g_State.RD_flash_index + g_State.WR_flash_index ;
	if(Li>18)Count=18;
	else Count=(unsigned char)Li; 		
	
	g_State.BulkRD_index = g_State.RD_flash_index;
	i=0;
	while(i<Count)
	{	
		if(SFlash_Read_Record(&record,g_State.BulkRD_index)==0)
		{
				break;
		}
		else
		{
			PCSendBuff[i*14+0] = record.ID[0];
			PCSendBuff[i*14+1] = record.ID[1];
			PCSendBuff[i*14+2] = record.ID[2];
			PCSendBuff[i*14+3] = record.ID[3];
			PCSendBuff[i*14+4] = record.ID[4];
			PCSendBuff[i*14+5] = record.time.YEAR; 
			PCSendBuff[i*14+6] = record.time.MONTH;
			PCSendBuff[i*14+7] = record.time.DOM;
			PCSendBuff[i*14+8] = record.time.HOUR;
			PCSendBuff[i*14+9] = record.time.MIN;
			PCSendBuff[i*14+10] = record.time.SEC;
			PCSendBuff[i*14+11] = record.record1;
			PCSendBuff[i*14+12] = record.record2;
			PCSendBuff[i*14+13] = record.chksum;
			++g_State.BulkRD_index;			
			if (g_State.BulkRD_index >= NUM_OF_ALL_RECORD)
				g_State.BulkRD_index = 0; 				
		}
		i++;
	}			
	Write_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
	//g_State.BulkRD_index = g_State.RD_flash_index;
	return i;
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
uint8_t STX_BulkGetRec(uint32_t index,uint32_t count,uint8_t PCSendBuff[])
{

	uint32_t i,Li,j;
	Record_t record;	           

	i=0;            
	for(Li=0;Li<count && Li<18 ;Li++){ 
			
		if(SFlash_Read_Record(&record,index) == FALSE)
		{
				break;
		}
			
		PCSendBuff[i*14+0] = record.ID[0];
		PCSendBuff[i*14+1] = record.ID[1];
		PCSendBuff[i*14+2] = record.ID[2];
		PCSendBuff[i*14+3] = record.ID[3];
		PCSendBuff[i*14+4] = record.ID[4];
		PCSendBuff[i*14+5] = record.time.YEAR; 
		PCSendBuff[i*14+6] = record.time.MONTH;
		PCSendBuff[i*14+7] = record.time.DOM;
		PCSendBuff[i*14+8] = record.time.HOUR;
		PCSendBuff[i*14+9] = record.time.MIN;
		PCSendBuff[i*14+10] = record.time.SEC;
		PCSendBuff[i*14+11] = record.record1;
		PCSendBuff[i*14+12] = record.record2;
		PCSendBuff[i*14+13] = record.chksum;  
		index++;
		index = index%NUM_OF_ALL_RECORD;		
		i++;
	} 
	return i;
}

/*********************************************************************//**
 * @author             
 * @brief 	read image from MMC and Send to PC
 * @date 
 * @version  
 * @description 
 * @param[in]	ID
 * @param[in]		buff[] array.
 * @param[out]		None.
 * @return 				len of read data             
 *                         
 **********************************************************************/ 
void STX_CalcChksumRec(Record_t *Rec1)
{
	uint16_t chksum = 0;
	uint8_t *chp,i;
	chp = (uint8_t *)Rec1;
	for(i=0;i<13;i++)
		chksum^= chp[i];
	Rec1->chksum = chksum;
	return ;
}
/*********************************************************************//**
 * @author             
 * @brief 	read image from MMC and Send to PC
 * @date 
 * @version  
 * @description 
 * @param[in]	ID
 * @param[in]		buff[] array.
 * @param[out]		None.
 * @return 				len of read data             
 *                         
 **********************************************************************/ 
uint8_t STX_CompRec(Record_t Rec1,Record_t Rec2)
{
	if(*((uint32_t *)Rec1.ID) == *((uint32_t *)Rec2.ID))
		if(Rec1.chksum == Rec2.chksum)
			return SUCCESS;
	return ERROR;
}
/*********************************************************************//**
 * @author             
 * @brief 	read image from MMC and Send to PC
 * @date 
 * @version  
 * @description 
 * @param[in]	ID
 * @param[in]		buff[] array.
 * @param[out]		None.
 * @return 				len of read data             
 *                         
 **********************************************************************/ 
uint8_t STX_PutRec(Record_t Record) ////////////////////////////
{
	signed char *ptr,i,Verify,RetValue=0;
	unsigned long int WR_ptr;
	unsigned int Address,Sector;
	unsigned char Mem;
	uint8_t Li,j,Count;
	Record_t Rectmp;
	
	Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);           
  WR_ptr=g_State.WR_flash_index;
  //SFlash_Read((uint8_t*)&Rectmp,sizeof(Rectmp),WR_ptr*sizeof(Rectmp));  
	if(SFlash_Write_Data_Record(&Record,WR_ptr)!= TRUE)
	//if(STX_CompRec(Record,Rectmp) != SUCCESS)
	{
		return ERROR;
	}
	++g_State.WR_flash_index;
	if(g_State.WR_flash_index >= NUM_OF_ALL_RECORD)
			g_State.WR_flash_index=0;
	
	if(g_State.WR_flash_index == g_State.RD_flash_index)   
			REC_storage_state = FULL;
	else
			REC_storage_state = SOME;     
    //Write_nv_pointers();        
	Write_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);	
  return SUCCESS;
        
}


/*********************************************************************//**
 * @author             
 * @brief 	read image from MMC and Send to PC
 * @date 
 * @version  
 * @description 
 * @param[in]	ID
 * @param[in]		buff[] array.
 * @param[out]		None.
 * @return 				len of read data             
 *                         
 **********************************************************************/ 
uint8_t STX_GetRec(Record_t *Record,uint16_t recNum) 
{
	recNum = recNum%NUM_OF_ALL_RECORD;
	SFlash_Read_Record(Record,recNum);  
  return recNum;
        
}

/*********************************************************************//**
 * @author             
 * @brief 	read image from MMC and Send to PC
 * @date 
 * @version  
 * @description 
 * @param[in]	ID
 * @param[in]		buff[] array.
 * @param[out]		None.
 * @return 				len of read data             
 *                         
 **********************************************************************/ 
uint8_t STX_GetImage(uint16_t ID,uint8_t buff[])
{
//read image from MMC and Send to PC
	//read 256 byte
	return 0;
}
 /*

EOF
*/
