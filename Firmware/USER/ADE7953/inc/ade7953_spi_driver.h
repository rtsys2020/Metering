/**********************************************************************
* $Id$		ade7953.h			2013-10
*//**
* @file		ade7953.h
* @brief	Use as Template
*			
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee
**********************************************************************/
#ifndef ADE7953_H
#define ADE7953_H
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

#include "includes.h"


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               DEFINIATION
*********************************************************************************************************
*/
// Flash pin	Config
#define ADE7953_EN	1
#define ADE7953_SSP_NUM			1


#define ADE7953_MOSI_PORT_NUM			0
#define ADE7953_MOSI_PIN_NUM			9
#define ADE7953_MOSI_FUN_NUM			2

#define ADE7953_MISO_PORT_NUM			0
#define ADE7953_MISO_PIN_NUM			8
#define ADE7953_MISO_FUN_NUM			2

#define ADE7953_SCK_PORT_NUM			0
#define ADE7953_SCK_PIN_NUM				7
#define ADE7953_SCK_FUN_NUM				2

#define ADE7953_CS_PORT		4
#define ADE7953_CS_PIN		9

#define ADE7953_RESET_PORT	2
#define ADE7953_RESET_PIN	17

#if (ADE7953_SSP_NUM == 0)
#define ADE7953_SSP	LPC_SSP0
#elif (ADE7953_SSP_NUM == 1)
#define ADE7953_SSP	LPC_SSP1
#elif (ADE7953_SSP_NUM == 2)
#define ADE7953_SSP	LPC_SSP2
#endif

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/
#define ADE7953_CS_LOW()    GPIO_ClearValue( ADE7953_CS_PORT, (1<<ADE7953_CS_PIN) )  
#define ADE7953_CS_HIGH()   GPIO_SetValue( ADE7953_CS_PORT, (1<<ADE7953_CS_PIN) ) 

#define ADE7953_RESET_LOW()    GPIO_ClearValue( ADE7953_RESET_PORT, (1<<ADE7953_RESET_PIN) )  
#define ADE7953_RESET_HIGH()   GPIO_SetValue( ADE7953_RESET_PORT, (1<<ADE7953_RESET_PIN) ) 

/*
*********************************************************************************************************
*                                           DEFINITIONS
*********************************************************************************************************
*/
/*
IRQENB (Address 0x22F and 
Address 0x32F), the status register, IRQSTATB (Address 0x230 
and Address 0x330), and the reset status register, RSTIRQSTATB
(Address 0x231 and Address 0x331). 

, IRQENA 
(Address 0x22C and Address 0x32C), the status register, 
IRQSTATA (Address 0x22D and Address 0x32D), and the 
reset status register, RSTIRQSTATA (Address 0x22E and 
Address 0x32E). 
#define ADE_7953_IRQENA_R	0x32c
typedef enum
{
IRQA_EN_AEHFA_BIT ,
IRQA_EN_VAREHFA_BIT, 
IRQA_EN_VAEHFA_BIT ,
IRQA_EN_AEOFA_BIT ,
IRQA_EN_VAREOFA_BIT ,
IRQA_EN_VAEOFA_BIT ,
IRQA_EN_AP_NOLOADA_BIT ,
IRQA_EN_VAR_NOLOADA_BIT,
IRQA_EN_VA_NOLOADA_BIT ,
IRQA_EN_APSIGN_A_BIT ,
IRQA_EN_VARSIGN_A_BIT ,
IRQA_EN_ZXTO_IA_BIT ,
IRQA_EN_ZXIA_BIT ,
IRQA_EN_OIA_BIT ,
IRQA_EN_ZXTO_BIT ,
IRQA_EN_ZXV_BIT ,
IRQA_EN_OV_BIT ,
IRQA_EN_WSMP_BIT, 
IRQA_EN_CYCEND_BIT, 
IRQA_EN_Sag_BIT ,
IRQA_EN_Reset_BIT, 
IRQA_EN_CRC_BIT ,
}IRQA_ENBit_t;
*/
/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void ADE7953_SPI_Init(void);

uint16_t ADE7953_SPI_ReadReg16(uint16_t reg);

/*
EOF
*/
#endif

