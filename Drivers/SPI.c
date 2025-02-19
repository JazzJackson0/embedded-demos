#include "SPI.h"

//Static Prototypes---------------------------------------------
static void SPI_PinInit(uint8_t spiNumber);
static void SPIClockSelect(uint8_t spiNumber);
static SPIx* Get_SPI(uint8_t spiNum);

//Global Variables------------------------------------------------
//Clock
SPI_CLOCK_1 *const SPIClock = ADDR_SPI_CLOCK_1;
SPI_CLOCK_2_3 *const SPIClock2_3 = ADDR_SPI_CLOCK_2_3;
//SPI
SPIx *const SPI1 = ADDR_SPI1;
SPIx *const SPI2 = ADDR_SPI2; 
SPIx *const SPI3 = ADDR_SPI3; 


void SPI_ClockSetup(uint8_t spiNumber, E_Phase phase, E_Polarity polarity, E_Prescaler prescaler) {
	
	SPIx *const SPI = Get_SPI(spiNumber);
	SPI->ControlReg1.enable_SPI = 0;
	SPI->ControlReg1.trans1ClockPhase0_trans2ClockPhase1 = 0;
	SPI->ControlReg1.clockPolarityLow0_clockPolarityHigh1 = 0;
	SPI->ControlReg1.rw_BaudRate = CLOCK_DIV_4;
}


void SPI_Init(uint8_t spiNumber, E_Mode mode, E_BitOrder bitOrder, uint8_t dataSize) {
	
	SPIx *const SPI = Get_SPI(spiNumber);
	SPI_PinInit(spiNumber);
	SPIClockSelect(spiNumber);
	
	SPI->ControlReg1.enable_SPI = 0;
	SPI->ControlReg1.slaveMode0_masterMode1 = 1;
	SPI->ControlReg1.msbFirst0_lsbFirst1 = 0;
	
	switch (dataSize) {
		case 8 :
			SPI->ControlReg1.dataFrame8Bit0_dataFrame16Bit1 = 0;
			break;
		case 16 :
			SPI->ControlReg1.dataFrame8Bit0_dataFrame16Bit1 = 1;
			break;
	}
	
	//Hardware NSS
	SPI->ControlReg2.enable_HardwareSlaveSelectAsOutput = 1;
	//Software NSS
	/* SPI->ControlReg1.enable_SoftwareSlaveSelect = 1; 
	SPI->ControlReg1.softwareNSSLow0_softwareNSSHigh1 = 0; 
	*/
	SPI->ControlReg1.enable_SPI = 1;
}

uint8_t SPI_Receive(uint8_t spiNumber) {
	SPIx *const SPI = Get_SPI(spiNumber);
	while (SPI->StatusReg.dataReadyToRead != 1);
	return SPI->DataReg.rw_Data;
} 


uint8_t SPI_Transmit(uint8_t spiNumber, uint8_t data) {
	SPIx *const SPI = Get_SPI(spiNumber);
	while(SPI->StatusReg.transferRegisterOpen != 1);
	SPI->DataReg.rw_Data = data;
	return 1;
} 


//Helper Functions--------------------------------------------------------------------------------------------------------------
static void SPI_PinInit(uint8_t spiNumber) {
	
	switch(spiNumber) {
		
		case 1 :
			//NSS
			Pin_Init('A', 4, AF5);
			//SCK
			Pin_Init('A', 5, AF5);
			//MISO
			Pin_Init('A', 6, AF5);
			//MOSI
			Pin_Init('A', 7, AF5);
			break;
		case 2 :
			//NSS
			Pin_Init('B', 9, AF5);
			//SCK
			Pin_Init('B', 10, AF5);
			//MISO
			Pin_Init('B', 14, AF5);
			//MOSI
			Pin_Init('B', 15, AF5);
			break;
		case 3 :
			//NSS
			Pin_Init('A', 4, AF6);
			//SCK
			Pin_Init('B', 3, AF6);
			//MISO
			Pin_Init('B', 4, AF6);
			//MOSI
			Pin_Init('B', 5, AF6);
			break;
	}
}

static void SPIClockSelect(uint8_t spiNumber) {
	
	switch(spiNumber) {
		case 1 :
			SPIClock->spi1_StartTick = 1;
			break;
		case 2 :
			SPIClock2_3->spi2_StartTick = 1;
			break;
		case 3 :
			SPIClock2_3->spi3_StartTick = 1;
			break;
	}
}

static SPIx* Get_SPI(uint8_t spiNum) {

	switch(spiNum) {
		case 1:
			return SPI1;
		case 2:
			return SPI2;
		case 3:
			return SPI3;
		default:
			return ((void*)0);
	}
}