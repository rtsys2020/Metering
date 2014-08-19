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
#include "touchkey.h"
#include "includes.h"

/*************************************************************************************************  
    sensor api  
*************************************************************************************************/   
/*   

Key Settings 

NTHR – Negative Thresholdis used to adjust the sensitivity of a key. Higher values make keys 
less sensitive, lower values make keys more sensitive. 
NDRIFT – Negative Driftis the rate at which drift compensation is carried out for a negative going 
signal (when a key is touched or receives increased loading). The value is seconds/reference level. 
PDRIFT – Positive Driftis the rate at which drift compensation is carried out for a positive going 
signal (when a key is touched or receives increased loading). The value is seconds/reference level. 
NDIL – Negative Detection Integrator Limitallows enabling and disabling of keys and provides 
signal filtering. Higher values provide more filtering but increase the response time of the key. 
FDIL – Fast Detection Integrator Limitprovides filtering but has less effect on response time. 
Total filtering is a combination of NDIL multiplied by FDIL. 
NRD – Negative Recalibration Delaydetermines the maximum time a key can be active before 
being automatically recalibrated by the IC. The value is in seconds. 
BL – Burst Length modifies key sensitivity. Higher values make the key more sensitive, lower 
values make it less sensitive. The correct sensitivity for a key should be achieved with BL and 
NTHR. Generally, BL should be as low as possible and NTHR should range from 7 to 12. 
AKS – Adjacent Key Suppressioncan be enabled or disabled. To become active, a key with this 
option enabled must receive the strongest signal relative to other AKS-enabled keys. 
Scope Sync – sends a positive pulse that brackets the burst of a selected key. This feature is 
invaluable for diagnostics. 
WH – Wake allows the device to be configured to wakeup when specific keys are touched. Each 
key has its own configuration bit so that any combination of keys can be configured for this 
purpose
   
*/
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
int TouchKey_initialize(void)
{
	uint8_t data;
	uint32_t valKey,i,j;			//key1	2			3			4			5			6			7			8			9			10		11		12		13		14		15		16		17		18		19		20		21		22		23		24		
//	uint8_t registers[24]={131	,132,  133,	 134,	 135,  136,	 137,  138,	 139,  140,	 141,  142,	 143,  144,	 145,  146,	 147,  148,	 149,  150,	 151,  152,	 153,  154};
	uint8_t values[24]=		{0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
	key_val_t keyVal;
	
	PINSEL_ConfigPin(BRD_TOUCHKEY_CHN_PORT,BRD_TOUCHKEY_CHN_PIN,0);
	GPIO_SetDir(BRD_TOUCHKEY_CHN_PORT,BRD_TOUCHKEY_CHN_PIN,0);	
	GPIO_IntCmd(BRD_TOUCHKEY_CHN_PORT, 1<<BRD_TOUCHKEY_CHN_PIN, 0);
	PINSEL_SetPinMode(BRD_TOUCHKEY_CHN_PORT,BRD_TOUCHKEY_CHN_PIN,IOCON_MODE_PULLDOWN);	

	//read a register for unlock
	TOUCHKEY_READ_REG(0,&data);

	for(i=179;i<203;i++)//FDIL7..4 NDIL3..0
	{
		TouchKey_UnlockKey();
		TOUCHKEY_WRITE_REG(i,0x52);
	}

	for(i=131,j=0;i<155;i++)//NDRIFT7..4 NTHR3..0 
	{
		TouchKey_UnlockKey();
		TOUCHKEY_WRITE_REG(i,values[j++]);//0x52
	}	
	for(i=155;i<179;i++)//PDRIFT7..4 - 0
	{
		TouchKey_UnlockKey();
		TOUCHKEY_WRITE_REG(i,0x40);
	}
	for(i=203;i<227;i++)//NRD7..0
	{
		TouchKey_UnlockKey();
		TOUCHKEY_WRITE_REG(i,0x0A);
	}	
	for(i=227;i<250;i++)//SSYNC.7 AKS.6 BL5.4 WAKE.3   
	{
		TouchKey_UnlockKey();
		TOUCHKEY_WRITE_REG(i,0x1C);//
	}
	//reg 251 => SLEEP2..1 MSYNC.6  
	//reg 252 ==> AWAKE
	//reg 253 ==> DHT
	TouchKey_Rcalibrate();

	return 0;
}

/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_ReadKey(uint32_t *val)
{
	uint8_t buff;
	//read register 1,2,3 for all key 1 bit for every key
	TOUCHKEY_READ_REG(1,&buff);
	*val = buff;
	TOUCHKEY_READ_REG(2,&buff);
	*val |= buff<<8;
	TOUCHKEY_READ_REG(3,&buff);
	*val |= buff<<16;
	//i2c_readMultiple(TOUCH_KES_SLAVE_ADDR,1,(uint8_t*)val,3);
}
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_ReadKeyDataAll(uint8_t *val)
{
	i2c_readMultiple(TOUCH_KES_SLAVE_ADDR,4,(uint8_t*)val,119);
}
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_ReadKeyData(uint8_t key,key_val_t *val)
{
	//read register 4 to 123 for key value
	i2c_readMultiple(TOUCH_KES_SLAVE_ADDR,(key*5)+4,(uint8_t*)val,5);
	
}

/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_Rcalibrate(void)
{
	//write reg 125 to 0x55 for recalibrate
	TOUCHKEY_WRITE_REG(125,0x55);
}
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_UnlockKey(void)
{
	//write reg 130 to 0x55 for unlock key for write
	//befor writing setup
	TOUCHKEY_WRITE_REG(130,0x55);

}
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_WriteReg(uint8_t reg,uint8_t val)
{
//
	i2c_write(TOUCH_KES_SLAVE_ADDR,reg,val);
}
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_ReadReg(uint8_t reg,uint8_t* val)
{
//
	i2c_read(TOUCH_KES_SLAVE_ADDR,reg,val);
	
}
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/  
void TouchKey_ReadRegMulti(uint8_t reg,uint8_t* val,uint8_t len)
{
//
	i2c_readMultiple(TOUCH_KES_SLAVE_ADDR,reg,(uint8_t*)val,len);
	
}


/*************************************************************************************************  
    sensor driver  
*************************************************************************************************/   
   
