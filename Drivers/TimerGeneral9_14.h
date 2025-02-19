//STM32F407 Driver
#ifndef TIMERGENERAL9_14_H_
#define TIMERGENERAL9_14_H_
//Genreal Purpose Timers 9-15
#include <stdint.h>
#include <stdio.h>
#include "GPIO.h"

//CLOCKS
#define CLOCK 0x40023800
#define APB2 0x44
#define APB1 0x40
#define ADDR_TIM9_10_11_CLOCK ( (TIM9_10_11_CLOCK*) ((CLOCK) + APB2) )
#define ADDR_TIM12_13_14_CLOCK ( (TIM12_13_14_CLOCK*) ((CLOCK) + APB1) )

//TIMERS
typedef struct _general_timer_9_14 GEN_TIMER_9_14x;
#define TIM_GEN_9_14_BASE 0x40000000
#define ADDR_TIM9 ( (GEN_TIMER_9_14x*) ((TIM_GEN_9_14_BASE) + 0x14000) )
#define ADDR_TIM10 ( (GEN_TIMER_9_14x*) ((TIM_GEN_9_14_BASE) + 0x14400) )
#define ADDR_TIM11 ( (GEN_TIMER_9_14x*) ((TIM_GEN_9_14_BASE) + 0x14800) )
#define ADDR_TIM12 ( (GEN_TIMER_9_14x*) ((TIM_GEN_9_14_BASE) + 0x01800) )
#define ADDR_TIM13 ( (GEN_TIMER_9_14x*) ((TIM_GEN_9_14_BASE) + 0x01C00) )
#define ADDR_TIM14 ( (GEN_TIMER_9_14x*) ((TIM_GEN_9_14_BASE) + 0x02000) )


#define ADDR_TIM11_OPTION ( (TIM11_OPTION*) (() + 0x50) )

//TIM9_14_CONTROL1
/*Alignment Mode*/
#define EDGE_ALIGN 0x00
#define CENTER_ALIGN_DOWNCOUNT 0x01
#define CENTER_ALIGN_UPCOUNT 0x02
#define CENTER_ALIGN_UP_DOWN 0x03
/*Alignment Mode*/
#define TIMCLOCK 0x00
#define TIMCLOCK_x2 0x01
#define TIMCLOCK_x4 0x02

//TIM9_14_SLAVEMODE_CONTROL & TIM9_14_CAPTURECOMP_MODE1 (For Input Capture Filter)
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

//TIM9_14_CAPTURECOMP_MODE1
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
#define G9_14_NO_PRESCALE 0x00
#define CAPTURE_EVERY_2EVENTS 0x01
#define CAPTURE_EVERY_4EVENTS 0x02
#define CAPTURE_EVERY_8EVENTS 0x03

/**
TIMER Pins ---------------------------
		+ TIM9_CH1: PA2, PE5 (AF3)
		+ TIM9_CH2: PA3, PE6 (AF3)
		
		+ TIM10_CH1: PB8, PF6 (AF3)
		
		+ TIM11_CH1: PB9, PF7 (AF3)

		+ TIM12_CH1: PB14, PH6 (AF9)
		+ TIM12_CH2: PB15, PH9 (AF9)
		
		+ TIM13_CH1: PA6, PF8 (AF9)
		
		+ TIM14_CH1: PA7, PF9 (AF9)
		------------------------------------
**/

//DECLARATIONS
/**
 * @brief Initialize and Start Timer
 * @param timerNum Timer Number (9 - 14)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @return ** uint8_t 
 */
uint8_t GeneralTimer9_14_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time);
/**
 * @brief Initialize and Start Pulse Width Modulation
 * @param timerNum Timer Number (9 - 14)
 * @param captCompNum Capture Compare Number (1 - 2)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @param dutyCyclePercent PWM Duty Cycle as a percentage value (0% - 100%).
 * @return ** void 
 */
void GeneralTimer9_14_PWM_Start(uint8_t timerNum, uint8_t captCompNum, 
	uint16_t prescaler, uint16_t time, float dutyCyclePercent);
