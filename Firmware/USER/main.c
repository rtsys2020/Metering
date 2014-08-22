/**********************************************************************
* $Id$		main.c			
*//**
* @file		main.c
* @brief	
*			
* @version	1.0
* @date		
* @author	s.rezaee
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */
/* Includes ------------------------------------------------------------------*/
#include <includes.h>

/* Private variables ---------------------------------------------------------*/

void os_initial(void);
void  delay_ms (uint16_t dly);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

///__CHECK_DEVICE_DEFINES
#define DIV_0_TRP_BIT			4	
#define UNALIGN_TRP_BIT		3
#define MEMFAULTENA				16	
#define BUSFAULTENA				17
#define USGFAULTENA				18

	
int main (void)
{
	int i;
	SCB->SHCSR = 1<<MEMFAULTENA | 1<<BUSFAULTENA /*| 1<<USGFAULTENA*/;
	SCB->CCR &= 0;//~(1<<UNALIGN_TRP_BIT);
	//SCnSCB->ACTLR |= 3; 
	os_initial();
	return (0);
}





/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
