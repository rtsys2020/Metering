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
#include "hdlc.h"
#include "uart.h"
#include "FlashRTC.h"
#include "record.h"
#include "setting.h"
#include "calender.h"
#include "filesystem.h"
#include "lpc177x_8x_crc.h"
#include "touchkey.h"

Session_t Session;
extern setup_t Setup;
extern uint8_t REC_storage_state;
extern OS_MEM *HDLCmem;



/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 




extern void HDLC_SendPacket(uint8_t ControlByte,uint8_t PCSendBuff[],unsigned int DataLenght);

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
unsigned char HDLC_ValidatePacket(HDLC_packet_t* packet){
	uint16_t i,CRC16=0xFFFF , len,CRCR=0;
	uint16_t PC_DataLenght;
	
	len  = packet->len;
	CRC16 = CRC16_update(CRC16,packet->src);
	CRC16 = CRC16_update(CRC16,packet->dest);
	CRC16 = CRC16_update(CRC16,packet->cmd);
	CRC16 = CRC16_update(CRC16,len);
	CRC16 = CRC16_update(CRC16,len>>8);	

	for(i=0;i<len;i++)
	{
		CRC16 = CRC16_update(CRC16,packet->data[i]);
	}
	if(CRC16 != packet->crc)
	{
		return ERROR;
	}
	return SUCCESS;

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
uint16_t CRC16_update(uint16_t crc, uint16_t a)
{
	uint16_t i;

	crc ^= a;
	for (i = 0; i < 8; ++i)
	{
		if (crc & 1)
				crc = (crc >> 1) ^ 0xA001;
		else
				crc = (crc >> 1);
	}

  return crc;
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
void SendResult(uint8_t resultcode){
	uint8_t PCSendBuff[1];
	PCSendBuff[0] = resultcode;
	HDLC_SendPacket(0,PCSendBuff,1);
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
uint8_t HDLC_packet_free(HDLC_packet_t* packet)
{
	free(packet->data);
	return SUCCESS;
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
void STX_SendInfo(void)
{
	uint8_t PCSendBuff[]="st_x_ver;ver 1,0;rec 5000;usr 6000;CAM;";   
	HDLC_SendPacket(0,PCSendBuff,43);  
	return;
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
uint8_t STX_SetTime(uint8_t PCRecBuff[])///////////////
{
	
	RTC_TIME_Type RTC_time,RTC_time2;
	if(PCRecBuff[0] == CRISTIAN)
	{
		RTC_time.YEAR=PCRecBuff[2];
		RTC_time.YEAR<<=8;
		RTC_time.YEAR+=PCRecBuff[1];
		RTC_time.MONTH=PCRecBuff[3];
		RTC_time.DOM=PCRecBuff[4]; 
	}
	else //(PCRecBuff[0]==SOLAR)
	{
		RTC_time.YEAR=PCRecBuff[1];
		RTC_time.YEAR<<=8;
		RTC_time.YEAR+=PCRecBuff[2];
		RTC_time.MONTH=PCRecBuff[3];
		RTC_time.DOM=PCRecBuff[4]; 	
		SolarToChristian((uint16_t *)&RTC_time.YEAR,(uint8_t *)&RTC_time.MONTH,(uint8_t *)&RTC_time.DOW);  //?????????????????????
	}
	RTC_time.HOUR=PCRecBuff[5];
	RTC_time.MIN=PCRecBuff[6];
	RTC_time.SEC=PCRecBuff[7];
	Set_RTC_Time(&RTC_time);
	Get_RTC_Time(&RTC_time2);
	if(RTC_time.YEAR == RTC_time2.YEAR)
		if(RTC_time.MONTH == RTC_time.MONTH)
			if(RTC_time.DOM == RTC_time2.DOM)
				if(RTC_time.HOUR == RTC_time2.HOUR)
					//if(RTC_time.MIN == RTC_time2.MIN)
						return TRUE;
  return FALSE;   		
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
uint8_t STX_GetTime(uint8_t mode,uint8_t PCSendBuff[])
{
	RTC_TIME_Type RTC_time;
	Get_RTC_Time(&RTC_time);
	if(mode==CRISTIAN){
			PCSendBuff[0] =RTC_time.YEAR;//(unsigned char)Year;
			PCSendBuff[1] =RTC_time.YEAR>>8;//Year>>8;
			PCSendBuff[2] =RTC_time.MONTH;//Month;
			PCSendBuff[3] =RTC_time.DOM;//Day;
	}
	else if(mode==SOLAR){
			ChristianToSolar((uint16_t*)&RTC_time.YEAR,(uint8_t*)&RTC_time.MONTH,(uint8_t*)&RTC_time.DOM);
			PCSendBuff[0] =RTC_time.YEAR;//(unsigned char)Year;
			PCSendBuff[1] =RTC_time.YEAR>>8;//Year>>8;
			PCSendBuff[2] =RTC_time.MONTH;//Month;
			PCSendBuff[3] =RTC_time.DOM;//Day;
	}      
	PCSendBuff[4] =RTC_time.HOUR;//Hour;
	PCSendBuff[5] =RTC_time.MIN;//Min;
	PCSendBuff[6] =RTC_time.SEC;//Sec; 
	
	return TRUE; 		
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
void ProcessPacket(HDLC_packet_t* packet)
{
	static uint8_t PC_LastCommand;
	unsigned int i,j;
	unsigned long int Li;
	uint32_t AURPointer;
	uint32_t Count;
	uint8_t paramCMD,paramData[20];
	
	Record_t record;
	uint8_t num_of_rec = 0;
	uint16_t PC_DataLenght = packet->len;
	uint8_t PCSendBuff[400],Command=COMM_DEVINFO;//////////////////////////////////////////

	if(HDLC_ValidatePacket(packet)==ERROR)
	{
		//SendResult(COMM_ERROR,PCSendBuff);
		HDLC_packet_free(packet);	
		return ;
	}		
	
	if(packet->cmd &(1<<COM_SESSION)){  
			if(Session.Status==SESSION_CLOSE){
					Session.Status=SESSION_ALIVE;
					Session.DestAddress= packet->src;               
					PCSendBuff[0]=0x10;
					PCSendBuff[1]=0x00;
					PCSendBuff[2]=0x00;  
					HDLC_SendPacket((1<<COM_SESSION)|(1<<COM_ACK),PCSendBuff,3);
					
			}                     
			else{
					if(Session.DestAddress == packet->src){ 
							Session.Status=SESSION_CLOSE;
							HDLC_SendPacket((1<<COM_SESSION)|(1<<COM_NACK),PCSendBuff,0);
					}
					else
					{
							HDLC_SendPacket((1<<COM_SESSION)|(1<<COM_BUSY),PCSendBuff,0);
					}
			}
			HDLC_packet_free(packet);
			return ;
	}  
	
	if(Session.Status==SESSION_CLOSE){ 
			HDLC_packet_free(packet);
			HDLC_SendPacket((1<<COM_SESSION)|(1<<COM_NACK),PCSendBuff,0);
			return ;
	}
	//while(1);/////////////////////////////
//	if(PCRecBuff[3]!=0)return 1;  
//	if(PC_DataLenght==0){return 1;}    
	
	Command=packet->data[0];  
      
	switch(Command){  

		case COMM_DEVINFO://is ok
		{	
			if(packet->len != 1){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			}   
			STX_SendInfo();
			HDLC_packet_free(packet);
			break;
		}
		case COMM_GETSTATUS://is ok  
		{
			if(packet->len != 1){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			}   
			//PCSendBuff[0] = COMM_GETSTATUS;
			
			
			if(STX_GetRecordStatus() == EMPTY)
			{
				PCSendBuff[0] = 0;  //status?????????
			}
			else
			{
				PCSendBuff[0] = 1;  //status?????????
			}
			PCSendBuff[1] =PC_LastCommand;
			HDLC_SendPacket(0,PCSendBuff,2);			
			HDLC_packet_free(packet);
			break;  
		}       
		case COMM_SETTIME://ok
		{
			if(packet->len != 9){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			} 
			if(STX_SetTime(&packet->data[1]) == TRUE) 
         SendResult(COMM_SUCCESS);
      else
         SendResult(COMM_ERROR); 			
			
			HDLC_packet_free(packet);
			break;			
		}  
		case COMM_GETTIME: //ok
		{
			if(packet->len != 2){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			}
			STX_GetTime(packet->data[1],PCSendBuff);
			HDLC_SendPacket(0,PCSendBuff,7);
			HDLC_packet_free(packet);			
			break;
		}
		case COMM_GETRECORD: //ok
		{
			if(packet->len != 1){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			}			
			HDLC_packet_free(packet);
			i = STX_GetRecord(PCSendBuff);
			if(i!=0)
			{
				HDLC_SendPacket(0,PCSendBuff,i*14);
			}
			else
			{
				SendResult(COMM_NODATA);
			}		
			break;    
		}
		case COMM_INCGETRECORD:  
		{   
			if(packet->len != 1){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			}			
			HDLC_packet_free(packet);
			i = STX_IncGetRecord(PCSendBuff);
			if(i!=0)
			{
				HDLC_SendPacket(0,PCSendBuff,i*14);
			}
			else
			{
				SendResult(COMM_NODATA);
			}
			break;    
		}  
		case COMM_GETRECORDBULK:  //ok
		{
			if(packet->len != 7){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			}				
			AURPointer = packet->data[1];
			AURPointer |= packet->data[2]<<8;
			AURPointer |= packet->data[3]<<16;
			//AURPointer |= packet->data[0]<<24;
			Count = packet->data[4];
			Count |= packet->data[5]<<8;
			Count |= packet->data[6]<<16;
			//Count |= packet->data[6]<<24;	
			HDLC_packet_free(packet);
			
			while(Count > 0)
			{
				i = STX_BulkGetRec(AURPointer,Count,PCSendBuff);
				if(i!=0)
				{
					HDLC_SendPacket(0,PCSendBuff,i*14);
				}
				else
				{
					SendResult(COMM_NODATA);
				}	
				Count -= i;
				AURPointer += i;				
				
			}
			//		
				break;
		}
		case COMM_INCPTR: //ok
		{
	
			if(packet->len != 1){
				SendResult(COMM_ERROR);
				HDLC_packet_free(packet);
				break;
			}		
			Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
			if(g_State.RD_flash_index != g_State.BulkRD_index){
					g_State.RD_flash_index = g_State.BulkRD_index;
					if (g_State.RD_flash_index == g_State.WR_flash_index)
					{
							REC_storage_state = EMPTY;
					}
					else
					{
							REC_storage_state = SOME;
					}
					Write_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);      
			}			
	
			if(REC_storage_state==SOME) 
					PCSendBuff[0] = 1;        
			else                     
					PCSendBuff[0] = 0;
			HDLC_SendPacket(0,PCSendBuff,1);	
			
			break;
		}
		case COMM_GETIMAGE:          
		{         
			break; 
		}           
		case COMM_SETPARAM://ok
		{
			SendResult(COMM_SUCCESS);   
			paramCMD = packet->data[1];
			memcpy(paramData,&packet->data[2],packet->len);
			HDLC_packet_free(packet);
			SetParameter(paramCMD,paramData); 
			
			break;
		}
		case COMM_GETPARAM://ok
		{			
			//SendResult(COMM_SUCCESS,PCSendBuff);   
			//delay_ms(10);
			i = GetParameter(packet->data[1],PCSendBuff);
			HDLC_SendPacket(0,PCSendBuff,i); 			
			break;
		}           
		case COMM_DIRECTFPM:
		{
			
			break;
		}
		case COMM_TOUCHKEY:
		{
			
			//TOUCHKEY_WRITE_REG(packet->data[1],packet->data[2]);
			SendResult(COMM_SUCCESS);
			HDLC_packet_free(packet);
			break;
		}
	}

   PC_LastCommand = Command; 

	return;
}





/*

EOF
*/

