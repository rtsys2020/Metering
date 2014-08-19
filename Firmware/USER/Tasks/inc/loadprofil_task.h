/**********************************************************************
* $Id$		loadprofil_task.h			2013-12-15
*//**
* @file		loadprofil_task.h
* @brief	
* @version	1.0
* @date		28. Decm. 2013
* @author	
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup CAN
 * @{
 */
#ifndef LOADPROFIL_TASK_H
#define  LOADPROFIL_TASK_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#include "includes.h"


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/

//<o> Daily Meter Task Priority
#define LOAD_PROFIL_TASK_START_PRIO 11
//<o> Daily Meter TaskStack Size
#define LOAD_PROFIL_TASK_START_STK_SIZE 64

#define LOAD_PROFIL_QEUEU_SIZE	5

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/
typedef enum
{
	LOAD_GAZ,
	LOAD_WATER,
	LOAD_ELECTRICITY
}LoadProfilSource_t;
/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


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
void LoadProfilSendSignalWater(void);
void LoadProfilSendSignalGaz(void);
void LoadProfilSendSignalElec(void);
/*
EOF
*/

#endif

/*
EOF
*/
