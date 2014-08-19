/**********************************************************************
* $Id$		ssp_driver.h			2013-10
*//**
* @file		ssp_driver.h
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/

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

#define SPI_FLASH_CS_LOW()    GPIO_ClearValue( FLASH_CS_PORT, (1<<FLASH_CS_PIN) )  
#define SPI_FLASH_CS_HIGH()   GPIO_SetValue( FLASH_CS_PORT, (1<<FLASH_CS_PIN) ) 

#define SPI_FLASH_RESET_LOW()    GPIO_ClearValue( FLASH_RESET_PORT, (1<<FLASH_RESET_PIN) )  
#define SPI_FLASH_RESET_HIGH()   GPIO_SetValue( FLASH_RESET_PORT, (1<<FLASH_RESET_PIN) ) 

#define SPI_FLASH_WP_ENABLE()    GPIO_ClearValue( FLASH_WP_PORT, (1<<FLASH_WP_PIN) )  
#define SPI_FLASH_WP_DISABLE()   GPIO_SetValue( FLASH_WP_PORT, (1<<FLASH_WP_PIN) ) 

#define Flash_ReadWriteByte(x)	LPC17xx_SPI_SendRecvByte(x)


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
