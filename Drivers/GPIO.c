#include "GPIO.h"

//Static Prototypes-----------------------------------------------------------------
static GPIOx* Get_Port(char port);
static void ClockStart_Choice(char port);

//Global Variables------------------------------------------------------------------
GPIOx_CLOCK *const GPIOClock = ADDR_GPIOx_CLOCK;
GPIOx *const A = ADDR_GPIOA;
GPIOx *const B = ADDR_GPIOB;
GPIOx *const C = ADDR_GPIOC;
GPIOx *const D = ADDR_GPIOD;
GPIOx *const E = ADDR_GPIOE;
GPIOx *const F = ADDR_GPIOF;
GPIOx *const G = ADDR_GPIOG;
GPIOx *const H = ADDR_GPIOH;
GPIOx *const I = ADDR_GPIOI;



void Pin_Init(char port, uint8_t pinNum, E_PinModes modeType) {
	
	ClockStart_Choice(port);
	
	GPIOx *const Port = Get_Port(port);
	if (Port == NULL) { return; }
	
	switch(pinNum) {
	
		case 0 :
			if (modeType < 0x10) { // Alternate Function
				
				Port->ModeReg.rw_Pin0_Mode = 0x00; // Clear Pin
				Port->ModeReg.rw_Pin0_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin0_AltFunction = modeType;
			}
			else { // IN, OUT, or Analog
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin0_Mode = 0x00;
				Port->ModeReg.rw_Pin0_Mode = modeType;
			}
			return;
		case 1 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin1_Mode = 0x00;
				Port->ModeReg.rw_Pin1_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin1_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin1_Mode = 0x00;
				Port->ModeReg.rw_Pin1_Mode = modeType;
			}
			return;
		case 2 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin2_Mode = 0x00;
				Port->ModeReg.rw_Pin2_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin2_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin2_Mode = 0x00;
				Port->ModeReg.rw_Pin2_Mode = modeType;
			}
			return;
		case 3 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin3_Mode = 0x00;
				Port->ModeReg.rw_Pin3_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin3_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin3_Mode = 0x00;
				Port->ModeReg.rw_Pin3_Mode = modeType;
			}
			return;
		case 4 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin4_Mode = 0x00;
				Port->ModeReg.rw_Pin4_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin4_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin4_Mode = 0x00;
				Port->ModeReg.rw_Pin4_Mode = modeType;
			}
			return;
		case 5 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin5_Mode = 0x00;
				Port->ModeReg.rw_Pin5_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin5_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin5_Mode = 0x00;
				Port->ModeReg.rw_Pin5_Mode = modeType;
			}
			return;
		case 6 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin6_Mode = 0x00;
				Port->ModeReg.rw_Pin6_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin6_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin6_Mode = 0x00;
				Port->ModeReg.rw_Pin6_Mode = modeType;
			}
			return;
		case 7 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin7_Mode = 0x00;
				Port->ModeReg.rw_Pin7_Mode = (AF - 0x10);
				Port->AltFuncLowReg.rw_Pin7_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin7_Mode = 0x00;
				Port->ModeReg.rw_Pin7_Mode = modeType;
			}
			return;
		case 8 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin8_Mode = 0x00;
				Port->ModeReg.rw_Pin8_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin8_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin8_Mode = 0x00;
				Port->ModeReg.rw_Pin8_Mode = modeType;
			}
			return;
		case 9 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin9_Mode = 0x00;
				Port->ModeReg.rw_Pin9_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin9_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin9_Mode = 0x00;
				Port->ModeReg.rw_Pin9_Mode = modeType;
			}
			return;
		case 10 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin10_Mode = 0x00;
				Port->ModeReg.rw_Pin10_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin10_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin10_Mode = 0x00;
				Port->ModeReg.rw_Pin10_Mode = modeType;
			}
			return;
		case 11 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin11_Mode = 0x00;
				Port->ModeReg.rw_Pin11_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin11_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin11_Mode = 0x00;
				Port->ModeReg.rw_Pin11_Mode = modeType;
			}
			return;
		case 12 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin12_Mode = 0x00;
				Port->ModeReg.rw_Pin12_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin12_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin12_Mode = 0x00;
				Port->ModeReg.rw_Pin12_Mode = modeType;
			}
			return;
		case 13 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin13_Mode = 0x00;
				Port->ModeReg.rw_Pin13_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin13_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin13_Mode = 0x00;
				Port->ModeReg.rw_Pin13_Mode = modeType;
			}
			return;
		case 14 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin14_Mode = 0x00;
				Port->ModeReg.rw_Pin14_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin14_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin14_Mode = 0x00;
				Port->ModeReg.rw_Pin14_Mode = modeType;
			}
			return;
		case 15 :
			if (modeType != IN && modeType != OUT && modeType != ANALOG) {
				
				Port->ModeReg.rw_Pin15_Mode = 0x00;
				Port->ModeReg.rw_Pin15_Mode = (AF - 0x10);
				Port->AltFuncHighReg.rw_Pin15_AltFunction = modeType;
			}
			else if (modeType >= 0x10){
				
				modeType = modeType - 0x10;
				Port->ModeReg.rw_Pin15_Mode = 0x00;
				Port->ModeReg.rw_Pin15_Mode = modeType;
			}
			return;
	}
}

