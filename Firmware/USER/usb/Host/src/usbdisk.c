/**********************************************************************
* $Id$		usbhost_main.c			2011-09-05
*//**
* @file		usbhost_main.c
* @brief	Demo for USB Host Controller.
* @version	1.0
* @date		05. September. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
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
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/*
**************************************************************************************************************
*                                       INCLUDE HEADER FILES
**************************************************************************************************************
*/
#include "includes.h"
#include "usbdisk.h"

static DSTATUS usb_state = RES_NOTRDY;

USBDISKCONF MassStorageConf;
 
/*********************************************************************//**
 * @brief 			This function is the main function where the execution begins
 * @param[in]		None
 * @return 		    None
 **********************************************************************/


DSTATUS USB_disk_initialize(void)
{
	int32_t  rc;
	uint32_t  numBlks, blkSize;	
	uint8_t  inquiryResult[INQUIRY_LENGTH];
	uint32_t numoftry = 10000;
	Host_Init();  /** Initialize the lpc17xx host controller */
	
	while(numoftry--){
		rc = Host_EnumDev();       /* Enumerate the device connected                                            */
		if ((rc == USB_HOST_FUNC_OK) && 
				(Host_GetDeviceType() == MASS_STORAGE_DEVICE)) {
#ifdef __DEBUG__					
						_DBG_("Mass Storage device connected\n");
#endif					
				break;
		}
	}
	if(numoftry == 0)
	{
		usb_state = RES_NOTRDY;
		return RES_NOTRDY;
	}
	
	/* Initialize the mass storage and scsi interfaces */
	rc = MS_Init( &blkSize, &numBlks, inquiryResult );
	if (rc == MS_FUNC_OK) 
	{
		//usbmass_read_conf();
		usb_state = RES_OK;
#ifdef __DEBUG__	
		_DBG_("MassStorage initialize\n\r");
#endif
		return RES_OK;
	}
	else
	{
#ifdef __DEBUG__		
		_DBG_("Error in MassStorage initialize\n\r");
#endif		
		usb_state = RES_ERROR;
		return RES_ERROR;
	}
	
//	rc = MS_BulkRecv(0,1,FATBuffer);
//		if (rc == MS_FUNC_OK) 
//	{
//		usb_state = RES_OK;
//		//_DBG_("read sector 0\n\r");
//		return RES_OK;
//	}
//	else
//	{
//		//_DBG_("Error in read sector 0\n\r");
//		usb_state = RES_ERROR;
//		return RES_ERROR;
//	}
	
}

/*********************************************************************//**
 * @brief 			This function is the main function where the execution begins
 * @param[in]		None
 * @return 		    None
 **********************************************************************/
DSTATUS USB_disk_status(void)
{
	return usb_state;
}


/*********************************************************************//**
 * @brief 			This function is the main function where the execution begins
 * @param[in]		None
 * @return 		    None
 **********************************************************************/
DRESULT USB_disk_read (
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	uint32_t i = 0;
	if(MS_BulkRecv(sector, count, FATBuffer) == MS_FUNC_OK)
	{
		for(i=0;i<512;i++)
		{
			buff[i] = FATBuffer[i];
		}
		return RES_OK;
	}
	else
	{
		return RES_NOTRDY;
	}
}

/*********************************************************************//**
 * @brief 			This function is the main function where the execution begins
 * @param[in]		None
 * @return 		    None
 **********************************************************************/

#if _READONLY == 0
DRESULT USB_disk_write (
	const BYTE *buff,	/* Pointer to the data to be written */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	uint32_t i = 0;
	for(i=0;i<512;i++)
	{
		FATBuffer[i] = buff[i];
	}
	if(MS_BulkSend(sector,count,(volatile uint8_t*)FATBuffer) == MS_FUNC_OK)
	{
		return RES_OK;
	}
	else
	{
		return RES_NOTRDY;
	}

}
#endif

/*********************************************************************//**
 * @brief 			This function is the main function where the execution begins
 * @param[in]		None
 * @return 		    None
 **********************************************************************/
DRESULT USB_disk_ioctl (
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{

	DRESULT res;
	//BYTE  *ptr = buff;
	//if (Stat & STA_NOINIT) return RES_NOTRDY;

	res = RES_ERROR;

	switch (ctrl) {
		case CTRL_SYNC :
		{		/* Make sure that no pending write process */
			if(MS_TestUnitReady() == MS_FUNC_OK)
			{
				res = RES_OK;
			}		
			break;
		}
		case GET_SECTOR_COUNT :
		{		/* Get number of sectors on the disk (DWORD) */
			*(DWORD*)buff =  MassStorageConf.SectorCount;
			res = RES_OK;
			break;
		}
		case GET_SECTOR_SIZE :
		{		/* Get R/W sector size (WORD) */
			*(DWORD*)buff =  MassStorageConf.BlockSize;
			res = RES_OK;
			break;
		}
		case GET_BLOCK_SIZE :	
		{/* Get erase block size in unit of sector (DWORD) */
			*(DWORD*)buff =  MassStorageConf.BlockSize;
			res = RES_OK;
			break;
		}
		default:
		{
			res = RES_PARERR;
		}
	}

	return res;
}



/**
  * @brief  Read card configuration and fill structure CardConfig.
  *
  * @param  None
  * @retval TRUE or FALSE. 
  */
Bool usbmass_read_conf (void)
{
	uint32_t c_size, read_bl_len;
	MassStorageConf.SectorSize = 512;
	if(MS_ReadCapacity(&read_bl_len,&c_size)== MS_FUNC_OK)
	{
		MassStorageConf.SectorCount  = read_bl_len;///????????????????c_size
		MassStorageConf.BlockSize =  c_size;///?????????????
	}
	return FALSE;
}
