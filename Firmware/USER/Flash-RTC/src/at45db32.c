/**********************************************************************
* $Id$		at45db32.c			2013-10
*//**
* @file		at45db32.c
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup FlashRTC
 * @{
 */
#include "includes.h"
#include "at45db32.h"
#include "ssp_driver.h"
#include "lpc177x_8x_rtc.h"



/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */

//	int8_t ali;

/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 

/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_Init(void)
{
	uint32_t i=0;
    SSP_CFG_Type SSP_ConfigStruct;
	/*
	 * Initialize SPI pin connect
	 * P2.19 - SSEL - used as GPIO
	 * P2.22 - SCK
	 * P2.26 - MISO
	 * P2.27 - MOSI
	 */
	PINSEL_ConfigPin(AT45DBXX_CS_PORT, AT45DBXX_CS_PIN, 0);	 /* P2.19 - GPIO */
	//PINSEL_ConfigPin(RTC_CS_PORT_NUM, RTC_CS_PIN_NUM, 0);	 /* P2.21 - GPIO */
	
	PINSEL_ConfigPin(AT45DBXX_WP_PORT, AT45DBXX_WP_PIN, 0);	 /* P2.19 - GPIO */
	PINSEL_ConfigPin(AT45DBXX_RESET_PORT, AT45DBXX_RESET_PIN, 0);	 /* P2.21 - GPIO */
	
	PINSEL_ConfigPin(AT45DBXX_MOSI_PORT_NUM, AT45DBXX_MOSI_PIN_NUM, AT45DBXX_MOSI_FUN_NUM);	 /* SSP0_SCK */
	PINSEL_ConfigPin(AT45DBXX_MISO_PORT_NUM, AT45DBXX_MISO_PIN_NUM, AT45DBXX_MISO_FUN_NUM);	 /* SSP0_MISO */
	PINSEL_ConfigPin(AT45DBXX_SCK_PORT_NUM, AT45DBXX_SCK_PIN_NUM, AT45DBXX_SCK_FUN_NUM);	 /* SSP0_MOSI */

	PINSEL_SetPinMode(AT45DBXX_MOSI_PORT_NUM,AT45DBXX_MOSI_PIN_NUM,IOCON_MODE_PULLUP);
	PINSEL_SetPinMode(AT45DBXX_MISO_PORT_NUM,AT45DBXX_MISO_PIN_NUM,IOCON_MODE_PLAIN);
	/* P2.19 CS is output */
	GPIO_SetDir(AT45DBXX_CS_PORT, (1<<AT45DBXX_CS_PIN), 1);
	GPIO_SetDir(AT45DBXX_WP_PORT, (1<<AT45DBXX_WP_PIN), 1);
	GPIO_SetDir(AT45DBXX_RESET_PORT, (1<<AT45DBXX_RESET_PIN), 1);
	
	AT45DBXX_CS_LOW();
	AT45DBXX_RESET_LOW();
	for(i=0;i<0xa0000;i++);
	AT45DBXX_CS_HIGH();
	for(i=0;i<0xa00;i++);
	AT45DBXX_RESET_HIGH();
	
	AT45DBXX_WP_DISABLE();
/* P2.21 CS is output */
//	GPIO_SetDir(RTC_CS_PORT_NUM, (1<<RTC_CS_PIN_NUM), 1);
//	SPI_RTC_CS_HIGH();
	/* initialize SSP configuration structure to default */
	SSP_ConfigStructInit(&SSP_ConfigStruct);
	
	SSP_ConfigStruct.CPHA = SSP_CPHA_FIRST;
	SSP_ConfigStruct.CPOL = SSP_CPOL_HI;
	//SSP_ConfigStruct.FrameFormat = SSP_FRAME_TI;
	//SSP_ConfigStruct.Databit = SSP_DATABIT_8;
	/* Initialize SSP peripheral with parameter given in structure above */
	SSP_ConfigStruct.ClockRate = 3000000;
	//SSP_ConfigStruct.Mode = SSP_MASTER_MODE;
	SSP_Init(RTC_FLASH_SSP, &SSP_ConfigStruct);
	/* Enable SSP peripheral */
	SSP_Cmd(AT45DBXX_SSP, ENABLE);
}


//Manufacturer and Device Read (Opcode 9FH)
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
uint32_t AT45DBXX_ReadManDevice(void)
{
	uint32_t data = 0;
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x9F);
	
	data |= SPI_ReadWriteByte(0xFF)<<24;
	data |= SPI_ReadWriteByte(0xFF)<<16;
	data |= SPI_ReadWriteByte(0xFF)<<8;
	
	data |= SPI_ReadWriteByte(0xFF);
	AT45DBXX_CS_HIGH();
	return data;
}

//Status Register Read (Opcode D7H)
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
uint16_t AT45DBXX_ReadStatusReg(void)
{
	uint16_t data;
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0xD7);
	
	data |= SPI_ReadWriteByte(0xFF)<<8;
	data |= SPI_ReadWriteByte(0xFF);
	
	AT45DBXX_CS_HIGH();
	return data;
}

