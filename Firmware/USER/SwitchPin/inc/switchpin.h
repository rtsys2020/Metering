/**********************************************************************
* $Id$		switchpin.h			2013-12-15
*//**
* @file		switchpin.h
* @brief	
* @version	1.0
* @date		15. Decm. 2013
* @author	
**********************************************************************/


#ifndef __SWITCHPIN_H__
#define __SWITCHPIN_H__


/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#include "includes.h"
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

//<e> enable Pheripheral pin Select 0
//<o1>Pheripheral pin Select 0 Port
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>Pheripheral pin Select 0  pin <0-31>
//</e>
#define EN_1 1
#define PHER_SEL_0_PORT 5
#define PHER_SEL_0_PIN	 2
//<e> enable Pheripheral pin Select 1
//<o1>Pheripheral pin Select 1 Port
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>Pheripheral pin Select 1  pin <0-31>
//</e>
#define EN_2 1
 #define PHER_SEL_1_PORT 4
 #define PHER_SEL_1_PIN	 21
//<e> enable Finger And Serial select
//<o1>Finger And Serial select Port
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>Finger And Serial select  pin <0-31>
//</e>
#define EN_3 1
 #define FINGER_SERIAL_SW_PORT 3
 #define FINGER_SERIAL_SW_PIN	22
//<e> enable RS485 Recive Enable
//<o1>RS485 Recive Enable Port
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>RS485 Recive Enable  pin <0-31>
//</e>
#define EN_4 1
 #define RS485_RE_PORT 4
 #define RS485_RE_PIN	 26
//<e> enable RS485 Transmit Enable
//<o1>RS485 Transmit Enable Port
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>RS485 Transmit Enable  pin <0-31>
//</e>
#define EN_5 1
 #define RS485_DE_PORT 4
 #define RS485_DE_PIN	 22

//<e> enable Switch Key Power
//<o1>Switch Key Power Port
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>Switch Key Power  pin <0-31>
//</e>
#define EN_5 1
 #define SWITCH_KEY_POWER_PORT 4
 #define SWITCH_KEY_POWER_PIN	 19

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void SW_RS485FullDE(Bool en);
void SW_RS485HalfRE(Bool en);
void SW_SelFingerToRS485(void);
void SW_SelFingerToRS232(void);
void SW_SelFingerTouC(void);
void SW_SelRS485(void);
void SW_SelRS232(void);
void SW_Init(void);

/*
EOF
*/

#endif
