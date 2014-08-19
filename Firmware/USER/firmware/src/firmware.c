/**********************************************************************
* $Id$		firmware.c			2013-10
*//**
* @file		firmware.c
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee  Reasearch And Development Team
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
#include "inc\firmware.h"
#include "lpc_types.h" 
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
Status Firmware_CRC_Chk(firmware_page_t* page)
{
	
	return SUCCESS;
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
Status Firmware_WriteToSPI_Flash(firmware_page_t* page,uint16_t page_addr)
{
	uint8_t buff[528];
	firmware_page_t pbuff;
	memcpy(buff,(uint8_t*)page,sizeof(firmware_page_t));
	AT45DBXX_WriteBuffer_528(BUFFER_ONE,0,buff,528);
	AT45DBXX_WriteBuffToMem528(BUFFER_ONE,page_addr);
	return Firmware_ReadFromSPI_Flash(&pbuff,page_addr);
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
Status Firmware_ReadFromSPI_Flash(firmware_page_t* page,uint16_t page_addr)
{
	uint8_t buff[528];
	AT45DBXX_ReadMemContinueArray(page_addr,0,buff,528);
	memcpy((uint8_t*)page,buff,sizeof(firmware_page_t));
	return Firmware_CRC_Chk(page);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////