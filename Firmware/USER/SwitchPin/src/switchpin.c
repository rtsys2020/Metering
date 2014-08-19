/**********************************************************************
* $Id$		switchpin.c				2010-06-04
*//**
* @file		switchpin.c
* @brief	
* @version	2.0
* @date		04. June. 2010
* @author	
**********************************************************************/


#include "switchpin.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */

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
void SW_Init(void)
{
	PINSEL_ConfigPin(PHER_SEL_0_PORT,PHER_SEL_0_PIN,0);
	GPIO_SetDir(PHER_SEL_0_PORT,1<<PHER_SEL_0_PIN,1);
	
	PINSEL_ConfigPin(PHER_SEL_1_PORT,PHER_SEL_1_PIN,0);
	GPIO_SetDir(PHER_SEL_1_PORT,1<<PHER_SEL_1_PIN,1);
	
	PINSEL_ConfigPin(FINGER_SERIAL_SW_PORT,FINGER_SERIAL_SW_PIN,0);
	GPIO_SetDir(FINGER_SERIAL_SW_PORT,1<<FINGER_SERIAL_SW_PIN,1);
	
	PINSEL_ConfigPin(5,0,0);
	GPIO_SetDir(5,1<<0,1);
		//switch on/off enable
	PINSEL_ConfigPin (SWITCH_KEY_POWER_PORT, SWITCH_KEY_POWER_PIN, 0);
	PINSEL_SetPinMode(SWITCH_KEY_POWER_PORT,SWITCH_KEY_POWER_PIN,IOCON_MODE_PLAIN);
	PINSEL_SetOpenDrainMode(SWITCH_KEY_POWER_PORT,SWITCH_KEY_POWER_PIN,ENABLE);
	GPIO_SetDir(SWITCH_KEY_POWER_PORT,1<<SWITCH_KEY_POWER_PIN,0);	//enable switch Power
	
	return;
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
void SW_SelRS232(void)
{
	//peripheral set to 0b01
	GPIO_SetValue(PHER_SEL_0_PORT,1<<PHER_SEL_0_PIN);
	GPIO_ClearValue(PHER_SEL_1_PORT,1<<PHER_SEL_1_PIN);
	//FingerModule_SerialPort_Switch sel=1
	GPIO_SetValue(FINGER_SERIAL_SW_PORT,1<<FINGER_SERIAL_SW_PIN);
	
	return;
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
void SW_SelRS485(void)
{
	//peripheral set to 0b01
	GPIO_ClearValue(PHER_SEL_0_PORT,1<<PHER_SEL_0_PIN);
	GPIO_ClearValue(PHER_SEL_1_PORT,1<<PHER_SEL_1_PIN);
	//FingerModule_SerialPort_Switch sel=1
	GPIO_SetValue(FINGER_SERIAL_SW_PORT,1<<FINGER_SERIAL_SW_PIN);
	
	return;
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
void SW_SelFingerTouC(void)
{
	//peripheral set to 0b01
//	GPIO_SetValue(PHER_SEL_0_PORT,1<<PHER_SEL_0_PIN);
//	GPIO_ClearValue(PHER_SEL_1_PORT,1<<PHER_SEL_1_PIN);
	//FingerModule_SerialPort_Switch sel=1
	GPIO_SetValue(FINGER_SERIAL_SW_PORT,1<<FINGER_SERIAL_SW_PIN);
	
	return;
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
void SW_SelFingerToRS232(void)
{
	//peripheral set to 0b01
	GPIO_SetValue(PHER_SEL_0_PORT,1<<PHER_SEL_0_PIN);
	GPIO_ClearValue(PHER_SEL_1_PORT,1<<PHER_SEL_1_PIN);
	//FingerModule_SerialPort_Switch sel=1
	GPIO_ClearValue(FINGER_SERIAL_SW_PORT,1<<FINGER_SERIAL_SW_PIN);
	
	return;
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
void SW_SelFingerToRS485(void)
{
	//peripheral set to 0b01
	GPIO_ClearValue(PHER_SEL_0_PORT,1<<PHER_SEL_0_PIN);
	GPIO_ClearValue(PHER_SEL_1_PORT,1<<PHER_SEL_1_PIN);
	//FingerModule_SerialPort_Switch sel=1
	GPIO_ClearValue(FINGER_SERIAL_SW_PORT,1<<FINGER_SERIAL_SW_PIN);
	
	return;
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
void SW_RS485HalfRE(Bool en)
{
	//peripheral set to 0b01
	if(en)
		GPIO_ClearValue(RS485_RE_PORT,1<<RS485_RE_PIN);
	else
		GPIO_SetValue(RS485_RE_PORT,1<<RS485_RE_PIN);
	return;
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
void SW_RS485FullDE(Bool en)
{
	//peripheral set to 0b01
	if(en)
		GPIO_SetValue(RS485_DE_PORT,1<<RS485_DE_PIN);
	else
		GPIO_ClearValue(RS485_DE_PORT,1<<RS485_DE_PIN);
	return;
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
void SW_AudioMute(Bool en)
{
	//peripheral set to 0b01
	if(en)
		GPIO_SetValue(5,1<<0);
	else
		GPIO_ClearValue(5,1<<0);
	return;
}
/**
 * @}
*/
