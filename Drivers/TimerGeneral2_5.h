//STM32F407 Driver
#ifndef TIMERGENERAL2_5_H_
#define TIMERGENERAL2_5_H_
//Genreal Purpose Timers 2-5
#include <stdint.h>
#include <stdio.h>
#include "GPIO.h"

//CLOCK
#define CLOCK 0x40023800
#define APB1 0x40
#define ADDR_TIM2_5_CLOCK ( (TIM2_5_CLOCK*) ((CLOCK) + APB1) )

//TIMERS
typedef struct _general_timer_2_5 GEN_TIMER_2_5x;
#define TIM_GEN_2_5_BASE 0x40000000
#define ADDR_TIM2 ( (GEN_TIMER_2_5x*) ((TIM_GEN_2_5_BASE) + 0x000) )
#define ADDR_TIM3 ( (GEN_TIMER_2_5x*) ((TIM_GEN_2_5_BASE) + 0x400) )
#define ADDR_TIM4 ( (GEN_TIMER_2_5x*) ((TIM_GEN_2_5_BASE) + 0x800) )
#define ADDR_TIM5 ( (GEN_TIMER_2_5x*) ((TIM_GEN_2_5_BASE) + 0xC00) )


//TIM2_5_CONTROL1
/*Alignment Mode*/
#define EDGE_ALIGN 0x00
#define CENTER_ALIGN_DOWNCOUNT 0x01
#define CENTER_ALIGN_UPCOUNT 0x02
#define CENTER_ALIGN_UP_DOWN 0x03
/*Alignment Mode*/
#define TIMCLOCK 0x00
#define TIMCLOCK_x2 0x01
#define TIMCLOCK_x4 0x02

//TIM2_5_CONTROL2
/*Master Mode*/
#define RESET 0x00
#define COUNTEN_SIGNAL_AS_TRIGOUT 0x01
#define UPDATEEVENT_AS_TRIGOUT 0x02
#define COMPARE_PULSE_AS_TRIGOUT 0x03
#define OUTCOMP1_AS_TRIGOUT 0x04
#define OUTCOMP2_AS_TRIGOUT 0x05
#define OUTCOMP3_AS_TRIGOUT 0x06
#define OUTCOMP4_AS_TRIGOUT 0x07

//TIM2_5_SLAVEMODE_CONTROL & TIM2_5_CAPTURECOMP_MODE1 (For Input Capture Filter)
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

//TIM2_5_CAPTURECOMP_MODE1
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
#define G2_5_NO_PRESCALE 0x00
#define CAPTURE_EVERY_2EVENTS 0x01
#define CAPTURE_EVERY_4EVENTS 0x02
#define CAPTURE_EVERY_8EVENTS 0x03

/**
TIMER Pins ---------------------------
		
		+ TIM2_CH1: PA15 (AF1)
		+ TIM2_CH2: PA1, PB3 (AF1)
		+ TIM2_CH3: PA2, PB10 (AF1)
		+ TIM2_CH4: PA3, PB11 (AF1)
		+ TIM2_CH1_ETR: PA0, PA5 (AF1)
		+ TIM2_ETR: PA15 (AF1)

		+ TIM3_CH1: PA6, PB4, PC6 (AF2)
		+ TIM3_CH2: PA7, PB5, PC7 (AF2)
		+ TIM3_CH3: PB0, PC8 (AF2)
		+ TIM3_CH4: PB1, PC9 (AF2)
		+ TIM3_ETR: PD2 (AF2)

		+ TIM4_CH1: PB6, PD12 (AF2)
		+ TIM4_CH2: PB7, PD13 (AF2)
		+ TIM4_CH3: PB8, PD14 (AF2)
		+ TIM4_CH4: PB9, PD15 (AF2)
		+ TIM4_ETR: PE0 (AF2)
		
		+ TIM5_CH1: PA0, PH10 (AF2)
		+ TIM5_CH2: PA1, PH11 (AF2)
		+ TIM5_CH3: PA2, PH12 (AF2)
		+ TIM5_CH4: PA3, PI0 (AF2)
		------------------------------------
**/

//DECLARATIONS
/**
 * @brief Initialize and Start Timer		
 * @param timerNum Timer Number (2 - 5)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @return ** uint8_t 
 */
uint8_t GeneralTimer2_5_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time);
/**
 * @brief Initialize and Start Pulse Width Modulation
 * 
 * @param timerNum Timer Number (2 - 5)
 * @param captCompNum Capture Compare Number (1 - 4)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @param dutyCyclePercent PWM Duty Cycle as a percentage value (0% - 100%).
 * @return ** void 
 */
