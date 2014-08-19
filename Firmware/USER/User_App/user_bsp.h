/**********************************************************************
* $Id$		user_bsp.h		
*//**
* @file		user_bsp.h
* @brief	Use as Template
*			
* @version	1.0
* @date		
* @author	s.rezaee 
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

#include "includes.h"
#include "app_cfg.h"

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
#define _USB1_HOST_		0

#define _USB2_HOST_		0
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

// Convert bit-band address and bit number into
// bit-band alias address
#define BIT BAND(addr,bitnum) ((addr & 0xF0000000)+0x2000000+((addr&0xFFFFF)<<5)+(bitnum <<2))
// Convert the address as a pointer
#define MEM_ADDR(addr) *((volatile unsigned long *) (addr))

//__attribute__((bit band))
#define CARD_READER_ON_OFF_PORT		4
#define	CARD_READER_ON_OFF_PIN		16

// <e> Hardware Intrrupt Priority
//<o1>GPIO IRQ Priority<0-2048>
//</e>
#define HARDWARE_IRQ_EN	1
#define GPIO_IRQ_PRIORITY 	1





#define SCCB_salve_Address	0x70



//<e> I2C for camera and Touch key
//<i> p0.27 and p0.28 open drain fast mode (400kh) and standard mode (100KH)
//<i> p5.2 and p5.3  support fast mode (1MH) IOCON must be set to 0x10
//<i>  On reset, all I2C interfaces are enabled (PCI2C0/1/2 = 1)
//<o1>Cammera SDA pin <0-31>
//<o2>Cammera SDA Port 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o3>Cammera SCL pin <0-31>
//<o4>Cammera SCL Port 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o5.0>I2C Polling Enable
//<o6>Camera I2C number <0-2>
//<o7>Camera I2C Function number of Port <0-6> 
//<o8>Touch Key Change Port 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o9>Touch Key Change pin <0-31>
//</e>
#define ADE_7953_I2C_EN	1
#define ADE_7953_I2C_SDA_PIN	14
#define ADE_7953_I2C_SDA_PORT	2
#define ADE_7953_I2C_SCL_PIN	15	
#define ADE_7953_I2C_SCL_PORT	2
#define I2CDEV_TRANSFER_POLLING 1
#define ADE_7953_I2C	1
#define ADE_7953_I2C_FUNNUM	2	




// <e> MMC Card Enable
//<o1>MMC Card CLK PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>MMC Card CLK Pin <0-31>
//<o3>MMC Card CLK Function Number /////
//<o4>MMC Card CMD PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o5>MMC Card CMD Pin <0-31>
//<o6>MMC Card CMD Function Number /////

//<o7>MMC Card PWR PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o8>MMC Card PWR Pin <0-31>
//<o9>MMC Card PWR Function Number /////

//<o10>MMC Card Data_0 PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o11>MMC Card Data_0 Pin <0-31>
//<o12>MMC Card Data_0 Function Number /////

//<o13>MMC Card Data_1 PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o14>MMC Card Data_1 Pin <0-31>
//<o15>MMC Card Data_1 Function Number /////

//<o16>MMC Card Data_2 PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o17>MMC Card Data_2 Pin <0-31>
//<o18>MMC Card Data_2 Function Number /////

//<o19>MMC Card Data_3 PORT Number 
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o20>MMC Card Data_3 Pin <0-31>
//<o21>MMC Card Data_3 Function Number /////

//</e>
#define MMC_ENABLE	1

#define MMC_CLK_PORT_NUM	1
#define MMC_CLK_PIN_NUM		2
#define MMC_CLK_FUNC_NUM	2

#define MMC_CMD_PORT_NUM	1
#define MMC_CMD_PIN_NUM		3
#define MMC_CMD_FUNC_NUM	2

#define MMC_PWR_PORT_NUM	1
#define MMC_PWR_PIN_NUM		5
#define MMC_PWR_FUNC_NUM	2

#define MMC_DATA0_PORT_NUM	1
#define MMC_DATA0_PIN_NUM		6
#define MMC_DATA0_FUNC_NUM	2

#define MMC_DATA1_PORT_NUM	1
#define MMC_DATA1_PIN_NUM		7
#define MMC_DATA1_FUNC_NUM	2

#define MMC_DATA2_PORT_NUM	1
#define MMC_DATA2_PIN_NUM		11
#define MMC_DATA2_FUNC_NUM	2

#define MMC_DATA3_PORT_NUM	1
#define MMC_DATA3_PIN_NUM		12
#define MMC_DATA3_FUNC_NUM	2


// Flash pin	Config
#define RTC_FLASH_EN	1
#define RTC_FLASH_SSP_NUM			0

#define RTC_CS_PORT_NUM			3
#define RTC_CS_PIN_NUM			24


#define RTC_FLASH_MOSI_PORT_NUM			2
#define RTC_FLASH_MOSI_PIN_NUM			27
#define RTC_FLASH_MOSI_FUN_NUM			2

#define RTC_FLASH_MISO_PORT_NUM			2
#define RTC_FLASH_MISO_PIN_NUM			26
#define RTC_FLASH_MISO_FUN_NUM			2

#define RTC_FLASH_SCK_PORT_NUM			2
#define RTC_FLASH_SCK_PIN_NUM			22
#define RTC_FLASH_SCK_FUN_NUM			2

#define FLASH_CS_PORT		2
#define FLASH_CS_PIN		23

#define FLASH_WP_PORT	2
#define FLASH_WP_PIN	25

#define FLASH_RESET_PORT	2
#define FLASH_RESET_PIN	24

#if (RTC_FLASH_SSP_NUM == 0)
#define RTC_FLASH_SSP	LPC_SSP0
#elif (RTC_FLASH_SSP_NUM == 1)
#define RTC_FLASH_SSP	LPC_SSP1
#elif (RTC_FLASH_SSP_NUM == 2)
#define RTC_FLASH_SSP	LPC_SSP2
#endif



//<e> LED On The Core
//<o1>LED1 PORT  
//	<0=> LPC_GPIO0
//	<1=> LPC_GPIO1
//	<2=> LPC_GPIO2
//	<3=> LPC_GPIO3
//	<4=> LPC_GPIO4
//	<5=> LPC_GPIO5
//<o2>LED1 PIN  <0-31>
//</e>
#define LED1_ENABLE	1
#define LED1_CORE_PORT	0
#define LED1_CORE_PIN	15
//<e> External SDRAM Enable
// <o1> SDRAM Base Address <0-0xD0000000>
// <o2> SDRAM Size <0-0x10000000>
//</e>
#define SDRAM_EN	1
#define SDRAM_BASE_ADDR		0xA0000000
#define SDRAM_SIZE	      0x02000000   /* 32M 256Mbit 1024*1024*32 byte */ 


