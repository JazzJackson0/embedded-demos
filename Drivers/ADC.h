//STM32F407 Driver
#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>
#include "GPIO.h"

typedef struct adc_params ADC_Params;

//CLOCK
#define CLOCK 0x40023800
#define APB2 0x44
#define ADDR_ADC_CLOCK ( (ADC_CLOCK*) ((CLOCK) + APB2) )

//ADCx
typedef struct _adc ADCx;
typedef struct _adcCommon CommonADCRegisters;
#define ADC_BASE 0x40012000
#define ADDR_ADC1 ( (ADCx*) ((ADC_BASE) + 0x000) )
#define ADDR_ADC2 ( (ADCx*) ((ADC_BASE) + 0x100) )
#define ADDR_ADC3 ( (ADCx*) ((ADC_BASE) + 0x200) )
#define ADDR_COMMON_ADC_REG ( (CommonADCRegisters*) ((ADC_BASE) + 0x300) )


//For ADC_CONTROL2
/*Injected Group External Events*/
#define IJ_TIM1_CC4 0x00
#define IJ_TIM1_TRGO 0x01
#define IJ_TIM2_CC1 0x02
#define IJ_TIM2_TRGO 0x03
#define IJ_TIM3_CC2 0x04
#define IJ_TIM3_CC4 0x05
#define IJ_TIM4_CC1 0x06
#define IJ_TIM4_CC2 0x07
#define IJ_TIM4_CC3 0x08
#define IJ_TIM4_TRGO 0x09
#define IJ_TIM5_CC4 0x0A
#define IJ_TIM5_TRGO 0x0B
#define IJ_TIM8_CC2 0x0C
#define IJ_TIM8_CC3 0x0D
#define IJ_TIM8_CC4 0x0E
#define IJ_EXTI_LINE15 0x0F
/*Regular Group External Events*/
#define TIM1_CC1 0x00
#define TIM1_CC2 0x01
#define TIM1_CC3 0x02
#define TIM2_CC2 0x03
#define TIM2_CC3 0x04
#define TIM2_CC4 0x05
#define TIM2_TRGO 0x06
#define TIM3_CC1 0x07
#define TIM3_TRGO 0x08
#define TIM4_CC4 0x09
#define TIM5_CC1 0x0A
#define TIM5_CC2 0x0B
#define TIM5_CC3 0x0C
#define TIM8_CC1 0x0D
#define TIM8_TRGO 0x0E
#define EXTI_LINE11 0x0F
/*External Trigger Polarity*/
#define DISABLED 0x00
#define RISING_EDGE 0x01
#define FALLING_EDGE 0x02
#define RISING_AND_FALLING 0x03

/*Injected Sequence Length (i.e. Num of Conversions)*/
#define _1_IJ_CONVERSION 0x00
#define _2_IJ_CONVERSIONS 0x01
#define _3_IJ_CONVERSIONS 0x02
#define _4_IJ_CONVERSIONS 0x03

