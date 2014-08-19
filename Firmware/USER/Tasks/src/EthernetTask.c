/*


*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "EthernetTask.h"

#include "includes.h"

/* lwIP includes. */
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/stats.h"
#include "netif/loopif.h"
#include "ip.h"
#include "DestuffingTask.h"
#include "applicationtask.h"


static  OS_STK  AppLWIPTaskStk[APP_TASK_LWIP_STK_SIZE];
struct netbuf 		*__pstNetbuf;
comunication_t __EthData;

OS_EVENT *EthernetSendQ;
void *EthernetSendMsg[ETHERNETSEND_MSG_SIZE];

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void    EthernetTask  (void *pdata);
enum client_remote_connection    is_HDLC(struct netconn  *pstConn);


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
void  App_EthernetTaskCreate (void)
{
	INT8U err;

	err = err; /* prevent warning... */

	err = OSTaskCreateExt(EthernetTask,
	                      (void *)0,
					              &AppLWIPTaskStk[APP_TASK_LWIP_STK_SIZE - 1],
					              APP_TASK_LWIP_PRIO,
						            APP_TASK_LWIP_PRIO,
						            &AppLWIPTaskStk[0],
						            APP_TASK_LWIP_STK_SIZE,
						            0,
						            OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);		

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_LWIP_PRIO,(INT8U *) "Task LWIP", &err);
	#endif
}

static  void    EthernetTask(void *pdata)
{

	struct netconn  *__pstConn, *__pstNewConn; 

    Init_lwIP();

    __pstConn = netconn_new(NETCONN_TCP);
    netconn_bind(__pstConn, NULL,EOS_PORT_FOR_ETH);
    netconn_listen(__pstConn);

  	__pstNewConn = netconn_accept(__pstConn);
	
	for(;;)
   	{
			if(__pstNewConn != NULL)
			{			
				if(is_HDLC(__pstNewConn) == CLOSED_BY_CLIENT)
				{
					while(netconn_delete(__pstNewConn) != ERR_OK)
					{
							OSTimeDlyHMSM(0, 0, 0, 10);
					}
					__pstNewConn = netconn_accept(__pstConn);
				}
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
enum client_remote_connection is_HDLC(struct netconn  *pstConn)
{
	INT8U err;

	INT8S		  *__pbtempData;
	u16_t     Lencountdown;
	
	comunication_t *msg;
	

 	__pstNetbuf = netconn_recv(pstConn);
	if(__pstNetbuf != NULL)
	{
		netbuf_data (__pstNetbuf, (void *)&__EthData.dataframe, &__EthData.len );
		__EthData.port = ETHERNET_PORT;
		
		__pbtempData=__EthData.dataframe+1;
		Lencountdown=__EthData.len;

		if(*__EthData.dataframe == 0x7E)
		{
			while (--Lencountdown)
			{
				if (*(__pbtempData++)==0x7E)
				{
					if (Lencountdown==1)
					{
						err = OSQPost(RcvDestuffingQ, (void *)&__EthData);
						if (err == OS_ERR_NONE) {
							msg = OSQPend(EthernetSendQ, 0, &err);
							if (err == OS_ERR_NONE) {
								netconn_write(pstConn, (*msg).dataframe, (*msg).len, NETCONN_COPY);
							}
						}
					}
					break;
				}
			}
		}
		
		netbuf_delete(__pstNetbuf);	
		
		return STILL_OPEN_BY_CLIENT;
	}
	else
	{
		netbuf_delete(__pstNetbuf);	
		netconn_close(pstConn);
		
		return CLOSED_BY_CLIENT;
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

void App_EthernetSendQueueCreate (void)
{
	EthernetSendQ = OSQCreate(&EthernetSendMsg[0], ETHERNETSEND_MSG_SIZE);
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
