/**********************************************************************
* $Id$		FlashRTC.c			2013-12
*//**
* @file		FlashRTC.c
* @brief	Use for handling the interrupt of contactless reader and reading card ID
*			
* @version	1.0
* @date		21. decm. 2013
* @author	Amin Ezhdehakosh
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
/** @addtogroup FlashRTC
 * @{
 */
#include "includes.h"
#include "FlashRTC.h"
#include "ssp_driver.h"
#include "lpc177x_8x_rtc.h"

//NUM_OF_ALL_RECORD=FLASH_SIZE/RECORD_SIZE-->262144
const int FLASH_SIZE = 4194304;//byte
const int RECORD_SIZE =	1024;//byte
const int NUM_OF_ALL_RECORD	= (FLASH_SIZE/RECORD_SIZE);
//NUM_OF_RECORD_SEC=SECTOR_SIZE/RECORD_SIZE -->256
const int  SECTOR_SIZE	= 4096;//byte
#define NUM_OF_RECORD_SEC	(SECTOR_SIZE/RECORD_SIZE)

uint32_t FLASH_SIZE_g;

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */

//	int8_t ali;

/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 

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
void FlashRTC_Init(void)
{
	SPI_FLASH_RTC_Init();
	FLASH_SIZE_g = SFlash_Size();
	
	if(FLASH_SIZE_g == 0)
//		 FaultCode(RTC_FLASH_INIT_FAULT);
	FLASH_SIZE_g = 0x40000;
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
uint32_t SFlash_Size(void)
{
	uint32_t chipID;
	RTC_TIME_Type pTime;
	//while(1)
	//{
		chipID = SFlash_Read_ID(Device_ID);
	//}
	if (chipID == 0xBF4A)//////////////
		return SFLASH_SIZE_4MB;
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
uint32_t SFlash_Read_ID(IDtype_t IDType)
{
	uint32_t temp = 0;
              
	if (IDType == JEDEC_ID)
	{
		SPI_FLASH_CS_LOW();	
				
		Flash_ReadWriteByte(0x9F);		 		         /* Send read JEDEC ID command (9Fh) */
    	        
    temp = (temp | Flash_ReadWriteByte(0x00)) << 8;  /* Receive Data */
		temp = (temp | Flash_ReadWriteByte(0x00)) << 8;	
    temp = (temp | Flash_ReadWriteByte(0x00)); 	     /* temp value is 0xBF2541 */

    SPI_FLASH_CS_HIGH();
		return temp;
	}
	
	if ((IDType == Manufacturer_ID) || (IDType == Device_ID) )
	{
		
	  SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x90);				/* Send read ID command (90h or ABh) */
    Flash_ReadWriteByte(0x00);				/* Send address	*/
		Flash_ReadWriteByte(0x00);				/* Send address	*/
		Flash_ReadWriteByte(0x00);		    /* Send address - 00H or 01H */
		temp = Flash_ReadWriteByte(0x00)<<8;	    /* Receive Data */
		temp |= Flash_ReadWriteByte(0x00);	
		//delay_ms(1);	//if datarate less than 3000000hz add delay for cheap select	
    SPI_FLASH_CS_HIGH();
		return temp;
	}
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
void SFlash_Write_Enable(void)
{
	SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(WREN_OPCODE);
	SPI_FLASH_CS_HIGH();
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
void SFlash_Write_Disable(void)
{
	SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(WRDI_OPCODE);
	SPI_FLASH_CS_HIGH();
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
void SFlash_Enable_Write_Status_Register(void)
{
	//SFlash_Write_Enable();
	SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(EWSR_OPCODE);
	SPI_FLASH_CS_HIGH();
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
uint8_t SFlash_Read_Status_Register(void)
{
	uint8_t temp;
	
	SPI_FLASH_CS_LOW();				 
	Flash_ReadWriteByte(RDSR_OPCODE);						/* Send Read Status Register command */
	temp = Flash_ReadWriteByte(0xFF);				    	/* Save the read status register value */
	SPI_FLASH_CS_HIGH();	
	
	return temp;
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
void SFlash_Write_Status_Rregister(uint8_t statusByte)
{
	SFlash_Enable_Write_Status_Register();
	SFlash_Write_Enable();
	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(WRSR_OPCODE);							    /* Send write status register command */
	Flash_ReadWriteByte(statusByte);								    /* chip can be written */
	SPI_FLASH_CS_HIGH();
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
void SFlash_Write_Byte(uint8_t writeByte, uint32_t address)
{
	SFlash_Write_Status_Rregister(0x00);
	SFlash_Write_Enable();
	
	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(PROGRAM_BYTE_OPCODE); 			/* Send byte data programming command */
	Flash_ReadWriteByte(address >> 16);  				/* Send 3 byte address command */
	Flash_ReadWriteByte(address >> 8);
	Flash_ReadWriteByte(address);
	Flash_ReadWriteByte(writeByte);						/* Write data */
	SPI_FLASH_CS_HIGH();
	
	WaitBusy();
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
void SFlash_Write_AAI_All(uint8_t data[], uint8_t len, uint32_t address)
{
	uint32_t i;
	SFlash_Write_Status_Rregister(0x00);
	SFlash_Write_Enable();
	
	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(PROGRAM_AAI_OPCODE);
	Flash_ReadWriteByte(address >> 16);
	Flash_ReadWriteByte(address >> 8);
	Flash_ReadWriteByte(address);
	Flash_ReadWriteByte(data[0]);
	Flash_ReadWriteByte(data[1]);
	SPI_FLASH_CS_HIGH();
	//delay_ms(1);
	WaitBusy();
	//while (SFlash_Read_Status_Register() & 0x01);
	//while (Flash_ReadWriteByte(RDSR_OPCODE) & 0x01);/* Send Read Status Register command */
	//len = len-2;
	for (i = 2; i<len; i+=2)
	{
		SPI_FLASH_CS_LOW();
		Flash_ReadWriteByte(PROGRAM_AAI_OPCODE);
		Flash_ReadWriteByte(data[i]);
		Flash_ReadWriteByte(data[i+1]);	
		SPI_FLASH_CS_HIGH();
		//delay_ms(1);
		//while (SFlash_Read_Status_Register() & 0x01);
		//while (Flash_ReadWriteByte(RDSR_OPCODE) & 0x01);/* Send Read Status Register command */
		WaitBusy();
	}	
	
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
static void SFlash_Read_Data(uint8_t *readBuffer, uint32_t len, uint32_t address)
{
	uint32_t i = 0;
	
	SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(READ_OPCODE); 						// Send read command
//	Flash_ReadWriteByte(0x0B); 								// Send read command (high speed read)
	Flash_ReadWriteByte(address >> 16);						// Send 3 byte address command
	Flash_ReadWriteByte(address >> 8);
	Flash_ReadWriteByte(address);
//	Flash_ReadWriteByte(0xFF);						// for high speed read this line (dummy cycle) should be used
	for ( i = 0; i < len; i++ )		
	{
      readBuffer[i] = Flash_ReadWriteByte(0xFF);		/* Read data */
	}
  SPI_FLASH_CS_HIGH();
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

int SFlash_Write_Data_Record(Record_t *writeBuffer, uint32_t address)
{
	uint32_t tempAddr, i;
	uint8_t readBuff[RECORD_SIZE],*tmp;
	uint32_t firstSector, lastSector;
	i=0;
	if ((address) > NUM_OF_ALL_RECORD)
	{
		return FALSE;
	}

	if(address%NUM_OF_RECORD_SEC == 0)
	{
		SFlash_Sector_Erase_4KB(address/NUM_OF_RECORD_SEC);
	}
	SFlash_Read_Record((Record_t*)readBuff,address);
	for(i=0;i<RECORD_SIZE;i++)
	{
		if(readBuff[i] != 0xFF)
			return FALSE;
	}
	SFlash_Write_AAI_All((uint8_t*)writeBuffer,RECORD_SIZE,address*RECORD_SIZE);

	SFlash_Write_Disable();
	SFlash_Read_Record((Record_t*)readBuff,address);
	tmp = (uint8_t*)writeBuffer;
	for(i=0;i<RECORD_SIZE;i++)
	{
		if(readBuff[i]!=tmp[i])
			return FALSE;
	}
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
uint8_t SFlash_Read_Record(Record_t *readBuffer, uint32_t address)
{
	uint32_t i = 0;
	uint8_t *buff;
	if ((address) > NUM_OF_ALL_RECORD)
		return FALSE;


	address = address*RECORD_SIZE;
	SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(READ_OPCODE); 						// Send read command
//	Flash_ReadWriteByte(0x0B); 								// Send read command (high speed read)
	Flash_ReadWriteByte(address >> 16);						// Send 3 byte address command
	Flash_ReadWriteByte(address >> 8);
	Flash_ReadWriteByte(address);
//	Flash_ReadWriteByte(0xFF);						// for high speed read this line (dummy cycle) should be used
	buff = (uint8_t*)readBuffer;
	for ( i = 0; i < RECORD_SIZE; i++ )		
	{
      buff[i] = Flash_ReadWriteByte(0xFF);		/* Read data */
	}
  SPI_FLASH_CS_HIGH();
	//SFlash_Read_Data((uint8_t*)readBuffer, RECORD_SIZE, address*RECORD_SIZE);
	
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
void WaitBusy(void)
{
	SPI_FLASH_CS_LOW();	
	while (Flash_ReadWriteByte(RDSR_OPCODE) & 0x01);/* Send Read Status Register command */
	SPI_FLASH_CS_HIGH();	
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
void SFlash_Chip_Erase(void)
{
	SFlash_Write_Status_Rregister(0x00);
	SFlash_Write_Enable();
	
	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(ERASE_CHIP_OPCODE);
	SPI_FLASH_CS_HIGH();
	delay_ms(1000);
	WaitBusy();
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
void SFlash_Sector_Erase_4KB(uint32_t sectorAddress)
{
	SFlash_Write_Status_Rregister(0x00);
	SFlash_Write_Enable();

	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(ERASE_SECTOR_OPCODE);
	Flash_ReadWriteByte(sectorAddress >> 4);		// sectorAddress << 12 then sectorAddress >> 16
	Flash_ReadWriteByte(sectorAddress << 4);		// sectorAddress << 12 then sectorAddress >> 8
	Flash_ReadWriteByte(0);
	SPI_FLASH_CS_HIGH();
	delay_ms(100);
	WaitBusy();
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
uint32_t Flash_test(void)
{
	uint32_t i;
	uint8_t str2[20],str[20]={0x88,0xaa,0x55,0x88,0x77,0x66,0x88,0xaa,0x55,0x88,0x77,0x66};
	SFlash_Read_Status_Register();	
	//SFlash_Chip_Erase();
	delay_ms(100);
	//SFlash_Write_Data_Record((Record_t*)str,0);
	//while(1){
	for(i=0;i<NUM_OF_ALL_RECORD;i++)
	{
		SFlash_Read_Record((Record_t*)str2,i);
		if(!SFlash_Write_Data_Record((Record_t*)str,i))
		{
			break;
		}
		SFlash_Read_Record((Record_t*)str2,i);
	
		//delay_ms(100);
//			SFlash_Read_Record(str2,i);
	}
	return i;
}