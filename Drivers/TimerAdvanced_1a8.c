#include "TimerAdvanced_1a8.h"

//Static Prototypes--------------------------------------------------------------
static void PWM_PinInit(uint8_t timerNum);
static void Activate_Clock(uint8_t timerNum);
static ADVANCED_TIMERx* Get_Timer(uint8_t timerNum);

//Global Variables------------------------------------------------------------------
TIM1_8_CLOCK *const Adv1_8Clock = ADDR_TIM1_8_CLOCK;
//TIMER 1
ADVANCED_TIMERx *const TIM1 = ADDR_TIM1;
ADVANCED_TIMERx *const TIM8 = ADDR_TIM8;


uint8_t AdvancedTimer_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time) {
	
	Activate_Clock(timerNum);
	ADVANCED_TIMERx *const TIMER = Get_Timer(timerNum);

	TIMER->PrescalerReg.rw_PrescalerValue = prescaler;
	TIMER->AutoReloadReg.rw_AutoReloadValue = time;
	TIMER->CounterReg.rw_CounterValue = 0x00;
	TIMER->ControlReg1.enable_AutoReloadPreload = 1;
	TIMER->ControlReg1.enable_Counter = 1;
	return 1;
}

void AdvancedPWM_Start(uint8_t timerNum, uint8_t captCompNum, uint16_t prescaler, uint16_t time, float dutyCyclePercent) {
	
	ADVANCED_TIMERx *const TIMER = Get_Timer(timerNum);
	Activate_Clock(timerNum);
	PWM_PinInit(timerNum);
	
	TIMER->PrescalerReg.rw_PrescalerValue = prescaler;
	TIMER->AutoReloadReg.rw_AutoReloadValue = time;
	TIMER->CounterReg.rw_CounterValue = 0x00;
	TIMER->ControlReg1.enable_AutoReloadPreload = 1;
	TIMER->ControlReg1.enable_Counter = 1;

	if ( dutyCyclePercent > 100.0 ) { dutyCyclePercent = 100.0; }
	if ( dutyCyclePercent < 0.0 ) { dutyCyclePercent = 0.0; }

	switch (captCompNum) {
		case 1 :
			TIMER->CaptureCompModeReg1.OutputCompareMode.rw_OutputComp1Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp1Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp1 = 1;
			break;	
		case 2 :
			TIMER->CaptureCompModeReg1.OutputCompareMode.rw_OutputComp2Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp2Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp2 = 1;
			break;
		case 3 :
			TIMER->CaptureCompModeReg2.OutputCompareMode.rw_OutputComp3Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp3Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp3 = 1;
			break;
		case 4 :
			TIMER->CaptureCompModeReg2.OutputCompareMode.rw_OutputComp4Mode = PWM_ACTIVE_UNTIL_MATCH;
			TIMER->CaptureComp4Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp4 = 1;
			break;
	}
		
	TIMER->ControlReg1.enable_Counter = 1;		
}

void AdvancedPWM_Update(uint8_t timerNum, uint8_t captCompNum, uint16_t time, float dutyCyclePercent) {
	
	ADVANCED_TIMERx *const TIMER = Get_Timer(timerNum);

	if ( dutyCyclePercent > 100.0 ) { dutyCyclePercent = 100.0; }
	if ( dutyCyclePercent < 0.0 ) { dutyCyclePercent = 0.0; }
	
	switch (captCompNum) {
		case 1 :
			TIMER->CaptureComp1Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp1 = 1;
			break;	
		case 2 :
			TIMER->CaptureComp2Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp2 = 1;
			break;
		case 3 :
			TIMER->CaptureComp3Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp3 = 1;
			break;
		case 4 :
			TIMER->CaptureComp4Reg.rw_CaptureCompValue = ((dutyCyclePercent / 100) * time);
			TIMER->CaptureCompEnableReg.enable_CaptComp4 = 1;
			break;
	}
		
	TIMER->ControlReg1.enable_Counter = 1;	
}

//Helper Functions--------------------------------------------------------------------------------------------------------------
static void PWM_PinInit(uint8_t timerNum) {
	
	switch (timerNum) {
		case 1 :
			Pin_Init('A', 8, AF1); //Channel 1
			Pin_Init('A', 9, AF1); //Channel 2
			Pin_Init('A', 10, AF1); //Channel 3
			Pin_Init('A', 11, AF1); //Channel 4
			break;
		case 8 :
			Pin_Init('C', 6, AF3); //Channel 1
			Pin_Init('C', 7, AF3); //Channel 2
			Pin_Init('C', 8, AF3); //Channel 3
			Pin_Init('C', 9, AF3); //Channel 4
			break;
	}
}


static void Activate_Clock(uint8_t timerNum) {
	
	switch (timerNum) {
		case 1 : 
			Adv1_8Clock->tim1_StartTick = 1;
			break;
		case 8 : 
			Adv1_8Clock->tim8_StartTick = 1;	
			break;
	}
}

static ADVANCED_TIMERx* Get_Timer(uint8_t timerNum) {

	switch(timerNum) {
		case 1:
			return TIM1;
		case 8:
			return TIM8;
		default:
			return ((void*)0);
	}
}

