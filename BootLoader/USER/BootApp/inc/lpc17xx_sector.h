#ifndef __LPC17XX_SECTOR_H
#define __LPC17XX_SECTOR_H

#define MCU_FLASH_SIZE_512KB	1
#define MCU_FLASH_SIZE_256KB	0
#define MCU_FLASH_SIZE_128KB	0

#define INVALID_RESULT 0xFFFFFFFF
#define INITIAL_SECTOR_INDEX 0	// 假设扇区是从0开始编号的

typedef const struct
{
	unsigned char 	sec_num; 	/* sector number of the sector group */
	unsigned char 	sec_size;    /* each sector size in KB */
	unsigned char 	sec_index;	/* starting index of the sector group */
} SECTOR_DESC_T;

unsigned long getSectorIndex(unsigned long addr);
unsigned long getSectorSize(unsigned long sectorIndex);
unsigned long getEndSectorIndex(unsigned long sizeKB, unsigned long startIndex);
unsigned long getMaxSectorIndex(void);

#endif
