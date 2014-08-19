/*


*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "filesystem.h"

extern uint16_t getSerialNumber(uint8_t* serial);
extern uint16_t getCurrTime(uint8_t* serial);

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
//add by rezaee
//#ifdef _DEBUG_
//const char *fatErr[] ={
//		{"OK\0" "DISK_ERR\0"}, {"INT_ERR\0" }, {"NOT_READY\0" }, {"NO_FILE\0"}, { "NO_PATH\0"
//		}, {"INVALID_NAME\0" }, {"DENIED\0" }, {"EXIST\0"}, { "INVALID_OBJECT\0"}, { "WRITE_PROTECTED\0"
//		}, {"INVALID_DRIVE\0"}, { "NOT_ENABLED\0"}, { "NO_FILE_SYSTEM\0" }, {"MKFS_ABORTED\0" }, {"TIMEOUT\0"
//		}, {"LOCKED\0" }, {"NOT_ENOUGH_CORE\0"}, { "TOO_MANY_OPEN_FILES\0"}
//	};
//#endif

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
//add by rezaee
/* global variable for FatFs use */
FILINFO USBfileinfo;
//#if _USE_LFN
//char Lfname[_MAX_LFN+1];
//#endif
extern FATFS fs[];		/* File system object for MMC logical drive */
//FATFS USBfatfs;		/* File system object for USB logical drive */







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
 uint8_t USB_Init (void) 
{   

	FRESULT result = 1;
	result = f_mount(&fs[1],"2:",1);
	//mount file system
	if(result != FR_OK)
	{
		FaultCode(MMC_MOUNT_FAULT);////////////////
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
 * @param[in]		name and directory of file folder\file.txt.
 * @param[in]		 
 *							
 * @return 				             
 *                         
 **********************************************************************/
uint8_t USB_LoadImage(char* imageName)
{
	FIL filcrc;       /* File object */
	FRESULT result = 1;
	uint8_t ptr[30],directory[10],*arr,timstr[10];
	uint32_t i=0,fsize,fr;
	uint8_t *buffPNG;
	uint32_t br;
	//FILINFO	fno;
	sprintf((char*)ptr,"2:%s",imageName);
	result = f_open(&filcrc,(const TCHAR*)ptr,FA_READ);
	if(result != FR_OK )
	{	
		return ERROR ;
	}
	fsize = f_size(&filcrc);
	//f_lseek(&filcrc,fsize);
	buffPNG = calloc(fsize,sizeof(uint8_t));
	i=0;
	while(i<fsize)
	{
		fr = f_read(&filcrc,&buffPNG[i],512,&br);
		i+=br;
	}

	f_close(&filcrc);
	free(buffPNG);
	return SUCCESS;	
}

/*
EOF
*/

