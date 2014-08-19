/**********************************************************************
* $Id$		dac_sinewave_test.c				2010-06-04
*//**
* @file		dac_sinewave_test.c
* @brief	This example describes how to use DAC to generate a sine wave
* 			using DMA to transfer data
* @version	2.0
* @date		04. June. 2010
* @author	NXP MCU SW Application Team
*
* Copyright(C) 2010, NXP Semiconductor
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
**********************************************************************/

#include "includes.h"
#include "playsound.h"
#include "filesystem.h"
#include "DMA_Handeler.h"
/* Example group ----------------------------------------------------------- */
/** @defgroup DAC_SineWave	DAC SineWave
 * @ingroup DAC_Examples
 * @{
 */


extern void AudioWaitFlag(void);
// Terminal Counter flag for Channel 0
__IO uint32_t DACChannel0_TC;

// Error Counter flag for Channel 0
__IO uint32_t DACChannel0_Err;



WAVE_FormatTypeDef WAVE_Format;
uint16_t TIM6ARRValue;
static __IO uint32_t SpeechDataOffset = 0x00;
static __IO uint32_t WaveCounter;


FIL file_wav;
extern FATFS fs[];		/* File system object for MMC logical drive */
/************************** PRIVATE MACROS *************************/

/************************** PRIVATE VARIABLES *************************/
GPDMA_Channel_CFG_Type GPDMACfg;

#define DAC_NUM_SINE_SAMPLE	512

sound_t SoundList[10]={\
							//{0,0,0,"1:Fa_1059.wav"},
							{0,1,0,"1:test2.wav"},\
							{0,2,0,"1:wellcome.wav"},\
							{0,3,0,"1:test85.wav"}}
;
/*********************************************************************//**
 * @brief		SoundPlay: Main DAC program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
uint32_t PlaySound(sound_t *sound,uint32_t index,uint16_t len)
{
	
	uint32_t cnt,i;
	static uint32_t dac_sine_lut[DAC_NUM_SINE_SAMPLE];
	static uint16_t n = 0;
	for(i=0; i < len && i<DAC_NUM_SINE_SAMPLE;i++)
	{
		dac_sine_lut[i] = ((sound->data8[index])<<6 )|1<<16;
		index++;
	}

	// Setup GPDMA channel --------------------------------
	// channel 0
	GPDMACfg.ChannelNum = DAC_DMA_CH;
	// Source memory
	//GPDMACfg.SrcMemAddr = (uint32_t)(dac_sine_lut);
	GPDMACfg.SrcMemAddr = (uint32_t)(dac_sine_lut);
	// Destination memory - unused
	GPDMACfg.DstMemAddr = 0;
	// Transfer size
	GPDMACfg.TransferSize = i-4;//sound->num_of_sample;
	// Transfer width - unused
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	// Source connection - unused
	GPDMACfg.SrcConn = 0;
	// Destination connection
	GPDMACfg.DstConn = GPDMA_CONN_DAC;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);
//	/* Reset terminal counter */
//	DACChannel0_TC = 0;
//	/* Reset Error counter */
//	DACChannel0_Err = 0;
	/* Enable GPDMA interrupt */
	
	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(DAC_DMA_CH, ENABLE);
	//OSTimeDlyHMSM(0, 0, 0, 50);							 /* Delay One minute */
	//while (DACChannel0_TC == 0 );
	AudioWaitFlag();
	// Disable GPDMA channel 0
	GPDMA_ChannelCmd(DAC_DMA_CH, DISABLE);
	return i;
}

/***********************************************************************************
  * @brief  Reads a number of bytes from the SPI Flash and reorder them in Big
  *         or little endian.
  * @param  NbrOfBytes: number of bytes to read.
  *         This parameter must be a number between 1 and 4.
  * @param  ReadAddr: external memory address to read from.
  * @param  Endians: specifies the bytes endianness.
  *         This parameter can be one of the following values:
  *             - LittleEndian
  *             - BigEndian
  * @retval Bytes read from the SPI Flash.
  ************************************************************************************/
uint32_t ReadUnit(uint8_t *buffer, uint8_t idx, uint8_t NbrOfBytes, Endianness BytesFormat)
{
  uint32_t index = 0;
  uint32_t temp = 0;

  for (index = 0; index < NbrOfBytes; index++)
  {
    temp |= buffer[idx + index] << (index * 8);
  }

  if (BytesFormat == BigEndian)
  {
    temp = __REV(temp);
  }
  return temp;
}

/*************************************************************************************
  * @brief  Checks the format of the .WAV file and gets information about the audio
  *         format. This is done by reading the value of a number of parameters
  *         stored in the file header and comparing these to the values expected
  *         authenticates the format of a standard .WAV  file (44 bytes will be read).
  *         If  it is a valid .WAV file format, it continues reading the header
  *         to determine the  audio format such as the sample rate and the sampled
  *         data size. If the audio format is supported by this application, it
  *         retrieves the audio format in WAVE_Format structure and returns a zero
  *         value. Otherwise the function fails and the return value is nonzero.
  *         In this case, the return value specifies the cause of  the function
  *         fails. The error codes that can be returned by this function are declared
  *         in the header file.
  * @param  WavName: wav file name
  * @param  FileLen: wav file length   
  * @retval Zero value if the function succeed, otherwise it return a nonzero value
  *         which specifies the error code.
  ************************************************************************************/
