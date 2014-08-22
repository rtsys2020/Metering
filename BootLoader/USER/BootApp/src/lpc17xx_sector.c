#include "lpc17xx_sector.h"


/* internal flash sectors definition, 
	the last SECTOR_DESC_T.sec_num should be zero */
#if MCU_FLASH_SIZE_512KB
SECTOR_DESC_T sector_desc[] = 
{
	{8,  4,  0}, 	// 8 4KB sectors, index: 0..3
	{8, 4, 8},	// 8 42KB sectors, index: 8..21
	{14,  32, 16},	// 6 16KB sectors, index: 22..27
	{0,  0,  0}		// should be zero
}; 
#elif MCU_FLASH_SIZE_256KB
SECTOR_DESC_T sector_desc[] = 
{
	{8,  4,  0},
	{7, 32, 8},
	{0,  0,  0}
};
#elif MCU_FLASH_SIZE_128KB
SECTOR_DESC_T sector_desc[] = 
{
	{8,  4,  0},
	{3, 32, 8},
	{0,  0,  0}	
}
#endif

/* Return the sector index according to the specified address,
	if address is too large, return INVALID_RESULT */
unsigned long getSectorIndex(unsigned long addr)
{
	SECTOR_DESC_T *psg = &sector_desc[0];
	unsigned long tmp, size_acc, sector_index, size_addr;

	size_acc = 0;
	size_addr = addr>>10;
	sector_index = INITIAL_SECTOR_INDEX; 
	while (psg->sec_num)
	{
		tmp = size_addr - size_acc;  //KB
		if (psg->sec_size*psg->sec_num > tmp)
		{
			sector_index += tmp/psg->sec_size;
			return sector_index;	
		}
		else
		{
			sector_index += psg->sec_num;
			size_acc += psg->sec_size*psg->sec_num;
		}
		psg++;
	}
	
	return INVALID_RESULT;	
}

/* Return the size (in KB) of specified sector (sectorIndex),
	if failed, return INVALID_RESULT. */
unsigned long getSectorSize(unsigned long sectorIndex)
{
	SECTOR_DESC_T *psg = &sector_desc[0];
	unsigned long index;

	index =  sectorIndex;
	while (psg->sec_num)
	{
		if (index < psg->sec_num)
			return psg->sec_size;
		index -= psg->sec_num;
		psg++;
	}
	return INVALID_RESULT;		
}

/* Return the end sector index according to the start sector index and image size (in Byte),
	if failed , return INVALID_RESULT */
unsigned long getEndSectorIndex(unsigned long size, unsigned long startIndex)
{
	unsigned int index, sec_size_KB, size_tmp;

	if (size == 0)
		return INVALID_RESULT;

	index = startIndex;
	size_tmp = 0;	

	while (size_tmp < size)
	{
		sec_size_KB = getSectorSize(index);	 // in KB
		if (sec_size_KB == INVALID_RESULT)
			return INVALID_RESULT;

		size_tmp +=	(sec_size_KB<<10);
		index++;
	}
	return (index-1);	
}

/* return the max sector index,
	it is supposed that the sector index starts from 0 */
unsigned long getMaxSectorIndex(void)
{
	SECTOR_DESC_T *psg = &sector_desc[0];
	unsigned long index_sum = 0;

	while (psg->sec_num)
	{
		index_sum += psg->sec_num;	
	}
	
	return (index_sum-1);	
}
