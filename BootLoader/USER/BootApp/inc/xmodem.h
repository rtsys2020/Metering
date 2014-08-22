#ifndef _XMODEM_H
#define _XMODEM_H
#include "utils.h"
#include "includes.h"
//
// XMODEM control character
//
#define XMODEM_SOH		0x01
#define XMODEM_STX		0x02
#define XMODEM_EOT		0x04
#define XMODEM_ACK		0x06
#define XMODEM_NAK		0x15
#define XMODEM_CAN		0x18

//
// max retry times for sync
//
#define MAX_SYNC_TIME	80

//
// max re-transmit time
//
#define MAX_RETRANS_TIME		16

//
// max receive error times
//
#define MAX_ERROR_TIME	25

//
// time out for rx a character (unit: ticks)
//
#define READCHAR_TIMEOUT	0x100000  

//
// packet length is different for different frame header
//
#define XMODEM_SYNC_SOH_DATA_SIZE 	128
#define XMODEM_SYNC_STX_DATA_SIZE 	1024

//
// XMODEM protocol type
//
typedef enum
{
	XMODEM_STD = 0,
	XMODEM_CRC,
	XMODEM_E1K,
	XMODEM_E1G
}XMODEM_TYPE;

extern const char help[];
extern const char intro[];
extern char in_line[];
extern const SCMD cmd[];

#define CMD_COUNT   8//(sizeof (cmd) / sizeof (cmd[0]))

char *get_entry (char *cp, char **pNext);
void cmd_run (char *par);
void cmd_blkchk (char *par);
void cmd_erase (char *par);
void cmd_readid (char *par);
void cmd_prog (char *par);
void cmd_bootinfo (char *par);
void init_bootpara(void);
__inline void cmd_help (char *par);
void execute_user_code(uint32_t start_add);
 UNS_32 XMODEM_Update(UNS_32 update_addr, XMODEM_TYPE Type);

#endif
