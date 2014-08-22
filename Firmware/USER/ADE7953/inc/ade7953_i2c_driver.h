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

#define MASK_24TO32	0x100


#define		ADE7953_SAGLVL_REG				0x200 
#define		ADE7953_ACCMODE_REG				0x201 
#define		ADE7953_AP_NOLOAD _REG		0x203 
#define		ADE7953_VAR_NOLOAD_REG		0x204 
#define		ADE7953_VA_NOLOAD_REG			0x205 
#define		ADE7953_AVA_REG						0x210 
#define		ADE7953_BVA_REG						0x211 
#define		ADE7953_AWATT_REG					0x212 
#define		ADE7953_BWATT_REG					0x213 
#define		ADE7953_AVAR_REG					0x214 
#define		ADE7953_BVAR_REG					0x215 
#define		ADE7953_IA_REG						0x216 
#define		ADE7953_IB_REG						0x217 
#define		ADE7953_V_REG							0x218 
#define		ADE7953_IRMSA_REG					0x21A 
#define		ADE7953_IRMSB_REG					0x21B 
#define		ADE7953_VRMS_REG					0x21C 
#define		ADE7953_AENERGYA_REG			0x21E 
#define		ADE7953_AENERGYB_REG			0x21F 
#define		ADE7953_RENERGYA_REG			0x220 
#define		ADE7953_RENERGYB_REG			0x221 
#define		ADE7953_APENERGYA_REG			0x222 
#define		ADE7953_APENERGYB_REG			0x223 
#define		ADE7953_OVLVL_REG					0x224 
#define		ADE7953_OILVL_REG					0x225 
#define		ADE7953_VPEAK_REG					0x226 
#define		ADE7953_RSTVPEAK_REG			0x227 
#define		ADE7953_IAPEAK_REG				0x228 
#define		ADE7953_RSTIAPEAK_REG			0x229 
#define		ADE7953_IBPEAK_REG				0x22A 
#define		ADE7953_RSTIBPEAK_REG			0x22B 
#define		ADE7953_IRQENA_REG				0x22C 
#define		ADE7953_IRQSTATA_REG			0x22D 
#define		ADE7953_RSTIRQSTATA_REG		0x22E 
#define		ADE7953_IRQENB_REG				0x22F 
#define		ADE7953_IRQSTATB_REG			0x230 
#define		ADE7953_RSTIRQSTATB_REG		0x231 
//#define		ADE7953_CRC_REG		N/A 
#define		ADE7953_AIGAIN_REG				0x280 
#define		ADE7953_AVGAIN_REG				0x281 
#define		ADE7953_AWGAIN_REG				0x282 
#define		ADE7953_AVARGAIN_REG			0x283 
#define		ADE7953_AVAGAIN_REG				0x284 
#define		ADE7953_Reserved_REG			0x285 
#define		ADE7953_AIRMSOS_REG				0x286 
//#define		ADE7953_Reserved_REG		0x287 
#define		ADE7953_VRMSOS_REG				0x288 
#define		ADE7953_AWATTOS_REG				0x289 
#define		ADE7953_AVAROS_REG				0x28A 
#define		ADE7953_AVAOS_REG					0x28B 
#define		ADE7953_BIGAIN_REG				0x28C 
#define		ADE7953_BVGAIN_REG				0x28D 
#define		ADE7953_BWGAIN_REG				0x28E 
#define		ADE7953_BVARGAIN_REG			0x28F 
#define		ADE7953_BVAGAIN_REG				0x290 
//#define		ADE7953_Reserved_REG		0x291 
#define		ADE7953_BIRMSOS_REG				0x292 
//#define		ADE7953_Reserved_REG		0x293 
//#define		ADE7953_Reserved_REG		0x294 
#define		ADE7953_BWATTOS_REG				0x295 
#define		ADE7953_BVAROS_REG				0x296 
#define		ADE7953_BVAOS_REG					0x297 
#define		ADE7953_LAST_RWDATA_REG		0x2FF


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
void ADE7953_IRQB_Handler(void);
Status ADE7953_i2c_write(uint8_t slvAdd,uint16_t reg, unsigned char *data,uint8_t len);
Status ADE7953_i2c_Read(uint8_t slvAdd,uint16_t reg, unsigned char *data,uint8_t len);
#endif // _I2C_DRIVER_H_
