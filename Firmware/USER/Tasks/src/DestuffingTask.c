/*


*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "DestuffingTask.h"
#include "EthernetTask.h"
#include "includes.h"
//#include "StuffingTask.h"


OS_EVENT *RcvDestuffingQ;
void *DestuffingMsg[DESTUFFING_MSG_SIZE];
OS_STK DestuffingTaskStk[DESTUFFING_TASK_STK_SIZE];

uint8_t DestuffingDataBuffer[1500];
comunication_t DestuffedData;

extern OS_EVENT *HDLC_RcvFrameQ;


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

void App_DestuffingTaskCreate (void)
{
	INT8U err;
	
	err=err;
	RcvDestuffingQ = OSQCreate(&DestuffingMsg[0], DESTUFFING_MSG_SIZE);
	err = OSTaskCreateExt(DestuffingTask,
	                      (void *)0,
                        &DestuffingTaskStk[DESTUFFING_TASK_STK_SIZE-1],
                        DESTUFFING_TASK_PRIO,
                        DESTUFFING_TASK_PRIO,
                        &DestuffingTaskStk[0],
                        DESTUFFING_TASK_STK_SIZE,
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
void DestuffingTask (void *pdata)
{
	INT8U err;
	comunication_t *msg;
	uint16_t i;
	
	pdata=pdata;
	
	for (;;){
		msg = OSQPend(RcvDestuffingQ, 0, &err);

		if (err == OS_ERR_NONE) {
			i=0;
			while ((*msg).len--){
				if (*(*msg).dataframe == 0x7D){
					(*msg).dataframe++;
					(*msg).len--;
					switch (*(*msg).dataframe)
					{
						case 0x5E:
							DestuffingDataBuffer[i++] = 0x7E;
							(*msg).dataframe++;
							break;
						case 0x5D:
							DestuffingDataBuffer[i++] = 0x7D;
							(*msg).dataframe++;
							break;
						default :
							//corrupted frame
							//the next line would ignore the corruption
						  DestuffingDataBuffer[i++] = *(*msg).dataframe++;
							break;
					}
				}
				else {
					DestuffingDataBuffer[i++]=*(*msg).dataframe++;
				}
			}
			
			DestuffedData.len = i;
			DestuffedData.port = (*msg).port;
			DestuffedData.dataframe =(uint8_t*) &DestuffingDataBuffer[0];
			
			//Just for testing 
			err = OSQPost(HDLC_RcvFrameQ, (void *)&DestuffedData);
			
		}
		else
		{
			//OSTimeDlyHMSM(0, 0, 0, 500);							 /* Delay One minute */
		}
		
	}
}


/*
EOF
*/

