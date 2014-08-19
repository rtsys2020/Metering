/**********************************************************************
* $Id$		Handeler.c			2013-10
*//**
* @file		Handeler.c
* @brief	Use for rs232 functionality
*			
* @version	1.0
* @date		23. decm. 2013
* @author	s.rezaee ElmoSanaat Reasearch And Development Team
* 
* Copyright(C) 2013, ElmoSanaat.co
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
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under ElmoSanaat '
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with ElmoSanaat  .  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/
#include "includes.h"
#include  "lpc177x_8x_usbhost.h"
#include  "lpc177x_8x_pinsel.h"
#include  "bsp.h"
/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup template
 * @{
 */

/* Private Variables ---------------------------------------------------------- */
/** @defgroup Private FUNCTIONS
 * @{
 */
extern  volatile  int32_t       gUSBConnected ;
extern  volatile  USB_DEVICE_TYPE gUSBDeviceType ;
extern volatile  uint32_t   HOST_RhscIntr ;         /* Root Hub Status Change interrupt                       */
extern volatile  uint32_t   HOST_WdhIntr  ;         /* Semaphore to wait until the TD is submitted            */
extern volatile  uint8_t   HOST_TDControlStatus ;
extern volatile  HCED        *EDCtrl;                    /* Control endpoint descriptor structure                  */
extern volatile  HCED        *EDBulkIn;                  /* BulkIn endpoint descriptor  structure                  */
extern volatile  HCED        *EDBulkOut;                 /* BulkOut endpoint descriptor structure                  */
extern volatile  HCTD        *TDHead;                    /* Head transfer descriptor structure                     */
extern volatile  HCTD        *TDTail;                    /* Tail transfer descriptor structure                     */
extern volatile  HCCA        *Hcca;                      /* Host Controller Communications Area structure          */ 
        extern   uint16_t  *TDBufNonVol;               /* Identical to TDBuffer just to reduce compiler warnings */
extern volatile  uint8_t  *TDBuffer;                  /* Current Buffer Pointer of transfer descriptor          */
extern volatile  uint8_t  *FATBuffer;                 /* Buffer used by FAT file system                         */
extern volatile  uint8_t  *UserBuffer;                /* Buffer used by application                             */

extern volatile uint32_t  UnrecoverableIntCount ;
extern volatile uint8_t*		USB_DeviceDescriptor;
extern volatile uint8_t*		USB_ConfigDescriptor;
extern volatile uint8_t*		USB_InterfaceDescriptor;
/* Interrupt service routines */

/*********************************************************************//**
 * @brief 			services the interrupt caused by host controller.
 * @param[in]		None.
 * @return 		None.
 **********************************************************************/
void  USB_IRQHandler (void)
{
    uint32_t   int_status;
    uint32_t   ie_status;

    int_status    = LPC_USB->InterruptStatus;                          /* Read Interrupt Status                */
    ie_status     = LPC_USB->InterruptEnable;                          /* Read Interrupt enable status         */
 
    if (!(int_status & ie_status)) {
        return;
    } else {

        int_status = int_status & ie_status;
        if (int_status & OR_INTR_STATUS_RHSC) {                 /* Root hub status change interrupt     */
            if (LPC_USB->RhPortStatus1 & OR_RH_PORT_CSC) {
				if (LPC_USB->RhStatus & OR_RH_STATUS_DRWE) {
					/*
					 * When DRWE is on, Connect Status Change
					 * means a remote wakeup event.
					*/
					HOST_RhscIntr |= 0x01;// JUST SOMETHING FOR A BREAKPOINT
				}
				else {
					/*
					 * When DRWE is off, Connect Status Change
					 * is NOT a remote wakeup event
					*/
					if (LPC_USB->RhPortStatus1 & OR_RH_PORT_CCS) {
							HOST_TDControlStatus = 0;
							HOST_WdhIntr = 0;
							HOST_RhscIntr |= 0x01;
							gUSBConnected = 1;
					} else {
							//LPC_USB->InterruptEnable = 0; // why do we get multiple disc. rupts???
							HOST_RhscIntr &= ~0x01;
							gUSBConnected = 0;
					}
                }
            	LPC_USB->RhPortStatus1 = OR_RH_PORT_CSC;
            }
			if (LPC_USB->RhPortStatus2 & OR_RH_PORT_CSC) {
				if (LPC_USB->RhStatus & OR_RH_STATUS_DRWE) {
					/*
				 	* When DRWE is on, Connect Status Change
				 	* means a remote wakeup event.
					*/
					HOST_RhscIntr |= 0x02;// JUST SOMETHING FOR A BREAKPOINT
				}
				else {
					/*
				 	* When DRWE is off, Connect Status Change
				 	* is NOT a remote wakeup event
					*/
					if (LPC_USB->RhPortStatus2 & OR_RH_PORT_CCS) {
							HOST_TDControlStatus = 0;
							HOST_WdhIntr = 0;
							HOST_RhscIntr |= 0x02;
							gUSBConnected = 1;
					} else {
							//LPC_USB->InterruptEnable = 0; // why do we get multiple disc. rupts???
							HOST_RhscIntr &= ~0x02;
							gUSBConnected = 0;
					}
				}
				LPC_USB->RhPortStatus2 = OR_RH_PORT_CSC;
			}
			if (LPC_USB->RhPortStatus1 & OR_RH_PORT_PRSC) {
				LPC_USB->RhPortStatus1 = OR_RH_PORT_PRSC;
			}
			if (LPC_USB->RhPortStatus2 & OR_RH_PORT_PRSC) {
				LPC_USB->RhPortStatus2 = OR_RH_PORT_PRSC;
			}
		}
        if (int_status & OR_INTR_STATUS_WDH) {                  /* Writeback Done Head interrupt        */
            HOST_WdhIntr = 1;
			HOST_TDControlStatus = (TDHead->Control >> 28) & 0xf;
        }
		if (int_status & OR_INTR_STATUS_UE) {                   /* Unrecoverable Error interrupt        */
			UnrecoverableIntCount++;
        }    

        LPC_USB->InterruptStatus = int_status;                         /* Clear interrupt status register      */
    }           
    return;
}
