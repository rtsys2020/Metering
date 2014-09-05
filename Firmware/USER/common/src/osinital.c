/**********************************************************************
* $Id$		alarmmangment.c				
*//**
* @file		alarmmangment.c
* @brief	
* @version	1.0
* @date		
* @author	
*/
#include "applicationtask.h"
#include "includes.h"
#include "osinit.h" 
#include "inc\rtc_bsp.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */
 /* Private variables ---------------------------------------------------------*/

 OS_EVENT *ALARMMNGT_Q; 
void *ALARMMNGT_QList[ALARMMNGT_QEUEU_SIZE];

OS_EVENT *RTC_IRQ_Q; 
void *RTC_IRQ_QList[5];


OS_EVENT *dialyMeterQ; 
void *dialyMeterQList[DIALY_QEUEU_SIZE];

OS_EVENT *NRI_RST_Sem;

OS_EVENT *limitAndManageBarQ; 
void *limitAndManageBarQList[LIMIT_LOUAD_QEUEU_SIZE];


OS_EVENT *IHD_Q; 
void *IHD_QList[IHD_QEUEU_SIZE];


OS_EVENT *loadProfilQ; 
void *loadProfilQList[LOAD_PROFIL_QEUEU_SIZE];


OS_EVENT *srcOnOffQ; 
void *srcOnOffQList[SRC_ON_OFF_QEUEU_SIZE];

OS_EVENT *Tariff_Q; 
void *Tariff_QList[TARIFF_QEUEU_SIZE];

OS_EVENT *Dummy_Q; 
void *Dummy_QList[DUMMY_QEUEU_SIZE];

OS_EVENT *IRQ_Q; 
void *IRQ_QList[IRQ_QEUEU_SIZE];


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
void App_SignalQeueq_Init(void)
{
	RTC_IRQ_Q = OSQCreate(RTC_IRQ_QList,5);
	ALARMMNGT_Q = OSQCreate(ALARMMNGT_QList,ALARMMNGT_QEUEU_SIZE);
	dialyMeterQ = OSQCreate(dialyMeterQList,DIALY_QEUEU_SIZE);
	limitAndManageBarQ = OSQCreate(limitAndManageBarQList,LIMIT_LOUAD_QEUEU_SIZE);
	IHD_Q = OSQCreate(IHD_QList,IHD_QEUEU_SIZE);
	loadProfilQ = OSQCreate(loadProfilQList,LOAD_PROFIL_QEUEU_SIZE);
	srcOnOffQ = OSQCreate(srcOnOffQList,SRC_ON_OFF_QEUEU_SIZE);
	Tariff_Q = OSQCreate(Tariff_QList,TARIFF_QEUEU_SIZE);
	Dummy_Q = OSQCreate(Dummy_QList,DUMMY_QEUEU_SIZE);
	IRQ_Q = OSQCreate(IRQ_QList,IRQ_QEUEU_SIZE);	
	NRI_RST_Sem = OSSemCreate(0);
}
