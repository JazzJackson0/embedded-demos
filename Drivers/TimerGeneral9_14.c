#include "TimerGeneral9_14.h"

//Static Prototypes--------------------------------------------------------------
static void PWM_PinInit(uint8_t timerNum);
static void Activate_Clock(uint8_t timerNum);
static GEN_TIMER_9_14x* Get_Timer(uint8_t timerNum);

//Global Variables------------------------------------------------------------------
TIM9_10_11_CLOCK *const Clock9_11 = ADDR_TIM9_10_11_CLOCK;
TIM12_13_14_CLOCK *const Clock12_14 = ADDR_TIM12_13_14_CLOCK;
//TIMER 9
GEN_TIMER_9_14x *const TIM9 = ADDR_TIM9;
GEN_TIMER_9_14x *const TIM10 = ADDR_TIM10;
GEN_TIMER_9_14x *const TIM11 = ADDR_TIM11;
GEN_TIMER_9_14x *const TIM12 = ADDR_TIM12;
GEN_TIMER_9_14x *const TIM13 = ADDR_TIM13;
GEN_TIMER_9_14x *const TIM14 = ADDR_TIM14;


uint8_t GeneralTimer9_14_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time) {
	
	Activate_Clock(timerNum);
	GEN_TIMER_9_14x *const TIMER = Get_Timer(timerNum);

	TIMER->PrescalerReg.rw_PrescalerValue = prescaler;
	TIMER->AutoReloadReg.rw_AutoReloadValue = time;
	TIMER->CounterReg.rw_CounterValue = 0x00;
	TIMER->ControlReg1.enable_AutoReloadPreload = 1;
	TIMER->ControlReg1.enable_Counter = 1;
	
	return 1;
}


void GeneralTimer9_14_PWM_Start(uint8_t timerNum, uint8_t captCompNum, uint16_t prescaler, 
	uint16_t time, float dutyCyclePercent) {
	
	Activate_Clock(timerNum);
	PWM_PinInit(timerNum);
	GEN_TIMER_9_14x *const TIMER = Get_Timer(timerNum);
	
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
	}
		
	TIMER->ControlReg1.enable_Counter = 1;		
}

void GeneralTimer9_14_PWM_Update(uint8_t timerNum, uint8_t captCompNum, uint16_t time, float dutyCyclePercent) {
	GEN_TIMER_9_14x *const TIMER = Get_Timer(timerNum);

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
	}
		
	TIMER->ControlReg1.enable_Counter = 1;	
}

//Helper Functions--------------------------------------------------------------------------------------------------------------
void PWM_PinInit(uint8_t timerNum) {
	
	switch (timerNum) {
		case 9 :
			Pin_Init('A', 2, AF3); //Channel 1
			Pin_Init('A', 3, AF3); //Channel 2
			break;
		case 10 :
			Pin_Init('B', 8, AF3); //Channel 1
			break;
		case 11 :
			Pin_Init('B', 9, AF3); //Channel 1
			break;
		case 12 :
			Pin_Init('B', 14, AF9); //Channel 1
			Pin_Init('B', 15, AF9); //Channel 2
			break;
		case 13 :
			Pin_Init('A', 6, AF9); //Channel 1
			break;
		case 14 :
			Pin_Init('A', 7, AF9); //Channel 1
			break;
	}
}

static void Activate_Clock(uint8_t timerNum) {
	
	switch (timerNum) {
		case 9 : 
			Clock9_11->tim9_StartTick = 1;
			break;
		case 10 : 
			Clock9_11->tim10_StartTick = 1;	
			break;
		case 11 : 
			Clock9_11->tim11_StartTick = 1;	
			break;
		case 12 : 
			Clock12_14->tim12_StartTick = 1;	
			break;
		case 13 : 
			Clock12_14->tim13_StartTick = 1;	
			break;
		case 14 : 
			Clock12_14->tim14_StartTick = 1;	
			break;
	}
}

static GEN_TIMER_9_14x* Get_Timer(uint8_t timerNum) {

	switch(timerNum) {
		case 9:
			return TIM9;
		case 10:
			return TIM10;
		case 11:
			return TIM11;
		case 12:
			return TIM12;
		case 13:
			return TIM13;
		case 14:
			return TIM14;
		default:
			return ((void*)0);
	}
}