uint8_t Pin_GetInput(char port, uint8_t pinNum) {
	
	GPIOx *const Port = Get_Port(port);
	
	switch(pinNum) {
	
		case 0 :
			return Port->InputReg.read_Pin0;
		case 1 :
			return Port->InputReg.read_Pin1;
		case 2 :
			return Port->InputReg.read_Pin2;
		case 3 :
			return Port->InputReg.read_Pin3;
		case 4 :
			return Port->InputReg.read_Pin4;
		case 5 :
			return Port->InputReg.read_Pin5;
		case 6 :
			return Port->InputReg.read_Pin6;
		case 7 :
			return Port->InputReg.read_Pin7;
		case 8 :
			return Port->InputReg.read_Pin8;
		case 9 :
			return Port->InputReg.read_Pin9;
		case 10 :
			return Port->InputReg.read_Pin10;
		case 11 :
			return Port->InputReg.read_Pin11;
		case 12 :
			return Port->InputReg.read_Pin12;
		case 13 :
			return Port->InputReg.read_Pin13;
		case 14 :
			return Port->InputReg.read_Pin14;
		case 15 :
			return Port->InputReg.read_Pin15;
		default :
			return 0;
	}
}

void Pin_Out(char port, uint8_t pinNum, uint8_t pinState) {
	
	GPIOx *const Port = Get_Port(port);
	
	switch(pinNum) {
	
		case 0 :
			Port->OutputReg.rw_Pin0_Out = pinState;
			break;
		case 1 :
			Port->OutputReg.rw_Pin1_Out = pinState;
			break;
		case 2 :
			Port->OutputReg.rw_Pin2_Out = pinState;
			break;
		case 3 :
			Port->OutputReg.rw_Pin3_Out = pinState;
			break;
		case 4 :
			Port->OutputReg.rw_Pin4_Out = pinState;
			break;
		case 5 :
			Port->OutputReg.rw_Pin5_Out = pinState;
			break;
		case 6 :
			Port->OutputReg.rw_Pin6_Out = pinState;
			break;
		case 7 :
			Port->OutputReg.rw_Pin7_Out = pinState;
			break;
		case 8 :
			Port->OutputReg.rw_Pin8_Out = pinState;
			break;
		case 9 :
			Port->OutputReg.rw_Pin9_Out = pinState;
			break;
		case 10 :
			Port->OutputReg.rw_Pin10_Out = pinState;
			break;
		case 11 :
			Port->OutputReg.rw_Pin11_Out = pinState;
			break;
		case 12 :
			Port->OutputReg.rw_Pin12_Out = pinState;
			break;
		case 13 :
			Port->OutputReg.rw_Pin13_Out = pinState;
			break;
		case 14 :
			Port->OutputReg.rw_Pin14_Out = pinState;
			break;
		case 15 :
			Port->OutputReg.rw_Pin15_Out = pinState;
			break;
	}
}