void GeneralTimer2_5_PWM_Start(uint8_t timerNum, uint8_t captCompNum, 
	uint16_t prescaler, uint16_t time, float dutyCyclePercent);
/**
 * @brief Update Pulse Width Modulation with new Duty Cycle
 * 
 * @param timerNum Timer Number (2 - 5)
 * @param captCompNum Capture Compare Number (1 - 4)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @param dutyCyclePercent PWM Duty Cycle as a percentage value (0% - 100%).
 * @return ** void 
 */
void GeneralTimer2_5_PWM_Update(uint8_t timerNum, uint8_t captCompNum, 
	uint16_t time, float dutyCyclePercent);


// Registers----------------------------------------------------------------------

typedef struct {
	const uint32_t reserved:32;
}GENERAL_TIMER_2_5_RESERVED;

typedef struct {
	volatile uint32_t tim2_StartTick:1;
	volatile uint32_t tim3_StartTick:1;
	volatile uint32_t tim4_StartTick:1;
	volatile uint32_t tim5_StartTick:1;
	const uint32_t reserved:28;
}TIM2_5_CLOCK;

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
}TIM2_5_CONTROL1;

typedef struct {
	const uint16_t reserved0:3;
	volatile uint16_t dmaSendOnCaptCompEvent0_dmaSendOnUpdateEvent1:1;
	volatile uint16_t rw_MasterMode:3;
	volatile uint16_t channel1ToTimInput0_channel123toTimInput1:1;
	const uint16_t reserved1:8;
}TIM2_5_CONTROL2;

typedef struct {
	volatile uint16_t rw_SlaveModeSelection:3;
	const uint16_t reserved:1;
	volatile uint16_t rw_TriggerInputType:3;
	volatile uint16_t enable_DelayEventEffectForSync:1;
	volatile uint16_t rw_ExternalTriggerFilter:4;
	volatile uint16_t rw_ExternalTriggerPrescaler:2;
	volatile uint16_t enable_ExternalClock:1;
	volatile uint16_t polarityActiveHigh0_polarityActiveLow1:1;
}TIM2_5_SLAVEMODE_CONTROL;

typedef struct {
	volatile uint16_t enable_UpdateInterrupt:1;
	volatile uint16_t enable_CaptureComp1:1;
	volatile uint16_t enable_CaptureComp2:1;
	volatile uint16_t enable_CaptureComp3:1;
	volatile uint16_t enable_CaptureComp4:1;
	const uint16_t reserved0:1;
	volatile uint16_t enable_TriggerInterrupt:1;
	const uint16_t reserved1:1;
	volatile uint16_t enable_DMAReqInterrupt:1;
	volatile uint16_t enable_CaptureComp1DMAReq:1;
	volatile uint16_t enable_CaptureComp2DMAReq:1;
	volatile uint16_t enable_CaptureComp3DMAReq:1;
	volatile uint16_t enable_CaptureComp4DMAReq:1;
	const uint16_t reserved2:1;
	volatile uint16_t enable_TriggerDMAReq:1;
	const uint16_t reserved3:1;
}TIM2_5_DMAINTERRUPT_ENABLE;

typedef struct {
	volatile uint16_t updateInterruptOccurred:1;
	volatile uint16_t captureComp1InterruptOccurred:1;
	volatile uint16_t captureComp2InterruptOccurred:1;
	volatile uint16_t captureComp3InterruptOccurred:1;
	volatile uint16_t captureComp4InterruptOccurred:1;
	const uint16_t reserved0:1;
	volatile uint16_t triggerInterruptOccurred:1;
	const uint16_t reserved1:2;
	volatile uint16_t captureComp1OvercaptureOccurred:1;
	volatile uint16_t captureComp2OvercaptureOccurred:1;
	volatile uint16_t captureComp3OvercaptureOccurred:1;
	volatile uint16_t captureComp4OvercaptureOccurred:1;
	const uint16_t reserved2:3;
}TIM2_5_STATUS;

typedef struct {
	volatile uint16_t generate_UpdateEvent:1;
	volatile uint16_t generate_CaptureCompare1Event:1;
	volatile uint16_t generate_CaptureCompare2Event:1;
	volatile uint16_t generate_CaptureCompare3Event:1;
	volatile uint16_t generate_CaptureCompare4Event:1;
	const uint16_t reserved0:1;
	volatile uint16_t generate_TriggerEvent:1;
	const uint16_t reserved1:9;
}TIM2_5_EVENTGEN;

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
}TIM2_5_CAPTURECOMP_MODE1;

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
}TIM2_5_CAPTURECOMP_MODE2;

