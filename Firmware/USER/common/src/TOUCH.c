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
 #include "touch.h"



static uint16_t ADC_GetVal(uint8_t ch)
{
	uint16_t adc_val;
		// Start conversion
	ADC_StartCmd(LPC_ADC, ADC_START_NOW);
	//Wait conversion complete
	while (!(ADC_ChannelGetStatus(LPC_ADC, ch, ADC_DATA_DONE)));
	adc_val = ADC_ChannelGetData(LPC_ADC, ch);
	return adc_val;
}

static uint16_t TP_GetX(void)
{
	uint16_t val;
	//highe YP
	PINSEL_ConfigPin(TP_YP_PORT, TP_YP_PIN, 0);
	GPIO_SetValue( TP_YP_PORT, TP_YP_PIN );
	//low YM
	GPIO_ClearValue( TP_YM_PORT, TP_YM_PIN ); 
	//HZ XM
	GPIO_ClearValue( TP_XM_PORT, TP_XM_PIN );
	//Analog pin XP
	PINSEL_ConfigPin(TP_XP_PORT, TP_XP_PIN, TP_XP_FUN_NUM);
  PINSEL_SetAnalogPinMode(TP_XP_PORT,TP_XP_PIN,ENABLE);

	ADC_ChannelCmd(LPC_ADC, TP_XP_ADC_CH, ENABLE);	
	//read adc value
	val = ADC_GetVal(TP_XP_ADC_CH);
	ADC_ChannelCmd(LPC_ADC, TP_XP_ADC_CH, DISABLE);
	return val;
}
 
static uint16_t TP_GetY(void)
{
	uint16_t val;
	//highe XP
	PINSEL_ConfigPin(TP_XP_PORT, TP_XP_PIN, 0);
	GPIO_SetValue( TP_XP_PORT, TP_XP_PIN );
	//low XM
	GPIO_ClearValue( TP_XM_PORT, TP_XM_PIN ); 
	//HZ YM
	GPIO_ClearValue( TP_YM_PORT, TP_YM_PIN );
	//Analog pin YP
	PINSEL_ConfigPin(TP_YP_PORT, TP_YP_PIN, TP_YP_FUN_NUM);
  PINSEL_SetAnalogPinMode(TP_YP_PORT,TP_YP_PIN,ENABLE);
	
	ADC_ChannelCmd(LPC_ADC, TP_YP_ADC_CH, ENABLE);	
	//read adc value
	val = ADC_GetVal(TP_YP_ADC_CH);
	ADC_ChannelCmd(LPC_ADC, TP_YP_ADC_CH, DISABLE);
	return val;
}
// void TP_Init(void)
 static void TP_GetAdXY(int *x,int *y)
{
	*y = TP_GetY();
	*x = TP_GetX();
	return;
}
 
 
 Coordinate *ReadTouch(void)
{
  static Coordinate  screen;
  int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
  uint8_t count=0;
  int buffer[2][9]={{0},{0}};  
  do					   
  {		   
    TP_GetAdXY(TP_X,TP_Y);  
	buffer[0][count]=TP_X[0];  
	buffer[1][count]=TP_Y[0];
	count++;  
  }
  while( count<9); 
  if(count==9)   
  {  
    
		temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
		temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
		temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;


		m0=temp[0]-temp[1];
		m1=temp[1]-temp[2];
		m2=temp[2]-temp[0];
			
		m0=m0>0?m0:(-m0);
			m1=m1>0?m1:(-m1);
		m2=m2>0?m2:(-m2);
	
	if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;
	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.x=(temp[0]+temp[2])/2;
	  else 
	    screen.x=(temp[0]+temp[1])/2;	
	}
	else if(m2<m1) 
	  screen.x=(temp[0]+temp[2])/2;
	else 
	  screen.x=(temp[1]+temp[2])/2;

	temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3;
	temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3;
	temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3;
	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];
	m0=m0>0?m0:(-m0);
	m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);
	if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.y=(temp[0]+temp[2])/2;
	  else 
	    screen.y=(temp[0]+temp[1])/2;	
    }
	else if(m2<m1) 
	   screen.y=(temp[0]+temp[2])/2;
	else
	   screen.y=(temp[1]+temp[2])/2;

	return &screen;
  }  
  return 0; 
}


void BSP_TP_Initial(void)
{
	/* Configuration for ADC :
	 *  ADC conversion rate = 400Khz
	 */
	ADC_Init(LPC_ADC, 4000);

	ADC_IntConfig(LPC_ADC, (ADC_TYPE_INT_OPT)TP_YP_ADC_CH, DISABLE);
	ADC_IntConfig(LPC_ADC, (ADC_TYPE_INT_OPT)TP_XP_ADC_CH, DISABLE);

}

