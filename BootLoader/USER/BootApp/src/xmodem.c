#include "xmodem.h"
#include <stdio.h>
#include "utils.h"
#include "config.h"
#include "iap.h"
#include "lpc17xx_sector.h"
#include "includes.h"
/*
*	error code when update using XMODEM
*				1: cancelled by remote sender
*				2: synchronized failure
*				3: code size too large
*				4: retransmission time too many
*				5: too many error
*				9: save to flash failure
*				IAP error code
*				10: parepare sector failed
*				11: erase flash failed
*				12: copy from ram to flash failed
*				13: verify ram and flash content failed	
*/
static UNS_32 error_code;
// for display of bootloader info
extern char Image$$ER_IROM1$$RO$$Base[];
extern char Image$$ER_IROM1$$RO$$Length[];
extern char Image$$RW_IRAM1$$RW$$Base[];
extern char Image$$RW_IRAM1$$RW$$Length[];
__align(4) UNS_8  IAP_Buf[IAP_BUF_SIZE];
 const char intro[] =
   "\n"
   "+-----------------------------------------------------------------------+\n"
   "|                LPC2000 Bootloader via XMODEM                          |\n";
 const char help[] = 
   "+ command ------------------+ function ---------------------------------+\n"
   "| INFO                      | display the bootloader info               |\n"
   "| READID                    | read part ID                              |\n"
   "| BLKCHK [from_idx] [to_idx]| check if flash sectors are blank          |\n"
   "| ERASE [from_idx] [to_idx] | erase flash sectors                       |\n"
   "| RUN [addr]                | Run application in internal FLASH         |\n"
   "|                           | [addr - app. address, default=0x10000     |\n"
   "| PROG [addr]               | Dowload BIN file and program to addr      |\n"
   "|                           | [addr - app. address, default=0x10000     |\n"
   "| HELP  or  ?               | displays this help                        |\n"
   "+---------------------------+-------------------------------------------+\n";
/* Local variables */
 char in_line[80];
static UNS_32 bl_size, bl_sector_startidx, bl_sector_endidx;
 const SCMD cmd[] = {
   "INFO", 	 cmd_bootinfo,
   "BLKCHK", cmd_blkchk,
   "ERASE",  cmd_erase,
   "READID", cmd_readid,
   "RUN",    cmd_run,
   "PROG", 	 cmd_prog,
   "HELP",   cmd_help,
   "?",      cmd_help };
/*----------------------------------------------------------------------------
 *        Process input string for long or short name entry
 *---------------------------------------------------------------------------*/
 char *get_entry (char *cp, char **pNext) {
   char *sp, lfn = 0, sep_ch = ' ';

   if (cp == NULL) {                          /* skip NULL pointers          */
      *pNext = cp;
      return (cp);
   }

   for ( ; *cp == ' ' || *cp == '\"'; cp++) { /* skip blanks and starting  " */
      if (*cp == '\"') { sep_ch = '\"'; lfn = 1; }
      *cp = 0;
   }
 
   for (sp = cp; *sp != CR && *sp != LF; sp++) {
      if ( lfn && *sp == '\"') break;
      if (!lfn && *sp == ' ' ) break;
   }

   for ( ; *sp == sep_ch || *sp == CR || *sp == LF; sp++) {
      *sp = 0;
      if ( lfn && *sp == sep_ch) { sp ++; break; }
   }

   *pNext = (*sp) ? sp : NULL;                /* next entry                  */
   return (cp);
}

/*----------------------------------------------------------------------------
 *        Display Command Syntax help
 *---------------------------------------------------------------------------*/
 __inline void cmd_help (char *par) {
   printf (help);
}

