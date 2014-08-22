/**********************************************************************
* $Id$		i2c_driver.c			2013-10
*//**
* @file		i2c_driver.c
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/



#include "inc\ade7953_i2c_driver.h"
#include "user_bsp.h"
#include "irqhandlertask.h"
#include "EXTIT_Handeler.h"
#include "inc\ade7953_spi_driver.h"

__IO complete;

void ADE7953_Reset(void);

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
	I2C_MasterHandler((en_I2C_unitId)ADE_7953_I2C);
	if (I2C_MasterTransferComplete((en_I2C_unitId)ADE_7953_I2C)){
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

void ADE7953_I2C_Inititial(void)   
{   
	EINT_init_t eint_irqa;
	static IRQ_msg_t ade_irqa;
	EXTI_InitTypeDef exti_cfg;
	uint32_t data;
	
	exti_cfg.EXTI_Line = EXTI_EINT0;
	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	exti_cfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
	
	ade_irqa.src = ADE7953_IRQA_SRC;
	ade_irqa.fun = ADE7953_IRQA_Handler;
	
	eint_irqa.port = ADE7953_IRQA_PORT;
	eint_irqa.pin = ADE7953_IRQA_PIN;
	eint_irqa.func_num = ADE7953_IRQA_FUNC_NUM;
	eint_irqa.eint_num = 0;
	eint_irqa.irq_msg = &ade_irqa;
	eint_irqa.exti_cfg = &exti_cfg;
	
	
#if ((ADE_7953_I2C == 0))
	PINSEL_ConfigPin (ADE_7953_I2C_SDA_PORT, ADE_7953_I2C_SDA_PIN, ADE_7953_I2C_FUNNUM);
	PINSEL_ConfigPin (ADE_7953_I2C_SCL_PORT, ADE_7953_I2C_SCL_PIN, ADE_7953_I2C_FUNNUM);
	PINSEL_SetPinMode(ADE_7953_I2C_SDA_PORT,ADE_7953_I2C_SDA_PIN,IOCON_MODE_PLAIN);
	PINSEL_SetPinMode(ADE_7953_I2C_SCL_PORT,ADE_7953_I2C_SCL_PIN,IOCON_MODE_PLAIN);

#elif ((ADE_7953_I2C == 1))
	PINSEL_ConfigPin (ADE_7953_I2C_SDA_PORT, ADE_7953_I2C_SDA_PIN, ADE_7953_I2C_FUNNUM);//3
	PINSEL_ConfigPin (ADE_7953_I2C_SCL_PORT, ADE_7953_I2C_SCL_PIN, ADE_7953_I2C_FUNNUM);//3
	PINSEL_SetOpenDrainMode(ADE_7953_I2C_SDA_PORT, ADE_7953_I2C_SDA_PIN, ENABLE);
	PINSEL_SetOpenDrainMode(ADE_7953_I2C_SCL_PORT, ADE_7953_I2C_SCL_PIN, ENABLE);
	PINSEL_SetPinMode(ADE_7953_I2C_SDA_PORT, ADE_7953_I2C_SDA_PIN, PINSEL_BASICMODE_PLAINOUT);
	PINSEL_SetPinMode(ADE_7953_I2C_SCL_PORT, ADE_7953_I2C_SCL_PIN, PINSEL_BASICMODE_PLAINOUT);
#elif ((ADE_7953_I2C == 2))
	PINSEL_ConfigPin (ADE_7953_I2C_SDA_PORT, ADE_7953_I2C_SDA_PIN, CAMERA_I2C_FUNNUM);//2
	PINSEL_ConfigPin (ADE_7953_I2C_SCL_PORT, ADE_7953_I2C_SCL_PIN, CAMERA_I2C_FUNNUM);//2
	PINSEL_SetOpenDrainMode(ADE_7953_I2C_SDA_PORT, ADE_7953_I2C_SDA_PIN, ENABLE);
	PINSEL_SetOpenDrainMode(ADE_7953_I2C_SCL_PORT, ADE_7953_I2C_SCL_PIN, ENABLE);
	PINSEL_SetPinMode(ADE_7953_I2C_SDA_PORT, ADE_7953_I2C_SDA_PIN, PINSEL_BASICMODE_PLAINOUT);
	PINSEL_SetPinMode(ADE_7953_I2C_SCL_PORT, ADE_7953_I2C_SCL_PIN, PINSEL_BASICMODE_PLAINOUT);
#else
	while(1);
#endif	
	//initial gpio
	I2C_Init(ADE_7953_I2C,100000);
	//I2C_Cmd(ADE_7953_I2C_I2C,I2C_MASTER_MODE,ENABLE);
	I2C_Cmd(ADE_7953_I2C,I2C_GENERAL_MODE,ENABLE);
	
	ADE7953_Reset();
	ADE7953_I2C_Read_24_Bit(ADE7953_IRQENA_REG,(uint8_t*)&data);//IRQENA
	ADE7953_I2C_Read_24_Bit(ADE7953_IRQSTATA_REG,(uint8_t*)&data);//IRQSTATA
	ADE7953_I2C_Read_24_Bit(ADE7953_RSTIRQSTATA_REG,(uint8_t*)&data);//RSTIRQSTATA

	ADE7953_I2C_Read_24_Bit(ADE7953_IRQENB_REG     ,(uint8_t*)&data);//IRQENA
	ADE7953_I2C_Read_24_Bit(ADE7953_IRQSTATB_REG   ,(uint8_t*)&data);//IRQSTATA
	ADE7953_I2C_Read_24_Bit(ADE7953_RSTIRQSTATB_REG,(uint8_t*)&data);//RSTIRQSTATA
	
	EINT_BSP_Init(&eint_irqa);
	
	exti_cfg.EXTI_Line = EXTI_EINT1;
	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	exti_cfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
	
	ade_irqa.src = ADE7953_IRQB_SRC;
	ade_irqa.fun = ADE7953_IRQB_Handler;
	eint_irqa.port = ADE7953_IRQB_PORT;
	eint_irqa.pin = ADE7953_IRQB_PIN;
	eint_irqa.func_num = ADE7953_IRQB_FUNC_NUM;
	eint_irqa.eint_num = 1;
	eint_irqa.irq_msg = &ade_irqa;
	eint_irqa.exti_cfg = &exti_cfg;
	EINT_BSP_Init(&eint_irqa);
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
 Status ADE7953_i2c_write(uint8_t slvAdd,uint16_t reg, uint8_t *data,uint8_t len)   
{   
	I2C_M_SETUP_Type transferMCfg;
	__IO uint8_t Master_Buf[8],i;
	
	Master_Buf[0] = reg>>8;
	Master_Buf[1] = reg;
	for(i=0;i<len ;i++)
		Master_Buf[i+2] = data[i];
	
	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = slvAdd & 0xFE;//0x60;//SCCB_salve_Address;
	transferMCfg.tx_data = Master_Buf;
	transferMCfg.tx_length = len+2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 0;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 3;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)ADE_7953_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
	return SUCCESS;
#else
	return I2C_MasterTransferData((en_I2C_unitId)ADE_7953_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
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
 Status ADE7953_i2c_Read(uint8_t slvAdd,uint16_t reg, uint8_t *data,uint8_t len)   
{   

	I2C_M_SETUP_Type transferMCfg;
	__IO uint8_t Master_Buf[2];
	Master_Buf[0] = reg>>8;
	Master_Buf[1] = reg;
	transferMCfg.sl_addr7bit = slvAdd;//0x60;//SCCB_salve_Address|0x01;
	transferMCfg.tx_data = Master_Buf;
	transferMCfg.tx_length = 2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 1;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 1;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)ADE_7953_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
#else
	 I2C_MasterTransferData((en_I2C_unitId)ADE_7953_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
#endif  
	//module reset 
	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = slvAdd|0x01;//0x61;//SCCB_salve_Address|0x01;
	transferMCfg.tx_data = NULL;
	transferMCfg.tx_length = 0;
	transferMCfg.rx_data = data;
	transferMCfg.rx_length = len;
	transferMCfg.retransmissions_max = 1;
	transferMCfg.tx_count = 0;
	transferMCfg.rx_count = 0;
	transferMCfg.retransmissions_count = 1;	
#if (I2CDEV_TRANSFER_POLLING == 0)
	complete = FALSE;
	I2C_MasterTransferData((en_I2C_unitId)ADE_7953_I2C, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	while(!complete) ;
	return SUCCESS;
#else
	return I2C_MasterTransferData((en_I2C_unitId)ADE_7953_I2C, &transferMCfg, I2C_TRANSFER_POLLING);
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
 **********************************************************************/   
