#include "ADC.h"


//Static Prototypes------------------------------------------------------------
static void ADCClockSelect(uint8_t adcNumber);
static ADCx* Get_ADC(char adcNum);
static void ADCChannel_Init(uint8_t adcNumber, ADC_Params params);
static void Set_ChannelSamplePeriod(ADCx *ADC, ADC_Params params);

//Global Variables-------------------------------------------------------
ADC_CLOCK *const ADCClock = ADDR_ADC_CLOCK;
//ADC
CommonADCRegisters *const CommonRegs = ADDR_COMMON_ADC_REG;
ADCx *const ADC1 = ADDR_ADC1;
ADCx *const ADC2 = ADDR_ADC2;
ADCx *const ADC3 = ADDR_ADC3;


void ADC_Init(uint8_t adcNumber, ADC_Params params, char port, uint8_t pin) {
	
	ADCClockSelect(adcNumber);
	Pin_Init(port, pin, ANALOG);
	ADCx *const ADC = Get_ADC(adcNumber);
	ADCChannel_Init(adcNumber, params);
	
	// Injected Channel Setup
	if (params.channelType == ADC_INJECTED_CH) {
		ADC->ControlReg1.enable_AutoInjectedGroupConversion = 1;
		ADC->InjectedSeqReg.rw_NumOfConversionsInInjectedSequence = params.numOfConversions;
	}

	// Regular Channel Setup
	else {
		ADC->RegularSequenceReg1.rw_NumOfConversionsInRegSequence = params.numOfConversions;
	}
	
	ADC->ControlReg1.rw_Resolution = params.resolution;
	ADC->ControlReg2.singleConvert0_continuousConvert1 = params.singleContinuous;
	ADC->ControlReg2.enable_ADC = 1; 
}


void ADC_StartConversion(uint8_t adcNumber, uint8_t channelType) {
	
	ADCx *const ADC = Get_ADC(adcNumber);

	// Injected Channel Conversion
	if (channelType == 1) { 
		ADC->ControlReg2.start_InjectedChannelConversion = 1;
	}

	// Regular Channel Conversion
	else {
		// ADC->ControlReg2.eocSetPerRegSequence0_eocSetPerRegConversion1 = 1;
		ADC->ControlReg2.start_RegChannelConversion = 1;
	}
	
}


void ADC_StopConversion(uint8_t adcNumber, uint8_t channelType) {
	
	ADCx *const ADC = Get_ADC(adcNumber);

	// Injected Channel Conversion
	if (channelType == 1) { 
		ADC->ControlReg2.start_InjectedChannelConversion = 0;
	}

	// Regular Channel Conversion
	else {
		ADC->ControlReg2.start_RegChannelConversion = 0;
	}
	
}

int16_t ADC_ConversionResult(uint8_t adcNumber, ADC_Params params) {
	
	ADCx *const ADC = Get_ADC(adcNumber);

	// Injected Channel Conversion
	if (params.channelType == ADC_INJECTED_CH) { 
		while (ADC->StatusReg.injectedChannelEndOfConversion == 0);	
		switch(params.channelNum) {
			case 1 :
				return ADC->InjectedDataReg1.read_InjectedConversionDataResult;
			case 2 :
				return ADC->InjectedDataReg2.read_InjectedConversionDataResult;
			case 3 :
				return ADC->InjectedDataReg3.read_InjectedConversionDataResult;
			case 4 :
				return ADC->InjectedDataReg4.read_InjectedConversionDataResult;
		}
		
	}

	// Regular Channel Conversion
	else {
		while (ADC->StatusReg.regChannelEndOfConversion == 0);	
		return ADC->RegularDataReg.read_RegularConversionDataResult;
	}
	
}

void ADC_SetExternalTrigger(uint8_t adcNumber, uint8_t channelType, uint8_t triggerPolarity, uint8_t triggerSource) {

	ADCx *const ADC = Get_ADC(adcNumber);

	// Regular Channel
	if (channelType == ADC_REGULAR_CH) {
		ADC->ControlReg2.rw_RegGroupExternalEvent = triggerSource;
		ADC->ControlReg2.enable_RegExternalTriggerPolarity = triggerPolarity;
	}

	// Injected Channel
	else {
		ADC->ControlReg2.rw_InjectedGroupExternalEvent = triggerSource;
		ADC->ControlReg2.enable_InjectedExternalTriggerPolarity = triggerPolarity;
	}
}

void ADC_UseDMA(uint8_t adcNumber) {
	ADCx *const ADC = Get_ADC(adcNumber);
	ADC->ControlReg2.enable_DMAMode = 1;
	ADC->ControlReg2.enable_continuousDMARequests = 1;
}

//Helper Functions--------------------------------------------------------------------------------------------------------------

