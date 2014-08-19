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
#ifdef _DEBUG_
const char *fatErr[] ={
		{"OK\0" "DISK_ERR\0"}, {"INT_ERR\0" }, {"NOT_READY\0" }, {"NO_FILE\0"}, { "NO_PATH\0"
		}, {"INVALID_NAME\0" }, {"DENIED\0" }, {"EXIST\0"}, { "INVALID_OBJECT\0"}, { "WRITE_PROTECTED\0"
		}, {"INVALID_DRIVE\0"}, { "NOT_ENABLED\0"}, { "NO_FILE_SYSTEM\0" }, {"MKFS_ABORTED\0" }, {"TIMEOUT\0"
		}, {"LOCKED\0" }, {"NOT_ENOUGH_CORE\0"}, { "TOO_MANY_OPEN_FILES\0"}
	};
#endif

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
FILINFO fileinfo;
#if _USE_LFN
char Lfname[_MAX_LFN+1];
#endif

FATFS MMCfatfs;		/* File system object for MMC logical drive */







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
 uint8_t MMC_Init (void) 
{   

	FRESULT result = 1;
	result = f_mount(&MMCfatfs,"1:",1);
	//mount file system
	if(result != FR_OK)
	{
		FaultCode(MMC_MOUNT_FAULT);
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
uint8_t MMC_mkdir(uint8_t dir[])
{
	FRESULT result = 1;
	uint8_t ptr[20] = "1:";
	int32_t i=0;
	
	i=0;
	while(dir[i]!= 0 && i<10)
	{
		ptr[i+2] = dir[i];
		i++;
	}
	ptr[i+2] = 0;	
	result = f_mkdir((TCHAR*)ptr);
	if(result == FR_EXIST || result == FR_OK)
	{
		return SUCCESS;
	}
	return ERROR;
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
uint8_t MMC_chdir(uint8_t dir[])
{
	FRESULT result = 1;
	uint8_t ptr[20] = "1:";
	int32_t i=0;
	
	i=0;
	while(dir[i]!= 0 && i<10)
	{
		ptr[i+2] = dir[i];
		i++;
	}	
	ptr[i+2] = 0;
	//center folder exist or create
	result = f_chdir((TCHAR*)ptr);
	if(result != FR_OK)
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
 * @param[in]		name and directory of file folder\file.txt.
 * @param[in]		mode for open file. 
 *							FA_WRITE ,FA_CREATE_NEW
 * @return 				             
 *                         
 **********************************************************************/
FIL MMC_open(uint8_t dir[],BYTE mode	/* Access mode and file open mode flags */)
{
	FIL filcrc;       /* File object */
	FRESULT result = 1;
	uint8_t ptr[20] = "1:";
	int32_t i=0;
	
	i=0;
	while(dir[i]!= 0 && i<10)
	{
		ptr[i+2] = dir[i];
		i++;
	}		
	ptr[i+2] = 0;

	//all folder exsist or cearte
	//now write data to file
	result = f_open(&filcrc,(const TCHAR*)ptr,mode);
	if(result == FR_EXIST )
	{	
		return filcrc;
	}
	return filcrc;	
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
uint8_t MMC_close(FIL file)
{
	FRESULT result = 1;
	result = f_close(&file);
	return result;
}
	
/*
EOF
*/

