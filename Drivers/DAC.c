#include "DAC.h"

//Static Prototypes------------------------------------------------------
static void DAC_PinInit(uint8_t dacNum);

//Global Variables-------------------------------------------------------
DAC_CLOCK *const DACClock = ADDR_DAC_CLOCK;
//DAC
DACx *const DAC = ADDR_DAC;


void DAC_Init(uint8_t dacNum){
	
	DAC_PinInit(dacNum);
	DACClock->dac_StartTick = 1;

	switch (dacNum) {
		
		case 1 : 
			DAC->ControlReg.enable_DACChannel1 = 1;
			break;
		case 2 :
			DAC->ControlReg.enable_DACChannel2 = 1;
			break;
		default :
			break;
	}
}


uint16_t DAC_Out(uint8_t dacNum, uint16_t digitalData) {
	
	switch (dacNum) {
		
		case 1 : 
			DAC->Ch1_12BitRightAlignDatHoldReg.rw_Data12Bit = digitalData; 
			return DAC->Ch1_DataOutputReg.read_Channel1DataOutput;
		case 2 :
			DAC->Ch2_12BitRightAlignDatHoldReg.rw_Data12Bit = digitalData; 
			return DAC->Ch2_DataOutputReg.read_Channel2DataOutput;
		default :
			return 0;
	}
}

float Decibel_Out(int16_t analogVolt) {
	
	/*dB(mW): power relative to 1 milliwatt. 
			In audio and telephony, dBm is typically referenced relative to a 600 Ω impedance, 
			which corresponds to a voltage level of 0.775 volts or 775 millivolts
 	*/
	return analogVolt * 0.775;
	
}

// Helper Functions--------------------------------------------------------------------------------------------------------------
static void DAC_PinInit(uint8_t dacNum) {
	
	switch (dacNum) {
		
		case 1 : 
			Pin_Init('A', 4, ANALOG);
			break;
		case 2 :
			Pin_Init('A', 5, ANALOG);
			break;
	}
}