/**********************************************************************
* @file		gen_aes192_expkey.c
* @brief	generate the key expansion for the AES192 algo
* @version	1.0
* @date		03.07.2012
* @author	nxp28536
*
* Copyright(C) 2012, NXP Semiconductor
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
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

#include "cypher.h"
#include "cypher_internal.h"

#ifdef AES192_SUPPORT

#ifdef TEST_MODE

void checkAes192ExpCryptKey(expKey_t expKey[KSCH_AES192_SIZE], const expKey_t referenceKey[KSCH_AES192_SIZE]) {

	uint32_t* keyPtr = (uint32_t*) &expKey[0];
	const uint32_t* referenceKeyPtr = (uint32_t*) &referenceKey[0];	
	int i = 0;
	uint32_t value;
	
	for(i=0;i<KSCH_AES192_SIZE;i++) {
	
			value = (*referenceKeyPtr++);
			value = swapBytes(value);
			if((*keyPtr++) != value) {
				setErrorCode(AES192_CRYPTKEY_FAILURE);
				return;
			};
	}
}

void checkAes192ExpDecryptKey(expKey_t expKey[KSCH_AES192_SIZE], const expKey_t referenceKey[KSCH_AES192_SIZE]) {

	uint32_t* keyPtr = (uint32_t*) &expKey[0];
	const uint32_t* referenceKeyPtr = (uint32_t*) &referenceKey[0];	
	int i = 0;
	uint32_t value;
	
	for(i=0;i<KSCH_AES192_SIZE;i++) {
	
			value = (*referenceKeyPtr++);
			value = swapBytes(value);
			if((*keyPtr++) != value) {
				setErrorCode(AES192_DECRYPTKEY_FAILURE);
				return;
			};
	}
}


#endif



/* this function generates the expanded AES192 Key */
void genAes192ExpKey(const key_t key[4*NK_AES192], expKey_t expKey[KSCH_AES192_SIZE]) {

	uint32_t temp;
	uint32_t i = 0;
	uint32_t* copyPtr = (uint32_t*) &key[0];

	i = 0;
	while( i < NK_AES192) {
		expKey[i] = *copyPtr++;
		i++;
	}
	
	i = NK_AES192; 
	
	while(i < KSCH_AES192_SIZE) {
	
		temp = expKey[i-1];
		
		if((i % NK_AES192) == 0) {
		
				temp = rotWord(temp);
				temp = subWord(temp);
				temp ^= Rcon[(i/NK_AES192) - 1];;
		}
		
		expKey[i] = expKey[i - NK_AES192] ^ temp;
	
		i++;
	};
	
}

/* this function is used for adapting the expanded key to the inverse encryption algorithm */
void eqInvKeyShuffle192(expKey_t expKey[KSCH_AES192_SIZE]) {

	uint8_t round;
	
	for(round=1;round<NR_AES192;round++) {
	
		invMixColumns(&expKey[round*NB]);
	}

}

#endif


