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
#include "bsp.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

// <e> ADC Channel0 Enable
// </e>
#define ADC_IN0_EN 1
// <e> ADC Channel1 Enable
// </e>
#define ADC_IN1_EN 0
// <e> ADC Channel2 Enable
// </e>
#define ADC_IN2_EN 1
// <e> ADC Channel3 Enable
// </e>
#define ADC_IN3_EN 0
// <e> ADC Channel4 Enable
// </e>
#define ADC_IN4_EN 0
// <e> ADC Channel5 Enable
// </e>
#define ADC_IN5_EN 0
// <e> ADC Channel6 Enable
// </e>
#define ADC_IN6_EN 0
// <e> ADC Channel7 Enable
// </e>
#define ADC_IN7_EN 0
// <o> ADC Sampling Frequency <100-4000>
#define ADC_FREQ	400
// <o> Number Of Sample Per Channel <1-10>
#define NUM_OF_SAMPLE	3
#define ADC_DMA_EN		0
/** DMA size of transfer */

#if (ADC_DMA_EN == 1 )
extern uint32_t ADC_buf[];		
// Terminal Counter flag for Channel 0
extern __IO uint32_t DMA_ADC_TC;
// Error Counter flag for Channel 0
extern __IO uint32_t DMA_ADC_Err;
#endif /*__DMA_USED__*/
/************************** PRIVATE VARIABLES *************************/




void BSP_ADC_Init(void);
/*
EOF
*/

