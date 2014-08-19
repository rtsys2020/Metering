/**********************************************************************
* $Id$		ssp_driver.c			2013-10
*//**
* @file		ssp_driver.c
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "ssp_driver.h"
#include "user_bsp.h"


/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : SPI FLASH Configuration
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void SPI_FLASH_RTC_Init(void)
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

	PINSEL_ConfigPin(FLASH_CS_PORT, FLASH_CS_PIN, 0);	 /* P2.19 - GPIO */
	//PINSEL_ConfigPin(RTC_CS_PORT_NUM, RTC_CS_PIN_NUM, 0);	 /* P2.21 - GPIO */
	
	PINSEL_ConfigPin(FLASH_WP_PORT, FLASH_WP_PIN, 0);	 /* P2.19 - GPIO */
	PINSEL_ConfigPin(FLASH_RESET_PORT, FLASH_RESET_PIN, 0);	 /* P2.21 - GPIO */
	
	PINSEL_ConfigPin(RTC_FLASH_MOSI_PORT_NUM, RTC_FLASH_MOSI_PIN_NUM, RTC_FLASH_MOSI_FUN_NUM);	 /* SSP0_SCK */
	PINSEL_ConfigPin(RTC_FLASH_MISO_PORT_NUM, RTC_FLASH_MISO_PIN_NUM, RTC_FLASH_MISO_FUN_NUM);	 /* SSP0_MISO */
	PINSEL_ConfigPin(RTC_FLASH_SCK_PORT_NUM, RTC_FLASH_SCK_PIN_NUM, RTC_FLASH_SCK_FUN_NUM);	 /* SSP0_MOSI */

	PINSEL_SetPinMode(RTC_FLASH_MOSI_PORT_NUM,RTC_FLASH_MOSI_PIN_NUM,IOCON_MODE_PULLUP);
	PINSEL_SetPinMode(RTC_FLASH_MISO_PORT_NUM,RTC_FLASH_MISO_PIN_NUM,IOCON_MODE_PLAIN);
	/* P2.19 CS is output */
	GPIO_SetDir(FLASH_CS_PORT, (1<<FLASH_CS_PIN), 1);
	SPI_FLASH_CS_LOW();
	SPI_FLASH_RESET_LOW();
	for(i=0;i<0xa0000;i++);
	SPI_FLASH_CS_HIGH();
	for(i=0;i<0xa00;i++);
	SPI_FLASH_RESET_HIGH();
	
	SPI_FLASH_WP_DISABLE();
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
	SSP_Cmd(RTC_FLASH_SSP, ENABLE);
}

/*******************************************************************************
* Function Name  : LPC17xx_SPI_SendRecvByte
* Description    : Send one byte then recv one byte of response
* Input          : - byte_s: byte_s
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
uint8_t LPC17xx_SPI_SendRecvByte (uint8_t byte_s)
{
	uint32_t timeout = 0xFFFFFF;
	/* wait for current SSP activity complete */
	while ((SSP_GetStatus(RTC_FLASH_SSP, SSP_STAT_BUSY) ==  SET ));
	//SSP_SendData(RTC_FLASH_SSP, (uint16_t) byte_s);
	RTC_FLASH_SSP->DR = byte_s;
	while ((SSP_GetStatus(RTC_FLASH_SSP, SSP_STAT_RXFIFO_NOTEMPTY) == RESET));
	return RTC_FLASH_SSP->DR;
	//return (SSP_ReceiveData(RTC_FLASH_SSP));
}
/*****************************************************************************
* Function Name  : Flash_ReadWriteByte
* Description    : send a byte
* Input          : - data: send data
* Output         : None
* Return         : return data
* Attention		 : None
*******************************************************************************/
uint8_t SPI_ReadWriteByte(uint8_t dataW)		
{
	uint16_t tmp;
	while ((SSP_GetStatus(RTC_FLASH_SSP, SSP_STAT_RXFIFO_NOTEMPTY) ==  SET ))
	{
		tmp = SSP_ReceiveData(RTC_FLASH_SSP);
	}
	SSP_SendData(RTC_FLASH_SSP, (uint16_t) dataW);
	while ((SSP_GetStatus(RTC_FLASH_SSP, SSP_STAT_RXFIFO_NOTEMPTY) ==  RESET ))
	{
	}	
	tmp = SSP_ReceiveData(RTC_FLASH_SSP); 
	return tmp;                                   
}
/*****************************************************************************
* Function Name  : Flash_ReadWriteByte
* Description    : send a byte to SST25VF016B
* Input          : - data: send data
* Output         : None
* Return         : return data
* Attention		 : None
*******************************************************************************/
void SPI_WriteByte(uint8_t data)		
{
	while ((SSP_GetStatus(RTC_FLASH_SSP, SSP_STAT_TXFIFO_NOTFULL) ==  RESET ));
	SSP_SendData(RTC_FLASH_SSP, (uint16_t) data);
}
/*****************************************************************************
* Function Name  : Flash_ReadWriteByte
* Description    : send a byte to SST25VF016B
* Input          : - data: send data
* Output         : None
* Return         : return data
* Attention		 : None
*******************************************************************************/
uint8_t SPI_ReadByte(uint8_t* data)		
{
	uint16_t tmp;
	while ((SSP_GetStatus(RTC_FLASH_SSP, SSP_STAT_RXFIFO_NOTEMPTY) ==  SET ))
	{
		tmp = SSP_ReceiveData(RTC_FLASH_SSP);
	}
	SSP_SendData(RTC_FLASH_SSP, (uint16_t) 0xFFFF);
	while ((SSP_GetStatus(RTC_FLASH_SSP, SSP_STAT_RXFIFO_NOTEMPTY) ==  RESET ))
	{
	}	
	tmp = SSP_ReceiveData(RTC_FLASH_SSP); 
	return tmp;
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