//FOR ADC_COMMON_CONTROL Register
/*Multi ADC Mode Selection*/
#define INDEPENDENT 0x00
#define DUAL_1_2_COMBINED_REG_SIMULT_INJECTED_SIMULT 0x01
#define DUAL_1_2_COMBINED_REG_SIMULT_ALT_TRIG 0x02
#define RESERVED0 0x03
#define DUAL_1_2_INJECTED_SIMULTANEOUS 0x05
#define DUAL_1_2_REG_SIMULTANEOUS 0x06
#define DUAL_1_2_INTERLEAVED 0x07
#define DUAL_1_2_ALT_TRIG 0x09
#define TRIPPLE_1_2_3_COMBINED_REG_SIMULT_INJECTED_SIMULT 0x11
#define TRIPPLE_1_2_3_COMBINED_REG_SIMULT_ALT_TRIG 0x12
#define RESERVED1 0x13
#define TRIPPLE_1_2_3_INJECTED_SIMULTANEOUS 0x15
#define TRIPPLE_1_2_3_REG_SIMULTANEOUS 0x16
#define TRIPPLE_1_2_3_INTERLEAVED 0x17
#define TRIPPLE_1_2_3_ALT_TRIG 0x19
/*Delay Between 2 Sample Phases*/
#define CLKx5 0x00
#define CLKx6 0x01
#define CLKx7 0x02
#define CLKx8 0x03
#define CLKx9 0x04
#define CLKx10 0x05
#define CLKx11 0x06
#define CLKx12 0x07
#define CLKx13 0x08
#define CLKx14 0x09
#define CLKx15 0x0A
#define CLKx16 0x0B
#define CLKx17 0x0C
#define CLKx18 0x0D
#define CLKx19 0x0E
#define CLKx20 0x0F
/*DMA Mode*/
#define DISABLED 0x00
#define MODE_1 0x01
#define MODE_2 0x02
#define MODE_3 0x03
/*DADC Clock Prescaler*/
#define DIV_2 0x00
#define DIV_4 0x01
#define DIV_6 0x02
#define DIV_8 0x03
//FOR ADC SEQUENCE Registers 1-3 (and Injected)
/*Channels to be given a Conversion Order*/

#define ADC_CH_0 0x00
#define ADC_CH_1 0x01
#define ADC_CH_2 0x02
#define ADC_CH_3 0x03
#define ADC_CH_4 0x04
#define ADC_CH_5 0x05
#define ADC_CH_6 0x06
#define ADC_CH_7 0x07
#define ADC_CH_8 0x08
#define ADC_CH_9 0x09
#define ADC_CH_10 0x0A
#define ADC_CH_11 0x0B
#define ADC_CH_12 0x0C
#define ADC_CH_13 0x0D
#define ADC_CH_14 0x0E
#define ADC_CH_15 0x0F
#define ADC_CH_16 0x10
#define ADC_CH_17 0x11
#define ADC_CH_18 0x12
//For ADC_SAMPLETIME Registers 1 & 2
/*Channel Sample Periods*/
#define ADC_SAMPLE_3_CYCLES 0x00
#define ADC_SAMPLE_15_CYCLES 0x01
#define ADC_SAMPLE_28_CYCLES 0x02
#define ADC_SAMPLE_56_CYCLES 0x03
#define ADC_SAMPLE_84_CYCLES 0x04
#define ADC_SAMPLE_112_CYCLES 0x05
#define ADC_SAMPLE_144_CYCLES 0x06
#define ADC_SAMPLE_480_CYCLES 0x07

//For ADC_CONTROL1
/*Resolution*/
#define ADC_12BIT_RES 0x00 //15 ADCCLK cycles
#define ADC_10BIT_RES 0x01 //13 ADCCLK cycles
#define ADC_8BIT_RES 0x02 //11 ADCCLK cycles
#define ADC_6BIT_RES 0x03 //9 ADCCLK cycles

//FOR ADC SEQUENCE Registers (Reg and Injected)
/*Reg Sequence Length (i.e. Num of Conversions)*/
#define ADC_1_CONVERSION 0x00
#define ADC_2_CONVERSIONS 0x01
#define ADC_3_CONVERSIONS 0x02
#define ADC_4_CONVERSIONS 0x03
#define ADC_5_CONVERSIONS 0x04
#define ADC_6_CONVERSIONS 0x05
#define ADC_7_CONVERSIONS 0x06
#define ADC_8_CONVERSIONS 0x07
#define ADC_9_CONVERSIONS 0x08
#define ADC_10_CONVERSIONS 0x09
#define ADC_11_CONVERSIONS 0x0A
#define ADC_12_CONVERSIONS 0x0B
#define ADC_13_CONVERSIONS 0x0C
#define ADC_14_CONVERSIONS 0x0D
#define ADC_15_CONVERSIONS 0x0E
#define ADC_16_CONVERSIONS 0x0F

#define ADC_REGULAR_CH 0 
#define ADC_INJECTED_CH 1

