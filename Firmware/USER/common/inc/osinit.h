/**********************************************************************
* $Id$		osinit.h			2013-12-15
*//**
* @file		osinit.h
* @brief	
* @version	1.0
* @date		28. Decm. 2013
* @author	
* 
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#ifndef  OSINITITIAL_H
#define  OSINITITIAL_H


#include "includes.h"


#define ALARMMNGT_QEUEU_SIZE	5
#define DIALY_QEUEU_SIZE	5

#define IHD_QEUEU_SIZE	5
#define IRQ_QEUEU_SIZE	5
#define LIMIT_LOUAD_QEUEU_SIZE	5
#define LOAD_PROFIL_QEUEU_SIZE	5
#define SRC_ON_OFF_QEUEU_SIZE	5
#define TARIFF_QEUEU_SIZE	5
#define DUMMY_QEUEU_SIZE	5
/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/
extern OS_EVENT *IRQ_Q;
extern OS_EVENT *Dummy_Q; 
extern OS_EVENT *Tariff_Q;
extern OS_EVENT *srcOnOffQ; 
extern OS_EVENT *loadProfilQ; 
extern OS_EVENT *IHD_Q; 
extern OS_EVENT *limitAndManageBarQ; 
extern OS_EVENT *ALARMMNGT_Q; 
extern OS_EVENT *RTC_IRQ_Q; 
extern OS_EVENT *dialyMeterQ; 
extern OS_EVENT *NRI_RST_Sem;
/*
*********************************************************************************************************
*                                          GPIO PIN DEFINITIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void App_SignalQeueq_Init(void);


#endif

/*
EOF
*/