void Pin_OutputSpeed(char port, uint8_t pinNum, E_OutSpeeds speed) {
	
	GPIOx *const Port = Get_Port(port);
	
	switch(pinNum) {
	
		case 0 :
			Port->OutSpeedReg.rw_Pin0_OutSpeed = speed;
			break;
		case 1 :
			Port->OutSpeedReg.rw_Pin1_OutSpeed = speed;
			break;
		case 2 :
			Port->OutSpeedReg.rw_Pin2_OutSpeed = speed;
			break;
		case 3 :
			Port->OutSpeedReg.rw_Pin3_OutSpeed = speed;
			break;
		case 4 :
			Port->OutSpeedReg.rw_Pin4_OutSpeed = speed;
			break;
		case 5 :
			Port->OutSpeedReg.rw_Pin5_OutSpeed = speed;
			break;
		case 6 :
			Port->OutSpeedReg.rw_Pin6_OutSpeed = speed;
			break;
		case 7 :
			Port->OutSpeedReg.rw_Pin7_OutSpeed = speed;
			break;
		case 8 :
			Port->OutSpeedReg.rw_Pin8_OutSpeed = speed;
			break;
		case 9 :
			Port->OutSpeedReg.rw_Pin9_OutSpeed = speed;
			break;
		case 10 :
			Port->OutSpeedReg.rw_Pin10_OutSpeed = speed;
			break;
		case 11 :
			Port->OutSpeedReg.rw_Pin11_OutSpeed = speed;
			break;
		case 12 :
			Port->OutSpeedReg.rw_Pin12_OutSpeed = speed;
			break;
		case 13 :
			Port->OutSpeedReg.rw_Pin13_OutSpeed = speed;
			break;
		case 14 :
			Port->OutSpeedReg.rw_Pin14_OutSpeed = speed;
			break;
		case 15 :
			Port->OutSpeedReg.rw_Pin15_OutSpeed = speed;
			break;
	}
}

void Pin_PullUp_PullDown(char port, uint8_t pinNum, E_PullUpDown upDown) {
	
	GPIOx *const Port = Get_Port(port);
	
	switch(pinNum) {
	
		case 0 :
			Port->PullupPullDownReg.rw_Pin0_PUp_PDwn = upDown;
			break;
		case 1 :
			Port->PullupPullDownReg.rw_Pin1_PUp_PDwn = upDown;
			break;
		case 2 :
			Port->PullupPullDownReg.rw_Pin2_PUp_PDwn = upDown;
			break;
		case 3 :
			Port->PullupPullDownReg.rw_Pin3_PUp_PDwn = upDown;
			break;
		case 4 :
			Port->PullupPullDownReg.rw_Pin4_PUp_PDwn = upDown;
			break;
		case 5 :
			Port->PullupPullDownReg.rw_Pin5_PUp_PDwn = upDown;
			break;
		case 6 :
			Port->PullupPullDownReg.rw_Pin6_PUp_PDwn = upDown;
			break;
		case 7 :
			Port->PullupPullDownReg.rw_Pin7_PUp_PDwn = upDown;
			break;
		case 8 :
			Port->PullupPullDownReg.rw_Pin8_PUp_PDwn = upDown;
			break;
		case 9 :
			Port->PullupPullDownReg.rw_Pin9_PUp_PDwn = upDown;
			break;
		case 10 :
			Port->PullupPullDownReg.rw_Pin10_PUp_PDwn = upDown;
			break;
		case 11 :
			Port->PullupPullDownReg.rw_Pin11_PUp_PDwn = upDown;
			break;
		case 12 :
			Port->PullupPullDownReg.rw_Pin12_PUp_PDwn = upDown;
			break;
		case 13 :
			Port->PullupPullDownReg.rw_Pin13_PUp_PDwn = upDown;
			break;
		case 14 :
			Port->PullupPullDownReg.rw_Pin14_PUp_PDwn = upDown;
			break;
		case 15 :
			Port->PullupPullDownReg.rw_Pin15_PUp_PDwn = upDown;
			break;
	}
}



//Helper Functions---------------------------------------------------------------------------


static GPIOx* Get_Port(char port) {

	switch(port) {

		case 'A':
			return A;
		case 'B':
			return B;
		case 'C':
			return C;
		case 'D':
			return D;
		case 'E':
			return E;
		case 'F':
			return F;
		case 'G':
			return G;
		case 'H':
			return H;
		case 'I':
			return I;
		default:
			return ((void*)0);
	}
}


static void ClockStart_Choice(char port) {
	
	switch (port) {
		
		case 'A' :
			GPIOClock->gpioA_StartTick = 1;
			break;
		case 'B' :
			GPIOClock->gpioB_StartTick = 1;
			break;
		case 'C' :
			GPIOClock->gpioC_StartTick = 1;
			break;
		case 'D' :
			GPIOClock->gpioD_StartTick = 1;
			break;
		case 'E' :
			GPIOClock->gpioE_StartTick = 1;
			break;
		case 'F' :
			GPIOClock->gpioF_StartTick = 1;
			break;
		case 'G' :
			GPIOClock->gpioG_StartTick = 1;
			break;
		case 'H' :
			GPIOClock->gpioH_StartTick = 1;
			break;
		case 'I' :
			GPIOClock->gpioI_StartTick = 1;
			break;
	}
}