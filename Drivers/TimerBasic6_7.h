//STM32F407 Driver
#ifndef TIMERBASIC6_7_H_
#define TIMERBASIC6_7_H_
#include <stdint.h>
#include <stdio.h>
#include "GPIO.h"

//CLOCK
#define CLOCK 0x40023800
#define APB1 0x40
#define ADDR_TIM6_7_CLOCK ( (TIM6_7_CLOCK*) ((CLOCK) + APB1) )

//TIMERS
typedef struct _basic_timer BASIC_TIMx;
#define BASIC_TIM_BASE 0x40001000
#define ADDR_TIM6 ( (BASIC_TIMx*) ((BASIC_TIM_BASE) + 0x000) )
#define ADDR_TIM7 ( (BASIC_TIMx*) ((BASIC_TIM_BASE) + 0400) )

//TIM6_7_CONTROL2
/*Master Mode*/
#define RESET 0x00
#define COUNTEN_SIGNAL_AS_TRIGOUT 0x01
#define UPDATEEVENT_AS_TRIGOUT 0x02
#define COMPARE_PULSE_AS_TRIGOUT 0x03
#define OUTCOMP1_AS_TRIGOUT 0x04
#define OUTCOMP2_AS_TRIGOUT 0x05
#define OUTCOMP3_AS_TRIGOUT 0x06
#define OUTCOMP4_AS_TRIGOUT 0x07

//Basic Timers 6-7
/*TIMER Pins ---------------------------
		+ No Pins Needed
		------------------------------------*/


//DECLARATIONS
/**
 * @brief Initialize and Start Timer				
 * @param timerNum Timer Number (6 & 7)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @return ** uint8_t 
 */
uint8_t BasicTimer_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time);
/**
 * @brief Initialize and Start Timer. Timer will not repeat, but will return 1 upon
 * 			reaching time goal.
 * 
 * @param timerNum Timer Number (6 & 7)
 * @param prescaler Timer Clock Prescaler Value (Clock Speed / Presclaler = Number of Hz per Second)
 * @param time Time Goal: Example: Let (Clock Speed / Prescaler) = 1000Hz/Sec
 * 							---- For 1sec Time Goal: Time = 1000(Hz)
 * 						|||  00:00 ---> Time Goal |||  RESET
 *						|||  00:00 ---> Time Goal |||  RESET |||  ETC...)
 * @return ** uint8_t 
 */
uint8_t BasicOneShotTimer_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time);


// Registers------------------------------------------------------------------------
typedef struct {
	const uint32_t reserved1:32;
}BASIC_TIMER_RESERVED;

typedef struct {
	const uint32_t reserved0:4;
	volatile uint32_t tim6_StartTick:1;
	volatile uint32_t tim7_StartTick:1;
	const uint32_t reserved1:26;
}TIM6_7_CLOCK;


typedef struct {
	volatile uint16_t enable_Counter:1;
	volatile uint16_t disable_UpdateEventGeneration:1;
	volatile uint16_t updateOnOverflowOrUGBit0_updateOnOverflow1:1;
	volatile uint16_t enable_OnePulseMode:1;
	const uint16_t reserved0:3;
	volatile uint16_t enable_AutoReloadPreload:1;
	const uint16_t reserved1:8;
}TIM6_7_CONTROL1;

typedef struct {
	const uint16_t reserved0:4;
	volatile uint16_t rw_MasterMode:3;
	const uint16_t reserved1:9;
}TIM6_7_CONTROL2;

typedef struct {
	volatile uint16_t enable_UpdateInterrupt:1;
	const uint16_t reserved0:7;
	volatile uint16_t enable_UpdateDMAReqInterrupt:1;
	const uint16_t reserved1:7;
}TIM6_7_DMAINTERRUPT_ENABLE;

typedef struct {
	volatile uint16_t updateInterruptOccurred:1;
	const uint16_t reserved:15;
}TIM6_7_STATUS;

typedef struct {
	volatile uint16_t generate_UpdateEvent:1;
	const uint16_t reserved:15;
}TIM6_7_EVENTGEN;

typedef struct {
	volatile uint16_t rw_CounterValue:16;
}TIM6_7_COUNTER;

typedef struct {
	volatile uint16_t rw_PrescalerValue:16;
}TIM6_7_PRESCALER;

typedef struct {
	volatile uint16_t rw_AutoReloadValue:16;
}TIM6_7_AUTORELOAD;





struct _basic_timer {
	TIM6_7_CONTROL1 ControlReg1; // 0x00
	TIM6_7_CONTROL2 ControlReg2; // 0x04
	BASIC_TIMER_RESERVED reserved0; // 0x08
	TIM6_7_DMAINTERRUPT_ENABLE DMAInterruptEnableReg; // 0x0C
	TIM6_7_STATUS StatusReg; // 0x10
	TIM6_7_EVENTGEN EventGenReg; // 0x14
	BASIC_TIMER_RESERVED reserved1; // 0x18
	BASIC_TIMER_RESERVED reserved2; // 0x1C
	BASIC_TIMER_RESERVED reserved3; // 0x20
	TIM6_7_COUNTER CounterReg; // 0x24
	TIM6_7_PRESCALER PrescalerReg; // 0x28
	TIM6_7_AUTORELOAD AutoReloadReg; // 0x2C
};



#endif