#define ADC_SINGLE_CONV 0
#define ADC_CONTINUOUS_CONV 1




/**
ADC Pins ---------------------------
		These are 'Additional Functions' not 'Alternate Functions'
		Meaning: Functions are directly selected/enabled through peripheral registers.
		They are not selected through GPIOx_AFR registers.
		
		+ ADC3_IN4: PF6
		+ ADC3_IN5: PF7
		+ ADC3_IN6: PF8
		+ ADC3_IN7: PF9
		+ ADC3_IN8: PF10
		+ ADC3_IN9: PF3
		+ ADC3_IN14: PF4
		+ ADC3_IN15: PF5
	
		+ ADC12_IN4: PA4
		+ ADC12_IN5: PA5
		+ ADC12_IN6: PA6
		+ ADC12_IN7: PA7
		+ ADC12_IN8: PB0
		+ ADC12_IN9: PB1
		+ ADC12_IN14: PC4
		+ ADC12_IN15: PC5
		
		+ ADC123_IN0: PA0
		+ ADC123_IN1: PA1
		+ ADC123_IN2: PA2
		+ ADC123_IN3: PA3
		+ ADC123_IN10: PC0
		+ ADC123_IN11: PC1
		+ ADC123_IN12: PC2
		+ ADC123_IN13: PC3
		------------------------------------
**/


//DECLARATIONS
/**
 * @brief Initialize ADC
 * 
 * @param adcNumber ADC Number. (1 - 3)
 * @param params
 * @param port 
 * @param pin 
 * @return ** void 
 */
void ADC_Init(uint8_t adcNumber, ADC_Params params, char port, uint8_t pin);


/**
 * @brief Start Conversion
 * 
 * @param adcNumber ADC Number. (1 - 3)
 * @param channelType Regular or Injected
 */
void ADC_StartConversion(uint8_t adcNumber, uint8_t channelType);



/**
 * @brief Stop Conversion
 * 
 * @param adcNumber ADC Number. (1 - 3)
 * @param channelType Regular or Injected
 */
void ADC_StopConversion(uint8_t adcNumber, uint8_t channelType);



/**
 * @brief Read Channel Conversion Result. 
 * 
 * @param adcNumber ADC Number. (1 - 3)
 * @param params
 * @return ** int16_t Channel Conversion Result
 */
int16_t ADC_ConversionResult(uint8_t adcNumber, ADC_Params params);


/**
 * @brief 
 * 
 * @param adcNumber ADC Number. (1 - 3)
 * @param channelType Regular or Injected
 * @param triggerPolarity 
 * @param triggerSource 
 */
void ADC_SetExternalTrigger(uint8_t adcNumber, uint8_t channelType, uint8_t triggerPolarity, uint8_t triggerSource);

/**
 * @brief Enable use of DMA to transfer conversion results
 * 
 * @param adcNumber 
 */
void ADC_UseDMA(uint8_t adcNumber);


// Enums----------------------------------------------------------------------








// Structs------------------------------------------------------------------

/**
 * @brief 
 * 
 * @param channelType Regular or Injected
 * @param channelNum ADC (Regular) Channel Number. (CH_0 - CH_18)
 * @param conversionOrderNum Set the conversion order for the Channel (1st - 16th conversion) 
 * @param cycles Number of clock cycles per sample. (_x_CYCLES: Where x = 3, 15, 28, 56, 
 * 				84, 112, 144, 480)
 * @param resolution ADC Resolution. (_xBIT_ADC: Where x = 10, 12, 16, 18)
 * @param singleContinuous A SINGLE conversion or CONTINUOUS conversions.
 * @param numOfConversions Number of Channels to be converted in the Sequence of 16.
 * 							|||  _x_CONVERSION: Where x = 1 - 16
 * 							||| Example: _3_CONVERSIONS = Only 1st, 2nd and 3rd Channels in
 * 								conversion sequence will run (Out of a Max of a sequence of 16) .
 */
