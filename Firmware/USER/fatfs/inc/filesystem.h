/*---------------------------------------------------------------------------/
/  FatFs - FAT file system module include file  R0.10     (C)ChaN, 2013
/----------------------------------------------------------------------------/
/ FatFs module is a generic FAT file system module for small embedded systems.
/ This is a free software that opened for education, research and commercial
/ developments under license policy of following terms.
/
/  Copyright (C) 2013, ChaN, all right reserved.
/
/ * The FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/----------------------------------------------------------------------------*/

#ifndef _FILESYSTEM
#define _FILESYSTEM	

#ifdef __cplusplus
extern "C" {
#endif

#include "integer.h"	/* Basic integer types */
#include "ffconf.h"		/* FatFs configuration options */
#include "ff.h"
#include "record.h"
#include "includes.h"
//add by rezaee
/* global variable for FatFs use */
extern FILINFO fileinfo;
#if _USE_LFN
extern char Lfname[_MAX_LFN+1];
#endif
extern FATFS MMCfatfs;		/* File system object for each logical drive */
	
uint8_t MMC_Init (void) ;
uint8_t MMC_mkdir(uint8_t dir[]);
uint8_t MMC_chdir(uint8_t dir[]);
FIL MMC_open(uint8_t dir[],BYTE mode	/* Access mode and file open mode flags */);	
uint8_t MMC_close(FIL file);	
	
	
extern FATFS USBfatfs;		/* File system object for each logical drive */
	
uint8_t USB_Init (void) ;
uint8_t USB_mkdir(uint8_t dir[]);
uint8_t USB_chdir(uint8_t dir[]);
uint8_t MMC_test(void);
uint8_t MMC_PutRec(Record_t record);
uint8_t MMC_PutRecImage(Record_t record,uint8_t *imgRAW);		
FRESULT scan_files (char* path );

#ifdef __cplusplus
}
#endif

#endif /* _FILESYSTEM */
