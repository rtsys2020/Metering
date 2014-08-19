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
#include "setting.h"
#include "hdlc.h"
#include "record.h"
#include "FlashRTC.h"
//add by rezaee
setup_t Setup;
extern STX_Sate_t g_State;
extern uint8_t REC_storage_state;

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
void resetFactory(void)
{

	Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0); 
	g_State.BulkRD_index = 0;
	g_State.GlobState = 0;
	g_State.RD_flash_index = 0;
	g_State.WR_flash_index = 0;
	REC_storage_state = EMPTY;
	Write_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);

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

uint8_t SetParameter(uint8_t ParameterIndex,uint8_t PCRecBuff[])
{
	uint32_t word;
    switch(ParameterIndex)
    {
        case PARAM_LANG://ok 
				{					
            //if(PC_DataLenght!=2)return 1;
					if(PCRecBuff[1]==ENGLISH) 
							Setup.Language=ENGLISH;
					else if(PCRecBuff[1]==FARSI)
							Setup.Language=FARSI;
					else if(PCRecBuff[1]==ARABIC)
							Setup.Language=ARABIC;    
					break;
				}
        case PARAM_CALENDAR://ok  
				{					
            //if(PC_DataLenght!=2)return 1;
					if(PCRecBuff[1]==CRISTIAN) 
							Setup.Calendar=CRISTIAN;
					else //if(PCRecBuff[1]==SOLAR)
							Setup.Calendar=SOLAR;
					break;                              
				}       
        case PARAM_DAYLIGHT: //ok    
				{					
           // if(PC_DataLenght!=2)return 1;
            if(PCRecBuff[1]==ENABLE) 
                Setup.Daylight=ENABLE;
            else if(PCRecBuff[1]==DISABLE)
                Setup.Daylight=DISABLE;
            break; 
				}
        case PARAM_SPEAKER://ok
				{
					//if(PC_DataLenght!=2)return 1;
					if(PCRecBuff[1]==SPEAKER_ON) 
							Setup.Speaker = SPEAKER_ON;
					else if(PCRecBuff[1]==SPEAKER_OFF)
							Setup.Speaker=SPEAKER_OFF;
					break;   
				}
        case PARAM_BACKLIGHT://ok
				{
            //if(PC_DataLenght!=2)return 1;
					if(PCRecBuff[1]==BACKLIGHT_ON){ 
							Setup.Backlight=BACKLIGHT_ON;                 
					}
					else if(PCRecBuff[DATAOFFSET+1]==BACKLIGHT_OFF){
							Setup.Backlight=BACKLIGHT_OFF;                 
					}
					break;
				}  
        case PARAM_STANDBY://ok
				{
					Setup.Standby=PCRecBuff[1];
					break;  
        }
        case PARAM_ALARM:
				{
            //if(PC_DataLenght!=6)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>7)return 1;  // index
//            if(PCRecBuff[DATAOFFSET+2]>99)return 1; // duration
//            if(PCRecBuff[DATAOFFSET+3]>7)return 1;  // weekday
//            if(PCRecBuff[DATAOFFSET+4]>23)return 1; // hour
//            if(PCRecBuff[DATAOFFSET+5]>59)return 1; // min
//            
//            Setup.AlarmSet[PCRecBuff[DATAOFFSET+3]*8+PCRecBuff[DATAOFFSET+1]][0]=PCRecBuff[DATAOFFSET+2];
//            Setup.AlarmSet[PCRecBuff[DATAOFFSET+3]*8+PCRecBuff[DATAOFFSET+1]][1]=PCRecBuff[DATAOFFSET+4];
//            Setup.AlarmSet[PCRecBuff[DATAOFFSET+3]*8+PCRecBuff[DATAOFFSET+1]][2]=PCRecBuff[DATAOFFSET+5];  
//            CheckAlarm();
            break; 
				}
        case PARAM_SETUPPASS://ok
				{
            //if(PC_DataLenght!=4)return 1;
					Setup.Password = PCRecBuff[1];
					Setup.Password |= PCRecBuff[2]<<8;
					Setup.Password |= PCRecBuff[3]<<16;
					Setup.Password |= 0;
					break;  
        }    
        case PARAM_SN://ok
				{
					Setup.SerialNumber = PCRecBuff[1];
					Setup.SerialNumber |= PCRecBuff[2]<<8;
					Setup.SerialNumber |= PCRecBuff[3]<<16;
					Setup.SerialNumber |= 0;
					break;
				}  
        case PARAM_FC://ok
				{
					Setup.FactoryCode = PCRecBuff[1];
					Setup.FactoryCode |= PCRecBuff[2]<<8;
					Setup.FactoryCode |= PCRecBuff[3]<<16;
					Setup.FactoryCode |= 0;
					break;
				}
        case PARAM_RDINDEX: //ok
				{					

					Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
					word = g_State.RD_flash_index; 
					PCRecBuff[1] = word;
					PCRecBuff[2]|= word <<8;
					PCRecBuff[3]|= word <<16;
										
					break;
				}   
        case PARAM_WRINDEX:  //ok
				{
					word = PCRecBuff[1];
					word |= PCRecBuff[2]<<8;
					word |= PCRecBuff[3]<<16;
					//word |= 0; 
					g_State.WR_flash_index = word;
					Write_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);
					break;
        }    
        case PARAM_REPEATTIME:   
				{
            //if(PC_DataLenght!=2)return 1;
            //if(PCRecBuff[DATAOFFSET+1]>99)return 1;
					Setup.RepeatTime=PCRecBuff[1];
					break;
        }
        case PARAM_VALIDITY://ok  
				{
           // if(PC_DataLenght!=2)return 1; 
					if(PCRecBuff[1]==ENABLE) 
							Setup.ValidityCheck=ENABLE;
					else if(PCRecBuff[1]==DISABLE)
							Setup.ValidityCheck=DISABLE;
					break; 
				}
        case PARAM_F1: //ok
				{					
            //if(PC_DataLenght!=2)return 1; 
					if(PCRecBuff[1]==ENABLE) 
							Setup.F1Key=ENABLE;
					else if(PCRecBuff[1]==DISABLE)
							Setup.F1Key=DISABLE;
					break;
				}   
        case PARAM_F2: //ok 
				{
            //if(PC_DataLenght!=2)return 1; 
					if(PCRecBuff[1]==ENABLE) 
							Setup.F2Key=ENABLE;
					else if(PCRecBuff[1]==DISABLE)
							Setup.F2Key=DISABLE;
					break;
				}
        case PARAM_MISSIONKEY:  //ok
				{
            //if(PC_DataLenght!=2)return 1; 
					if(PCRecBuff[1]==ENABLE) 
							Setup.MisionKey=ENABLE;
					else if(PCRecBuff[1]==DISABLE)
							Setup.MisionKey=DISABLE;
					break;
				}   
        case PARAM_VACATIONKEY: //ok
				{
            //if(PC_DataLenght!=2)return 1; 
					if(PCRecBuff[1]==ENABLE) 
							Setup.VacationKey=ENABLE;
					else if(PCRecBuff[1]==DISABLE)
							Setup.VacationKey=DISABLE;
					break;
				}    
        case PARAM_MISSIONCARD://ok
				{
            //if(PC_DataLenght!=2)return 1; 
					if(PCRecBuff[1]==ENABLE) 
							Setup.MisionCard=ENABLE;
					else if(PCRecBuff[1]==DISABLE)
							Setup.MisionCard=DISABLE;
					break;
				}   
        case PARAM_VACATIONCARD: //ok
				{
            //if(PC_DataLenght!=2)return 1; 
					if(PCRecBuff[1]==ENABLE) 
							Setup.VacationCard=ENABLE;
					else if(PCRecBuff[1]==DISABLE)
							Setup.VacationCard=DISABLE;
					break;
				}   
        case PARAM_READERSCH:
				{
            //if(PC_DataLenght!=7)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>7)return 1;  // index
//            if(PCRecBuff[DATAOFFSET+2]>1)return 1;  // EnDis
//            if(PCRecBuff[DATAOFFSET+3]>23)return 1; // SHour
//            if(PCRecBuff[DATAOFFSET+4]>59)return 1; // SMin
//            if(PCRecBuff[DATAOFFSET+5]>23)return 1; // EHour
//            if(PCRecBuff[DATAOFFSET+5]>59)return 1; // EMin
//            
//            Setup.ReaderSch[PCRecBuff[DATAOFFSET+1]][0]=PCRecBuff[DATAOFFSET+2];
//            Setup.ReaderSch[PCRecBuff[DATAOFFSET+1]][1]=PCRecBuff[DATAOFFSET+3];
//            Setup.ReaderSch[PCRecBuff[DATAOFFSET+1]][2]=PCRecBuff[DATAOFFSET+4];
//            Setup.ReaderSch[PCRecBuff[DATAOFFSET+1]][3]=PCRecBuff[DATAOFFSET+5];
//            Setup.ReaderSch[PCRecBuff[DATAOFFSET+1]][4]=PCRecBuff[DATAOFFSET+6]; 
//            CheckReaderSch();
            break; 
				}   
        case PARAM_INOUTSCH:
				{
//            if(PC_DataLenght!=7)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>7)return 1;  // index
//            if(PCRecBuff[DATAOFFSET+2]>1)return 1;  // EnDis
//            if(PCRecBuff[DATAOFFSET+3]>23)return 1; // SHour
//            if(PCRecBuff[DATAOFFSET+4]>59)return 1; // SMin
//            if(PCRecBuff[DATAOFFSET+5]>23)return 1; // EHour
//            if(PCRecBuff[DATAOFFSET+5]>59)return 1; // EMin
//            
//            Setup.IOSch[PCRecBuff[DATAOFFSET+1]][0]=PCRecBuff[DATAOFFSET+2];
//            Setup.IOSch[PCRecBuff[DATAOFFSET+1]][1]=PCRecBuff[DATAOFFSET+3];
//            Setup.IOSch[PCRecBuff[DATAOFFSET+1]][2]=PCRecBuff[DATAOFFSET+4];
//            Setup.IOSch[PCRecBuff[DATAOFFSET+1]][3]=PCRecBuff[DATAOFFSET+5];
//            Setup.IOSch[PCRecBuff[DATAOFFSET+1]][4]=PCRecBuff[DATAOFFSET+6]; 
//            if(CheckInOutSch())
//                Setup.InOut=ENABLE;
            break;
				} 
        case PARAM_TIMEOUT://ok
				{
					//if(PC_DataLenght!=2)return 1;
					//if(PCRecBuff[DATAOFFSET+1]>99)return 1;
					Setup.SessionTimeout=PCRecBuff[1];
					break;
				}   
        case PARAM_IPD:
				{
//            if(PC_DataLenght!=2)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>99)return 1;
//            Setup.IPD=PCRecBuff[DATAOFFSET+1];
            break;
				}   
        case PARAM_TRTADDRESS:
				{
            //if(PC_DataLenght!=2)return 1;
            Setup.TRTAddress=PCRecBuff[1];
            break;   
				}   
        case PARAM_IP://ok
				{
            //if(PC_DataLenght!=5)return 1; 
            Setup.IP[0]=PCRecBuff[1];
            Setup.IP[1]=PCRecBuff[2];
            Setup.IP[2]=PCRecBuff[3];
            Setup.IP[3]=PCRecBuff[4];  
            break;
				}
        case PARAM_SUBNET://ok
				{
            //if(PC_DataLenght!=5)return 1;
            Setup.SUBNET[0]=PCRecBuff[1];
            Setup.SUBNET[1]=PCRecBuff[2];
            Setup.SUBNET[2]=PCRecBuff[3];
            Setup.SUBNET[3]=PCRecBuff[4];  
            break;
				}
        case PARAM_GETWAY://ok
				{
            //if(PC_DataLenght!=5)return 1;    
            Setup.GETWAY[0]=PCRecBuff[1];
            Setup.GETWAY[1]=PCRecBuff[2];
            Setup.GETWAY[2]=PCRecBuff[3];
            Setup.GETWAY[3]=PCRecBuff[4]; 
            break;
				}
        case PARAM_SERVER://ok
				{
            //if(PC_DataLenght!=5)return 1;  
            Setup.SERVER[0]=PCRecBuff[1];
            Setup.SERVER[1]=PCRecBuff[2];
            Setup.SERVER[2]=PCRecBuff[3];
            Setup.SERVER[3]=PCRecBuff[4];
            break;
        }
        case PARAM_BAUDRATE://ok
				{
            //if(PC_DataLenght!=2)return 1;
            //if(PCRecBuff[DATAOFFSET+1]>4)return 1; 
            Setup.Baud=PCRecBuff[1];  
            break;
					}   
        case PARAM_FINGER://ok
				{
//            if(PC_DataLenght!=2)return 1; 
           if(PCRecBuff[1]==ENABLE) 
                Setup.Finger=ENABLE;
            else if(PCRecBuff[1]==DISABLE)
                Setup.Finger=DISABLE;
            break;  
				}          
        case PARAM_MIFARE://ok
				{
            //if(PC_DataLenght!=2)return 1; 
            if(PCRecBuff[1]==ENABLE) 
                Setup.Mifare=ENABLE;
            else if(PCRecBuff[1]==DISABLE)
                Setup.Mifare=DISABLE;
            break;  
				}   
        case PARAM_MIFAREMODE:
				{
            //if(PC_DataLenght!=2)return 1;
            //if(PCRecBuff[DATAOFFSET+1]>2)return 1; 
            Setup.Mifare=PCRecBuff[1];
            break;
				}
        case PARAM_MIFARESECTOR://ok
				{
            //if(PC_DataLenght!=2)return 1;
            Setup.MifareSector=PCRecBuff[1];
            break;   
				}   
        case PARAM_MIFAREBLOCK://ok
				{
            //if(PC_DataLenght!=2)return 1;
            Setup.MifareBlock=PCRecBuff[1];
            break;
				}   
        case PARAM_PROXIMITY:
				{
//            if(PC_DataLenght!=2)return 1; 
//            if(PCRecBuff[DATAOFFSET+1]==ENABLE) 
//                Module.Contactless=ENABLE;
//            else if(PCRecBuff[DATAOFFSET+1]==DISABLE)
//                Module.Contactless=DISABLE;
            break; 
        }
        case PARAM_PROXMODE:
				{
//            if(PC_DataLenght!=2)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>3)return 1; 
            Setup.ContactlessMode=PCRecBuff[1];
            break;
				}   
        case PARAM_MAGNET:
				{
//            if(PC_DataLenght!=2)return 1; 
//            if(PCRecBuff[DATAOFFSET+1]==ENABLE) 
//                Module.Magnet=ENABLE;
//            else if(PCRecBuff[DATAOFFSET+1]==DISABLE)
//                Module.Magnet=DISABLE;
            break;
				}   
        case PARAM_MAGNETMODE:
				{
//            if(PC_DataLenght!=2)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>1)return 1; 
//            Setup.Magnet=PCRecBuff[DATAOFFSET+1];
            break;
        }    
        case PARAM_BARCODE:
				{
//            if(PC_DataLenght!=2)return 1; 
//            if(PCRecBuff[DATAOFFSET+1]==ENABLE) 
//                Module.Barcode=ENABLE;
//            else if(PCRecBuff[DATAOFFSET+1]==DISABLE)
//                Module.Barcode=DISABLE;
            break; 
					}   
        case PARAM_BARCODEMODE:
				{
//            if(PC_DataLenght!=2)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>1)return 1; 
//            Setup.Barcode=PCRecBuff[DATAOFFSET+1];
            break;
				}   
        case PARAM_CAMERA:
				{
//            if(PC_DataLenght!=2)return 1; 
//            if(PCRecBuff[DATAOFFSET+1]==ENABLE) 
//                Module.Camera=ENABLE;
//            else if(PCRecBuff[DATAOFFSET+1]==DISABLE)
//                Module.Camera=DISABLE;
            break;
					}   
        case PARAM_CAMERAMODE:
				{
//            if(PC_DataLenght!=2)return 1;
//            if(PCRecBuff[DATAOFFSET+1]>1)return 1; 
//            Setup.Camera=PCRecBuff[DATAOFFSET+1];
            break;  
				}   
        case PARAM_NET:
				{
//            if(PC_DataLenght!=2)return 1; 
//            if(PCRecBuff[DATAOFFSET+1]==ENABLE) 
//                Module.Net=ENABLE;
//            else if(PCRecBuff[DATAOFFSET+1]==DISABLE)
//                Module.Net=DISABLE;
            break;
				}   
        case PARAM_WIFI:
				{
//            if(PC_DataLenght!=2)return 1; 
//            if(PCRecBuff[DATAOFFSET+1]==ENABLE) 
//                Module.Wifi=ENABLE;
//            else if(PCRecBuff[DATAOFFSET+1]==DISABLE)
//                Module.Wifi=DISABLE;
            break;
				}   
        case PARAM_GPRS:
				{
//            if(PC_DataLenght!=2)return 1; 
//            if(PCRecBuff[DATAOFFSET+1]==ENABLE) 
//                Module.GPRS=ENABLE;
//            else if(PCRecBuff[DATAOFFSET+1]==DISABLE)
//                Module.GPRS=DISABLE;
            break;
        }
				case PARAM_RESET:
				{
					resetFactory();
					break;
				}
        default:
            return 1;   
            
    } 
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
uint8_t GetParameter(uint8_t ParameterIndex,uint8_t PCSendBuff[])
{
	uint32_t word;
	Record_t record;
	

    switch(ParameterIndex)
    {
        case PARAM_LANG: 
				{  
            PCSendBuff[0] = Setup.Language;
            return 1;
				}
        case PARAM_CALENDAR:  
				{					
            PCSendBuff[0] = Setup.Calendar;
            return 1;
				}               
        case PARAM_DAYLIGHT: 
				{					
            PCSendBuff[0] = Setup.Daylight;
            return 1;
				}       
        case PARAM_SPEAKER: 
				{					
            PCSendBuff[0] = Setup.Speaker;
            return 1;
				}
        case PARAM_BACKLIGHT:
				{					
            PCSendBuff[0] = Setup.Backlight;
            return 1;
				}           
        case PARAM_STANDBY: 
				{					
            PCSendBuff[0] = Setup.Standby;
            return 1;
				}           
        case PARAM_ALARM:
				{
//            PCSendBuff[0] = Setup.AlarmSet[ParameterIndex][0];
//            PCSendBuff[1] = Setup.AlarmSet[ParameterIndex][1];
//            PCSendBuff[2] = Setup.AlarmSet[ParameterIndex][2];
//            PCSendBuff[3] = Setup.AlarmSet[ParameterIndex][3];
					  return 4;
				} 
        case PARAM_SETUPPASS:  
				{
					word = Setup.Password;
					PCSendBuff[0]=word;
					PCSendBuff[1]=word>>8;
					PCSendBuff[2]=word>>16;
          return 3;
				} 
        case PARAM_SN:  
				{
					word = Setup.SerialNumber;
					PCSendBuff[0]=word;
					PCSendBuff[1]=word>>8;
					PCSendBuff[2]=word>>16;
					PCSendBuff[3]=word>>24;
					return 4;
				} 
        case PARAM_RDINDEX: 
				{					
            Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);	
            word=g_State.RD_flash_index;
            PCSendBuff[0]=word;
            PCSendBuff[1]=word>>8;
            PCSendBuff[2]=word>>16;
						//PCSendBuff[3]=word>>24;
						return 3;
				}
        case PARAM_WRINDEX:    
				{					
            Read_RTC_SRAM((uint8_t*)&g_State,sizeof(g_State),0);	
            word=g_State.WR_flash_index;
            PCSendBuff[0]=word;
            PCSendBuff[1]=word>>8;
            PCSendBuff[2]=word>>16;
						//PCSendBuff[3]=word>>24;
						return 3;
				}
        case PARAM_REPEATTIME:
				{
            PCSendBuff[0] = Setup.RepeatTime;
						return 1;
				} 
        case PARAM_VALIDITY:
				{
            PCSendBuff[0] = Setup.ValidityCheck;
						return 1;
				} 
            
        case PARAM_F1:
				{
            PCSendBuff[0] = Setup.F1Key;
						return 1;
				} 
        case PARAM_F2:
				{
            PCSendBuff[0] = Setup.F2Key;
						return 1;
				} 
         
        case PARAM_MISSIONKEY:
				{
            PCSendBuff[0] = Setup.MisionKey;
						return 1;
				} 
            
        case PARAM_VACATIONKEY:
				{
            PCSendBuff[0] = Setup.VacationKey;
						return 1;
				} 
         
        case PARAM_MISSIONCARD:
				{
            PCSendBuff[0] = Setup.MisionCard;
						return 1;
				} 
        case PARAM_VACATIONCARD:
				{
            PCSendBuff[0] = Setup.VacationCard;
						return 1;
				} 
        case PARAM_READERSCH:
				{
            PCSendBuff[0] = 0;//Setup.ReaderSch[ParameterIndex][0];
            PCSendBuff[1] = 1;//Setup.ReaderSch[ParameterIndex][1];
            PCSendBuff[2] = 2;//Setup.ReaderSch[ParameterIndex][2];
            PCSendBuff[3] = 3;//Setup.ReaderSch[ParameterIndex][3];
            PCSendBuff[4] = 4;//Setup.ReaderSch[ParameterIndex][4];
						return 5;
				} 
        case PARAM_INOUTSCH:
				{
            PCSendBuff[0] =4;// Setup.IOSch[ParameterIndex][0];
            PCSendBuff[1] =4;// Setup.IOSch[ParameterIndex][1];
            PCSendBuff[2] =4;// Setup.IOSch[ParameterIndex][2];
            PCSendBuff[3] =4;// Setup.IOSch[ParameterIndex][3];
            PCSendBuff[4] =4;// Setup.IOSch[ParameterIndex][4];
						return 5;
				} 
        case PARAM_TIMEOUT: 
				{
            PCSendBuff[0] = Setup.SessionTimeout;
						return 1;
				} 
        case PARAM_IPD:
				{					
            //PCSendBuff[0] = Setup.IPD;
						return 1;
				} 
        case PARAM_TRTADDRESS:
				{
            PCSendBuff[0] = Setup.TRTAddress;
						return 1;
				} 
        case PARAM_IP:
				{					
            PCSendBuff[0]=Setup.IP[0];
            PCSendBuff[1]=Setup.IP[1];
            PCSendBuff[2]=Setup.IP[2];
            PCSendBuff[3]=Setup.IP[3];
						return 4;
				} 
        case PARAM_SUBNET:
				{
            PCSendBuff[0]=Setup.SUBNET[0];
            PCSendBuff[1]=Setup.SUBNET[1];
            PCSendBuff[2]=Setup.SUBNET[2];
            PCSendBuff[3]=Setup.SUBNET[3];
						return 4;
				} 

        case PARAM_GETWAY:
				{
            PCSendBuff[0]=Setup.GETWAY[0];
            PCSendBuff[1]=Setup.GETWAY[1];
            PCSendBuff[2]=Setup.GETWAY[2];
            PCSendBuff[3]=Setup.GETWAY[3];
						return 4;
				} 

        case PARAM_SERVER:
				{

            PCSendBuff[0]=Setup.SERVER[0];
            PCSendBuff[1]=Setup.SERVER[1];
            PCSendBuff[2]=Setup.SERVER[2];
            PCSendBuff[3]=Setup.SERVER[3];
						return 4;
				} 
        
        case PARAM_BAUDRATE:
				{
            PCSendBuff[0] = Setup.Baud;
						return 1;
				} 
            
        case PARAM_FINGER:
				{
            //PCSendBuff[0] = Module.Finger;
						return 1;
				}  
                   
        case PARAM_MIFARE:
				{
            //PCSendBuff[0] = Module.Mifare;
						return 1;
				} 
        case PARAM_MIFAREMODE:
				{
            PCSendBuff[0] = Setup.Mifare;
						return 1;
				} 

        case PARAM_MIFARESECTOR:
				{
            PCSendBuff[0] = Setup.MifareSector;
						return 1;
				} 
        case PARAM_MIFAREBLOCK:
				{
           PCSendBuff[0] = Setup.MifareBlock;
						return 1;
				} 
            
        case PARAM_PROXIMITY:
				{
            //PCSendBuff[0] = Module.Contactless;
						return 1;
				} 
        
        case PARAM_PROXMODE:
				{
            PCSendBuff[0] = Setup.ContactlessMode;
						return 1;
				} 
            
        case PARAM_MAGNET:
				{
            //PCSendBuff[0] = Module.Magnet;
						return 1;
				} 
            
        case PARAM_MAGNETMODE:
				{
            //PCSendBuff[0] = Setup.Magnet;
						return 1;
				} 
            
        case PARAM_BARCODE:
				{
            //PCSendBuff[0] = Module.Barcode;
						return 1;
				} 
            
        case PARAM_BARCODEMODE:
				{
            //PCSendBuff[0] = Setup.Barcode;
						return 1;
				} 
            
        case PARAM_CAMERA:
				{
            //PCSendBuff[0] = Module.Camera;
						return 1;
				} 
            
        case PARAM_CAMERAMODE:
				{
            //PCSendBuff[0] = Setup.Camera;
						return 1;
				} 
            
        case PARAM_NET:
				{
            //PCSendBuff[0] = Module.Net;
						return 1;
				} 
        case PARAM_WIFI:
				{           
					//PCSendBuff[0] = Module.Wifi;
					return 1;
				} 
        case PARAM_GPRS:
				{
            //PCSendBuff[0] = Module.GPRS;
						return 1;
				} 
            
    }
		return 0;
}


/*
EOF
*/