/**
 * @brief Update Pulse Width Modulation with new Duty Cycle
 * 
 * @param timerNum Timer Number (9 - 14)
 * @param captCompNum Capture Compare Number (1 - 2)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @param dutyCyclePercent PWM Duty Cycle as a percentage value (0% - 100%).
 * @return ** void 
 */
void GeneralTimer9_14_PWM_Update(uint8_t timerNum, uint8_t captCompNum, 
	uint16_t time, float dutyCyclePercent);



//Registers------------------------------------------------------------------------
typedef struct {
	const uint32_t reserved:32;
}GENERAL_TIMER_9_14_RESERVED;

typedef struct {
	const uint32_t reserved0:16;
	volatile uint32_t tim9_StartTick:1;
	volatile uint32_t tim10_StartTick:1;
	volatile uint32_t tim11_StartTick:1;
	const uint32_t reserved1:13;
}TIM9_10_11_CLOCK ;

typedef struct {
	const uint32_t reserved0:6;
	volatile uint32_t tim12_StartTick:1;
	volatile uint32_t tim13_StartTick:1;
	volatile uint32_t tim14_StartTick:1;
	const uint32_t reserved:23;
}TIM12_13_14_CLOCK ;

typedef struct {
	volatile uint16_t enable_Counter:1;
	volatile uint16_t disable_UpdateEventGeneration:1;
	volatile uint16_t updateOnOverflowOrUGBit0_updateOnOverflow1:1;
	volatile uint16_t enable_OnePulseMode:1;
	const uint16_t reserved0:3;
	volatile uint16_t enable_AutoReloadPreload:1;
	volatile uint16_t rw_ClockDivisionRatio:2;
	const uint16_t reserved1:6;
}TIM9_14_CONTROL1; // Alternate Varsion for STM32F446 below

/*
Alternate Varsion for STM32F446
typedef struct {
	volatile uint16_t enable_Counter:1;
	volatile uint16_t disable_UpdateEventGeneration:1;
	volatile uint16_t updateOnOverflowOrUGBit0_updateOnOverflow1:1;
	const uint16_t reserved0:4;
	volatile uint16_t enable_AutoReloadPreload:1;
	volatile uint16_t rw_ClockDivisionRatio:2;
	const uint16_t reserved1:6;
}TIM9_14_CONTROL1;
*/

typedef struct {
	volatile uint16_t rw_SlaveModeSelection:3;
	const uint16_t reserved0:1;
	volatile uint16_t rw_TriggerInputType:3;
	volatile uint16_t enable_DelayEventEffectForSync:1;
	const uint16_t reserved1:8;
}TIM9_AND_12_SLAVEMODE_CONTROL;

typedef struct {
	volatile uint16_t enable_UpdateInterrupt:1;
	volatile uint16_t enable_CaptureComp1:1;
	volatile uint16_t enable_CaptureComp2:1;
	const uint16_t reserved0:3;
	volatile uint16_t enable_TriggerInterrupt:1;
	const uint16_t reserved1:9;
}TIM9_14_INTERRUPT_ENABLE;

typedef struct {
	volatile uint16_t updateInterruptOccurred:1;
	volatile uint16_t captureComp1InterruptOccurred:1;
	volatile uint16_t captureComp2InterruptOccurred:1;
	const uint16_t reserved0:3;
	volatile uint16_t triggerInterruptOccurred:1;
	const uint16_t reserved1:2;
	volatile uint16_t captureComp1OvercaptureOccurred:1;
	volatile uint16_t captureComp2OvercaptureOccurred:1;
	const uint16_t reserved2:5;
}TIM9_14_STATUS;

typedef struct {
	volatile uint16_t generate_UpdateEvent:1;
	volatile uint16_t generate_CaptureCompare1Event:1;
	volatile uint16_t generate_CaptureCompare2Event:1;
	const uint16_t reserved0:3;
	volatile uint16_t generate_TriggerEvent:1;
	const uint16_t reserved1:9;
}TIM9_14_EVENTGEN;

