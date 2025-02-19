//STM32F407 Driver
#ifndef USART_H_
#define USART_H_
#include <stdint.h>
#include "GPIO.h"

//CLOCK
#define CLOCK 0x40023800
#define APB1 0x40
#define APB2 0x44
#define ADDR_USART_CLOCK ( (USART_CLOCK*) ((CLOCK) + APB1) )
#define ADDR_USART_CLOCK_1_6 ( (USART_CLOCK_1_6*) ((CLOCK) + APB2) )

//USART & UART
typedef struct _usart USARTx;
#define USART_BASE 0x40000000
#define ADDR_USART1 ( (USARTx*) ((USART_BASE) + 0x11000) )
#define ADDR_USART2 ( (USARTx*) ((USART_BASE) + 0x4400) )
#define ADDR_USART3 ( (USARTx*) ((USART_BASE) + 0x4800) )
#define ADDR_UART4 ( (USARTx*) ((USART_BASE) + 0x4C00) )
#define ADDR_UART5 ( (USARTx*) ((USART_BASE) + 0x5000) )
#define ADDR_USART6 ( (USARTx*) ((USART_BASE) + 0x11400) )


//For USART_CONTROL2
#define ONE_STOPBIT 0x00
#define HALF_STOPBIT 0x01
#define TWO_STOPBIT 0x02
#define ONE_AND_HALF_STOPBIT 0x03

typedef enum _Parity E_Parity;

/**
USART/UART Pins ---------------------------
		+ USART1_CK: PA4 (AF7)
		+ USART1_TX: PA2, PB6 (AF7)
		+ USART1_RX: PA3, PB7 (AF7)
		+ USART1_CTS: PA0 (AF7)
		+ USART1_RTS: PA1 (AF7)
		
		+ USART2_CTS: PA0, PD3 (AF7)
		+ USART2_RTS: PA1, PD4 (AF7)
		+ USART2_TX: PA2, PD5 (AF7)
		+ USART2_RX: PA3, PD6 (AF7)
		+ USART2_CK: PA4, PD7 (AF7)
		
		+ USART3_TX: PB10, PC10, PD8 (AF7)
		+ USART3_RX: PB11, PC11, PD9 (AF7)
		+ USART3_CK: PB12, PC12, PD10 (AF7)
		+ USART3_CTS: PB13, PD11 (AF7)
		+ USART3_RTS: PB14, PD12 (AF7)
		
		+ UART4_TX: PA0, PC10 (AF8)
		+ UART4_RX: PA1, PC11 (AF8)
		
		+ UART5_TX: PC12 (AF8)
		+ UART5_RX: PD2 (AF8)
		
		+ USART6_TX: PC6, PG14 (AF8)
		+ USART6_RX: PC7, PG9 (AF8)
		+ USART6_CK: PC8, PG7 (AF8)
		+ USART6_RTS: PG8, PG12 (AF8)
		+ USART6_CTS: PG13, PG15 (AF8)
		------------------------------------
**/

//DECLARATIONS
/**
 * @brief Set USART Baud & Oversample Rates
 * 				|||  Default System Clock (fclk): HSI 16MHz w/ No prescales or PLL
 *				|||  USART 1 & 6 fclk: APB2 High Speed Bus (84MHz MAX Freq)
 *				|||  USART/UART 2,3,4 & 5 fclk: APB1 Low Speed Bus (42MHz MAX Freq)
 *				
 *			
 * @param usartNumber USART Number (USART: 1-3, 6 UART: 4-5)
 * @param baudRate USART BaudRate
 * @param overSampleRate OverSample Rate: 8 or 16
 * @return ** void 
 */
void USART_BaudRate_and_OverSample(uint8_t usartNumber, uint32_t baudRate, uint8_t overSampleRate);
/**
 * @brief Initialize USART
 * 
 * @param usartNumber USART Number (USART: 1-3, 6 UART: 4-5)
 * @param parityType Parity Type: EVEN_PARITY, ODD_PARITY or NO_PARITY
 * @param dataBitSize Data Frame Size: 8-Bit or 9-Bit
 * @param stopBitSize Stop Bit Size: 0.5, 1.0, 1.5 or 2.0
 * @return ** void 
 */
void USART_Init(uint8_t usartNumber, E_Parity parityType, uint8_t dataBitSize, float stopBitSize);
/**
 * @brief Transmit data via USART
 * 
 * @param usartNumber USART Number (USART: 1-3, 6 UART: 4-5)
 * @param data Data to transmit
 * @return ** uint8_t 
 */
uint8_t USART_Transmit(uint8_t usartNumber, uint8_t data);
/**
 * @brief Receive data via USART
 * 
 * @param usartNumber USART Number (USART: 1-3, 6 UART: 4-5)
 * @return ** uint8_t Received Data
 */
uint8_t USART_Receive(uint8_t usartNumber);


//Enums----------------------------------------------------------------------
enum _Parity {
	EVEN_PARITY = 0, ODD_PARITY = 1, NO_PARITY = 2
};

