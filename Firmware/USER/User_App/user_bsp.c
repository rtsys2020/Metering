/**********************************************************************
* $Id$		user_bsp.c			
*//**
* @file		user_bsp.c
* @brief	
*			
* @version	1.0
* @date		
* @author	s.rezaee
**********************************************************************/

#include "includes.h"
#include "user_bsp.h"

#include "inc\ade7953_i2c_driver.h"
#include "i3c.h"
#include "flashrtc.h"
#include "inc\rtc_bsp.h"
#include "inc\ade7953_spi_driver.h"
#include  "EXTIT_Handeler.h"
//add by rezaee
extern funp funSecCounter;

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

void BlinkLED(void)
{
	uint8_t i;
	i++;
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

void  User_BSP_Init (void)
{
	uint8_t data[10]={0,0,0,0,0,0,0,0,0,0};
	Status ret;
	RTC_TIME_Type rtc_time;
	uint16_t i;
	NVIC_SetPriority(GPIO_IRQn, GPIO_IRQ_PRIORITY);
	NVIC_EnableIRQ(GPIO_IRQn);

	GPIO_Init();
	GPDMA_Init();
	NVIC_EnableIRQ(DMA_IRQn);///????

	funSecCounter = BlinkLED;
	rtc_time.SEC = 10;
	rtc_time.MIN = 35;
	rtc_time.HOUR = 23;
	//RTC_BSP_Init(&rtc_time);
	EXTI_Init();	
#if (APP_CFG_DEBUG_ON_UART0 == DEF_ENABLED)
		debug_frmwrk_init();
#endif
	//ADE7953_SPI_Init();
	ADE7953_I2C_Inititial();
//////	AT45DBXX_Init();
//ADE7953_Init();
////	I2C_Inititial();
////	GPIO_SetDir(2,1<<17,1);

////	GPIO_ClearValue(2,1<<17);
////	delay_ms(100);
////	GPIO_SetValue(2,1<<17);
//	i=0x0ff;	
//	while(1)
//	{
//		delay_ms(1000);
//		//ADE7953_SPI_ReadReg16(0x107);
////////		i = AT45DBXX_ReadSecProtReg();
//					ret = ADE7953_I2C_Read_8_Bit(i,data);
////////		AT45DBXX_ReadManDevice();
//		//ADE7953_ReadReg(1,data);
//	}
	

#if (WWDT_ENABLE==1) 	
	// Read back TimeOut flag to determine previous timeout reset
	if (WWDT_GetStatus(WWDT_TIMEOUT_FLAG))
	{
		//_DBG_("Last MCU reset caused by WDT TimeOut!\n\r");
		// Clear WDT TimeOut
		WWDT_ClrTimeOutFlag();
	} 
	else
	{
		//_DBG_("Last MCU reset caused by External!\n\r");
	}	
#endif

}

/*********************************************************************//**
 * @brief		Enable GPIO interrupt (just used for P0.0-P0.30, P2.0-P2.13)
 * @param[in]	portNum		Port number to read value, should be: 0 or 2
 * @param[in]	pinNum	Value that contains all bits on GPIO to enable,
 * 							in range from 0 to 31.
 * @param[in]	edgeState	state of edge, should be:
 * 							- 0: Rising edge
 * 							- 1: Falling edge
 * @return		None
 **********************************************************************/
void GPIO_IntCmdDisable(uint8_t portNum, uint32_t pinNum, uint8_t edgeState)
{
	if((portNum == 0)&&(edgeState == 0))
		LPC_GPIOINT->IO0IntEnR &= ~(1<<pinNum);
	else if ((portNum == 2)&&(edgeState == 0))
		LPC_GPIOINT->IO2IntEnR &= ~(1<<pinNum);
	else if ((portNum == 0)&&(edgeState == 1))
		LPC_GPIOINT->IO0IntEnF &= ~(1<<pinNum);
	else if ((portNum == 2)&&(edgeState == 1))
		LPC_GPIOINT->IO2IntEnF &= ~(1<<pinNum);
	else
		//Error
		while(1);
}




/*
EOF
*/