typedef union {
	struct {
		const uint16_t reserved0:2;
		volatile uint16_t enable_OutputComp1FastResponse:1;
		volatile uint16_t enable_OutputComp1Preload:1;
		volatile uint16_t rw_OutputComp1Mode:3;
		const uint16_t reserved1:3;
		volatile uint16_t enable_OutputComp2FastResponse:1;
		volatile uint16_t enable_OutputComp2Preload:1;
		volatile uint16_t rw_OutputComp2Mode:3;
		const uint16_t reserved2:1;
	}OutputCompareMode;

	struct {
		volatile uint16_t rw_InputCapt1PinMapping:2;
		volatile uint16_t rw_InputCapt1Prescaler:2;
		volatile uint16_t rw_InputCapt1Filter:4;
		volatile uint16_t rw_InputCapt2PinMapping:2;
		volatile uint16_t rw_InputCapt2Prescaler:2;
		volatile uint16_t rw_InputCapt2Filter:4;
	}InputCaptureMode;
}TIM9_14_CAPTURECOMP_MODE1;

typedef struct {
	volatile uint16_t enable_CaptComp1:1;
	volatile uint16_t cc1Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved0:1;
	volatile uint16_t cc1PolarityPart2Input:1;
	volatile uint16_t enable_CaptComp2:1;
	volatile uint16_t cc2Polarity_highOrPart1Input0_lowOrPart1Input1:1;
	const uint16_t reserved1:1;
	volatile uint16_t cc2PolarityPart2Input:1;
	const uint16_t reserved2:8;
}TIM9_14_CAPTURECOMP_ENABLE;

typedef struct {
	volatile uint16_t rw_CounterValue:16;
}TIM9_14_COUNTER;

typedef struct {
	volatile uint16_t rw_PrescalerValue:16;
}TIM9_14_PRESCALER;

typedef struct {
	volatile uint16_t rw_AutoReloadValue:16;
}TIM9_14_AUTORELOAD;

typedef struct {
	volatile uint16_t rw_CaptureCompValue:16;
}TIM9_14_CAPTURECOMPx;

typedef struct {
	volatile uint16_t rw_InternalTrig1Remap:2; //No Macros For This
	const uint16_t reserved1:14;
}TIM11_OPTION;






struct _general_timer_9_14 {
	TIM9_14_CONTROL1 ControlReg1; // 0x00
	GENERAL_TIMER_9_14_RESERVED reserved0; // 0x08
	TIM9_AND_12_SLAVEMODE_CONTROL SlaveModeControlReg; // 0x08 -- ONLY AVAILABLE FOR TIM 9 & 12
	TIM9_14_INTERRUPT_ENABLE DMAInterruptEnableReg; // 0x0C
	TIM9_14_STATUS StatusReg; // 0x10
	TIM9_14_EVENTGEN EventGenReg; // 0x14
	TIM9_14_CAPTURECOMP_MODE1 CaptureCompModeReg1; // 0x18
	GENERAL_TIMER_9_14_RESERVED reserved1; // 0x1C
	TIM9_14_CAPTURECOMP_ENABLE CaptureCompEnableReg; // 0x20
	TIM9_14_COUNTER CounterReg; // 0x24
	TIM9_14_PRESCALER PrescalerReg; // 0x28
	TIM9_14_AUTORELOAD AutoReloadReg; // 0x2C
	GENERAL_TIMER_9_14_RESERVED reserved2; // 0x30
	TIM9_14_CAPTURECOMPx CaptureComp1Reg; // 0x34
	TIM9_14_CAPTURECOMPx CaptureComp2Reg; // 0x38 -- ONLY AVAILABLE FOR TIM 9 & 12
	GENERAL_TIMER_9_14_RESERVED reserved3; // 0x3C
	GENERAL_TIMER_9_14_RESERVED reserved4; // 0x40
	GENERAL_TIMER_9_14_RESERVED reserved5; // 0x44
	GENERAL_TIMER_9_14_RESERVED reserved6; // 0x48
	GENERAL_TIMER_9_14_RESERVED reserved7; // 0x4C
	TIM11_OPTION TIM11OptionReg; //0x50 
};



#endif