//Read Security Register (Opcode 77H)
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
uint8_t AT45DBXX_ReadSecurityReg(void)
{
	uint8_t data;
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x77);
	
	SPI_ReadWriteByte(0xFF);
	SPI_ReadWriteByte(0xFF);
	SPI_ReadWriteByte(0xFF);
	
	data = SPI_ReadWriteByte(0xFF);
	AT45DBXX_CS_HIGH();
	return data;
}

//////Read Sector Lockdown Register (Opcode 35H)
/////*********************************************************************//**
//// * @author  
//// * @brief 	
//// * @date 
//// * @version  1.0
//// * @description 
//// * @param[in]		None.
//// * @param[out]		None.
//// * @return 				             
//// *                         
//// **********************************************************************/
////uint8_t AT45DBXX_ReadLockDownReg(void)
////{
////	uint8_t data;
////	AT45DBXX_CS_LOW();
////	SPI_ReadWriteByte(0x35);
////	
////	SPI_ReadWriteByte(0xFF);
////	SPI_ReadWriteByte(0xFF);
////	SPI_ReadWriteByte(0xFF);
////	
////	data = SPI_ReadWriteByte(0xFF);
////	AT45DBXX_CS_HIGH();
////	return data;
////}

//Read Sector Protection Register (Opcode 32H)
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_ReadProtectReg(uint8_t *data)//ok
{
	uint8_t i;
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x32);
	
	SPI_ReadWriteByte(0xFF);
	SPI_ReadWriteByte(0xFF);
	SPI_ReadWriteByte(0xFF);
	for(i=0;i<64;i++)
		data[i] = SPI_ReadWriteByte(0xFF);
	AT45DBXX_CS_HIGH();
	return;
}

// Sequence for Read/Write Operations for a 528-Byte Page Size
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_Read528Page(uint16_t page_add,uint16_t byte_add,uint8_t *buff)
{
	uint8_t data;
	uint32_t add;
	uint16_t i;
	
	add = (page_add&0x1FFF)<<10|(byte_add&0x03FF);
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x03);
	
	SPI_ReadWriteByte(add<<16);//address 13 page address
	SPI_ReadWriteByte(add<<8);
	SPI_ReadWriteByte(add);//10 bit byte address in page

	for(i=0;i<528;i++)
	{
		data = SPI_ReadWriteByte(0xFF);
		buff[i]=data;
	}
	
	AT45DBXX_CS_HIGH();
	return ;
}

// Sequence for Read page in array mode if one page end start to read from next page
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_ReadMemContinueArray(uint16_t page_add,uint16_t byte_add,uint8_t *buff,uint16_t len)//ok
{
	uint8_t data;
	uint32_t add;
	uint16_t i;
	
	add = (page_add&0x001FFF)<<10|(byte_add&0x0003FF);
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x03);
	
	SPI_ReadWriteByte(add<<16);//address 13 page address
	SPI_ReadWriteByte(add<<8);
	SPI_ReadWriteByte(add);//10 bit byte address in page

	for(i=0;i<len;i++)
	{
		data = SPI_ReadWriteByte(0xFF);
		buff[i]=data;
	}
	
	AT45DBXX_CS_HIGH();
	return ;
}


// Sequence for Read page in array mode if one page end start to read from next page
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_ReadBufferContinue528(buff_num_t buff_num,uint16_t byte_add,uint8_t *buff,uint16_t len)//ok
{
	uint8_t data;
	uint32_t add;
	uint16_t i;
	
	add = (byte_add&0x000003FF);
	AT45DBXX_CS_LOW();
	if(buff_num==BUFFER_ONE)
		SPI_ReadWriteByte(0xD1);//0xd3
	else
		SPI_ReadWriteByte(0xD3);//
	SPI_ReadWriteByte(0xFF);
	SPI_ReadWriteByte(add<<8);
	SPI_ReadWriteByte(add);//10 bit byte address in page

	
	for(i=0;i<len;i++)
	{
		data = SPI_ReadWriteByte(0xFF);
		buff[i]=data;
	}
	
	AT45DBXX_CS_HIGH();
	return ;
}
// Sequence for Read buffer and rotate to begin
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_WriteBuffer_528(buff_num_t buff_num,uint16_t byte_add,uint8_t *buff,uint16_t len)//ok
{
	uint8_t data;
	uint32_t add;
	uint16_t i;
	
	add = (byte_add&0x000003FF);
	AT45DBXX_CS_LOW();
	if(buff_num==BUFFER_ONE)
		SPI_ReadWriteByte(0x84);//ox87 Buff2
	else
		SPI_ReadWriteByte(0x87);//ox87 Buff2
	SPI_ReadWriteByte(0xFF);
	SPI_ReadWriteByte(add<<8);
	SPI_ReadWriteByte(add);//10 bit byte address in page

	
	for(i=0;i<len;i++)
	{
		SPI_ReadWriteByte(buff[i]);
	}
	
	AT45DBXX_CS_HIGH();
	return ;
}


