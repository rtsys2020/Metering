/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			SST25VF016B.h
** Descriptions:		SST25VF016B Head function 
**
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2012-8-18
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/

#ifndef __SSP_DRIVER_H 
#define __SSP_DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "lpc_types.h"
#include "lpc177x_8x_ssp.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum ERTYPE{ Sec1, Sec8, Sec16, Chip } ErType;  
//typedef enum IDTYPE{ Manufacturer_ID, Device_ID, JEDEC_ID } idtype;

/* Private define ------------------------------------------------------------*/
/*
//add by rezaei
//<e> RTC and Flash Enable
//<o1>RTC_FLASH SSP Number 
//	<0=> LPC_SSP0
//	<1=> LPC_SSP1
//	<2=> LPC_SSP2
//<o2>PORT number that /RtcCS pin assigned on 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o3>PIN number that  /RtcCS pin assigned on <0-31>
//<o4>RTC_FLASH MOSI PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o5>RTC_FLASH MOSI Pin <0-31>
//<o6>RTC_FLASH MOSI Function Number /////
//<o7>RTC_FLASH MISO PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o8>RTC_FLASH MISO Pin <0-31>
//<o9>RTC_FLASH MISO Function Number /////
//<o10>RTC_FLASH SCK PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o11>RTC_FLASH SCK Pin <0-31>
//<o12>RTC_FLASH SCK Function Number /////
//<o13>PORT number that /FlashCS pin assigned on 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o14>PIN number that  /FlashCS pin assigned on <0-31>
//</e>
*/
#define RTC_FLASH_EN	0
#define RTC_FLASH_SSP_NUM			0
#define RTC_CS_PORT_NUM			2
#define RTC_CS_PIN_NUM			21

#define RTC_FLASH_MOSI_PORT_NUM			2
#define RTC_FLASH_MOSI_PIN_NUM			27
#define RTC_FLASH_MOSI_FUN_NUM			2

#define RTC_FLASH_MISO_PORT_NUM			2
#define RTC_FLASH_MISO_PIN_NUM			26
#define RTC_FLASH_MISO_FUN_NUM			2

#define RTC_FLASH_SCK_PORT_NUM			2
#define RTC_FLASH_SCK_PIN_NUM			22
#define RTC_FLASH_SCK_FUN_NUM			2

#define FLASH_CS_PORT_NUM		2
#define FLASH_CS_PIN_NUM		19

#if (RTC_FLASH_SSP_NUM == 0)
#define RTC_FLASH_SSP	LPC_SSP0
#elif (RTC_FLASH_SSP_NUM == 1)
#define RTC_FLASH_SSP	LPC_SSP1
#elif (RTC_FLASH_SSP_NUM == 2)
#define RTC_FLASH_SSP	LPC_SSP2
#endif

#define SPI_FLASH_CS_LOW()    GPIO_ClearValue( FLASH_CS_PORT_NUM, (1<<FLASH_CS_PIN_NUM) )  
#define SPI_FLASH_CS_HIGH()   GPIO_SetValue( FLASH_CS_PORT_NUM, (1<<FLASH_CS_PIN_NUM) ) 

#define Flash_ReadWriteByte(x)	LPC17xx_SPI_SendRecvByte(x)

//#define SPI_RTC_CS_LOW()    GPIO_ClearValue( RTC_CS_PORT_NUM, (1<<RTC_CS_PIN_NUM) )  
//#define SPI_RTC_CS_HIGH()   GPIO_SetValue( RTC_CS_PORT_NUM, (1<<RTC_CS_PIN_NUM) )

/* Private function prototypes -----------------------------------------------*/
void  SPI_FLASH_RTC_Init     (void);
uint8_t Flash_ReadWriteByte(uint8_t data);


void SPI_WriteByte(uint8_t data);
uint8_t SPI_ReadByte(uint8_t* data)		;
uint8_t SPI_ReadWriteByte(uint8_t dataW)	;

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