static void ADCChannel_Init(uint8_t adcNumber, ADC_Params params) {
	
	ADCx *const ADC = Get_ADC(adcNumber);

	//Set-up Channel for Analog signal.
	ADC->ControlReg2.enable_ADC = 1;
	Set_ChannelSamplePeriod(ADC, params);
	
	// Injected Channel Setup
	if (params.channelType == ADC_INJECTED_CH) { 
		switch (params.conversionOrderNum) {
			case 1 :
				ADC->InjectedSeqReg.rw_1stInjectedSequenceConversion = params.channelNum;
				break;
			case 2 :
				ADC->InjectedSeqReg.rw_2ndInjectedSequenceConversion = params.channelNum;
				break;
			case 3 :
				ADC->InjectedSeqReg.rw_3rdInjectedSequenceConversion = params.channelNum;
				break;
			case 4 :
				ADC->InjectedSeqReg.rw_4thInjectedSequenceConversion = params.channelNum;
				break;
		}
	}

	// Regular Channel Setup
	else {
		switch (params.conversionOrderNum) {
			case 1 :
				ADC->RegularSequenceReg3.rw_1stRegSequenceConversion = params.channelNum;
				break;
			case 2 :
				ADC->RegularSequenceReg3.rw_2ndRegSequenceConversion = params.channelNum;
				break;
			case 3 :
				ADC->RegularSequenceReg3.rw_3rdRegSequenceConversion = params.channelNum;
				break;
			case 4 :
				ADC->RegularSequenceReg3.rw_4thRegSequenceConversion = params.channelNum;
				break;
			case 5 :
				ADC->RegularSequenceReg3.rw_5thRegSequenceConversion = params.channelNum;
				break;
			case 6 :
				ADC->RegularSequenceReg3.rw_6thRegSequenceConversion = params.channelNum;
				break;
			case 7 :
				ADC->RegularSequenceReg2.rw_7thRegSequenceConversion = params.channelNum;
				break;
			case 8 :
				ADC->RegularSequenceReg2.rw_8thRegSequenceConversion = params.channelNum;
				break;
			case 9 :
				ADC->RegularSequenceReg2.rw_9thRegSequenceConversion = params.channelNum;
				break;
			case 10 :
				ADC->RegularSequenceReg2.rw_10thRegSequenceConversion = params.channelNum;
				break;
			case 11 :
				ADC->RegularSequenceReg2.rw_11thRegSequenceConversion = params.channelNum;
				break;
			case 12 :
				ADC->RegularSequenceReg2.rw_12thRegSequenceConversion = params.channelNum;
				break;
			case 13 :
				ADC->RegularSequenceReg1.rw_13thRegSequenceConversion = params.channelNum;
				break;
			case 14 :
				ADC->RegularSequenceReg1.rw_14thRegSequenceConversion = params.channelNum;
				break;
			case 15 :
				ADC->RegularSequenceReg1.rw_15thRegSequenceConversion = params.channelNum;
				break;
			case 16 :
				ADC->RegularSequenceReg1.rw_16thRegSequenceConversion = params.channelNum;
				break;
		}
	}
	
}

static void ADCClockSelect(uint8_t adcNumber) {
	
	switch(adcNumber) {
		
		case 1 :
			ADCClock->adc1_StartTick = 1;
			break;
		case 2 :
			ADCClock->adc2_StartTick = 1;
			break;
		case 3 :
			ADCClock->adc3_StartTick = 1;
			break;
	}
}

static ADCx* Get_ADC(char adcNum) {

	switch(adcNum) {

		case 1:
			return ADC1;
		case 2:
			return ADC2;
		case 3:
			return ADC3;
		default:
			return ((void*)0);
	}
}

static void Set_ChannelSamplePeriod(ADCx *ADC, ADC_Params params) {
	
	switch (params.channelNum) {
		case 0 :
			ADC->SampleTimeReg2.rw_Channel0SamplePeriod = params.cycles;
			break;
		case 1 :
			ADC->SampleTimeReg2.rw_Channel1SamplePeriod = params.cycles;
			break;
		case 2 :
			ADC->SampleTimeReg2.rw_Channel2SamplePeriod = params.cycles;
			break;
		case 3 :
			ADC->SampleTimeReg2.rw_Channel3SamplePeriod = params.cycles;
			break;
		case 4 :
			ADC->SampleTimeReg2.rw_Channel4SamplePeriod = params.cycles;
			break;
		case 5 :
			ADC->SampleTimeReg2.rw_Channel5SamplePeriod = params.cycles;
			break;
		case 6 :
			ADC->SampleTimeReg2.rw_Channel6SamplePeriod = params.cycles;
			break;
		case 7 :
			ADC->SampleTimeReg2.rw_Channel7SamplePeriod = params.cycles;
			break;
		case 8 :
			ADC->SampleTimeReg2.rw_Channel8SamplePeriod = params.cycles;
			break;
		case 9 :
			ADC->SampleTimeReg2.rw_Channel9SamplePeriod = params.cycles;
			break;
		case 10 :
			ADC->SampleTimeReg1.rw_Channel10SamplePeriod = params.cycles;
			break;
		case 11 :
			ADC->SampleTimeReg1.rw_Channel11SamplePeriod = params.cycles;
			break;
		case 12 :
			ADC->SampleTimeReg1.rw_Channel12SamplePeriod = params.cycles;
			break;
		case 13 :
			ADC->SampleTimeReg1.rw_Channel13SamplePeriod = params.cycles;
			break;
		case 14 :
			ADC->SampleTimeReg1.rw_Channel14SamplePeriod = params.cycles;
			break;
		case 15 :
			ADC->SampleTimeReg1.rw_Channel15SamplePeriod = params.cycles;
			break;
		case 16 :
			ADC->SampleTimeReg1.rw_Channel16SamplePeriod = params.cycles;
			break;
		case 17 :
			ADC->SampleTimeReg1.rw_Channel17SamplePeriod = params.cycles;
			break;
		case 18 :
			ADC->SampleTimeReg1.rw_Channel18SamplePeriod = params.cycles;
			break;
	}
}		