__asm void boot_jump( uint32_t address ){
   LDR SP, [R0]		;Load new stack pointer address
   LDR PC, [R0, #4]	;Load new program counter address
}

void execute_user_code(uint32_t start_add)
{
	/* Change the Vector Table to the USER_FLASH_START 
	in case the user application uses interrupts */
	SCB->VTOR = start_add ;//& 0x1FFFFF80;
	//NVIC_SetVectorTable(0x2000, start_add);
	boot_jump(start_add);
}

/* Run appliication at specified address */
 void cmd_run (char *par)
{
	char *entry, *next;
	int run_addr;
	UNS_32 i;
	PFV fp;
	
	// get run address
	entry = get_entry (par, &next);
	if (entry == NULL) 
		run_addr = DEFAULT_RUN_ADDR;
	else
		run_addr = strtoul(entry);

	//fp = (PFV)(run_addr);
	printf("Run applicaiton at 0x%x...\n", run_addr);
	for (i=0x1000;i!=0; i--);
	//(*fp)(); 
	execute_user_code(run_addr);
}

/* Check specified flash blanks are blank or not */
 void cmd_blkchk (char *par)
{
	char *start_index, *end_index, *next;
	UNS_32 start_idx, end_idx;
	UNS_32 IAP_return[2], ret;

	start_index = get_entry (par, &next);
	if (start_index == NULL) 
	{
		printf("\nSector start index missing!\n");
		return;
	}
	start_idx = strtoul(start_index);

	end_index = get_entry (next, &next);  
	if (end_index == NULL)
		end_idx = start_idx;
	else
		end_idx = strtoul(end_index);

	if (start_idx > end_idx)
	{
		printf("\nEnd index should be greater or equal to the start index!\n");
		return;
	}

	ret = IAP_BlankChkSec(start_idx, end_idx, IAP_return);
	if (ret == IAP_STA_CMD_SUCCESS)
	{
		printf("\nSectors from %d to %d are blank.\n", start_idx, end_idx);  	
	}
	else if (ret == IAP_STA_SECTOR_NOT_BLANK )
	{
		printf("\nNot blank.\nOffset of the first non blank word location is 0x%x.\n", IAP_return[1]);
	}
	else
		printf("\nFailed to check blank.\n");

}
/* erase flash sectors with specified start and end index */
 void cmd_erase (char *par)
{
	char *start_index, *end_index, *next;
	UNS_32 start_idx, end_idx;
	UNS_32 ret;

	// get start index
	start_index = get_entry (par, &next);
	if (start_index == NULL) 
	{
		printf("\nSector start index missing!\n");
		return;
	}
	start_idx = strtoul(start_index);

	// get end index
	end_index = get_entry (next, &next);  // Image entry point
	if (end_index == NULL)
		end_idx = start_idx;
	else
		end_idx = strtoul(end_index);
	
	// check the start and end index
	if (start_idx <= bl_sector_endidx)
	{
		printf("\nApplication address overlapped with boot loader!\n");	
		return;
	}
	if (end_idx < start_idx)
	{
		printf("\nEnd index should be greater or equal to the start index!\n");
		return;
	}

	// prepre sectors to erase
	if (IAP_PrepareSec(start_idx, end_idx) != IAP_STA_CMD_SUCCESS)
	{
		printf("\nFailed to prepare sectors.\n");
		return;
	}

	__disable_irq();
	ret = IAP_EraseSec(start_idx, end_idx);
	__enable_irq();
	if (ret == IAP_STA_CMD_SUCCESS)
	{
		printf("\nErased sectors from %d to %d .\n", start_idx, end_idx);
	}
	else
		printf("\nFailed to erase.\n");

}

/* Read Part Identification number */
 void cmd_readid (char *par)
{
	UNS_32 id[1];

	//IRQDisable();
	IAP_ReadParID((unsigned long*)&id[0]);
	//IRQEnable();

	printf("\nPart ID: 0x%x.\n", id[0]);
}

/* progrom a BIN file to a specified address in internal flash */
 void cmd_prog (char *par)
{
	char *entry, *next;
	UNS_32 update_addr, sector_index;
	UNS_32 app_len;

	// program address
	entry = get_entry (par, &next);  //Image entry point
	if (entry == NULL)
		update_addr = DEFAULT_PROG_ADDR;
	else
		update_addr = strtoul(entry);	

	// app_addr should be a starting address of some sector,
	// it's better to verify here

	sector_index = getSectorIndex(update_addr);
	if (sector_index == INVALID_RESULT)
	{
		printf("\nInvalid application address!\n");
		return;
	}
	if (sector_index <= bl_sector_endidx)
	{
		printf("\nApplication address overlapped with boot loader!\n");	
		return;
	}

	printf("\nApplication address: 0x%x.\n", update_addr);
	printf("Please transfer a BIN file via 1K XMODEM...\n");
					
	app_len = XMODEM_Update( update_addr, XMODEM_E1K);
	if (app_len == 0)
		printf("\nUpdate failed, error code: %d.\n", error_code);
	else
		printf("\n%d bytes programmed.\n", app_len);
}

/* Display info of bootloader */
 void cmd_bootinfo (char *par)
{
	printf("  Bootloader:\n");
	printf("             Entry:    0x%x\n", (UNS_32)Image$$ER_IROM1$$RO$$Base);
	printf("             Size:     0x%x bytes (%d)\n", bl_size, bl_size);
	printf("             Sectors:  %d to %d\n", bl_sector_startidx, bl_sector_endidx);
	printf("             Version:  %s\n", __DATE__);
}

 void init_bootpara(void)
{
	bl_size = (UNS_32)Image$$ER_IROM1$$RO$$Length + (UNS_32)Image$$RW_IRAM1$$RW$$Length;
	bl_sector_startidx = getSectorIndex((UNS_32)Image$$ER_IROM1$$RO$$Base);
	bl_sector_endidx = getEndSectorIndex(bl_size, bl_sector_startidx);
}
///////////////////////////////////////////////////////////////////////////////////////
/****************************************************************************
* name:		Port_ReadUChar
* func:		read an unsigned char from a pre-specified port
* para:		timeout value(unit: tick)
* ret:		0 : timeout 
*			1 : valid byte(put in ch)
*
* Description:		
****************************************************************************/
static int Port_ReadUChar(UNS_8* ch, UNS_32 timeout)
{
	int t;

	for (t=timeout; t!=0; t--)
	{
		if (RxDataReady())
		{
			*ch = getkey();
			return 1;
		}
	}
	return 0;
}

/****************************************************************************
* name:		Port_WriteUChar
* func:		write an unsigned char to a pre-specified port
* para:		char
* ret:		
*
* Description:		
****************************************************************************/
static void __inline Port_WriteUChar(UNS_8 ch)
{
	sendchar(ch);
}

/****************************************************************************
* name:		Port_FlushInput
* func:		flush the input
* para:		
* ret:		
*
* Description:		
****************************************************************************/
static void Port_FlushInput()
{
	UNS_32 t;
	for (t=2*READCHAR_TIMEOUT; t!=0; t--)
	{
		if (RxDataReady())
			getkey();
	}
}

/****************************************************************************
* name:		calcrc16
* func:		calculate the crc16
* para:		
* ret:		checksum
*
* Description:		
****************************************************************************/
static UNS_16 calcrc16(const UNS_8 *ptr, int count) 
{ 
    int crc = 0; 
    UNS_8 i; 
     
    while (--count >= 0) 
    { 
        crc = crc ^ (int) *ptr++ << 8; 
        i = 8; 
        do 
        { 
        if (crc & 0x8000) 
            crc = crc << 1 ^ 0x1021; 
        else 
            crc = crc << 1; 
        } while(--i); 
    } 
    return (UNS_16)(crc); 
} 

/****************************************************************************
* name:		calc_checksum
* func:		calculate the checksum
* para:		
* ret:		checksum
*
* Description:		
****************************************************************************/
static UNS_16 calc_checksum(const UNS_8 *buf, UNS_32 len, char crc_flag)
{
	UNS_16 check = 0;
	
	if (crc_flag) // CRC16
	{
		//check = crc16_ccitt(buf, len);
		check = calcrc16(buf, len);
	}
	else	// sum
	{
		UNS_32 i;
		for (i=0;i<len;i++)
			check += buf[i];
		
		check &= 0xff;
	}
	
	return check;
}

/* Cancel the transmission */
static void XMODEM_Cancel()
{
	Port_FlushInput();
	Port_WriteUChar(XMODEM_CAN);
	Port_WriteUChar(XMODEM_CAN);
	Port_WriteUChar(XMODEM_CAN);	
}

/* prepare and erase sector with specified index,
	if OK, return 0, otherwise return the error code */
static int IAP_PrepareErase(UNS_32 sector_index)
{
	int ret = 0;

	// prepre sector [sector_index] to erase
	if(IAP_PrepareSec(sector_index, sector_index) != IAP_STA_CMD_SUCCESS)
	{
		return 10;
	}
	// erase sector [sector_index]
	__disable_irq();
	if (IAP_EraseSec(sector_index, sector_index) != IAP_STA_CMD_SUCCESS)
	{
		ret = 11;
	}
	__enable_irq();
	
	return ret;	
}


/* program content in IAP_Buf to internal flash with address of 
	app_addr, and sector index of sector_index.
	if ok, return 0, otherwise return the error code. */
static int IAP_Program(UNS_32 sector_index, UNS_32 app_addr)
{
	UNS_32 IAP_return[2];

	// program 1kb [app_addr]			
	// prepre sector [sector_index] to write
	if(IAP_PrepareSec(sector_index, sector_index) != IAP_STA_CMD_SUCCESS)
	{
		return 10;
	}

	__disable_irq();
	if ((IAP_CopyRAMToFlash(app_addr, (UNS_32)IAP_Buf, IAP_BUF_SIZE)) != IAP_STA_CMD_SUCCESS)
	{
		__enable_irq();
		return 12;
	}
	__enable_irq();

	if (IAP_Compare(app_addr, (UNS_32)IAP_Buf, IAP_BUF_SIZE, IAP_return) != IAP_STA_CMD_SUCCESS)
	{
		return 13;
	}

	return 0;	
}


/****************************************************************************
* name:		XMODEM_Update
* func:		receive data via XMODEM protocol and write to internal flash
* if failed, return 0, otherwise return the application size in bytes
****************************************************************************/
 UNS_32 XMODEM_Update(UNS_32 update_addr, XMODEM_TYPE Type)
{
	UNS_32 app_addr, sector_index, sector_size, sector_size_sum;
	BOOL_32 new_sector;
	int ret;
		
	UNS_8 ch; 
	UNS_8 *pch;
	int i;
	
	int data_size;	// data length in packet
	UNS_8 sync_char;	// sync byte
	UNS_8 crc_flag;		// crc flag(1: CRC£¬0: sum£©
	UNS_8 recv_pktno; // packet no. of received packet
		
	UNS_16 checksum; // 
	
	UNS_8 *pbuf = IAP_Buf; // 
	UNS_32 recv_len = 0;	// received packet length
	UNS_8 packet_no = 1; // packet no. we want this time
	
	int err_cnt = 0; // error count during receive
	int retrans = MAX_RETRANS_TIME; // max re-transmit times
		
	app_addr = update_addr;
	new_sector = 1;	
	sector_index = getSectorIndex(app_addr);  //starting sector index


	//
	// set sync byte based on the xmodem bypte
	// packet length was set based on the received frame header
	//
	switch(Type)
	{
		case XMODEM_STD:
			sync_char = XMODEM_NAK;
			crc_flag = 0;
			break;
		case XMODEM_CRC:
		case XMODEM_E1K:
			sync_char = 'C';
			crc_flag = 1;
			break;
		case XMODEM_E1G:
			sync_char = 'G';
			crc_flag = 1;
			break;
		default:
			sync_char = XMODEM_NAK;
			crc_flag = 0;
			break;	 
	}
	
	//
	// start to receive
	//
	for (;;)
	{				
		// prepare to receive the frame header
		for (i=0;i<MAX_SYNC_TIME;i++) 
		{
			// sync with sender
			if (sync_char)
				Port_WriteUChar(sync_char);
				
			if (Port_ReadUChar(&ch, READCHAR_TIMEOUT)) // 
			{				
				switch (ch)
				{
					case XMODEM_SOH:
					{
						data_size = XMODEM_SYNC_SOH_DATA_SIZE;
						goto start_recv;
					}
					case XMODEM_STX:
					{
						data_size = XMODEM_SYNC_STX_DATA_SIZE;
						goto start_recv;					
					}
					case XMODEM_EOT:// normal end
					{
						Port_WriteUChar(XMODEM_ACK);						
						
						// program left data in pbuf to flash?
						if (pbuf != IAP_Buf)
						{
							// wait for XMODEM_ACK sent out
							i = 5000;
							while(i--);

							// program left data in pbuf to flash???
	
						}

						return recv_len;
					}
					case XMODEM_CAN:
					{
						Port_ReadUChar(&ch, READCHAR_TIMEOUT);							
						// sender cancel the transmit
						if (ch == XMODEM_CAN)
						{
							Port_FlushInput();
							Port_WriteUChar(XMODEM_ACK);
							
							error_code = 1;
							return 0; 
						}
						break;
					}
					default:
						break;
				}
			} // end of if (ch != 0)
		} // end of for (retry=0 ...
		
		// syn failed, rx abort
		XMODEM_Cancel();

		error_code = 2;
		return 0;	
		
start_recv:
		sync_char = 0;	// already in syn state
						
		// receive packet_no
		if ((Port_ReadUChar(&pbuf[0], READCHAR_TIMEOUT)) == 0)
			goto reject;
		// receive ~packet_no
		if ((Port_ReadUChar(&pbuf[1], READCHAR_TIMEOUT)) == 0)
			goto reject;
				
		// check packet_no
		if (pbuf[0] != (UNS_8)(~pbuf[1]) || 
			(pbuf[0] != packet_no && pbuf[0] != packet_no - 1))
			goto reject;
	
		// start to receive packet	
		recv_pktno = pbuf[0]; 
					
		pch = pbuf;// point to current buf
		
		for (i=0;i<data_size;i++)
		{
			if ((Port_ReadUChar(&ch, READCHAR_TIMEOUT)) == 0)
				goto reject;
			*pch++ = ch;
		}
		
		// get check sum
		if ((Port_ReadUChar(&ch, READCHAR_TIMEOUT)) == 0)
			goto reject;
		else
			checksum = ch;
		
		// CRC check sum
		if (crc_flag)
		{
			if ((Port_ReadUChar(&ch, READCHAR_TIMEOUT)) == 0)
				goto reject;
				
			checksum = (checksum<<8) + ch;
		}
		
		if (calc_checksum(pbuf, data_size, crc_flag) != checksum)
		
			goto reject;
		
		//
		// here, a complete packet has beed received.
		// it is the packet we want or a packet sent again
		//
			
		if (recv_pktno == packet_no) // is the packet we want
		{
			recv_len += data_size;
			pbuf += data_size;	// move to the next buf start address
			packet_no++;

			// IAP_Buf is full, ready to program
			if ((pbuf - IAP_Buf) >=  IAP_BUF_SIZE)
			{
				if (new_sector)
				{
					ret = IAP_PrepareErase(sector_index);
					if (ret != 0)
					{
						XMODEM_Cancel();

						error_code = ret;
						return 0;
					}			

					sector_size = (getSectorSize(sector_index) << 10);
					sector_size_sum = 0;
					new_sector = 0;	
				}

				ret =  IAP_Program(sector_index, app_addr);
				if (ret != 0)
				{
					XMODEM_Cancel();

					error_code = ret;
					return 0;
				}
				
				pbuf = IAP_Buf;
				app_addr += IAP_BUF_SIZE;
				sector_size_sum += 	IAP_BUF_SIZE;
				if (sector_size_sum	== sector_size)
				{
					sector_index++;
					new_sector = 1;
				}
			}
						
			retrans = MAX_RETRANS_TIME;									
		}

		// too many errors when re-send last packet
		if (--retrans <= 0)
		{
			Port_FlushInput();
			Port_WriteUChar(XMODEM_CAN);
			Port_WriteUChar(XMODEM_CAN);
			Port_WriteUChar(XMODEM_CAN);

			error_code = 4;
			return 0; 			
		}
		
		// acknowledge for a correctly received packet, this will inform the 
		// sender to send next packet
		Port_WriteUChar(XMODEM_ACK);
		continue;	
	
reject:		
		Port_FlushInput();
		// too many rx error, transmit abort
		if (err_cnt++ > MAX_ERROR_TIME)
		{
			Port_WriteUChar(XMODEM_CAN);
			Port_WriteUChar(XMODEM_CAN);
			Port_WriteUChar(XMODEM_CAN);
			
			error_code = 5;
			return 0; 			
		}
		else // re-send the packet
		{
			Port_WriteUChar(XMODEM_NAK);
		}
		
	} // end of for (;;) ...
	
}