struct adc_params {
	uint8_t channelType;
	uint8_t channelNum;
	uint8_t conversionOrderNum;
	uint8_t cycles;
	uint8_t resolution;
	uint8_t singleContinuous;
	uint8_t numOfConversions;
};

//Registers------------------------------------------------------------------

typedef struct {
	const uint32_t reserved0:8;
	volatile uint32_t adc1_StartTick:1;
	volatile uint32_t adc2_StartTick:1;
	volatile uint32_t adc3_StartTick:1;
	const uint32_t reserved1:21;
}ADC_CLOCK;


typedef struct {
	volatile uint32_t analogWatchdogEventOccurred:1;
	volatile uint32_t regChannelEndOfConversion:1;
	volatile uint32_t injectedChannelEndOfConversion:1;
	volatile uint32_t injectedChannelConversionStarted:1;
	volatile uint32_t regChannelconversionStarted:1;
	volatile uint32_t overrunOccurred:1;
	const uint32_t reserved:26;
}ADC_STATUS;


typedef struct {
	volatile uint32_t rw_ADCAnalogInputChannel:5;
	volatile uint32_t enable_EndOfConversionInterrupt:1;
	volatile uint32_t enable_AnalogWatchDogInterrupt:1;
	volatile uint32_t enable_EndOfInjectedConversionInterrupt:1;
	volatile uint32_t enable_ScanMode:1;
	volatile uint32_t enable_AnalogWatchDogOnSingleChannel:1;
	volatile uint32_t enable_AutoInjectedGroupConversion:1;
	volatile uint32_t enable_RegChannelDiscontinuousMode:1;
	volatile uint32_t enable_InjectedChannelDiscontinuousMode:1;
	volatile uint32_t rw_NumOfDiscontinuousModeChannels:3;
	const uint32_t reserved0:6;
	volatile uint32_t enable_AnalogWatchDogInjectedChannels:1;
	volatile uint32_t enable_AnalogWatchDogRegChannels:1;
	volatile uint32_t rw_Resolution:2;
	volatile uint32_t enable_OverrunInterrupt:1;
	const uint32_t reserved1:5;
}ADC_CONTROL1;


typedef struct {
	volatile uint32_t enable_ADC:1;
	volatile uint32_t singleConvert0_continuousConvert1:1;
	const uint32_t reserved0:6;
	volatile uint32_t enable_DMAMode:1;
	volatile uint32_t enable_continuousDMARequests:1;
	volatile uint32_t eocSetPerRegSequence0_eocSetPerRegConversion1:1;
	volatile uint32_t rightAlignedData0_leftAlignedData1:1;
	const uint32_t reserved1:4;
	volatile uint32_t rw_InjectedGroupExternalEvent:4;
	volatile uint32_t enable_InjectedExternalTriggerPolarity:2;
	volatile uint32_t start_InjectedChannelConversion:1;
	const uint32_t reserved2:1;
	volatile uint32_t rw_RegGroupExternalEvent:4;
	volatile uint32_t enable_RegExternalTriggerPolarity:2;
	volatile uint32_t start_RegChannelConversion:1;
	const uint32_t reserved3:1;
}ADC_CONTROL2;


typedef struct {
	volatile uint32_t rw_Channel10SamplePeriod:3;
	volatile uint32_t rw_Channel11SamplePeriod:3;
	volatile uint32_t rw_Channel12SamplePeriod:3;
	volatile uint32_t rw_Channel13SamplePeriod:3;
	volatile uint32_t rw_Channel14SamplePeriod:3;
	volatile uint32_t rw_Channel15SamplePeriod:3;
	volatile uint32_t rw_Channel16SamplePeriod:3;
	volatile uint32_t rw_Channel17SamplePeriod:3;
	volatile uint32_t rw_Channel18SamplePeriod:3;
	const uint32_t reserved:5;
}ADC_SAMPLETIME1;


