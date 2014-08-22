/**********************************************************************
* $Id$		ov9650_cfg.c			2013-10
*//**
* @file		ov9650_cfg.c
* @brief	camera configuration file for i/o and interface
*			
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee ElmoSanaat R&D
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



#include "i2c_driver.h"



__IO Bool complete;



/*********************************************************************//**
 * @auther s.rezaee
 * @brief 		initial i2c and i/o for camera	
 * @description initial camera i2c interface and initial port for get raw data of 
				camera
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void I2C_IRQ(void)
{
	I2C_MasterHandler((en_I2C_unitId)CAMERA_TOUCH_I2C);
	if (I2C_MasterTransferComplete((en_I2C_unitId)CAMERA_TOUCH_I2C)){
		  complete = TRUE;
	}   
}
/*********************************************************************//**
 * @auther s.rezaee
 * @brief 		initial i2c and i/o for camera	
 * @description initial camera i2c interface and initial port for get raw data of 
				camera
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/

void I2C_init(void)   
{   
	uint8_t i;

#if ((CAMERA_TOUCH_I2C == 0))
	PINSEL_ConfigPin (CAMERA_TOUCH_SDA_PORT, CAMERA_TOUCH_SDA_PIN, CAMERA_TOUCH_I2C_FUNNUM);
	PINSEL_ConfigPin (CAMERA_TOUCH_SCL_PORT, CAMERA_TOUCH_SCL_PIN, CAMERA_TOUCH_I2C_FUNNUM);
	PINSEL_SetPinMode(CAMERA_TOUCH_SDA_PORT,CAMERA_TOUCH_SDA_PIN,IOCON_MODE_PLAIN);
	PINSEL_SetPinMode(CAMERA_TOUCH_SCL_PORT,CAMERA_TOUCH_SCL_PIN,IOCON_MODE_PLAIN);

#elif ((CAMERA_TOUCH_I2C == 1))
	PINSEL_ConfigPin (CAMERA_TOUCH_SDA_PORT, CAMERA_TOUCH_SDA_PIN, CAMERA_TOUCH_I2C_FUNNUM);//3
	PINSEL_ConfigPin (CAMERA_TOUCH_SCL_PORT, CAMERA_TOUCH_SCL_PIN, CAMERA_TOUCH_I2C_FUNNUM);//3
	PINSEL_SetOpenDrainMode(CAMERA_TOUCH_SDA_PORT, CAMERA_TOUCH_SDA_PIN, ENABLE);
	PINSEL_SetOpenDrainMode(CAMERA_TOUCH_SCL_PORT, CAMERA_TOUCH_SCL_PIN, ENABLE);
	PINSEL_SetPinMode(CAMERA_TOUCH_SDA_PORT, CAMERA__TOUCHSDA_PIN, PINSEL_BASICMODE_PLAINOUT);
	PINSEL_SetPinMode(CAMERA_TOUCH_SCL_PORT, CAMERA_TOUCH_SCL_PIN, PINSEL_BASICMODE_PLAINOUT);
#elif ((CAMERA_TOUCH_I2C == 2))
	PINSEL_ConfigPin (CAMERA_TOUCH_SDA_PORT, CAMERA_TOUCH_SDA_PIN, CAMERA_I2C_FUNNUM);//2
	PINSEL_ConfigPin (CAMERA_TOUCH_SCL_PORT, CAMERA_TOUCH_SCL_PIN, CAMERA_I2C_FUNNUM);//2
	PINSEL_SetOpenDrainMode(CAMERA_TOUCH_SDA_PORT, CAMERA_TOUCH_SDA_PIN, ENABLE);
	PINSEL_SetOpenDrainMode(CAMERA_TOUCH_SCL_PORT, CAMERA_TOUCH_SCL_PIN, ENABLE);
	PINSEL_SetPinMode(CAMERA_TOUCH_SDA_PORT, CAMERA_TOUCH_SDA_PIN, PINSEL_BASICMODE_PLAINOUT);
	PINSEL_SetPinMode(CAMERA_TOUCH_SCL_PORT, CAMERA_TOUCH_SCL_PIN, PINSEL_BASICMODE_PLAINOUT);
#else
	while(1);
#endif	
	//initial gpio
	I2C_Init(CAMERA_TOUCH_I2C,100000);
	//I2C_Cmd(CAMERA_TOUCH_I2C,I2C_MASTER_MODE,ENABLE);
	I2C_Cmd(CAMERA_TOUCH_I2C,I2C_GENERAL_MODE,ENABLE);
	//ov965x_initialize();
	//ov965x_initialize();
	

	
}  


/*********************************************************************//**
 * @auther s.rezaee
 * @brief 	write camera register		that default camera address is SCCB_salve_Address
 * @description write data to camera register
 * @param[in]		reg. selected register for write data
 * @param[in]		data. data that write to register
 * @return 			SUCCESS or ERROR	             
 *                         
 **********************************************************************/
 Status i2c_write(uint8_t slvAdd,unsigned char reg, unsigned char data)   
{   
	I2C_M_SETUP_Type transferMCfg;
	__IO uint8_t Master_Buf[2];
	Master_Buf[0] = reg;
	Master_Buf[1] = data;
	//module reset 
		//SCC_E = L
	//SCCB_salve_Address=0x60;
	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = slvAdd & 0xFE;//0x60;//SCCB_salve_Address;
	transferMCfg.tx_data = Master_Buf;
	transferMCfg.tx_length = 2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 0;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 3;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
	return SUCCESS;
#else
	return I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
#endif
	//SCC_E = H   
  
}   
   
/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/   
 Status i2c_read(uint8_t slvAdd,unsigned char reg, unsigned char *data)   
{   

	I2C_M_SETUP_Type transferMCfg;
	__IO uint8_t Master_Buf[2];
	Master_Buf[0] = reg;
	transferMCfg.sl_addr7bit = slvAdd;//0x60;//SCCB_salve_Address|0x01;
	transferMCfg.tx_data = Master_Buf;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = 0;//data
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 0;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 1;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
#else
	 I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
#endif  
	//module reset 
	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = slvAdd|0x01;//0x61;//SCCB_salve_Address|0x01;
	transferMCfg.tx_data = 0;//Master_Buf;
	transferMCfg.tx_length = 0;
	transferMCfg.rx_data = data;
	transferMCfg.rx_length = 1;
	transferMCfg.retransmissions_max = 1;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 1;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
	return SUCCESS;
#else
	return I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
#endif  
//  return ret;   
} 


/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/   
 Status i2c_readMultiple(uint8_t slvAdd,unsigned char reg, unsigned char *data,uint8_t len)   
{   

	I2C_M_SETUP_Type transferMCfg;
	__IO uint8_t Master_Buf[2];
	Master_Buf[0] = reg;
	transferMCfg.sl_addr7bit = slvAdd;//0x60;//SCCB_salve_Address|0x01;
	transferMCfg.tx_data = Master_Buf;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = data;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 1;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 1;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
#else
	 I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
#endif  
	//module reset 
	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = slvAdd|0x01;//0x61;//SCCB_salve_Address|0x01;
	transferMCfg.tx_data = Master_Buf;
	transferMCfg.tx_length = 0;
	transferMCfg.rx_data = data;
	transferMCfg.rx_length = len;
	transferMCfg.retransmissions_max = 1;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 1;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
	return SUCCESS;
#else
	return I2C_MasterTransferData((en_I2C_unitId)CAMERA_TOUCH_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
#endif  
//  return ret;   
} 