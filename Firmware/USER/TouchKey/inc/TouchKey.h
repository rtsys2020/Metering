/**********************************************************************
* $Id$		ov9650.h			2013-10
*//**
* @file		ov9650.h
* @brief	camera register defination
*			
* @version	1.0
* @date		10. decm. 2013
* @author	s.rezaee ElmoSanaat R&D
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



#ifndef _TOUCHKEY_H_
#define _TOUCHKEY_H_
#include "i2c_driver.h"

#define TOUCH_KES_SLAVE_ADDR	0x0E

#define TOUCHKEY_WRITE_REG(x,d)	i2c_write(TOUCH_KES_SLAVE_ADDR,x,d)
#define TOUCHKEY_READ_REG(x,d)	i2c_read(TOUCH_KES_SLAVE_ADDR,x,d)


#define TOUCH_KEY1	0x000001
#define TOUCH_KEY2	0x000002
#define TOUCH_KEY3	0x000004
#define TOUCH_KEY4	0x000008
#define TOUCH_KEY5	0x000010
#define TOUCH_KEY6	0x000020
#define TOUCH_KEY7	0x000030
#define TOUCH_KEY8	0x000040
#define TOUCH_KEY9	0x000080
#define TOUCH_KEY10	0x000100
#define TOUCH_KEY11	0x000200
#define TOUCH_KEY12	0x000400
#define TOUCH_KEY13	0x000800
#define TOUCH_KEY14	0x001000
#define TOUCH_KEY15	0x002000
#define TOUCH_KEY16	0x004000
#define TOUCH_KEY17	0x008000
#define TOUCH_KEY18	0x010000
#define TOUCH_KEY19	0x020000
#define TOUCH_KEY20	0x040000
#define TOUCH_KEY21	0x080000
#define TOUCH_KEY22	0x100000
#define TOUCH_KEY23	0x200000
#define TOUCH_KEY24	0x400000



typedef struct 
{
	uint16_t signal;
	uint16_t refrence;
	uint16_t dCount;
}key_val_t;

int TouchKey_initialize(void);
void TouchKey_UnlockKey(void);
void TouchKey_ReadKey(uint32_t *val);
void TouchKey_ReadKeyData(uint8_t key,key_val_t *val);
void TouchKey_ReadRegMulti(uint8_t reg,uint8_t* val,uint8_t len);
void TouchKey_Rcalibrate(void);
void TouchKey_ReadKeyDataAll(uint8_t *val);
#endif // _TOUCHKEY_H_
