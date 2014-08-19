/**********************************************************************
* $Id$		template.c			2013-10
*//**
* @file		rs232.c
* @brief	Use for rs232 functionality
*			
* @version	1.0
* @date		23. decm. 2013
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

#include "buzzer.h"

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
uint16_t melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_A6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_A6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 
 /*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/


void BSP_Buzzer_Init(void)
{
	TIM_MATCHCFG_Type tim_match_cfg;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	
	PINSEL_ConfigPin(BUZZER_PORT,BUZZER_PIN_MATCH,BUZZER_FUN_NUM);
		// Initialize timer 0, prescale count time of 100uS
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL;//TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 99;
	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(BUZZER_TIMER, TIM_TIMER_MODE, &TIM_ConfigStruct);
	tim_match_cfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	tim_match_cfg.IntOnMatch = 0;
	tim_match_cfg.MatchChannel = 0;//ch0
	tim_match_cfg.MatchValue = 1;//BUZZER_VAL;
	tim_match_cfg.ResetOnMatch = 1;
	tim_match_cfg.StopOnMatch = 0;
	TIM_ConfigMatch(BUZZER_TIMER,  &tim_match_cfg);
	TIM_Cmd(BUZZER_TIMER,ENABLE);
	
}

void BuzzerPly(uint32_t tone,uint16_t dly)
{
//	TIM_MATCHCFG_Type tim_match_cfg;
	uint32_t match;
	if(tone != 0)
	{
		match = (600000)/(tone)-1;
	}
	else
	{
		match = 0;
	}
	BUZZER_TIMER->MR0 = match;
	//delay_ms(1);
	BUZZER_TIMER->TCR = 0x03;
	delay_ms(1);
	BUZZER_TIMER->TCR = 0x01;
	//TIM_Cmd(BUZZER_TIMER,ENABLE);
	delay_ms(dly);	
}

void BuzzerEnable(void)
{
	BUZZER_TIMER->TCR = 0x00000003;
}

void BuzzerDisable(void)
{
	BUZZER_TIMER->TCR = 0x00000000;
}

void playMusic(void)
{
	uint16_t i;
	for(i=0;i<20;i++)
	{
		BuzzerPly(melody[i],300);
	}
}


