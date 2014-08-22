#include "IAP.h"
#include "LPC17xx.h"


const uint32_t crp __attribute__((section(".ARM.__at_0x1FC"))) = CRP;

extern uint32_t SystemFrequency;
#define IAP_LOCATION 0x1FFF1FF1
#define iap_entry(a, b)     ((void (*)())(IAP_LOCATION))(a, b)

unsigned long command[5] = {0,0,0,0,0};
unsigned long result[3]= {0,0,0};


/*************************************************************************
 * Function Name: IAP_PrepareSec
 * Parameters: 	unsigned long StartSecNum -- Start Sector Number
 *			 	unsigned long EndSecNum -- End Sector Number
 * Return: unsigned long -- Status Code 
 *
 * Description: This command must be executed before executing "Copy RAM to Flash" or
 *			"Erase Sector(s)" command.
 *
 *************************************************************************/
unsigned long IAP_PrepareSec (unsigned long StartSecNum,  unsigned long EndSecNum)
{
	if (EndSecNum < StartSecNum)
		return IAP_STA_INVALD_PARAM;

	command[0] = IAP_CMD_PrepareSec;
	command[1] = StartSecNum;
	command[2] = EndSecNum;
	iap_entry(command, result);
//     param_table[0] = PREPARE_SECTOR_FOR_WRITE;
//     param_table[1] = start_sector;
//     param_table[2] = end_sector;
//     param_table[3] = SystemFrequency/1000;
//     iap_entry(param_table,result_table);
	return result[0];
}

/*************************************************************************
 * Function Name: IAP_CopyRAMToFlash
 * Parameters: 	unsigned long dst -- Destination Flash address, should be a 256 byte boundary.
 *			 	unsigned long src -- Source RAM address, should be a word boundary
 *				unsigned long number -- 256 | 512 |1024 |4096			
 * Return: unsigned long -- Status Code 
 *
 * Description: This command is used to program the flash memory.
 *
 *************************************************************************/
unsigned long IAP_CopyRAMToFlash (unsigned long dst,  unsigned long src, 
	unsigned long number)
{
	command[0] = IAP_CMD_CopyRAMToFlash;
	command[1] = dst;
	command[2] = src;
	command[3] = number;
	command[4] = SystemFrequency / 1000;	// Fcclk in KHz
	iap_entry(command, result);

	return result[0];
}


/*************************************************************************
 * Function Name: IAP_EraseSec
 * Parameters: 	unsigned long StartSecNum -- Start Sector Number
 *			 	unsigned long EndSecNum -- End Sector Number
 * Return: unsigned long -- Status Code 
 *
 * Description: This command is used to erase a sector or multiple sectors of on-chip Flash
 *			 memory.
 *
 *************************************************************************/
unsigned long IAP_EraseSec (unsigned long StartSecNum,  unsigned long EndSecNum)
{
	if (EndSecNum < StartSecNum)
		return IAP_STA_INVALD_PARAM;

	command[0] = IAP_CMD_EraseSec;
	command[1] = StartSecNum;
	command[2] = EndSecNum;
	command[3] = SystemFrequency / 1000;
	iap_entry(command, result);

	return result[0];
}

/*************************************************************************
 * Function Name: IAP_BlankChkSec
 * Parameters: 	unsigned long StartSecNum -- Start Sector Number
 *			 	unsigned long EndSecNum -- End Sector Number
 * Return: unsigned long -- Status Code 
 *
 * Description: This command is used to blank check a sector or mutilple sectors of on-chip
 *			  Flash memory.
 *
 *************************************************************************/
unsigned long IAP_BlankChkSec (unsigned long StartSecNum,  unsigned long EndSecNum,
					unsigned long * pResult)
{
	if (EndSecNum < StartSecNum)
		return IAP_STA_INVALD_PARAM;

	command[0] = IAP_CMD_BlankChkSec;
	command[1] = StartSecNum;
	command[2] = EndSecNum;

	iap_entry(command, result);

	if (result[0] == IAP_STA_SECTOR_NOT_BLANK)
	{
		*pResult = result[0];
		*(pResult+1) = result[1];
	}

	return result[0];
}

/*************************************************************************
 * Function Name: IAP_ReadParID
 * Parameters: 	unsigned long * PartID
 * Return: unsigned long -- Status Code 
 *
 * Description: This command is used to read the part identification number.
 *
 *************************************************************************/
unsigned long IAP_ReadParID (unsigned long * PartID)
{

	command[0] = IAP_CMD_ReadParID;
	iap_entry(command, result);
	*PartID = result[1];

	return result[0];
}

/*************************************************************************
 * Function Name: IAP_ReadBootVer
 * Parameters: 	char * MajorVer
 *				char * MinorVer
 * Return: unsigned long -- Status Code 
 *
 * Description: This command is used to read the boot code version number.
 *
 *************************************************************************/
unsigned long IAP_ReadBootVer (unsigned long * MajorVer, unsigned long * MinorVer)
{
	command[0] = IAP_CMD_ReadBootVer;
	iap_entry(command, result);
	*MajorVer = (result[1] & 0xff00)>>8;
	*MinorVer = result[1] & 0xff;

	return result[0];
}

/*************************************************************************
 * Function Name: IAP_Compare
 * Parameters: 	unsigned long dst -- Destination Flash address
 *			 	unsigned long src -- Source RAM address
 *				unsigned long number -- Should be in mutilple of 4		
 * Return: unsigned long -- Status Code 
 *
 * Description: This command is used to compary the memory contents at two locations.
 *
 * NOTE:	Compary result may not be correct when source or destination address contains
 *		any of the first 64 bytes starting from address zero. First 64 bytes can be re-mapped
 *		to RAM.
 *
 *************************************************************************/
unsigned long IAP_Compare (unsigned long dst,  unsigned long src, 
	unsigned long number, unsigned long *offset)
{
	command[0] = IAP_CMD_Compare;
	command[1] = dst;
	command[2] = src;
	command[3] = number;
	iap_entry(command, result);

	if (result[0] == IAP_STA_COMPARE_ERROR)
		*offset = result[1];

	return result[0];
}

void  IAP_ReinvokeISP(void)
{
	command[0] = IAP_CMD_REINVOKEISP;					
	iap_entry(command, result);;	
}