typedef struct {
	volatile uint32_t rw_Channel0SamplePeriod:3;
	volatile uint32_t rw_Channel1SamplePeriod:3;
	volatile uint32_t rw_Channel2SamplePeriod:3;
	volatile uint32_t rw_Channel3SamplePeriod:3;
	volatile uint32_t rw_Channel4SamplePeriod:3;
	volatile uint32_t rw_Channel5SamplePeriod:3;
	volatile uint32_t rw_Channel6SamplePeriod:3;
	volatile uint32_t rw_Channel7SamplePeriod:3;
	volatile uint32_t rw_Channel8SamplePeriod:3;
	volatile uint32_t rw_Channel9SamplePeriod:3;
	const uint32_t reserved:2;
}ADC_SAMPLETIME2;


typedef struct {
	volatile uint32_t rw_InjectedChannelDataOffset:12;
	const uint32_t reserved:20;
}ADC_INJECTED_CHANNEL_DATA_OFFSET;


typedef struct {
	volatile uint32_t rw_AnalogWatchDogHigherThreshold:12;
	const uint32_t reserved:20;
}ADC_WATCHDOG_HIGHER_THRESHOLD;


typedef struct {
	volatile uint32_t rw_AnalogWatchDogLowerThreshold:12;
	const uint32_t reserved:20;
}ADC_WATCHDOG_LOWER_THRESHOLD;


typedef struct {
	volatile uint32_t rw_13thRegSequenceConversion:5;
	volatile uint32_t rw_14thRegSequenceConversion:5;
	volatile uint32_t rw_15thRegSequenceConversion:5;
	volatile uint32_t rw_16thRegSequenceConversion:5;
	volatile uint32_t rw_NumOfConversionsInRegSequence:4;
	const uint32_t reserved:8;
}ADC_REGULAR_SEQUENCE1;


typedef struct {
	volatile uint32_t rw_7thRegSequenceConversion:5;
	volatile uint32_t rw_8thRegSequenceConversion:5;
	volatile uint32_t rw_9thRegSequenceConversion:5;
	volatile uint32_t rw_10thRegSequenceConversion:5;
	volatile uint32_t rw_11thRegSequenceConversion:5;
	volatile uint32_t rw_12thRegSequenceConversion:5;
	const uint32_t reserved:2;
}ADC_REGULAR_SEQUENCE2;


typedef struct {
	volatile uint32_t rw_1stRegSequenceConversion:5;
	volatile uint32_t rw_2ndRegSequenceConversion:5;
	volatile uint32_t rw_3rdRegSequenceConversion:5;
	volatile uint32_t rw_4thRegSequenceConversion:5;
	volatile uint32_t rw_5thRegSequenceConversion:5;
	volatile uint32_t rw_6thRegSequenceConversion:5;
	const uint32_t reserved:2;
}ADC_REGULAR_SEQUENCE3;


typedef struct {
	volatile uint32_t rw_1stInjectedSequenceConversion:5;
	volatile uint32_t rw_2ndInjectedSequenceConversion:5;
	volatile uint32_t rw_3rdInjectedSequenceConversion:5;
	volatile uint32_t rw_4thInjectedSequenceConversion:5;
	volatile uint32_t rw_NumOfConversionsInInjectedSequence:2;
	const uint32_t reserved:10;
}ADC_INJECTED_SEQUENCE;


typedef struct {
	volatile uint32_t read_InjectedConversionDataResult:16;
	const uint32_t reserved:16;
}ADC_INJECTED_DATA;


typedef struct {
	volatile uint32_t read_RegularConversionDataResult:16;
	const uint32_t reserved:16;
}ADC_REGULAR_DATA;


