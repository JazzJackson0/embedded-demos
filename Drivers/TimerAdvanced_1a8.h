//STM32F407 Driver
#ifndef TIMERADVANCED1_A8_H_
#define TIMERADVANCED1_A8_H_
//Advanced Timers 1 & 8
#include <stdint.h>
#include <stdio.h>
#include "GPIO.h"

//CLOCK
#define CLOCK 0x40023800
#define APB2 0x44
#define ADDR_TIM1_8_CLOCK ( (TIM1_8_CLOCK*) ((CLOCK) + APB2) )

//TIMERS
typedef struct _advanced_timer ADVANCED_TIMERx;
#define TIM1_BASE 0x40010000
#define ADDR_TIM1 ( (ADVANCED_TIMERx*) ((TIM1_BASE) + 0x000) )
#define ADDR_TIM8 ( (ADVANCED_TIMERx*) ((TIM1_BASE) + 0x400) )


//TIM1_A8_CONTROL1
/*Alignment Mode*/
#define EDGE_ALIGN 0x00
#define CENTER_ALIGN_DOWNCOUNT 0x01
#define CENTER_ALIGN_UPCOUNT 0x02
#define CENTER_ALIGN_UP_DOWN 0x03
/*Alignment Mode*/
#define TIMCLOCK 0x00
#define TIMCLOCK_x2 0x01
#define TIMCLOCK_x4 0x02

//TIM1_A8_CONTROL2
/*Master Mode*/
#define RESET 0x00
#define COUNTEN_SIGNAL_AS_TRIGOUT 0x01
#define UPDATEEVENT_AS_TRIGOUT 0x02
#define COMPARE_PULSE_AS_TRIGOUT 0x03
#define OUTCOMP1_AS_TRIGOUT 0x04
#define OUTCOMP2_AS_TRIGOUT 0x05
#define OUTCOMP3_AS_TRIGOUT 0x06
#define OUTCOMP4_AS_TRIGOUT 0x07

//TIM1_A8_SLAVEMODE_CONTROL & TIM1_A8_CAPTURECOMP_MODE1 (For Input Capture Filter)
/*Slave Mode Selection*/
#define DISABLE_SLAVEMODE 0x00
#define ENCODERMODE_1 0x01
#define ENCODERMODE_2 0x02
#define ENCODERMODE_3 0x03
#define EDGE_DETECT 0x04
#define RESET_MODE 0x05
#define GATED_MODE 0x06
#define TRIGGER_MODE 0x07
/*Trigger Selection*/
#define INTERNAL_TRIG0 0x00
#define INTERNAL_TRIG1 0x01
#define INTERNAL_TRIG2 0x02
#define INTERNAL_TRIG3 0x03
#define EDGE_DETECT 0x04
#define FILTERED_TIM_INPUT1 0x05
#define FILTERED_TIM_INPUT2 0x06
#define EXTERNAL_TRIG_INPUT 0x07
/*External Trigger Filter AND Input Capture Filter*/
#define NO_FILTER 0x00
#define _2EVENTVAL 0x01
#define _4EVENTVAL 0x02
#define _8EVENTVAL 0x03
#define DIV2_8EVENTVAL 0x04
#define DIV2_6EVENTVAL 0x05
#define DIV4_8EVENTVAL 0x06
#define DIV4_6EVENTVAL 0x07
#define DIV8_8EVENTVAL 0x08
#define DIV8_6EVENTVAL 0x09
#define DIV16_8EVENTVAL 0x0A
#define DIV16_5EVENTVAL 0x0B
#define DIV16_6EVENTVAL 0x0C
#define DIV32_8EVENTVAL 0x0D
#define DIV32_5EVENTVAL 0x0E
#define DIV32_6EVENTVAL 0x0F

