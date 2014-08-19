/**********************************************************************
* $Id$		dac_sinewave_test.c				2010-06-04
*//**
* @file		dac_sinewave_test.c
* @brief	This example describes how to use DAC to generate a sine wave
* 			using DMA to transfer data
* @version	2.0
* @date		04. June. 2010
* @author	NXP MCU SW Application Team
*
* Copyright(C) 2010, NXP Semiconductor
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
**********************************************************************/
#include "hdlctask.h"
#include "switchpin.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/
extern Session_t Session;
extern setup_t Setup;

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private Variable
 * @{
 */
 
static  OS_STK        App_HDLCTestStk[APP_TASK_HDLC_STK_SIZE ];


OS_EVENT *HDLC_RcvFrameQ;
extern OS_EVENT *RcvDestuffingQ;
extern OS_EVENT *SendStuffingQ;
//extern OS_EVENT *UartDMAQ[];
//extern void *UartDMABuffQ[5][UDMA_MSG_SIZE];
void *HDLC_RcvFrameQList[HDLC_RCV_MSGQ_SIZE];
//extern uint8_t UartDMABuffDataQ[];
//extern OS_EVENT *UART_DMA_Semaphore[];
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
void  App_HDLCTaskCreat (void)
{
	CPU_INT08U  os_err;

	os_err = os_err; /**< Comment on variable . */
	HDLC_RcvFrameQ = OSQCreate(&HDLC_RcvFrameQList[0], HDLC_RCV_MSGQ_SIZE);					
	os_err = OSTaskCreateExt((void (*)(void *))HDLC_Start,
	                      (void *)0,
					      &App_HDLCTestStk[APP_TASK_HDLC_STK_SIZE - 1],
					      APP_TASK_HDLC_PRIO,
						  APP_TASK_HDLC_PRIO,
						  &App_HDLCTestStk[0],
						  APP_TASK_HDLC_STK_SIZE,
						  0,
						  OS_TASK_OPT_STK_CHK);
	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_HDLC_PRIO, (INT8U*)"Task HDLC", &os_err);
	#endif
}

/*********************************************************************//**
 * @author  get hdlc packet in uart interrupt           
 * @brief 	
 * @date 
 * @version  
 * @description 
 * @param[in]		None.
 * @param[out]		None.
 * @return 				             
 *                         
 **********************************************************************/
void UartGetPacketMachin(UART_ID_Type UartID,uint8_t byte)
{
	static uint8_t interState = HDLC_START_OF_PACKET;
	static uint32_t i;
	static comunication_t tmp;
	static uint8_t buff[1500];
	
	INT8U err;
	
	if(interState == HDLC_START_OF_PACKET)
	{
			if(byte == START_FLAG & i<1500)
			{
//				//buff = OSMemGet(HDLCmem, &err);
//				if (buff == (void *)0) {
//					/* Memory block allocated 		*/
//					return;
//				}	
				i=0;
				tmp.dataframe = buff;
				tmp.dataframe[i++] = byte;
				interState = HDLC_DATA;
				
			}
	}
	else
	{
				if(byte == START_FLAG)
				{
						//put mesage to queue
					tmp.port = 1;
					tmp.dataframe[i++] = byte;
					tmp.len = i;	
					err = OSQPost(RcvDestuffingQ, (void *)&tmp);
					interState = HDLC_START_OF_PACKET;
					
					return;					
				}
				else if(i<1500)
				{
					tmp.dataframe[i++] = byte;
				}
				else
				{
					interState = HDLC_START_OF_PACKET;
				}	
	}
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

uint8_t  GetPacket(HDLC_packet_t *packet,uint32_t Timeout)
{
	INT8U err;
	comunication_t *mem;
	uint8_t i = 0;
	uint16_t len;
	//time1 = OSTimeGet();
	mem = (comunication_t *)OSQPend(HDLC_RcvFrameQ,Timeout,&err);//get raw data
	//time2 = OSTimeGet();
	if(err == OS_ERR_NONE)
	{
		packet->cmd = mem->dataframe[3];
		packet->src = mem->dataframe[1];
		packet->dest = mem->dataframe[2];
		len = packet->len = mem->dataframe[4]| mem->dataframe[5]<<8;
		if(len >= 1500)
			len = 1499;
		packet->data = (uint8_t *)calloc(len, sizeof(uint8_t));
		if(packet->data != NULL)
		{
			memcpy(packet->data,&mem->dataframe[6],packet->len);
			len+=6;
		}
		else
		{
			return ERROR;
		}
		packet->crc = (mem->dataframe[len+1]<<8)| mem->dataframe[len];
		return SUCCESS;
	}
	else
	{
		return ERROR;
	}
	//packet->data = &msg[7];//////////////////////////free memory later
	
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
void HDLC_SendPacket(uint8_t ControlByte,uint8_t PCSendBuff[],unsigned int DataLenght)
{
	unsigned int i=0,j=0; 
	uint8_t Control;
	uint8_t *buff;
	uint32_t crc;
  comunication_t *senp;  

	
	
	senp->len= j;
	senp->port= 0;//??????????????????
	senp->dataframe = buff;
	OSQPost(SendStuffingQ,senp);
//	BSP_HDLC_SendDMA(&senp);
   
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
void HDLC_Start(void)
{
	HDLC_packet_t packet1;

	
	BSP_UART_Initial(UART_0);
	SW_SelRS232();

	while(1)	
	{
	  
		if( GetPacket(&packet1,0)==SUCCESS)
		{
			//ProcessPacket(&packet1);
		}
//		else
//		{
//				OSTimeDlyHMSM(0, 0, 0, 500);							 /* Delay One minute */
//		}
		//process packet
	}
}
/**
 * @}
*/
