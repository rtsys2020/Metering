/**********************************************************************
* $Id$		template.c			2013-10
*//**
* @file		template.c
* @brief	Use as Template
*			
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee ElmoSanaat Reasearch And Development Team
* 
* Copyright(C) 2013, ElmoSanaat.co
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under ElmoSanaat '
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with ElmoSanaat  .  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
#include "includes.h"
#include "i3c.h"

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
void writeByte(uint8_t data)
{
	uint8_t i;
	uint8_t writeByte;
	writeByte = data;
	
	makeOutputSDA();
	
	for ( i = 0; i < 8; i++) {
		changeStateSCL(0);
		delay_ms(1);
		changeStateSDA(writeByte & 0x80);
		delay_ms(1);
		changeStateSCL(1);
		delay_ms(1);
		writeByte = writeByte << 1;
	}
	makeInputSDA();
	changeStateSCL(0);
	delay_ms(1);
	changeStateSCL(1);
	if (readSDA()) {	//check for ack
		//RETAILMSG(1,(TEXT("ACK is not received!\r\n")));
	}
	delay_ms(1);
	changeStateSCL(0);
	makeOutputSDA();
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
uint8_t readByte(uint8_t ackGenerate)
{
	uint8_t readByte = 0,i;
	makeInputSDA();
	for ( i = 0; i < 8; i++) {
		delay_ms(1);
		readByte = readByte << 1;
		changeStateSCL(1);
		readByte |= (readSDA() & 0x1);
		delay_ms(1);
		changeStateSCL(0);
	}	
	makeOutputSDA();

	if (ackGenerate) // if the received byte is not the last one, then ack must be sent to the slave
		changeStateSDA(0);
	else			// otherwise, nack is sent
		changeStateSDA(1);

	delay_ms(1);

	changeStateSCL(1);
	delay_ms(1);
	changeStateSCL(0);

	return readByte;
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
// change sda from 1 to 0 while scl is 1
void startBit(void)
{
	changeStateSDA(1);
	delay_ms(1);
	changeStateSCL(1);
	delay_ms(1);
	changeStateSDA(0);
	delay_ms(1);
	changeStateSCL(0);
	delay_ms(1);
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
// change sda from 0 to 1 while scl is 1
void stopBit(void)
{
	delay_ms(1);
	changeStateSDA(0);
	delay_ms(1);
	changeStateSCL(1);
	delay_ms(1);
	changeStateSDA(1);
	delay_ms(1);
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
void makeInputSDA(void)
{
	I3C_SDA_GPIO->DIR &= ~(1<<I3C_SDA_PIN);
	return;
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
void makeOutputSDA(void)
{
	I3C_SDA_GPIO->DIR |= (1<<I3C_SDA_PIN);
	return;
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
void changeStateSDA(uint8_t bitVal)
{
	if (bitVal)
		I3C_SDA_GPIO->SET = (1<<I3C_SDA_PIN);
	else
		I3C_SDA_GPIO->CLR = (1<<I3C_SDA_PIN);
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
void changeStateSCL(uint8_t bitVal)
{
	if (bitVal)
		I3C_SCL_GPIO->SET = (1<<I3C_SCL_PIN);
	else
		I3C_SCL_GPIO->CLR = (1<<I3C_SCL_PIN);
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
uint8_t readSDA(void)
{
	uint8_t temp;
	temp = (I3C_SDA_GPIO->PIN >> I3C_SDA_PIN);

	return temp;
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
uint8_t HW_Read (PIIC_IO_DESC* pInData ,PIIC_IO_DESC *pOutData)
{
  uint8_t    retVal  = TRUE,i;        // Initialize to success
	uint8_t Count,g_pcIIC_BUFFER[10];
	HW_Write(pInData);

	Count    =    pOutData->Count;

	startBit();

	writeByte(pOutData->SlaveAddress);

	for ( i = 0; i < Count; i++) {
		if (i == Count -1)
			g_pcIIC_BUFFER[i] = readByte(0);
		else
			g_pcIIC_BUFFER[i] = readByte(1);
	}

	stopBit();
	
	memcpy(pOutData->Data, g_pcIIC_BUFFER, pOutData->Count);	//amin

	return retVal;
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
uint8_t HW_Write (PIIC_IO_DESC* pInData)
{
  uint8_t   retVal= TRUE,i;        // Initialize to success
	uint8_t Count,g_pcIIC_BUFFER[10];
	
	memcpy(g_pcIIC_BUFFER, pInData->Data, pInData->Count);

	Count    =    pInData->Count;
	
	startBit();
	
	writeByte(pInData->SlaveAddress);

	for ( i = 0; i < Count; i++) {
		writeByte(g_pcIIC_BUFFER[i]);
	}
	stopBit();

  return retVal;
}

