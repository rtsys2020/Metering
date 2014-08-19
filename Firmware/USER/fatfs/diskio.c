/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#if (USB_ENABLE == 1)
#include "usbdisk.h"	/* Example: USB drive control */
#endif
//#include "atadrive.h"	/* Example: ATA drive control */
#include "sdcard.h"		/* Example: MMC/SDC contorl */

/* Definitions of physical drive number for each media */
//remove by rezaee add to diskio.h
/*
#define ATA		0
#define MMC		1
#define USB		2
*/
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	DSTATUS stat;
	int result;
	//if (pdrv) return STA_NOINIT;			/* Supports only single drive */
//	if (Stat & STA_NODISK) return Stat;	/* No card in the socket */

	/* Reset */
	stat = STA_NOINIT;
	
	switch (pdrv) {
	case ATA :
		//result = ATA_disk_initialize();

		// translate the reslut code here

		return stat;

	case MMC :
		result = MMC_disk_initialize();
		// translate the reslut code here
		stat = result;
		return stat;

	case USB :
#if (USB_ENABLE == 1)
		stat = USB_disk_initialize();
#endif	
		// translate the reslut code here
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case ATA :
		//result = ATA_disk_status();

		// translate the reslut code here

		return stat;

	case MMC :
		stat = MMC_disk_status();
		// translate the reslut code here
		return stat;

	case USB :
#if (USB_ENABLE == 1)		
		stat = USB_disk_status();
#endif	
		// translate the reslut code here
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	DRESULT res;
	
	switch (pdrv) {
	case ATA :
		// translate the arguments here
		//result = ATA_disk_read(buff, sector, count);
		// translate the reslut code here
		return res;

	case MMC :
		// translate the arguments here
		res = MMC_disk_read(buff, sector, count);
		// translate the reslut code here
		return res;

	case USB :
		// translate the arguments here
#if (USB_ENABLE == 1)	
		res = USB_disk_read(buff, sector, count);
#endif	
		// translate the reslut code here
		return res;
	}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case ATA :
		// translate the arguments here

		//result = ATA_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here
		res = (DRESULT)result;
		return res;

	case USB :
		// translate the arguments here
#if (USB_ENABLE == 1)	
		res = USB_disk_write(buff, sector, count);
#endif	
		// translate the reslut code here
		return res;
	}
	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case ATA :
		// pre-process here
		//result = ATA_disk_ioctl(cmd, buff);
		// post-process here

		return res;

	case MMC :
		// pre-process here

		result = MMC_disk_ioctl(cmd,buff);

		// post-process here
		res = (DRESULT)result;
		return res;

	case USB :
		// pre-process here
#if (USB_ENABLE == 1)	
		res = USB_disk_ioctl(cmd, buff);
#endif	
		// post-process here
		return res;
	}
	return RES_PARERR;
}
#endif




