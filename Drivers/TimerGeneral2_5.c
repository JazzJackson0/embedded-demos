#include "TimerGeneral2_5.h"

//Static Prototypes--------------------------------------------------------------
static void PWM_PinInit(uint8_t timerNum);
static void Activate_Clock(uint8_t timerNum);
static GEN_TIMER_2_5x* Get_Timer(uint8_t timerNum);

//Global Variables------------------------------------------------------------------
TIM2_5_CLOCK *const Clock2_5 = ADDR_TIM2_5_CLOCK;
//TIMER 2
GEN_TIMER_2_5x *const TIM2 = ADDR_TIM2;
GEN_TIMER_2_5x *const TIM3 = ADDR_TIM3;
GEN_TIMER_2_5x *const TIM4 = ADDR_TIM4;
GEN_TIMER_2_5x *const TIM5 = ADDR_TIM5;

uint8_t GeneralTimer2_5_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time) {
	
	Activate_Clock(timerNum);
	GEN_TIMER_2_5x *const TIMER = Get_Timer(timerNum);
	TIMER->PrescalerReg.rw_PrescalerValue = prescaler;
	TIMER->AutoReloadReg.NormalAutoReload.rw_AutoReloadValue = time;
	TIMER->CounterReg.NormalCounter.rw_CounterValue = 0x00;
	TIMER->ControlReg1.enable_AutoReloadPreload = 1;
	TIMER->ControlReg1.enable_Counter = 1;
	
	return 1;
}

void GeneralTimer2_5_PWM_Start(uint8_t timerNum, uint8_t captCompNum, uint16_t prescaler, 
	uint16_t time, float dutyCyclePercent) {
	
	Activate_Clock(timerNum);
	GEN_TIMER_2_5x *const TIMER = Get_Timer(timerNum);
	PWM_PinInit(timerNum);
	
	TIMER->PrescalerReg.rw_PrescalerValue = prescaler;
	TIMER->AutoReloadReg.NormalAutoReload.rw_AutoReloadValue = time;
	TIMER->CounterReg.NormalCounter.rw_CounterValue = 0x00;
	TIMER->ControlReg1.enable_AutoReloadPreload = 1;
	TIMER->ControlReg1.enable_Counter = 1;

	if ( dutyCyclePercent > 100.0 ) { dutyCyclePercent = 100.0; }
	if ( dutyCyclePercent < 0.0 ) { dutyCyclePercent = 0.0; }

	switch (captCompNum) {
		case 1 :
			TIMER->CaptureCompModeReg1.OutputCompareMode.rw_OutputComp1Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp1Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp1 = 1;
			break;
		case 2 :
			TIMER->CaptureCompModeReg1.OutputCompareMode.rw_OutputComp2Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp2Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp2 = 1;
			break;	
		case 3 :
			TIMER->CaptureCompModeReg2.OutputCompareMode.rw_OutputComp3Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp3Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp3 = 1;
			break;	
		case 4 :
			TIMER->CaptureCompModeReg2.OutputCompareMode.rw_OutputComp4Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp4Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp4 = 1;
			break;
	}
		
	TIMER->ControlReg1.enable_Counter = 1;		
}

void GeneralTimer2_5_PWM_Update(uint8_t timerNum, uint8_t captCompNum, uint16_t time, float dutyCyclePercent) {
	
	GEN_TIMER_2_5x *const TIMER = Get_Timer(timerNum);

	if ( dutyCyclePercent > 100.0 ) { dutyCyclePercent = 100.0; }
	if ( dutyCyclePercent < 0.0 ) { dutyCyclePercent = 0.0; }

	switch (captCompNum) {
		case 1 :
			TIMER->CaptureComp1Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp1 = 1;
			break;
		case 2 :
			TIMER->CaptureComp2Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp2 = 1;
			break;	
		case 3 :
			TIMER->CaptureComp3Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp3 = 1;
			break;	
		case 4 :
			TIMER->CaptureComp4Reg.NormalCaptureComp.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp4 = 1;
			break;
	}
		
	TIMER->ControlReg1.enable_Counter = 1;	
}

//Helper Functions--------------------------------------------------------------------------------------------------------------
static void PWM_PinInit(uint8_t timerNum) {
	
	switch (timerNum) {
		case 2 :
			Pin_Init('A', 15, AF1); //Channel 1
			Pin_Init('A', 1, AF1); //Channel 2
			Pin_Init('A', 2, AF1); //Channel 3
			Pin_Init('A', 3, AF1); //Channel 4
			break;
		case 3 :
			Pin_Init('A', 6, AF2); //Channel 1
			Pin_Init('A', 7, AF2); //Channel 2
			Pin_Init('B', 0, AF2); //Channel 3
			Pin_Init('B', 1, AF2); //Channel 4
			break;
		case 4 :
			Pin_Init('B', 6, AF2); //Channel 1
			Pin_Init('B', 7, AF2); //Channel 2
			Pin_Init('B', 8, AF2); //Channel 3
			Pin_Init('B', 9, AF2); //Channel 4
			break;
		case 5 :
			Pin_Init('A', 0, AF2); //Channel 1
			Pin_Init('A', 1, AF2); //Channel 2
			Pin_Init('A', 2, AF2); //Channel 3
			Pin_Init('A', 3, AF2); //Channel 4
			break;
	}
}


static void Activate_Clock(uint8_t timerNum) {
	
	switch (timerNum) {
		case 2 : 
			Clock2_5->tim2_StartTick = 1;
			break;
		case 3 : 
			Clock2_5->tim3_StartTick = 1;	
			break;
		case 4 : 
			Clock2_5->tim4_StartTick = 1;	
			break;
		case 5 : 
			Clock2_5->tim5_StartTick = 1;	
			break;
	}
}

static GEN_TIMER_2_5x* Get_Timer(uint8_t timerNum) {

	switch(timerNum) {
		case 2:
			return TIM2;
		case 3:
			return TIM3;
		case 4:
			return TIM4;
		case 5:
			return TIM5;
		default:
			return ((void*)0);
	}
}

