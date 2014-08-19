/**********************************************************************
* $Id$		ade7953.c			2013-10
*//**
* @file		ade7953.c
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee  Reasearch And Development Team
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
#include "inc\ade7953_spi_driver.h"

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 


/**
 * @}
 */
/* End of Private Variables ----------------------------------------------------*/ 




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

void ADE7953_SPI_Init(void)
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

	PINSEL_ConfigPin(ADE7953_CS_PORT, ADE7953_CS_PIN, 0);	 
	PINSEL_ConfigPin(ADE7953_RESET_PORT, ADE7953_RESET_PIN, 0);	 /* P2.21 - GPIO */
	
	PINSEL_ConfigPin(ADE7953_MOSI_PORT_NUM, ADE7953_MOSI_PIN_NUM, ADE7953_MOSI_FUN_NUM);	 /* SSP0_SCK */
	PINSEL_ConfigPin(ADE7953_MISO_PORT_NUM, ADE7953_MISO_PIN_NUM, ADE7953_MISO_FUN_NUM);	 /* SSP0_MISO */
	PINSEL_ConfigPin(ADE7953_SCK_PORT_NUM, ADE7953_SCK_PIN_NUM, ADE7953_SCK_FUN_NUM);	 /* SSP0_MOSI */

	PINSEL_SetPinMode(ADE7953_MOSI_PORT_NUM,ADE7953_MOSI_PIN_NUM,IOCON_MODE_PULLUP);
	PINSEL_SetPinMode(ADE7953_MISO_PORT_NUM,ADE7953_MISO_PIN_NUM,IOCON_MODE_PULLUP);
	/* P2.19 CS is output */
	GPIO_SetDir(ADE7953_CS_PORT, (1<<ADE7953_CS_PIN), 1);
	GPIO_SetDir(ADE7953_RESET_PORT, (1<<ADE7953_RESET_PIN), 1);
	
	ADE7953_CS_LOW();
	ADE7953_RESET_LOW();
	for(i=0;i<0xa0000;i++);
	ADE7953_CS_HIGH();
	for(i=0;i<0xa00;i++);
	ADE7953_RESET_HIGH();
	
/* P2.21 CS is output */
//	GPIO_SetDir(CS_PORT_NUM, (1<<CS_PIN_NUM), 1);
//	SPI_CS_HIGH();
	/* initialize SSP configuration structure to default */
	SSP_ConfigStructInit(&SSP_ConfigStruct);
	
	SSP_ConfigStruct.CPHA = SSP_CPHA_SECOND;
	SSP_ConfigStruct.CPOL = SSP_CPOL_LO;
	//SSP_ConfigStruct.FrameFormat = SSP_FRAME_TI;
	//SSP_ConfigStruct.Databit = SSP_DATABIT_8;
	/* Initialize SSP peripheral with parameter given in structure above */
	SSP_ConfigStruct.ClockRate = 3000000;
	//SSP_ConfigStruct.Mode = SSP_MASTER_MODE;
	SSP_Init(ADE7953_SSP, &SSP_ConfigStruct);
	/* Enable SSP peripheral */
	SSP_Cmd(ADE7953_SSP, ENABLE);

}

/*******************************************************************************
* Function Name  : LPC17xx_SPI_SendRecvByte
* Description    : Send one byte then recv one byte of response
* Input          : - byte_s: byte_s
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
uint8_t SPI_SendRecvByte (uint8_t byte_s)
{
	uint32_t timeout = 0xFFFFFF;
	/* wait for current SSP activity complete */
	while ((SSP_GetStatus(ADE7953_SSP, SSP_STAT_BUSY) ==  SET ));
	//SSP_SendData(RTC_FLASH_SSP, (uint16_t) byte_s);
	ADE7953_SSP->DR = byte_s;
	while ((SSP_GetStatus(ADE7953_SSP, SSP_STAT_RXFIFO_NOTEMPTY) == RESET));
	return ADE7953_SSP->DR;
	//return (SSP_ReceiveData(RTC_FLASH_SSP));
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
uint16_t ADE7953_SPI_ReadReg16(uint16_t reg)
{
	uint16_t data = 0;
	ADE7953_CS_LOW();
//reg 107  0x0300
	SPI_SendRecvByte(reg>>8);
	SPI_SendRecvByte(reg);
	
	SPI_SendRecvByte(0x80);
	
	data |= SPI_SendRecvByte(0xff)<<8;
	data |= SPI_SendRecvByte(0xff);
	ADE7953_CS_HIGH();
	return data;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////