#include "inc\sdram_config.h"

/*********************************************************************//**
 * @brief 		Initialize external SDRAM memory
 *	
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void SDRAMInit( void )
{
    volatile uint32_t i;
    volatile unsigned long Dummy;
    EMC_DYN_MEM_Config_Type config;
	  
    config.ChipSize = CHIPSIZE;
    config.AddrBusWidth = ADDRBUSWIDTH;
    config.AddrMap = ADDRMAP ;
    config.CSn = CHIPSELECTNUM;
    config.DataWidth = DATAWIDTH;
    config.TotalSize = TOTALSIZE ;

    config.CASLatency= CASLATENCY;
    config.RASLatency= RASLATENCY;
    config.Active2ActivePeriod = EMC_NS2CLK( SDRAM_TRC);
    config.ActiveBankLatency = EMC_NS2CLK( SDRAM_TRRD);
    config.AutoRefrehPeriod = EMC_NS2CLK( SDRAM_TRFC);
    config.DataIn2ActiveTime = SDRAM_TDAL + EMC_NS2CLK( SDRAM_TRP);
    config.DataOut2ActiveTime = SDRAM_TAPR;
    config.WriteRecoveryTime = SDRAM_TWR;
    config.ExitSelfRefreshTime = EMC_NS2CLK( SDRAM_TXSR);
    config.LoadModeReg2Active = SDRAM_TMRD;
    config.PrechargeCmdPeriod = EMC_NS2CLK( SDRAM_TRP);
    config.ReadConfig = 1;  /* Command delayed strategy, using EMCCLKDELAY */
    config.RefreshTime = EMC_NS2CLK( SDRAM_REFRESH) >> 4;
    config.Active2PreChargeTime = EMC_NS2CLK( SDRAM_TRAS);
    config.SeftRefreshExitTime = EMC_NS2CLK( SDRAM_TXSR);
	if(DynMem_Init(&config) != EMC_FUNC_OK)
	{
#ifdef __DEBUG__		
		_DBG_("sdram initial error\n");
#endif		
	}
	// SDRAM
	LPC_EMC->DynamicConfig0 = 0x0000680;
	// JEDEC General SDRAM Initialization Sequence
	// DELAY to allow power and clocks to stabilize ~100 us
	// NOP
	LPC_EMC->DynamicControl = 0x0183;//0000 00001 1000 0011  precharge,
	for(i= 200*30; i;i--);
	// PALL
	LPC_EMC->DynamicControl = 0x0103;//0000 00001 1000 0011  normal
	LPC_EMC->DynamicRefresh = 2;
	for(i= 256; i; --i); // > 128 clk
	LPC_EMC->DynamicRefresh = P2C(SDRAM_REFRESH) >> 4;//---------
	// COMM

    LPC_EMC->DynamicControl    = 0x00000083; /* Issue MODE command */
	Dummy = *((volatile uint32_t *)(SDRAM_BASE_ADDR | (0x33<<12)));
	// NORM
	LPC_EMC->DynamicControl = 0x0000;
	//enable buffers
    EMC_DynMemConfigB(0, EMC_DYNAMIC_CFG_BUFF_ENABLED);
	for(i = 100000; i;i--);		
	return;
}
