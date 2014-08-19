/**********************************************************************
* $Id$		rs232.h			2013-06-21
*//**
* @file		rs232.h
* @brief	Contains rs232 protocol 
*			
* @version	1.0
* @date		21. Decem. 2011
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

#ifndef PLAYSOUND_H
#define PLAYSOUND_H
#include "bsp.h"
#include "includes.h"


/** @defgroup UART_Dma		UART DMA
 * @ingroup UART_Examples
 * @{
 */
/**
@code 
  .WAV file format :
 Endian      Offset      Length      Contents
  big         0           4 bytes     'RIFF'             // 0x52494646
  little      4           4 bytes     <file length - 8>
  big         8           4 bytes     'WAVE'             // 0x57415645
Next, the fmt chunk describes the sample format:
  big         12          4 bytes     'fmt '          // 0x666D7420
  little      16          4 bytes     0x00000010      // Length of the fmt data (16 bytes)
  little      20          2 bytes     0x0001          // Format tag: 1 = PCM
  little      22          2 bytes     <channels>      // Channels: 1 = mono, 2 = stereo
  little      24          4 bytes     <sample rate>   // Samples per second: e.g., 22050
  little      28          4 bytes     <bytes/second>  // sample rate * block align
  little      32          2 bytes     <block align>   // channels * bits/sample / 8
  little      34          2 bytes     <bits/sample>   // 8 or 16
Finally, the data chunk contains the sample data:
  big         36          4 bytes     'data'        // 0x64617461
  little      40          4 bytes     <length of the data block>
  little      44          *           <sample data>
@endcode
*/

typedef enum
{
  LittleEndian,
  BigEndian
}Endianness;

typedef struct
{
  uint32_t  RIFFchunksize;
  uint16_t  FormatTag;
  uint16_t  NumChannels;
  uint32_t  SampleRate;
  uint32_t  ByteRate;
  uint16_t  BlockAlign;
  uint16_t  BitsPerSample;
  uint32_t  DataSize;
}
WAVE_FormatTypeDef;
typedef enum
{
  Valid_WAVE_File = 0,
  Unvalid_RIFF_ID,
  Unvalid_WAVE_Format,
  Unvalid_FormatChunk_ID,
  Unsupporetd_FormatTag,
  Unsupporetd_Number_Of_Channel,
  Unsupporetd_Sample_Rate,
  Unsupporetd_Bits_Per_Sample,
  Unvalid_DataChunk_ID,
  Unsupporetd_ExtraFormatBytes,
  Unvalid_FactChunk_ID,
	Unvalid_WAVE_File
} ErrorCode;

typedef struct
{
  __IO uint8_t wavelist[14];
} WavePlayList;

/** @defgroup WAVEPLAYER_Exported_Constants
  * @{
  */
#define SpeechReadAddr         0x0  /* Speech wave start read address */


/* Audio Play STATUS */
#define AudioPlayStatus_STOPPED       0
#define AudioPlayStatus_PLAYING	      1
#define AudioPlayStatus_PAUSED        2	 

#define  CHUNK_ID                            0x52494646  /* correspond to the letters 'RIFF' */
#define  FILE_FORMAT                         0x57415645  /* correspond to the letters 'WAVE' */
#define  FORMAT_ID                           0x666D7420  /* correspond to the letters 'fmt ' */
#define  DATA_ID                             0x64617461  /* correspond to the letters 'data' */
#define  FACT_ID                             0x66616374  /* correspond to the letters 'fact' */
#define  WAVE_FORMAT_PCM                     0x01
#define  FORMAT_CHNUK_SIZE                   0x10
#define  CHANNEL_MONO                        0x01
#define  SAMPLE_RATE_8000                    8000
#define  SAMPLE_RATE_11025                   11025
#define  SAMPLE_RATE_22050                   22050
#define  SAMPLE_RATE_44100                   44100
#define  BITS_PER_SAMPLE_8                   8
#define  BITS_PER_SAMPLE_16                   16
#define  WAVE_DUMMY_BYTE                     0xA5   
#define  DAC_DHR8R1_Address                  0x40007410
#define  DAC_DHR12R1_Address                 0x40007408
#define  DAC_DHR12L1_Address                 0x4000740C
/**
  * @}
  */


/** @defgroup WAVEPLAYER_Exported_Macros
  * @{
  */
/**
  * @}
  */

/**,************************ PRIVATE DEFINITIONS *************************/
typedef struct 
{
	uint32_t num_of_sample;
	uint32_t freq;
	uint8_t *data8;
	uint8_t name[20];
}sound_t;


#define DAC_PORT 0
#define DAC_PIN 26
#define DAC_FUNC_NUM	2

#define _DMA_USING				(1)

// Receive buffer
// Terminal Counter flag for Channel 0
extern __IO uint32_t DACChannel0_TC;

// Error Counter flag for Channel 0
extern __IO uint32_t DACChannel0_Err;

extern sound_t SoundList[];
/************************** PRIVATE VARIABLES *************************/
 
 
/************************** PRIVATE FUNCTIONS *************************/
ErrorCode WaveParsing(const char* WavName);//, uint32_t *FileLen
ErrorCode LoaudSound(sound_t *audio);
//uint32_t PlaySound(sound_t *sound);
uint32_t PlaySound(sound_t *sound,uint32_t index,uint16_t len);
void PlayAudio(sound_t audio1);
/*
EOF
*/
#endif //PLAYSOUND_H