ErrorCode WaveParsing(const char* WavName)//, uint32_t *FileLen
{

  uint32_t temp = 0x00;
  uint32_t extraformatbytes = 0;
	//uint8_t *Buffer1=audioBuff;
	uint8_t Buffer1[600];
	uint32_t BytesRead;
	FRESULT result = 1;
	sound_t sound;
	int i=512,j;
	//FIL fs2;
	//MMC_Init();
	//fs = MMC_open((uint8_t*)"test.txt",FA_READ);//????????????????????????
	f_mount(&fs[0], "1:", 0);//mmc
	result = f_chdir((TCHAR*)"1:\\audio");
	result = f_open(&file_wav,(const TCHAR*)WavName,FA_READ);
	if(result != FR_OK )
	{	
		return Unvalid_WAVE_File ;
	}
  f_read (&file_wav, Buffer1, _MAX_SS, &BytesRead);
	//f_close(&file_wav);
  /* Read chunkID, must be 'RIFF'  ----------------------------------------------*/
  temp = ReadUnit(Buffer1, 0, 4, BigEndian);
  if (temp != CHUNK_ID)
  {
    return(Unvalid_RIFF_ID);
  }
  /* Read the file length ----------------------------------------------------*/
  WAVE_Format.RIFFchunksize = ReadUnit(Buffer1, 4, 4, LittleEndian);

  /* Read the file format, must be 'WAVE' ------------------------------------*/
  temp = ReadUnit(Buffer1, 8, 4, BigEndian);
  if (temp != FILE_FORMAT)
  {
    return(Unvalid_WAVE_Format);
  }

  /* Read the format chunk, must be'fmt ' --------------------------------------*/
  temp = ReadUnit(Buffer1, 12, 4, BigEndian);
  if (temp != FORMAT_ID)
  {
    return(Unvalid_FormatChunk_ID);
  }
  /* Read the length of the 'fmt' data, must be 0x10 -------------------------*/
  temp = ReadUnit(Buffer1, 16, 4, LittleEndian);
  if (temp != 0x10)
  {
    extraformatbytes = 1;
  }
  /* Read the audio format, must be 0x01 (PCM) -------------------------------*/
  WAVE_Format.FormatTag = ReadUnit(Buffer1, 20, 2, LittleEndian);
  if (WAVE_Format.FormatTag != WAVE_FORMAT_PCM)
  {
    return(Unsupporetd_FormatTag);
  }

  /* Read the number of channels, must be 0x01 (Mono) ------------------------*/
  WAVE_Format.NumChannels = ReadUnit(Buffer1, 22, 2, LittleEndian);
  if (WAVE_Format.NumChannels != CHANNEL_MONO)
  {
    return(Unsupporetd_Number_Of_Channel);
  }

  /* Read the Sample Rate ----------------------------------------------------*/
  WAVE_Format.SampleRate = ReadUnit(Buffer1, 24, 4, LittleEndian);
  /* Update the OCA value according to the .WAV file Sample Rate */
  switch (WAVE_Format.SampleRate)
  {
    case SAMPLE_RATE_8000 :
      TIM6ARRValue = 8000;
      break; /* 8KHz = 48MHz / 6000 */
    case SAMPLE_RATE_11025:
      TIM6ARRValue = 11025;
      break; /* 11.025KHz = 48MHz / 4353 */
    case SAMPLE_RATE_22050:
      TIM6ARRValue = 22050;
      break; /* 22.05KHz = 48MHz / 2176 */
    case SAMPLE_RATE_44100:
      TIM6ARRValue = 44100;
      break; /* 44.1KHz = 48MHz / 1088 */
    default:
      return(Unsupporetd_Sample_Rate);
  }

  /* Read the Byte Rate ------------------------------------------------------*/
  WAVE_Format.ByteRate = ReadUnit(Buffer1, 28, 4, LittleEndian);

  /* Read the block alignment ------------------------------------------------*/
  WAVE_Format.BlockAlign = ReadUnit(Buffer1, 32, 2, LittleEndian);

  /* Read the number of bits per sample --------------------------------------*/
  WAVE_Format.BitsPerSample = ReadUnit(Buffer1, 34, 2, LittleEndian);
  if (WAVE_Format.BitsPerSample != BITS_PER_SAMPLE_8)
  {
    return(Unsupporetd_Bits_Per_Sample);
  }
  SpeechDataOffset = 36;
  /* If there is Extra format bytes, these bytes will be defined in "Fact Chunk" */
  if (extraformatbytes == 1)
  {
    /* Read th Extra format bytes, must be 0x00 ------------------------------*/
    temp = ReadUnit(Buffer1, 36, 2, LittleEndian);
    if (temp != 0x00)
    {
      return(Unsupporetd_ExtraFormatBytes);
    }
    /* Read the Fact chunk, must be 'fact' -----------------------------------*/
    temp = ReadUnit(Buffer1, 38, 4, BigEndian);
    if (temp != FACT_ID)
    {
      return(Unvalid_FactChunk_ID);
    }
    /* Read Fact chunk data Size ---------------------------------------------*/
    temp = ReadUnit(Buffer1, 42, 4, LittleEndian);
    SpeechDataOffset += 10 + temp;
  }
  /* Read the Data chunk, must be 'data' ---------------------------------------*/
  temp = ReadUnit(Buffer1, SpeechDataOffset, 4, BigEndian);
  SpeechDataOffset += 4;
  if (temp != DATA_ID)
  {
    return(Unvalid_DataChunk_ID);
  }

  /* Read the number of sample data ------------------------------------------*/
  WAVE_Format.DataSize = ReadUnit(Buffer1, SpeechDataOffset, 4, LittleEndian);
  SpeechDataOffset += 4;
  WaveCounter =  SpeechDataOffset;
	
	sound.freq = TIM6ARRValue;
	sound.num_of_sample = (512-SpeechDataOffset);
	sound.data8 = (uint8_t*)&Buffer1[SpeechDataOffset];
	sound.data8[0] = 0;
	PlaySound(&sound,0,512);

	i=512;
	while( i<WAVE_Format.DataSize)
	{
		f_read (&file_wav, &Buffer1[0], _MAX_SS, &BytesRead);//load data to bauffer
		i+=BytesRead;			
		sound.data8 = Buffer1;
		sound.num_of_sample = BytesRead;
		PlaySound(&sound,i,BytesRead);
	}

  return(Valid_WAVE_File);
}


