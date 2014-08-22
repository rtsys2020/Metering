/**********************************************************************
* $Id$		iaptest.c			2011-11-21
*//**
* @file		lpc177x_8x_iap.h
 * @brief	       IAP demo
* @version	1.0
* @date		21. November. 2011
* @author	
**********************************************************************/

#include "LPC177x_8x.h"
#include "lpc_types.h"
#include "lpc177x_8x_iap.h"
#include "debug_frmwrk.h"

 

/** The area will be erase and program */
#define FLASH_PROG_AREA_START       0x8000
#define FLASH_PROG_AREA_SIZE		0x1000


/** The origin buffer on RAM */
#define BUFF_SIZE           512
#ifdef __IAR_SYSTEMS_ICC__
#pragma data_alignment=4
uint8_t buffer[BUFF_SIZE];
#else
uint8_t __attribute__ ((aligned (4))) buffer[BUFF_SIZE];
#endif

/** @defgroup IAP_Demo	IAP Demo
 * @ingroup IAP_Examples
 * @{
 */
 
/*********************************************************************//**
 * @brief		The entry of the program
 *
 * @param[in]None
 *
 * @return 	None.
 *
 **********************************************************************/
void FlashProgram (void)
{	    		
  uint32_t result[4];
  uint8_t ver_major, ver_minor;
  uint32_t i;
  uint8_t *ptr;
  uint32_t flash_prog_area_sec_start;
  uint32_t flash_prog_area_sec_end;
  IAP_STATUS_CODE status;

  // Initialize
  debug_frmwrk_init();
  for (i = 0;i < sizeof(buffer);i++)
  {
    buffer[i] = (uint8_t)i;
  }
  flash_prog_area_sec_start = GetSecNum(FLASH_PROG_AREA_START);
  flash_prog_area_sec_end =  GetSecNum(FLASH_PROG_AREA_START + FLASH_PROG_AREA_SIZE);

 
  status = ReadPartID(result);
  if(status != CMD_SUCCESS)
  {
 //    _DBG("Read Part ID failed with code is ");_DBD(status);_DBG_("");
     while(1);
  }
 // _DBG("PartID: ");_DBH32(result[0]);_DBG_("");
  
  status = ReadBootCodeVer(&ver_major, &ver_minor);
  if(status != CMD_SUCCESS)
  {
   //  _DBG("Read Boot Code Version failed with code is ");_DBD(status);_DBG_("");
     while(1);
  }
  //_DBG("Boot Code Version: ");_DBD(ver_major);_DBG(".");_DBD(ver_minor);_DBG_("");

  status = ReadDeviceSerialNum(result);
  if(status != CMD_SUCCESS)
  {
   //  _DBG("Read UID failed with code is ");_DBD(status);_DBG_("");
     while(1);
  }

  status = EraseSector(flash_prog_area_sec_start, flash_prog_area_sec_end); 
  if(status != CMD_SUCCESS)
  {
//     _DBG("Erase chip failed with code is ");_DBD(status);_DBG_("");
     while(1); 
  }

  status = BlankCheckSector(flash_prog_area_sec_start, flash_prog_area_sec_end,
                                  &result[0], &result[1]);
  if(status != CMD_SUCCESS)
  {
  //   _DBG("Blank Check failed with code is ");_DBD(status);_DBG_("");
	 if(status == SECTOR_NOT_BLANK)
	 {
	   //_DBG(">>>>The first non-blank sector is sector ");
	   //_DBD(flash_prog_area_sec_start + result[0]);
	  // _DBG_("");
	 }
     while(1); 
  }
  //_DBG_("Erase chip: Success");


  /* Be aware that Program and ErasePage take long time to complete!!! If bigger
  RAM is present, allocate big buffer and reduce the number of Program blocks. */

  /* Program flash block by block until the end of the flash. */
  for ( i = 0; i < FLASH_PROG_AREA_SIZE/BUFF_SIZE; i++ )
  {
    ptr = (uint8_t*)(FLASH_PROG_AREA_START + i*BUFF_SIZE);
		//read data from spi flash and fill buffer
		status =  CopyRAM2Flash(ptr, buffer,IAP_WRITE_1024);
		if(status != CMD_SUCCESS)
		{
	   //_DBG("Program chip failed with code is ");_DBD(status);_DBG_("");
       while(1);
    }
  }
  // Compare
  for ( i = 0; i < FLASH_PROG_AREA_SIZE/BUFF_SIZE; i++ )
  {
    ptr = (uint8_t*)(FLASH_PROG_AREA_START + i*BUFF_SIZE);
		//read data from spi flash and fill buffer 
		status =  Compare(ptr, buffer,BUFF_SIZE);
		if(status != CMD_SUCCESS)
		{
	   //_DBG("Compare memory failed with code is ");_DBD(status);_DBG_("");
       while(1);
		}
  }
  //_DBG_("Program chip: Success");
  //_DBG_("Demo termination");  
  
  while (1);
}