//TIM1_A8_CAPTURECOMP_MODE1
/*Output Compare Modes*/
#define FROZEN 0x00
#define ACTIVE_ON_MATCH 0x01
#define INACTIVE_ON_MATCH 0x02
#define TOGGLE_ON_MATCH 0x03
#define FORCE_INACTIVE 0x04
#define FORCE_ATCIVE 0x05
#define PWM_ACTIVE_UNTIL_MATCH 0x06
#define PWM_INACTIVE_UNTIL_MATCH 0x07
/*Choose Input Pin Mapping*/
#define MAPTO_TI1 0x01
#define MAPTO_TI2 0x02
#define MAPTO_TRC 0x03
/*Input Capture Prescaler*/
#define A1_8_NO_PRESSCALE 0x00
#define CAPTURE_EVERY_2EVENTS 0x01
#define CAPTURE_EVERY_4EVENTS 0x02
#define CAPTURE_EVERY_8EVENTS 0x03


/**
TIMER Pins ---------------------------
		+ TIM1_CH1: PA8, PE9 (AF1)
		+ TIM1_CH2: PA9, PE11 (AF1)
		+ TIM1_CH3: PA10, PE13 (AF1)
		+ TIM1_CH4: PA11, PE14 (AF1)
		+ TIM1_CH1N: PA7 (AF1)
		+ TIM1_CH1N: PB13, PE8 (AF1)
		+ TIM1_CH2N: PB0, PB14, PE10 (AF1)
		+ TIM1_CH3N: PB1, PB15, PE12 (AF1)
		+ TIM1_ETR: PA12, PE7 (AF1)
		+ TIM1_BKIN: PA6, PB12, PE15 (AF1)
		
		+ TIM8_CH1: PC6, PI5 (AF3)
		+ TIM8_CH2: PC7, PI6 (AF3)
		+ TIM8_CH3: PC8, PI7 (AF3)
		+ TIM8_CH4: PC9, PI2 (AF3)
		+ TIM8_CH1N: PA5, PA7, PH13 (AF3)
		+ TIM8_CH2N: PB0, PB14, PH14 (AF3)
		+ TIM8_CH3N: PB1, PB15, PH15 (AF3)
		+ TIM8_ETR: PA0, PI3 (AF3)
		+ TIM8_BKIN: PA6, PI4 (AF3)
		------------------------------------
**/

//DECLARATIONS
/**
 * @brief Initialize and Start Timer
 * @param timerNum Timer Number (1 & 8)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @return ** uint8_t 
 */
uint8_t AdvancedTimer_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time);
/**
 * @brief Initialize and Start Pulse Width Modulation
 * @param timerNum Timer Number (1 & 8)
 * @param captCompNum Capture Compare Number (1 - 4)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @param dutyCyclePercent PWM Duty Cycle as a percentage value (0% - 100%).
 * @return ** void 
 */
void AdvancedPWM_Start(uint8_t timerNum, uint8_t captCompNum, uint16_t prescaler, 
	uint16_t time, float dutyCyclePercent);
/**
 * @brief Update Pulse Width Modulation with new Duty Cycle
 * 
 * @param timerNum Timer Number (1 & 8)
 * @param captCompNum Capture Compare Number (1 - 4)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @param dutyCyclePercent PWM Duty Cycle as a percentage value (0% - 100%).
 * @return ** void 
 */
void AdvancedPWM_Update(uint8_t timerNum, uint8_t captCompNum, uint16_t time, float dutyCyclePercent);



//Registers------------------------------------------------------------------------
typedef struct {
	volatile uint32_t tim1_StartTick:1;
	volatile uint32_t tim8_StartTick:1;
	const uint32_t reserved:30;
}TIM1_8_CLOCK ;

typedef struct {
	volatile uint16_t enable_Counter:1;
	volatile uint16_t disable_UpdateEventGeneration:1;
	volatile uint16_t updateOnOverflowUnderflowOrDMA:1;
	volatile uint16_t enable_OnePulseMode:1;
	volatile uint16_t upCounter0_downCounter1:1;
	volatile uint16_t rw_AlignmentMode:2;
	volatile uint16_t enable_AutoReloadPreload:1;
	volatile uint16_t rw_ClockDivisionRatio:2;
	const uint16_t reserved:6;
}TIM1_A8_CONTROL1;