/*********************************************************************//**
 * @author  
 * @brief 	erase page in flash memory and write buffer1 to flash memory
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_WriteBuffToMem528(buff_num_t buff_num, uint16_t page_add)//ok
{
	uint32_t add;
	
	add = (page_add&0x001FFF)<<10;
	AT45DBXX_CS_LOW();
	if(buff_num ==  BUFFER_ONE)
		SPI_ReadWriteByte(0x83);//86 for buff2
	else
		SPI_ReadWriteByte(0x86);//86 for buff2
	SPI_ReadWriteByte(add<<16);//address 13 page address
	SPI_ReadWriteByte(add<<8);
	SPI_ReadWriteByte(add);//10 bit byte address in page

	AT45DBXX_CS_HIGH();
	while((AT45DBXX_ReadStatusReg()&0x80)==0x00);
	//check rdy/busy for complete
	return ;
}

/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_ReadMemoryPageToBuff(buff_num_t buff_Num,uint16_t page_add)//ok
{
	uint32_t add;
	
	add = (page_add&0x00001FFF)<<10;
	AT45DBXX_CS_LOW();
	if(buff_Num == BUFFER_ONE)
		SPI_ReadWriteByte(0x53);//0x58
	else
		SPI_ReadWriteByte(0x58);//0x58
	SPI_ReadWriteByte(add<<16);//address 13 page address
	SPI_ReadWriteByte(add<<8);
	SPI_ReadWriteByte(0xff);//10 bit byte address in page

	AT45DBXX_CS_HIGH();
	while((AT45DBXX_ReadStatusReg()&0x80)==0x00);
	//check rdy/busy for complete
	
	return ;
}

// Sequence for Read page in array mode if one page end start to read from next page
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_ErasePage528(uint16_t page_add)//ok
{
	uint32_t add;
	
	add = (page_add&0x001FFF)<<10;
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x81);
	
	SPI_ReadWriteByte(add<<16);//address 13 page address
	SPI_ReadWriteByte(add<<8);
	SPI_ReadWriteByte(add);//10 bit byte address in page

	AT45DBXX_CS_HIGH();
	while((AT45DBXX_ReadStatusReg()&0x80)==0x00);
	//check rdy/busy for complete
	return ;
}

// Sequence for Read page in array mode if one page end start to read from next page
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_ChipErase(void)
{
	
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x81);
	
	SPI_ReadWriteByte(0xc7);//address 13 page address
	SPI_ReadWriteByte(0x94);
	SPI_ReadWriteByte(0x80);//10 bit byte address in page
	SPI_ReadWriteByte(0x9a);
	
	AT45DBXX_CS_HIGH();
	while((AT45DBXX_ReadStatusReg()&0x80)==0x00);
	//check rdy/busy for complete
	return ;
}

// Sequence for Read page in array mode if one page end start to read from next page
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_EnableSectorProtect(void)
{

	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x81);
	
	SPI_ReadWriteByte(0x3d);//address 13 page address
	SPI_ReadWriteByte(0x2a);
	SPI_ReadWriteByte(0x7f);//10 bit byte address in page
	SPI_ReadWriteByte(0xa9);
	
	AT45DBXX_CS_HIGH();
	while((AT45DBXX_ReadStatusReg()&0x80)==0x00);
	//check rdy/busy for complete
	return ;
}
// Sequence for Read page in array mode if one page end start to read from next page
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_DisableSectorProtect(void)
{
	
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x81);
	
	SPI_ReadWriteByte(0x3d);//address 13 page address
	SPI_ReadWriteByte(0x2a);
	SPI_ReadWriteByte(0x7f);//10 bit byte address in page
	SPI_ReadWriteByte(0x9a);
	
	AT45DBXX_CS_HIGH();
	while((AT45DBXX_ReadStatusReg()&0x80)==0x00);
	//check rdy/busy for complete
	return ;
}
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_EraseSectorProtect(void)
{
	
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x81);
	
	SPI_ReadWriteByte(0x3d);//address 13 page address
	SPI_ReadWriteByte(0x2a);
	SPI_ReadWriteByte(0x7f);//10 bit byte address in page
	SPI_ReadWriteByte(0xcf);
	
	AT45DBXX_CS_HIGH();

	return ;
}
/*********************************************************************//**
 * @author  
 * @brief 	
 * @date 
 * @version  1.0
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void AT45DBXX_DisableAllProtect(void)
{
	uint8_t i;
	AT45DBXX_EraseSectorProtect();
	
	AT45DBXX_CS_LOW();
	SPI_ReadWriteByte(0x81);
	
	SPI_ReadWriteByte(0x3d);//address 13 page address
	SPI_ReadWriteByte(0x2a);
	SPI_ReadWriteByte(0x7f);//10 bit byte address in page
	SPI_ReadWriteByte(0xfc);
	for(i=0;i<64;i++)
		SPI_ReadWriteByte(0x00);
	AT45DBXX_CS_HIGH();
}