//Registers------------------------------------------------------------------
typedef struct {
	const uint32_t reserved0:17;
	volatile uint32_t usart2_StartTick:1;
	volatile uint32_t usart3_StartTick:1;
	volatile uint32_t uart4_StartTick:1;
	volatile uint32_t uart5_StartTick:1;
	const uint32_t reserved1:11;
}USART_CLOCK;

typedef struct {
	const uint32_t reserved0:4;
	volatile uint32_t usart1_StartTick:1;
	volatile uint32_t usart6_StartTick:1;
	const uint32_t reserved1:26;
}USART_CLOCK_1_6;

typedef struct {
	volatile uint32_t parityError:1;
	volatile uint32_t FramingError:1;
	volatile uint32_t noiseDetected:1;
	volatile uint32_t overrunError:1;
	volatile uint32_t idleLineDetected:1;
	volatile uint32_t dataReadyToRead:1;
	volatile uint32_t transmissionComplete:1;
	volatile uint32_t transferRegisterOpen:1;
	volatile uint32_t localInterconnectNetworkBreak:1;
	volatile uint32_t clearToSend:1;
	const uint32_t reserved:22;
}USART_STATUS;


typedef struct {
	volatile uint32_t rw_Data:8;
	const uint32_t reserved:24;
}USART_DATA;


typedef struct {
	volatile uint32_t usartDividerFraction:4;
	volatile uint32_t usartDividerMantissa:12;
	const uint32_t reserved:16;
}USART_BAUDRATE;


typedef struct {
	volatile uint32_t send_BreakCharacter:1;
	volatile uint32_t enable_MuteMode:1;
	volatile uint32_t enable_Receiver:1;
	volatile uint32_t enable_Transmitter:1;
	volatile uint32_t enable_IDLEInterrupt:1;
	volatile uint32_t enable_readyToReadInterrupt:1;
	volatile uint32_t enable_TransmissionCompleteInterrupt:1;
	volatile uint32_t enable_TransferRegisterOpenInterrupt:1;
	volatile uint32_t enable_ParityErrorInterrupt:1;
	volatile uint32_t evenParity0_oddParity1:1;
	volatile uint32_t enable_ParityControl:1;
	volatile uint32_t idleLineWakeUp0_AddressMarkWakeUp1:1;
	volatile uint32_t data8Bit0_data9Bit1:1;
	volatile uint32_t enable_USART:1;
	const uint32_t reserved0:1;
	volatile uint32_t oversample16x0_oversample8x1:1;
	const uint32_t reserved1:16;
}USART_CONTROL1;


typedef struct {
	volatile uint32_t rw_USARTNodeAddress:4;
	const uint32_t reserved0:1;
	volatile uint32_t bit10BreakDetect0_bit11BreakDetect1:1;
	volatile uint32_t enable_LINBreakDetectionFlag:1;
	const uint32_t reserved1:1;
	volatile uint32_t enable_LastBitClockPulse:1;
	volatile uint32_t clkPhase1stTrans0_clckPhase2ndTrans1:1;
	volatile uint32_t clkPolarityLow0_clkPolarityHigh1:1;
	volatile uint32_t enable_Clock:1;
	volatile uint32_t numberOfStopBits:2;
	volatile uint32_t enable_LINMode:1;
	const uint32_t reserved2:17;
}USART_CONTROL2;


typedef struct {
	volatile uint32_t enable_ErrorFlag:1;
	volatile uint32_t enable_IrDAMode:1;
	volatile uint32_t enable_IrDALowPower:1;
	volatile uint32_t enable_HalfDuplexMode:1;
	volatile uint32_t enable_SmartcardNACK:1;
	volatile uint32_t enable_SmartcardMode:1;
	volatile uint32_t enable_DMAReceiver:1;
	volatile uint32_t enable_DMATransmitter:1;
	volatile uint32_t enable_RequestToSendInterrupt:1;
	volatile uint32_t enable_ClearToSendMode:1;
	volatile uint32_t enable_ClearToSendInterrupt:1;
	volatile uint32_t threeSampleBit0_oneSampleBit1:1;
	const uint32_t reserved:20;
}USART_CONTROL3;


typedef union {
	struct {
		volatile uint32_t rw_PrescalerValue:8;
		volatile uint32_t rw_GuardTimeValue:8;
		const uint32_t reserved:16;
	}IrDALowPowerMode;

	struct {
		volatile uint32_t rw_PrescalerValue:5;
		const uint32_t reserved0:3;
		volatile uint32_t rw_GuardTimeValue:8;
		const uint32_t reserved1:16;
	}NormalMode;
}USART_GUARDTIME_PRESCALER;





struct _usart {
	USART_STATUS StatusReg; // 0x00
	USART_DATA DataReg; // 0x04
	USART_BAUDRATE BaudRateReg; // 0x08
	USART_CONTROL1 ControlReg1; // 0x0C
	USART_CONTROL2 ControlReg2; // 0x10
	USART_CONTROL3 ControlReg3; // 0x14
	USART_GUARDTIME_PRESCALER GuardTimePrescalerReg; // 0x18
};



#endif