typedef struct {
	volatile uint16_t preloadCCxECCxNEAndOCxM:1;
	const uint16_t reserved0:1;
	volatile uint16_t updatePreloadsWithCOMGBit0_updatePreloadsWithCOMGAndRiseEdge1:1;
	volatile uint16_t dmaSendOnCaptCompEvent0_dmaSendOnUpdateEvent1:1;
	volatile uint16_t rw_MasterMode:3;
	volatile uint16_t channel1ToTimInput0_channel123toTimInput1:1;
	volatile uint16_t OutComp1LowIdle0_OutComp1HighIdle1:1;
	volatile uint16_t OutComp1NLowIdle0_OutComp1NHighIdle1:1;
	volatile uint16_t OutComp2LowIdle0_OutComp2HighIdle1:1;
	volatile uint16_t OutComp2NLowIdle0_OutComp2NHighIdle1:1;
	volatile uint16_t OutComp3LowIdle0_OutComp3HighIdle1:1;
	volatile uint16_t OutComp3NLowIdle0_OutComp3NHighIdle1:1;
	volatile uint16_t OutComp4LowIdle0_OutComp4HighIdle1:1;
	const uint16_t reserved1:1;
}TIM1_A8_CONTROL2;

typedef struct {
	volatile uint16_t rw_SlaveModeSelection:3;
	const uint16_t reserved:1;
	volatile uint16_t rw_TriggerInputType:3;
	volatile uint16_t enable_DelayEventEffectForSync:1;
	volatile uint16_t rw_ExternalTriggerFilter:4;
	volatile uint16_t rw_ExternalTriggerPrescaler:2;
	volatile uint16_t enable_ExternalClock:1;
	volatile uint16_t polarityActiveHigh0_polarityActiveLow1:1;
}TIM1_A8_SLAVEMODE_CONTROL;

typedef struct {
	volatile uint16_t enable_UpdateInterrupt:1;
	volatile uint16_t enable_CaptureComp1:1;
	volatile uint16_t enable_CaptureComp2:1;
	volatile uint16_t enable_CaptureComp3:1;
	volatile uint16_t enable_CaptureComp4:1;
	volatile uint16_t enable_COMInterrupt:1;
	volatile uint16_t enable_TriggerInterrupt:1;
	volatile uint16_t enable_BreakInterrupt:1;
	volatile uint16_t enable_DMAReqInterrupt:1;
	volatile uint16_t enable_CaptureComp1DMAReq:1;
	volatile uint16_t enable_CaptureComp2DMAReq:1;
	volatile uint16_t enable_CaptureComp3DMAReq:1;
	volatile uint16_t enable_CaptureComp4DMAReq:1;
	volatile uint16_t enable_COMDMAReq:1;
	volatile uint16_t enable_TriggerDMAReq:1;
	const uint16_t reserved3:1;
}TIM1_A8_DMAINTERRUPT_ENABLE;

typedef struct {
	volatile uint16_t updateInterruptOccurred:1;
	volatile uint16_t captureComp1InterruptOccurred:1;
	volatile uint16_t captureComp2InterruptOccurred:1;
	volatile uint16_t captureComp3InterruptOccurred:1;
	volatile uint16_t captureComp4InterruptOccurred:1;
	volatile uint16_t comInterruptOccurred:1;
	volatile uint16_t triggerInterruptOccurred:1;
	volatile uint16_t breakInterruptOccurred:1;
	volatile uint16_t captureComp1OvercaptureOccurred:1;
	volatile uint16_t captureComp2OvercaptureOccurred:1;
	volatile uint16_t captureComp3OvercaptureOccurred:1;
	volatile uint16_t captureComp4OvercaptureOccurred:1;
	const uint16_t reserved2:3;
}TIM1_A8_STATUS;

