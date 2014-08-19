/*


*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "filesystem.h"
#include "flashrtc.h"
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
FILINFO MMCfileinfo;
#if _USE_LFN
char Lfname[_MAX_LFN+1];
#endif

FATFS fs[2];		/* File system object for MMC logical drive */







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
	result = f_mount(&fs[0],"1:",1);
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
uint8_t MMC_test(void)
{
	FIL filcrc;       /* File object */
	FRESULT result = 1;
	uint8_t ptr[30],directory[30];
	int32_t i=0;
	FILINFO	fno;
	
	sprintf((char*)directory,"1:%d",93011602);
	result = f_mkdir((TCHAR*)directory);
	result = f_chdir((TCHAR*)directory);
	sprintf((char*)ptr,"1:dir\\4669546767_%d.txt",93011602);
	
	//sprintf((char*)ptr,"1:%s.txt",directory);
	//all folder exsist or cearte
	//now write data to file
	result = f_open(&filcrc,(const TCHAR*)ptr,FA_CREATE_ALWAYS | FA_WRITE);
	result = f_stat ((const TCHAR*)ptr, &fno);
	f_lseek(&filcrc,fno.fsize);
	f_write(&filcrc,ptr,5,&i);
	f_close(&filcrc);
	result = f_stat ((const TCHAR*)ptr, &fno);
	if(result == FR_EXIST )
	{	
		return ERROR ;
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
uint8_t MMC_PutRec(Record_t record)
{
	FIL filcrc;       /* File object */
	FRESULT result = 1;
	uint8_t ptr[30],directory[10],*arr,timstr[10];
	uint32_t i=0,fsize;
	//FILINFO	fno;
	time_t *time;
	//uint64_t *userID;
	//userID = (uint64_t*)record.ID;
	time = &record.time;
	arr = (uint8_t*)&record;
	sprintf((char*)directory,"1:\\%d%d%d",time->YEAR,time->MONTH,time->DOM);
	sprintf((char*)timstr,"%d%d%d",time->YEAR,time->MONTH,time->DOM);
	result = f_mkdir((TCHAR*)directory);
	result = f_chdir((TCHAR*)directory);
	//sprintf((char*)ptr,"1:%s\\%lld_%s%d.txt",directory,*userID,directory,time->SEC);
	sprintf((char*)ptr,"1:%s_records.txt",timstr);
	
	//sprintf((char*)ptr,"1:%s.txt",directory);
	//all folder exsist or cearte
	//now write data to file
	result = f_open(&filcrc,(const TCHAR*)ptr,FA_CREATE_ALWAYS | FA_WRITE);
	if(result != FR_OK )
	{	
		return ERROR ;
	}
	//result = f_stat ((const TCHAR*)ptr, &fno);
	fsize = f_size(&filcrc);
	f_lseek(&filcrc,fsize);
	
	f_write(&filcrc,arr,16,&i);
	f_close(&filcrc);
	//result = f_stat ((const TCHAR*)ptr, &fno);

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
int MMCtoUSB_filecpy (uint8_t fname[])
{
    //FATFS fs[2];         /* Work area (file system object) for logical drives */
    FIL fsrc, fdst;      /* File objects */
    BYTE buffer[512];   /* File copy buffer */
    FRESULT fr;          /* FatFs function common result code */
    UINT br, bw;         /* File read/write count */
		uint8_t tmp[20];

    /* Register work area for each logical drive */
    f_mount(&fs[0], "1:", 0);//mmc
    f_mount(&fs[1], "2:", 0);//usb
		
		sprintf(tmp,"1:%s",fname);
    /* Open source file on the drive 1 */
    fr = f_open(&fsrc, tmp, FA_OPEN_EXISTING | FA_READ);
    if (fr) return (int)fr;

    sprintf(tmp,"2:%s",fname);
		/* Create destination file on the drive 0 */
    fr = f_open(&fdst, tmp, FA_CREATE_ALWAYS | FA_WRITE);
    if (fr) return (int)fr;

    /* Copy source to destination */
    for (;;) {
        fr = f_read(&fsrc, buffer, sizeof buffer, &br);  /* Read a chunk of source file */
        if (fr || br == 0) break; /* error or eof */
        fr = f_write(&fdst, buffer, br, &bw);            /* Write it to the destination file */
        if (fr || bw < br) break; /* error or disk full */
    }

    /* Close open files */
    f_close(&fsrc);
    f_close(&fdst);

    /* Unregister work area prior to discard it */
    f_mount(NULL, "1:", 0);
    f_mount(NULL, "2:", 0);

    return (int)fr;
}

char * my_DirCat(const char * str1, const char * str2)
{
   char * ret = malloc(strlen(str1)+strlen(str2));

   if(ret!=NULL)
   {
     sprintf(ret, "%s\\%s", str1, str2);
     return ret;
   }
   return NULL;    
}
/*********************************************************************//**
 * @author             
 * @brief 	   Start node to be scanned (also used as work area)
 * @date 
 * @version  
 * @description 
 * @param[in]		name and directory of file folder\file.txt.
 * @param[in]		 
 *							
 * @return 				             
 *                         
 **********************************************************************/
FRESULT scan_files (char* path )
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
	uint8_t *dirName;
    char *fn;   /* This function is assuming non-Unicode cfg. */
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
    fno.lfname = lfn;
    fno.lfsize = sizeof lfn;
#endif


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fname[0] == '.') continue;             /* Ignore dot entry */
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                //sprintf(&path[i], "/%s", fn);
								dirName = (uint8_t*)my_DirCat(path,fn);
		
                res = scan_files((char*)dirName);
								free(dirName);
                //if (res != FR_OK) break;
                //path[i] = 0;
            } else {                                       /* It is a file. */
    
//#if (USB_HOST_EN == 1)								
//							MMCtoUSB_filecpy(fn);
//#endif							
            }
        }
        f_closedir(&dir);
    }

    return res;
}
/*
EOF
*/