typedef struct {
	volatile uint32_t analogWatchDogEventOccurred_ADC1:1;
	volatile uint32_t endOfConversion_ADC1:1;
	volatile uint32_t endOfInjectedConversion_ADC1:1;
	volatile uint32_t injectedChannelStarted_ADC1:1;
	volatile uint32_t regularChannelStarted_ADC1:1;
	volatile uint32_t overrunOccurred_ADC1:1;
	const uint32_t reserved0:2;
	volatile uint32_t analogWatchDogEventOccurred_ADC2:1;
	volatile uint32_t endOfConversion_ADC2:1;
	volatile uint32_t endOfInjectedConversion_ADC2:1;
	volatile uint32_t injectedChannelStarted_ADC2:1;
	volatile uint32_t regularChannelStarted_ADC2:1;
	volatile uint32_t overrunOccurred_ADC2:1;
	const uint32_t reserved1:2;
	volatile uint32_t analogWatchDogEventOccurred_ADC3:1;
	volatile uint32_t endOfConversion_ADC3:1;
	volatile uint32_t endOfInjectedConversion_ADC3:1;
	volatile uint32_t injectedChannelStarted_ADC3:1;
	volatile uint32_t regularChannelStarted_ADC3:1;
	volatile uint32_t overrunOccurred_ADC3:1;
	const uint32_t reserved2:10;
}ADC_COMMON_STATUS;


typedef struct {
	volatile uint32_t rw_MultiADCOperatingMode:5;
	const uint32_t reserved0:3;
	volatile uint32_t rw_DelayBtwn2SamplePhases:4;
	const uint32_t reserved1:1;
	volatile uint32_t enable_ContinuousDMARequestsMultiADC:1;
	volatile uint32_t enable_DMAModeMultiADC:2;
	volatile uint32_t rw_ADCPrescaler:2;
	const uint32_t reserved2:4;
	volatile uint32_t enable_VBATChannel:1;
	volatile uint32_t enable_TempSensor_and_VREFINT:1;
	const uint32_t reserved3:8;
}ADC_COMMON_CONTROL;


typedef struct {
	volatile uint32_t read_DataItem1:16;
	volatile uint32_t read_DataItem2:16;
}ADC_COMMON_REGDATA_DUAL_AND_TRIPPLE_NODES;




struct _adc {

	ADC_STATUS StatusReg; // 0x00
	ADC_CONTROL1 ControlReg1; // 0x04
	ADC_CONTROL2 ControlReg2; // 0x08
	ADC_SAMPLETIME1 SampleTimeReg1; // 0x0C
	ADC_SAMPLETIME2 SampleTimeReg2; // 0x10
	ADC_INJECTED_CHANNEL_DATA_OFFSET InjChannelDataOffsetReg1; // 0x14
	ADC_INJECTED_CHANNEL_DATA_OFFSET InjChannelDataOffsetReg2; // 0x18
	ADC_INJECTED_CHANNEL_DATA_OFFSET InjChannelDataOffsetReg3; // 0x1C
	ADC_INJECTED_CHANNEL_DATA_OFFSET InjChannelDataOffsetReg4; // 0x20
	ADC_WATCHDOG_HIGHER_THRESHOLD WatchDogHighThreshReg; // 0x24
	ADC_WATCHDOG_LOWER_THRESHOLD WatchDogLowThreshReg; // 0x28
	ADC_REGULAR_SEQUENCE1 RegularSequenceReg1; // 0x2C
	ADC_REGULAR_SEQUENCE2 RegularSequenceReg2; // 0x30
	ADC_REGULAR_SEQUENCE3 RegularSequenceReg3; // 0x34
	ADC_INJECTED_SEQUENCE InjectedSeqReg; // 0x38
	ADC_INJECTED_DATA InjectedDataReg1; // 0x3C
	ADC_INJECTED_DATA InjectedDataReg2; // 0x40
	ADC_INJECTED_DATA InjectedDataReg3; // 0x44
	ADC_INJECTED_DATA InjectedDataReg4; // 0x48
	ADC_REGULAR_DATA RegularDataReg; // 0x4C
};

struct _adcCommon {
	ADC_COMMON_STATUS CommonStatusReg; // 0x300
	ADC_COMMON_CONTROL CommonControlReg; // 0x304
	ADC_COMMON_REGDATA_DUAL_AND_TRIPPLE_NODES CommonRegularDataDualTrippleNodeReg; // 0x308
};


#endif