/*************************************************************************************
  * @brief  Checks the format of the .WAV file and gets information about the audio
  *         format. This is done by reading the value of a number of parameters
  *         stored in the file header and comparing these to the values expected
  *         authenticates the format of a standard .WAV  file (44 bytes will be read).
  *         If  it is a valid .WAV file format, it continues reading the header
  *         to determine the  audio format such as the sample rate and the sampled
  *         data size. If the audio format is supported by this application, it
  *         retrieves the audio format in WAVE_Format structure and returns a zero
  *         value. Otherwise the function fails and the return value is nonzero.
  *         In this case, the return value specifies the cause of  the function
  *         fails. The error codes that can be returned by this function are declared
  *         in the header file.
  * @param  WavName: wav file name
  * @param  FileLen: wav file length   
  * @retval Zero value if the function succeed, otherwise it return a nonzero value
  *         which specifies the error code.
  ************************************************************************************/
ErrorCode LoaudSound(sound_t *audio)
{
	uint8_t *Buffer;
	uint32_t BytesRead;
	FRESULT result = 1;
	int i=512,j;
	f_mount(&fs[0], "1:", 0);//mmc
	result = f_chdir((TCHAR*)"1:\\audio");
	result = f_open(&file_wav,(const TCHAR*)audio->name,FA_READ);
	if(result != FR_OK )
	{	
		return Unvalid_WAVE_File ;
	}
  f_read (&file_wav, (uint8_t*)audio, 12, &BytesRead);
	Buffer = calloc(audio->num_of_sample,sizeof(uint8_t));//
	i=0;
	while(1)
	{
			f_read (&file_wav,&Buffer[i] ,_MAX_SS, &BytesRead);//load data to bauffer 
			i+=BytesRead;	
			if(BytesRead == 0 || i >= audio->num_of_sample)
			break;
	}
	audio->data8 = Buffer;
	f_close(&file_wav);
  return(Valid_WAVE_File);
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
void PlayAudio(sound_t audio)
{
	uint32_t i=0,len,j,cnt;
	DAC_CONVERTER_CFG_Type DAC_ConverterConfigStruct;
	
	len =audio.num_of_sample/DAC_NUM_SINE_SAMPLE;
	
	cnt = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);
	cnt = cnt/(audio.freq);//
	DAC_SetDMATimeOut(0, cnt);	
//	/* Disable GPDMA interrupt */
//	NVIC_DisableIRQ(DMA_IRQn);
//	/* preemption = 1, sub-priority = 1 */
//	NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));

	DAC_ConverterConfigStruct.CNT_ENA =SET;
	DAC_ConverterConfigStruct.DMA_ENA = SET;
	DAC_ConverterConfigStruct.DBLBUF_ENA = 1;
	DAC_ConfigDAConverterControl(0, &DAC_ConverterConfigStruct);
	/* Initialize GPDMA controller */
	//GPDMA_Init();

	i=0;
	for(j=0;j<len;j++)
	{
		i+=PlaySound(&audio,i,DAC_NUM_SINE_SAMPLE);
	}
	i=PlaySound(&audio,i,audio.num_of_sample-(len*DAC_NUM_SINE_SAMPLE));
	
}



/**
 * @}
*/