// <e> enable Buzzer
// 	<o1> Initialize Buzzer Timer Number <0-4>
// 	<o2> Initialize Buzzer Match Port <0-5>
// 	<o3> Initialize Buzzer Match pin connect <0-31>
// 	<o4> Initialize Buzzer Match pin Function Number <0-4>
// 	<o5> Initialize Buzzer Frequency 
//		<10=> 10 Hz
//		<100=> 100 Hz
//		<1000=> 1000 Hz
//		<3000=> 3000 Hz
// </e>

#define BUZZER_EN		0
#define BUZZER_TIMER_NUM	1
#define BUZZER_PORT	3
#define BUZZER_PIN_MATCH 29
#define BUZZER_FUN_NUM	2
#define BUZZER_VAL	1000


#if BUZZER_TIMER_NUM == 0
#define BUZZER_TIMER LPC_TIM0
#elif BUZZER_TIMER_NUM== 1
#define BUZZER_TIMER LPC_TIM1
#elif BUZZER_TIMER_NUM == 2
#define BUZZER_TIMER LPC_TIM2
#else
#define BUZZER_TIMER LPC_TIM3
#endif



/*
//<e> USB Configuration
//	<i>  enabling hardware Clock 
// <h>  OTG Clock control Control
//		<o1.0>	HOST_CLK_EN
//					<0=>	 Disable
//					<1=>	 Enable
//		<o1.1>	DEV_CLK_EN
//					<0=>	 Disable
//					<1=>	 Enable
//		<o1.2>	I2C_CLK_EN
//					<0=>	 Disable
//					<1=>	 Enable
//		<o1.3>	OTG_CLK_EN
//					<0=>	 Disable
//					<1=>	 Enable
//		<o1.4>	AHB_CLK_EN
//					<0=>	 Disable
//					<1=>	 Enable
//</h>
// <h>  OTG Status Control
//	<i>  enabling hardware tracking during the HNP hand over 
//	<i>sequence, controlling the OTG timer, monitoring the timer count, and controlling the 
//	<i>functions mapped to port U1 and U2
//		<o2.0..1>	PORT_FUNC
//					<0=>	U1 = device (OTG), U2 = host
//					<1=>	U1 = host (OTG), U2 = host
//					<2=>	Reserved
//					<3=>	U1 = host, U2 = device	
//		<o2.2..3>	TMR_SCALE
//					<0=>	10us (100 KHz)
//					<1=>	100us (1000 KHz)
//					<2=>	1000us (10000 KHz)
//					<3=>	Reserved	
//		<o2.4>	Timer mode selection
//					<0=>	 monoshot
//					<1=>	 free running
//		<o2.5>	Timer enable
//					<1=>	 set, TMR_CNT increments
//					<0=>	 cleared, TMR_CNT is reset to 0
//		<o2.6>	Timer reset
//					<1=>	  resets TMR_CNT to 0
//					<0=>	  
//		<o2.8>	Enable HNP tracking for B-device (peripheral)
//					<0=>	 HNP_SUCCESS
//					<1=>	 HNP_FAILURE
//		<o2.9>	Enable HNP tracking for A-device (host)
//					<1=>	 HNP_SUCCESS
//					<0=>	 HNP_FAILURE
//		<o2.10>	PU_REMOVED
//					<1=>	 HNP_SUCCESS
//					<0=>	 HNP_FAILURE
//		<o2.16..31>	Current timer count value.<0-62535>
// </h>	
// <h>  USB HCCommandStatus
//	<i>  enabling hardware Clock 
//		<o3>	CommandStatus
//					<0x00000001=>	 OR_CMD_STATUS_HCR
//					<0x00000002=>	 OR_CMD_STATUS_CLF
//					<0x00000004=>	 OR_CMD_STATUS_BLF
// </h>	
// </e>	
*/
#define USB_HOST_EN 1
#define OTG_CLOCK_CTL	0x00000019//0x00000019
#define OTG_STATUS_CTL	0x0001//0x1002
#define USB_HOST_CMD_STATUS	0x00000002 //0x00000001

//#define USB_HOST_EN	1




/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

//#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_DISABLED
//#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED





void User_BSP_Init (void);
void GPIO_IntCmdDisable(uint8_t portNum, uint32_t pinNum, uint8_t edgeState);

void USB_HostPortCfg(void);
/*
EOF
*/

