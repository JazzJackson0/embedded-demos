#include "USART.h"

//Macros---------------------------------------------------------------
#define CLOCK_SPEED 16

//Static Prototypes----------------------------------------------------
static void USART_PinInit(uint8_t usartNumber);
static USARTx* Get_USART(uint8_t usartNum);
static void Set_DataBitSize(uint8_t usartNumber, uint8_t dataBitSize);
static void Set_StopBitSize(uint8_t usartNumber, float stopBitSize);
static void USARTClockSelect(uint8_t usartNumber);

//Global Variables-------------------------------------------------------
USART_CLOCK_1_6 *const USARTClock1_6 = ADDR_USART_CLOCK_1_6;
USART_CLOCK *const USARTClock = ADDR_USART_CLOCK;
//USART 1
USARTx *const USART1 = ADDR_USART1;
USARTx *const USART2 = ADDR_USART2;
USARTx *const USART3 = ADDR_USART3;
USARTx *const UART4 = ADDR_UART4;
USARTx *const UART5 = ADDR_UART5;
USARTx *const USART6 = ADDR_USART6;


void USART_BaudRate_and_OverSample(uint8_t usartNumber, uint32_t baudRate, uint8_t overSampleRate) {
	
	USARTx *const USART = Get_USART(usartNumber);
	uint8_t clockSpeed = CLOCK_SPEED;
	
	switch (overSampleRate) {
		
		case 8 :
			USART->ControlReg1.oversample16x0_oversample8x1 = 1;
		case 16 :
			USART->ControlReg1.oversample16x0_oversample8x1 = 0;
	}
	
	float usartDividerFraction = (float) clockSpeed / (overSampleRate * baudRate);
	USART->BaudRateReg.usartDividerMantissa = (uint32_t) usartDividerFraction; //Ex: 1.456 -> 1
	USART->BaudRateReg.usartDividerFraction = (usartDividerFraction - USART->BaudRateReg.usartDividerMantissa) * overSampleRate; //Ex: (1.456 - 1) = 0.456 -> 0.456 * OverSampRate
}

void USART_Init(uint8_t usartNumber, E_Parity parityType, uint8_t dataBitSize, float stopBitSize){
	
	USARTClockSelect(usartNumber);
	USART_PinInit(usartNumber);
	USARTx *const USART = Get_USART(usartNumber);
	USART->ControlReg1.enable_Transmitter = 1;
	USART->ControlReg1.enable_Receiver = 1;
	
	Set_DataBitSize(usartNumber, dataBitSize);
	Set_StopBitSize(usartNumber, stopBitSize);
	
	if (parityType != NO_PARITY) {
		USART->ControlReg1.evenParity0_oddParity1 = parityType;
		USART->ControlReg1.enable_ParityControl = 1;
	}
	
	USART->ControlReg1.enable_USART = 1; //Will send an Idle frame as first transmission
}


uint8_t USART_Transmit(uint8_t usartNumber, uint8_t data) {
	USARTx *const USART = Get_USART(usartNumber);
	while (USART->StatusReg.transferRegisterOpen != 1);
	USART->DataReg.rw_Data = data;
	return 1;
}

uint8_t USART_Receive(uint8_t usartNumber) {
	USARTx *const USART = Get_USART(usartNumber);
	while (USART->StatusReg.dataReadyToRead != 1);
	return USART->DataReg.rw_Data;
}


//Helper Functions--------------------------------------------------------------------------------------------------------------
static void USART_PinInit(uint8_t usartNumber) {
	
	switch(usartNumber) {
		case 1 :
			//TX
			Pin_Init('A', 2, AF7);
			//RX
			Pin_Init('A', 3, AF7);
			break;
		case 2 :
			//TX
			Pin_Init('D', 5, AF7);
			//RX
			Pin_Init('D', 6, AF7);
			break;
		case 3 :
			//TX
			Pin_Init('B', 10, AF7);
			//RX
			Pin_Init('B', 11, AF7);
			break;
		case 4 : 
			//TX
			Pin_Init('A', 0, AF8);
			//RX
			Pin_Init('A', 1, AF8);
			break;
		case 5 : 
			//TX
			Pin_Init('C', 12, AF8);
			//RX
			Pin_Init('D', 2, AF8);
			break;
		case 6 :
			//TX
			Pin_Init('C', 6, AF8);
			//RX
			Pin_Init('C', 7, AF8);
			break;
	}
}


static USARTx* Get_USART(uint8_t usartNum) {

	switch(usartNum) {
		case 1:
			return USART1;
		case 2:
			return USART2;
		case 3:
			return USART3;
		case 4:
			return UART4;
		case 5:
			return UART5;
		case 6:
			return USART6;
		default:
			return ((void*)0);
	}
}

static void Set_DataBitSize(uint8_t usartNumber, uint8_t dataBitSize) {
	
	USARTx *const USART = Get_USART(usartNumber);
	switch (dataBitSize) {
		case 8 : 
			USART->ControlReg1.data8Bit0_data9Bit1 = 0;
		case 9 : 
			USART->ControlReg1.data8Bit0_data9Bit1 = 1;
	}
}

static void Set_StopBitSize(uint8_t usartNumber, float stopBitSize) {
	
	USARTx *const USART = Get_USART(usartNumber);
	if (stopBitSize == (float) 0.5) { USART->ControlReg2.numberOfStopBits = HALF_STOPBIT; }
	if (stopBitSize == (float) 1.0) { USART->ControlReg2.numberOfStopBits = ONE_STOPBIT; }
	if (stopBitSize == (float) 1.5) { USART->ControlReg2.numberOfStopBits = ONE_AND_HALF_STOPBIT; }
	if (stopBitSize == (float) 2.0) { USART->ControlReg2.numberOfStopBits = TWO_STOPBIT; }
}

static void USARTClockSelect(uint8_t usartNumber) {
	
	switch(usartNumber) {
		case 1 :
			USARTClock1_6->usart1_StartTick = 1;
			break;
		case 2 :
			USARTClock->usart2_StartTick = 1;
			break;
		case 3 :
			USARTClock->usart3_StartTick = 1;
			break;
		case 4 : 
			USARTClock->uart4_StartTick = 1;
			break;
		case 5 : 
			USARTClock->uart5_StartTick = 1;
			break;
		case 6 :
			USARTClock1_6->usart6_StartTick = 1;
			break;
	}
}