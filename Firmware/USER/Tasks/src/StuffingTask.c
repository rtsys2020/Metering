/*


*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "StuffingTask.h"
#include "DestuffingTask.h"
#include "EthernetTask.h"
#include "includes.h"
#include "uart.h"

OS_EVENT *SendStuffingQ;

void *StuffingMsg[STUFFING_MSG_SIZE];
OS_STK StuffingTaskStk[STUFFING_TASK_STK_SIZE];

uint8_t StuffingDataBuffer[1500];
comunication_t StuffedData;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
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
void App_StuffingTaskCreate (void)
{
	INT8U err;
	
	err=err;
	SendStuffingQ = OSQCreate(&StuffingMsg[0], STUFFING_MSG_SIZE);
	err = OSTaskCreateExt(StuffingTask,
	                      (void *)0,
                        &StuffingTaskStk[STUFFING_TASK_STK_SIZE-1],
                        STUFFING_TASK_PRIO,
                        STUFFING_TASK_PRIO,
                        &StuffingTaskStk[0],
                        STUFFING_TASK_STK_SIZE,
                        (void *)0,
                        OS_TASK_OPT_STK_CHK);
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
void StuffingTask (void *pdata)
{
	INT8U err;
	comunication_t *msg;
	uint16_t i;
	
	pdata=pdata;
	
	for (;;){
		msg = OSQPend(SendStuffingQ, 0, &err);

		if (err == OS_ERR_NONE) {
			i=0;
			StuffingDataBuffer[i++] = *(*msg).dataframe++; //skipping the first 0x7E
			(*msg).len-=2;            //
			while ((*msg).len--){
				switch (*(*msg).dataframe)
				{
					case 0x7E:
						StuffingDataBuffer[i++] = 0x7D;
						StuffingDataBuffer[i++] = 0x5E;
						(*msg).dataframe++;
						break;
					case 0x7D:
						StuffingDataBuffer[i++] = 0x7D;
						StuffingDataBuffer[i++] = 0x5D;
						(*msg).dataframe++;
						break;
					default :
						StuffingDataBuffer[i++] = *(*msg).dataframe++;
						break;
				}
			}
			StuffingDataBuffer[i++] = *(*msg).dataframe;
			
			StuffedData.len = i;
			StuffedData.port = (*msg).port;
			StuffedData.dataframe = &StuffingDataBuffer[0];
			
			if (StuffedData.port == ETHERNET_PORT)
			{
				//err = OSQPost(EthernetSendQ, (void *)&StuffedData);
			}
			else
			{
				//Post data to SerialSendQ
				//	senp.len= j;
//					send.port= 0;
//					send.dataframe = StuffedData;
					BSP_HDLC_SendDMA(&StuffedData);
			}
		}
		else
		{
			OSTimeDlyHMSM(0, 0, 0, 500);							 /* Delay One minute */
		}
	}
}


/*
EOF
*/