void ADE7953_IRQA_Handler(void)
{
	uint32_t irqena,irqstat,rstirqstat;
	ADE7953_I2C_Read_24_Bit(ADE7953_IRQENA_REG,(uint8_t*)&irqena);//IRQENA
	ADE7953_I2C_Read_24_Bit(ADE7953_IRQSTATA_REG,(uint8_t*)&irqstat);//IRQSTATA
	ADE7953_I2C_Read_24_Bit(ADE7953_RSTIRQSTATA_REG,(uint8_t*)&rstirqstat);//RSTIRQSTATA
	
	//add a switch case for test flag
}

/*********************************************************************//**
 * @auther 
 * @brief 			
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				                            
 **********************************************************************/   
void ADE7953_IRQB_Handler(void)
{
	uint32_t irqen,irqstat,rstirqstat;
	ADE7953_I2C_Read_24_Bit(ADE7953_IRQENB_REG     ,(uint8_t*)&irqen);//IRQENA
	ADE7953_I2C_Read_24_Bit(ADE7953_IRQSTATB_REG   ,(uint8_t*)&irqstat);//IRQSTATA
	ADE7953_I2C_Read_24_Bit(ADE7953_RSTIRQSTATB_REG,(uint8_t*)&rstirqstat);//RSTIRQSTATA
	
	//add a switch case for test flag
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
void ADE7953_Reset(void)
{
	int i;
	
	ADE7953_RESET_LOW();
	for(i=0;i<0xa0000;i++);
	ADE7953_RESET_HIGH();
}