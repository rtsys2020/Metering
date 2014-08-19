/**********************************************************************
* $Id$		rs232.h			2013-06-21
*//**
* @file		rs232.h
* @brief	Contains rs232 protocol 
*			
* @version	1.0
* @date		21. Decem. 2011
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

#ifndef BUZZER_H
#define BUZZER_H
#include "bsp.h"
#include "includes.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
//<h>
// <i> driver for Buzzer in pulse width modulation
//</h>
/** @defgroup UART_Dma		UART DMA
 * @ingroup UART_Examples
 * @{
 */
typedef enum{
NOTE_A0	= 10, 
NOTE_A3 = 110,
NOTE_A6 = 880,
NOTE_B0 = 20,
NOTE_B3 = 123,
NOTE_B6 = 988,
NOTE_C0 = 16 ,
NOTE_C3 = 131 ,
NOTE_C6 = 1047,
NOTE_D0 = 18 ,
NOTE_D3 = 147 ,
NOTE_D6 = 1175,
NOTE_E0 = 21 ,
NOTE_E3 = 165 ,
NOTE_E6 = 1319,
NOTE_F0 = 22 ,
NOTE_F3 = 175 ,
NOTE_F6 = 1397,
NOTE_G0 = 25 ,
NOTE_G3 = 196 ,
NOTE_G6 = 1568,
NOTE_A1 = 28 ,
NOTE_A4 = 220 ,
NOTE_A7 = 1760,
NOTE_B1 = 31 ,
NOTE_B4 = 247 ,
NOTE_B7 = 1976,
NOTE_C1 = 33 ,
NOTE_C4 = 262 ,
NOTE_C7 = 2093,
NOTE_D1 = 37 ,
NOTE_D4 = 294 ,
NOTE_D7 = 2349,
NOTE_E1 = 41 ,
NOTE_E4 = 330 ,
NOTE_E7 = 2637,
NOTE_F1 = 44 ,
NOTE_F4 = 349 ,
NOTE_F7 = 2794,
NOTE_G1 = 49 ,
NOTE_G4 = 392 ,
NOTE_G7 = 3136,
NOTE_A2 = 55 ,
NOTE_A5 = 440 ,
NOTE_A8 = 3520,
NOTE_B2 = 62 ,
NOTE_B5 = 494 ,
NOTE_B8 = 3951,
NOTE_C2 = 65 ,
NOTE_C5 = 523 ,
NOTE_C8 = 4186,
NOTE_D2 = 73 ,
NOTE_D5 = 587 ,
NOTE_D8 = 4699,
NOTE_E2 = 82 ,
NOTE_E5 = 659 ,
NOTE_E8 = 5274,
NOTE_F2 = 87, 
NOTE_F5 = 698 ,
NOTE_F8 = 5588,
NOTE_G2 = 98 ,
NOTE_G5 = 784, 
NOTE_G8 = 6272,
}NOTE_t;
/**,************************ PRIVATE DEFINITIONS *************************/


// Receive buffer

/************************** PRIVATE VARIABLES *************************/
 
 
/************************** PRIVATE FUNCTIONS *************************/

void BSP_Buzzer_Init(void);
void BuzzerPly(uint32_t NOTE,uint16_t dly);
void BuzzerDisable(void);
void BuzzerEnable(void);
/*
EOF
*/
#endif