typedef struct {
	volatile uint16_t enable_CaptComp1:1;
	volatile uint16_t cc1Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved0:1;
	volatile uint16_t cc1PolarityPart2Input:1;
	volatile uint16_t enable_CaptComp2:1;
	volatile uint16_t cc2Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved1:1;
	volatile uint16_t cc2PolarityPart2Input:1;
	volatile uint16_t enable_CaptComp3:1;
	volatile uint16_t cc3Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved2:1;
	volatile uint16_t cc3PolarityPart2Input:1;
	volatile uint16_t enable_CaptComp4:1;
	volatile uint16_t cc4Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved3:1;
	volatile uint16_t cc4PolarityPart2Input:1;
}TIM2_5_CAPTURECOMP_ENABLE;

typedef union {
	struct {
		volatile uint32_t rw_CounterValue:32;
	}HighCounter;

	struct {
		volatile uint32_t rw_CounterValue:16;
		const uint32_t reserved:16;
	}NormalCounter;
}TIM2_5_COUNTER; // Alternate STM32F446 Version below

/*
Alternate STM32F446 Version
typedef struct {
	volatile uint16_t rw_CounterValue:16;
}TIM2_5_COUNTER;
*/

typedef struct {
	volatile uint16_t rw_PrescalerValue:16;
}TIM2_5_PRESCALER;

typedef union {
	struct {
		volatile uint32_t rw_AutoReloadValue:32;
	}HighAutoReload;

	struct {
		volatile uint32_t rw_AutoReloadValue:16;
		const uint32_t reserved:16;
	}NormalAutoReload;
}TIM2_5_AUTORELOAD; // Alternate STM32F446 Version below

/*
Alternate STM32F446 Version
typedef struct {
	volatile uint16_t rw_AutoReloadValue:16;
}TIM2_5_AUTORELOAD;
*/

typedef union {
	struct {
		volatile uint32_t rw_CaptureCompValue:32;
	}HighCaptureComp;

	struct {
		volatile uint32_t rw_CaptureCompValue:16;
		const uint32_t reserved:16;
	}NormalCaptureComp;
}TIM2_5_CAPTURECOMPx;

typedef struct {
	volatile uint16_t rw_DAMBaseAddress:5;
	const uint16_t reserved0:3;
	volatile uint16_t rw_DMABurstLength:5;
	const uint16_t reserved1:3;
}TIM2_5_DMA_CONTROL;

typedef struct {
	volatile uint16_t rw_DMABurstAccessRegister:16;
}TIM2_5_DMA_FULLTXADDRESS;

typedef union {
	struct {
		const uint16_t reserved0:10;
		volatile uint16_t rw_InternalTrig1Remap:2; //No Macros For This
		const uint16_t reserved1:4;
	}TIM2Option;

	struct {
		const uint16_t reserved0:6;
		volatile uint16_t rw_TimerInput4Remap:2; //No Macros For This
		const uint16_t reserved1:8;
	}TIM5Option;
}TIM2_5_OPTION;







struct _general_timer_2_5 {
	TIM2_5_CONTROL1 ControlReg1; // 0x00
	TIM2_5_CONTROL2 ControlReg2; // 0x04
	TIM2_5_SLAVEMODE_CONTROL SlaveModeControlReg; // 0x08
	TIM2_5_DMAINTERRUPT_ENABLE DMAInterruptEnableReg; // 0x0C
	TIM2_5_STATUS StatusReg; // 0x10
	TIM2_5_EVENTGEN EventGenReg; // 0x14
	TIM2_5_CAPTURECOMP_MODE1 CaptureCompModeReg1; // 0x18
	TIM2_5_CAPTURECOMP_MODE2 CaptureCompModeReg2; // 0x1C
	TIM2_5_CAPTURECOMP_ENABLE CaptureCompEnableReg; // 0x20
	TIM2_5_COUNTER CounterReg; // 0x24
	TIM2_5_PRESCALER PrescalerReg; // 0x28
	TIM2_5_AUTORELOAD AutoReloadReg; // 0x2C
	GENERAL_TIMER_2_5_RESERVED reserved0; // 0x30
	TIM2_5_CAPTURECOMPx CaptureComp1Reg; // 0x34
	TIM2_5_CAPTURECOMPx CaptureComp2Reg; // 0x38
	TIM2_5_CAPTURECOMPx CaptureComp3Reg; // 0x3C
	TIM2_5_CAPTURECOMPx CaptureComp4Reg; // 0x40
	GENERAL_TIMER_2_5_RESERVED reserved1; // 0x44
	TIM2_5_DMA_CONTROL DMAControlReg; // 0x48
	TIM2_5_DMA_FULLTXADDRESS DMAFullTXAddressReg; // 0x4C
	TIM2_5_OPTION OptionReg; //0x50 
};



#endif
