/**********************************************************************
* $Id$		i2c_driver.h			2013-10
*//**
* @file		i2c_driver.h
* @brief	
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee 
**********************************************************************/



#ifndef _ADE7953_I2C_DRIVER_H_
#define _ADE7953_I2C_DRIVER_H_

#include "includes.h"


Status ADE7953_i2c_Read(uint8_t slvAdd,uint16_t reg, unsigned char *data,uint8_t len) ;
Status ADE7953_i2c_write(uint8_t slvAdd,uint16_t reg, unsigned char *data,uint8_t len)  ;

#define ADE7953_I2C_Read_8_Bit(reg,data)	ADE7953_i2c_Read(0x70,reg,data,1)
#define ADE7953_I2C_Read_16_Bit(reg,data)	ADE7953_i2c_Read(0x70,reg,data,2)
#define ADE7953_I2C_Read_24_Bit(reg,data)	ADE7953_i2c_Read(0x70,reg,data,3)
#define ADE7953_I2C_Read_32_Bit(reg,data)	ADE7953_i2c_Read(0x70,reg,data,4)

#define ADE7953_I2C_Write_8_Bit(reg,data)	ADE7953_i2c_Write(0x70,reg,data,1)
#define ADE7953_I2C_Write_16_Bit(reg,data)	ADE7953_i2c_Write(0x70,reg,data,2)
#define ADE7953_I2C_Write_24_Bit(reg,data)	ADE7953_i2c_Write(0x70,reg,data,3)
#define ADE7953_I2C_Write_32_Bit(reg,data)	ADE7953_i2c_Write(0x70,reg,data,4)


void ADE7953_I2C_Inititial(void) ;
void ADE7953_IRQA_Handler(void);
Status ADE7953_i2c_write(uint8_t slvAdd,uint16_t reg, unsigned char *data,uint8_t len);
Status ADE7953_i2c_Read(uint8_t slvAdd,uint16_t reg, unsigned char *data,uint8_t len);
#endif // _I2C_DRIVER_H_
