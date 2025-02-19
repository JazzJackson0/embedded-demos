#include "TimerBasic6_7.h"

//Static Prototypes--------------------------------------------------------------
static void Activate_Clock(uint8_t timerNum);
static BASIC_TIMx* Get_Timer(uint8_t timerNum);

//Global Variables------------------------------------------------------------------
TIM6_7_CLOCK *const Basic6_7Clock = ADDR_TIM6_7_CLOCK;
//TIMER 6
BASIC_TIMx *const TIM6 = ADDR_TIM6;
BASIC_TIMx *const TIM7 = ADDR_TIM7;


uint8_t BasicTimer_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time) {
	Activate_Clock(timerNum);
	BASIC_TIMx *const TIMER = Get_Timer(timerNum);
	TIMER->PrescalerReg.rw_PrescalerValue = prescaler;
	TIMER->AutoReloadReg.rw_AutoReloadValue = time;
	TIMER->CounterReg.rw_CounterValue = 0x00;
	TIMER->ControlReg1.enable_AutoReloadPreload = 1;
	TIMER->ControlReg1.enable_Counter = 1;
	return 1;
}

uint8_t BasicOneShotTimer_Start(uint8_t timerNum, uint16_t prescaler, uint16_t time) {
	Activate_Clock(timerNum);
	BASIC_TIMx *const TIMER = Get_Timer(timerNum);
	TIMER->PrescalerReg.rw_PrescalerValue = prescaler;
	TIMER->AutoReloadReg.rw_AutoReloadValue = time;
	TIMER->CounterReg.rw_CounterValue = 0x00;
	TIMER->ControlReg1.enable_AutoReloadPreload = 1;
	TIMER->ControlReg1.enable_OnePulseMode = 1;
	TIMER->ControlReg1.enable_Counter = 1;
	while (TIMER->ControlReg1.enable_Counter == 1);
	return 1;
}

//Helper Functions--------------------------------------------------------------------------------------------------------------

static void Activate_Clock(uint8_t timerNum) {
	
	switch (timerNum) {
		case 6 : 
			Basic6_7Clock->tim6_StartTick = 1;
			break;
		case 7 : 
			Basic6_7Clock->tim7_StartTick = 1;	
			break;
	}
}

static BASIC_TIMx* Get_Timer(uint8_t timerNum) {

	switch(timerNum) {
		case 6:
			return TIM6;
		case 7:
			return TIM7;
		default:
			return ((void*)0);
	}
}