typedef struct {
	volatile uint16_t generate_UpdateEvent:1;
	volatile uint16_t generate_CaptureCompare1Event:1;
	volatile uint16_t generate_CaptureCompare2Event:1;
	volatile uint16_t generate_CaptureCompare3Event:1;
	volatile uint16_t generate_CaptureCompare4Event:1;
	volatile uint16_t generate_UpdateCaptCompControlBits:1;
	volatile uint16_t generate_TriggerEvent:1;
	volatile uint16_t generate_Break:1;
	const uint16_t reserved1:8;
}TIM1_A8_EVENTGEN;

typedef union {
	struct {
		const uint16_t reserved0:2;
		volatile uint16_t enable_OutputComp1FastResponse:1;
		volatile uint16_t enable_OutputComp1Preload:1;
		volatile uint16_t rw_OutputComp1Mode:3;
		volatile uint16_t enable_OutputComp1ClearOnExternalTrig:1;
		const uint16_t reserved1:2;
		volatile uint16_t enable_OutputComp2FastResponse:1;
		volatile uint16_t enable_OutputComp2Preload:1;
		volatile uint16_t rw_OutputComp2Mode:3;
		volatile uint16_t enable_OutputComp2ClearOnExternalTrig:1;
	}OutputCompareMode;

	struct {
		volatile uint16_t rw_InputCapt1PinMapping:2;
		volatile uint16_t rw_InputCapt1Prescaler:2;
		volatile uint16_t rw_InputCapt1Filter:4;
		volatile uint16_t rw_InputCapt2PinMapping:2;
		volatile uint16_t rw_InputCapt2Prescaler:2;
		volatile uint16_t rw_InputCapt2Filter:4;
	}InputCaptureMode;
}TIM1_A8_CAPTURECOMP_MODE1;

typedef union {
	struct {
		const uint16_t reserved0:2;
		volatile uint16_t enable_OutputComp3FastResponse:1;
		volatile uint16_t enable_OutputComp3Preload:1;
		volatile uint16_t rw_OutputComp3Mode:3;
		volatile uint16_t enable_OutputComp3ClearOnExternalTrig:1;
		const uint16_t reserved1:2;
		volatile uint16_t enable_OutputComp4FastResponse:1;
		volatile uint16_t enable_OutputComp4Preload:1;
		volatile uint16_t rw_OutputComp4Mode:3;
		volatile uint16_t enable_OutputComp4ClearOnExternalTrig:1;
	}OutputCompareMode;

	struct {
		volatile uint16_t rw_InputCapt3PinMapping:2;
		volatile uint16_t rw_InputCapt3Prescaler:2;
		volatile uint16_t rw_InputCapt3Filter:4;
		volatile uint16_t rw_InputCapt4PinMapping:2;
		volatile uint16_t rw_InputCapt4Prescaler:2;
		volatile uint16_t rw_InputCapt4Filter:4;
	}InputCaptureMode;
}TIM1_A8_CAPTURECOMP_MODE2;

typedef struct {
	volatile uint16_t enable_CaptComp1:1;
	volatile uint16_t cc1Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_ComplementaryCaptComp1:1;
	volatile uint16_t ccc1Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_CaptComp2:1;
	volatile uint16_t cc2Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_ComplementaryCaptComp2:1;
	volatile uint16_t ccc2Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_CaptComp3:1;
	volatile uint16_t cc3Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_ComplementaryCaptComp3:1;
	volatile uint16_t ccc3Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_CaptComp4:1;
	volatile uint16_t cc4Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved:1;
	volatile uint16_t ccc4Polarity_highOrPart1Input0_lowOrPart1Input1:1;
}TIM1_A8_CAPTURECOMP_ENABLE; // Alternate version for STM32F446 below

