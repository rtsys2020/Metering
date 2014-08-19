/*-----------------------------------------------------------------------
/  Low level disk interface modlue include file   (C)ChaN, 2013
/-----------------------------------------------------------------------*/

#ifndef _USBDISK_H
#define _USBDISK_H

#include "usbhost_inc.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#include "diskio.h"
#include "ff.h"
#include  "usbhost_ms.h"

 typedef struct tagUSBDISK
{
  uint32_t 		SectorSize;    /* size (in byte) of each sector, fixed to 512bytes */
  uint32_t 		SectorCount;     /* total sector number */  
  uint32_t 		BlockSize;     /* erase block size in unit of sector */
	uint32_t 		CardAddress;	/* Card Address */
	uint32_t 		OCR;			/* OCR */
	//en_Mci_CardType CardType;		/* Card Type */
	//st_Mci_CardId 	CardID;			/* CID */
	//uint8_t  		CSD[16];		/* CSD */
} USBDISKCONF;

extern USBDISKCONF MassStorageConf;
	
DSTATUS USB_disk_initialize (void);

DRESULT USB_disk_ioctl (
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
);


DRESULT USB_disk_read (
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
);
	
DSTATUS USB_disk_status (void);

//#if _READONLY == 0
DRESULT USB_disk_write (
	const BYTE *buff,	/* Pointer to the data to be written */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
);
//#endif

//typedef union
//{
//	struct
//	{
//		uint8_t byte[36];
//	};
//	struct
//	{
//		uint8_t PDT_QU;
//		uint8_t RBM;
//		uint8_t version;
//		uint8_t NORM_HI;
//		uint8_t ADDI_LEN;
//		uint8_t PRO_OB_PC_TP_AC_SC;
//		uint8_t ADDR_OB_MC_MU_VS_EN_BQ;
//		uint8_t VS_CMD_OB_LI_SYNC_WB_OB;
//		uint64_t T10_Ven;
//		uint64_t product_ident;
//		uint64_t product_rev;
//	};	
//	struct
//	{
//		uint8_t Peripheral;
//		uint8_t Removable;
//		uint8_t Version;
//		uint8_t Response_Data_Foarmat;
//		uint8_t AdditionalLength;
//		uint8_t Sccstp;
//		uint8_t bqueetc;
//		uint8_t CmdQue;
//		uint8_t vendorID[8];
//		uint8_t productID[16];
//		uint8_t productRev[4];
//	};		
//}InqueryResponse_t;


#define PDT_DIRECT_ACC	0x00
#define CD_DVD					0x05
#define OPTIC_MEM				0x07
#define REDUC_BLOCK			0x0E

Bool usbmass_read_conf (void);

#ifdef __cplusplus
}
#endif

#endif//_MASSSTORAGE_H
