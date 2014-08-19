/**********************************************************************
* $Id$		i3c.c			2013-10
*//**
* @file		i3c.c
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
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
		return;
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
	uint8_t Count;
	
	
	HW_Write(pInData);

	Count    =    pOutData->Count;

	startBit();

	writeByte(pOutData->SlaveAddress);

	for ( i = 0; i < Count; i++) {
		if (i == Count -1)
			pOutData->Data[i] = readByte(0);
		else
			pOutData->Data[i] = readByte(1);
	}

	stopBit();
	
	//memcpy(pOutData->Data, g_pcIIC_BUFFER, pOutData->Count);	//amin

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
	
	//memcpy(g_pcIIC_BUFFER, pInData->Data, pInData->Count);

	Count    =    pInData->Count;
	
	startBit();
	
	writeByte(pInData->SlaveAddress);

	for ( i = 0; i < Count; i++) {
		writeByte(pInData->Data[i]);
	}
	stopBit();

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

void ADE7953_Init(void)
{
	
	I3C_SDA_GPIO->DIR |= 1<<I3C_SDA_PIN;
	I3C_SDA_GPIO->DIR |= 1<<I3C_SCL_PIN;
	GPIO_SetDir(2,1<<17,1);

	GPIO_ClearValue(2,1<<17);
	delay_ms(100);
	GPIO_SetValue(2,1<<17);

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
void ADE7953_ReadReg(uint16_t reg,uint8_t *data)
{
	PIIC_IO_DESC discOut,discIn;
	
	
	discOut.SlaveAddress = 0x71;
	discOut.Count = 2;
	discOut.Data[0] = reg>>8;
	discOut.Data[1] = reg;
	
	discIn.SlaveAddress = 0x70;
	discIn.Count = 2;

	HW_Read(&discOut,&discIn);
	

}