/*
Alternate version for STM32F446
typedef struct {
	volatile uint16_t enable_CaptComp1:1;
	volatile uint16_t cc1Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_ComplementaryCaptComp1:1;
	volatile uint16_t ccc1Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_CaptComp2:1;
	volatile uint16_t cc2Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_ComplementaryCaptComp2:1;
	volatile uint16_t ccc2Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_CaptComp3:1;
	volatile uint16_t cc3Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_ComplementaryCaptComp3:1;
	volatile uint16_t ccc3Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	volatile uint16_t enable_CaptComp4:1;
	volatile uint16_t cc4Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved:2;
}TIM1_A8_CAPTURECOMP_ENABLE;
*/

typedef struct {
	volatile uint16_t rw_CounterValue:16;
}TIM1_A8_COUNTER;

typedef struct {
	volatile uint16_t rw_PrescalerValue:16;
}TIM1_A8_PRESCALER;

typedef struct {
	volatile uint16_t rw_AutoReloadValue:16;
}TIM1_A8_AUTORELOAD;

typedef struct {
	volatile uint16_t rw_RepetitionCounterValue:8;
	const uint16_t reserved:8;
}REPETITION_COUNTER;

typedef struct {
	volatile uint16_t rw_CaptureCompValue:16;
}TIM1_A8_CAPTURECOMPx;

typedef struct {
	volatile uint16_t rw_DeadTimeGeneratorSetUp:8;
	volatile uint16_t rw_LockConfiguration:2;
	volatile uint16_t rw_OffStateForIdleMode:1;
	volatile uint16_t rw_OffStateForRunMode:1;
	volatile uint16_t enable_BreakInputs:1;
	volatile uint16_t breakInPolarityLow0_breakInPolarityHigh1:1;
	volatile uint16_t enable_AutoOutput:1;
	volatile uint16_t enable_MainOutput:1;
}BREAK_AND_DATETIME;

typedef struct {
	volatile uint16_t rw_DAMBaseAddress:5;
	const uint16_t reserved0:3;
	volatile uint16_t rw_DMABurstLength:5;
	const uint16_t reserved1:3;
}TIM1_A8_DMA_CONTROL;

typedef struct {
	volatile uint32_t rw_DMABurstAccessRegister:32;
}TIM1_A8_DMA_FULLTXADDRESS;






struct _advanced_timer {
	TIM1_A8_CONTROL1 ControlReg1; // 0x00
	TIM1_A8_CONTROL2 ControlReg2; // 0x04
	TIM1_A8_SLAVEMODE_CONTROL SlaveModeControlReg; // 0x08
	TIM1_A8_DMAINTERRUPT_ENABLE DMAInterruptEnableReg; // 0x0C
	TIM1_A8_STATUS StatusReg; // 0x10
	TIM1_A8_EVENTGEN EventGenReg; // 0x14
	TIM1_A8_CAPTURECOMP_MODE1 CaptureCompModeReg1; // 0x18
	TIM1_A8_CAPTURECOMP_MODE2 CaptureCompModeReg2; // 0x1C
	TIM1_A8_CAPTURECOMP_ENABLE CaptureCompEnableReg; // 0x20
	TIM1_A8_COUNTER CounterReg; // 0x24
	TIM1_A8_PRESCALER PrescalerReg; // 0x28
	TIM1_A8_AUTORELOAD AutoReloadReg; // 0x2C
	REPETITION_COUNTER RepititionCounterReg; // 0x30
	TIM1_A8_CAPTURECOMPx CaptureComp1Reg; // 0x34
	TIM1_A8_CAPTURECOMPx CaptureComp2Reg; // 0x38
	TIM1_A8_CAPTURECOMPx CaptureComp3Reg; // 0x3C
	TIM1_A8_CAPTURECOMPx CaptureComp4Reg; // 0x40
	BREAK_AND_DATETIME BreakAndDateTimeReg; // 0x44
	TIM1_A8_DMA_CONTROL DMAControlReg; // 0x48
	TIM1_A8_DMA_FULLTXADDRESS DMAFullTXAddressReg; // 0x4C
};


#endif
