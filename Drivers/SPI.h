//STM32F407 Driver
#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>
#include "GPIO.h"

//CLOCK
#define CLOCK 0x40023800
#define APB2 0x44
#define APB1 0x40
#define ADDR_SPI_CLOCK_1 ( (SPI_CLOCK_1*) ((CLOCK) + APB2) )
#define ADDR_SPI_CLOCK_2_3 ( (SPI_CLOCK_2_3*) ((CLOCK) + APB1) )

//SPIx
typedef struct _spi SPIx;
#define SPI_BASE 0x40013000
#define ADDR_SPI1 ( (SPIx*) ((SPI_BASE) + 0x000) )
#define ADDR_SPI2 ( (SPIx*) ((SPI_BASE) + 0x800) ) // And IS2
#define ADDR_SPI3 ( (SPIx*) ((SPI_BASE) + 0xC00) ) // And IS3


//SPI_I2S_CONFIG Register
/*Len Of Transfer Data*/
#define LEN_16BIT 0x00
#define LEN_24BIT 0x01
#define LEN_32BIT 0x02


/*I2S Standards*/
#define PHILLIPS_STANDARD 0x00
#define MSB_JUSTIFIED_STANDARD 0x01
#define LSB_JUSTIFIED_STANDARD 0x02
#define PCM_STANDARD 0x03

/*I2S Config Modes*/
#define SLAVE_TRANSMIT 0x00
#define SLAVE_RECEIVE 0x01
#define MASTER_TRANSMIT 0x02
#define MASTER_RECEIVE 0x03

typedef enum _Phase E_Phase;
typedef enum _Polarity E_Polarity;
typedef enum _Prescaler E_Prescaler;
typedef enum _Mode E_Mode;
typedef enum _BitOrder E_BitOrder;


/**
SPI Pins ---------------------------
		+ SPI1_NSS: PA4, PA15 (AF5)
		+ SPI1_SCK: PA5, PB3 (AF5)
		+ SPI1_MISO: PA6, PB4 (AF5)
		+ SPI1_MOSI: PA7, PB5 (AF5)
		
		+ SPI2_NSS: PB9, PB12, PI0 (AF5)
		+ SPI2_SCK: PB10, PB13, PI1 (AF5)
		+ SPI2_MISO: PB14, PC2, PI2 (AF5)
		+ SPI2_MOSI: PB15, PC3, PI3 (AF5)
		
		+ SPI3_NSS: PA4, PA15 (AF6)
		+ SPI3_SCK: PB3, PC10 (AF6)
		+ SPI3_MISO: PB4, PC11 (AF6)
		+ SPI3_MOSI: PB5, PC12 (AF6)
		------------------------------------
**/

//DECLARATIONS
/**
 * @brief Set SPI Clock Settings
 * 
 * @param spiNumber SPI Number (1 - 3)
 * @param phase Clock Phase: _1ST_EDGE or _2ND_EDGE
 * @param polarity Clock Polarity: HIGH_POL or LOW_POL
 * @param prescaler Clock Prescaler: Sets the BaudRate. 
 * 					(CLOCK_DIV_x: Where x = 2, 4, 8, 16, 32, 64, 128, 256)
 * 					|||  (Example: Prescaler Value = [2]
 * 					|||  PCLK2 [AKA: APB2 84 MHz] -- SPI1 Clock Default
 * 					|||  Baud Rate = PCLK2 / [2] = 42 MHz)
 * @return ** void 
 */
void SPI_ClockSetup(uint8_t spiNumber, E_Phase phase, E_Polarity polarity, E_Prescaler prescaler);
/**
 * @brief Initialize SPI
 * 
 * @param spiNumber SPI Number (1 - 3)
 * @param mode SPI Mode: SLAVE or MASTER
 * @param bitOrder Order of Bits: LSB or MSB
 * @param dataSize Size of data frame: 8-Bit or 16-Bit 
 * @return ** void 
 */
void SPI_Init(uint8_t spiNumber, E_Mode mode, E_BitOrder bitOrder, uint8_t dataSize);
/**
 * @brief Receive Data via SPI
 * 
 * @param spiNumber SPI Number (1 - 3)
 * @return ** uint8_t Received Data
 */
uint8_t SPI_Receive(uint8_t spiNumber);
/**
 * @brief Transmit Data via SPI
 * 
 * @param spiNumber SPI Number (1 - 3)
 * @param data Data to transmit
 * @return ** uint8_t 
 */
uint8_t SPI_Transmit(uint8_t spiNumber, uint8_t data);


//Enums----------------------------------------------------------------------
enum _Phase {
	_1ST_EDGE = 0, _2ND_EDGE = 1
};

enum _Polarity {
	LOW_POL = 0, HIGH_POL = 1
};

//SPI_CONTROL1 Register
/*Baud Rate*/
enum _Prescaler {
	CLOCK_DIV_2 = 0x00, CLOCK_DIV_4 = 0x01,
	CLOCK_DIV_8 = 0x02, CLOCK_DIV_16 = 0x03,
	CLOCK_DIV_32 = 0x04, CLOCK_DIV_64 = 0x05,
	CLOCK_DIV_128 = 0x06, CLOCK_DIV_256 = 0x07
};

enum _Mode {
	SLAVE = 0, MASTER = 1
};

enum _BitOrder {
	MSB = 0, LSB = 1
};

//Registers------------------------------------------------------------------

typedef struct {
	const uint32_t reserved0:12;
	volatile uint32_t spi1_StartTick:1;
	const uint32_t reserved1:19;
}SPI_CLOCK_1;

typedef struct {
	const uint32_t reserved0:14;
	volatile uint32_t spi2_StartTick:1;
	volatile uint32_t spi3_StartTick:1;
	const uint32_t reserved1:16;
}SPI_CLOCK_2_3;

typedef struct {
	volatile uint16_t trans1ClockPhase0_trans2ClockPhase1:1;
	volatile uint16_t clockPolarityLow0_clockPolarityHigh1:1;
	volatile uint16_t slaveMode0_masterMode1:1;
	volatile uint16_t rw_BaudRate:3;
	volatile uint16_t enable_SPI:1;
	volatile uint16_t msbFirst0_lsbFirst1:1;
	volatile uint16_t softwareNSSLow0_softwareNSSHigh1:1;
	volatile uint16_t enable_SoftwareSlaveSelect:1;
	volatile uint16_t disable_Output:1;
	volatile uint16_t dataFrame8Bit0_dataFrame16Bit1:1;
	volatile uint16_t transfer_CRC:1;
	volatile uint16_t enable_CRCCalculation:1;
	volatile uint16_t enable_Output:1;
	volatile uint16_t uniDirect2Line0_BiDirect1Line1:1;
}SPI_CONTROL1;

typedef struct {
	volatile uint16_t enable_RXBufferDMA:1;
	volatile uint16_t enable_TXBufferDMA:1;
	volatile uint16_t enable_HardwareSlaveSelectAsOutput:1;
	const uint32_t reserved0:1;
	volatile uint16_t motorolaMode0_tiMode1:1;
	volatile uint16_t enable_ErrorInterrupt:1;
	volatile uint16_t enable_dataReadyToReadInterrupt:1;
	volatile uint16_t enable_transferRegisterOpenInterrupt:1;
	const uint32_t reserved1:8;
}SPI_CONTROL2;

typedef struct {
	volatile uint16_t dataReadyToRead:1;
	volatile uint16_t transferRegisterOpen:1;
	volatile uint16_t channelLeftTXRX0_channelRightTXRX1:1;
	volatile uint16_t underrunOccurred:1;
	volatile uint16_t crcErrorOccurred:1;
	volatile uint16_t modeFaultOccurred:1;
	volatile uint16_t overrunOccurred:1;
	volatile uint16_t spiBusy:1;
	volatile uint16_t frameFormatErrorOccurred:1;
	const uint16_t reserved:7;
}SPI_STATUS;

typedef struct {
	volatile uint16_t rw_Data:16;
}SPI_DATA;

typedef struct {
	volatile uint16_t rw_CRCPolynomial:16;
}SPI_CRC_POLYNOMIAL;

typedef struct {
	volatile uint16_t read_CRC:16;
}SPI_RX_CRC;

typedef struct {
	volatile uint16_t write_CRC:16;
}SPI_TX_CRC;

typedef struct {
	volatile uint16_t channelLen16Bit0_channelLen32Bit1:1;
	volatile uint16_t rw_LengthOfTransferData:2;
	volatile uint16_t clockPolarityLow0_clockPolarityHigh1:1;
	volatile uint16_t rw_I2SStandard:2;
	const uint16_t reserved0:1;
	volatile uint16_t shortFrameSync0_longFrameSync1:1;
	volatile uint16_t rw_I2SMode:2;
	volatile uint16_t enable_I2SPeripheral:1;
	volatile uint16_t enable_I2SMode:1;
	const uint16_t reserved1:4;
}SPI_I2S_CONFIG; // Alternate version for STM32F446 below

/*
STM32F446 Version
typedef struct {
	volatile uint16_t channelLen16Bit0_channelLen32Bit1:1;
	volatile uint16_t rw_LengthOfTransferData:2;
	volatile uint16_t clockPolarityLow0_clockPolarityHigh1:1;
	volatile uint16_t rw_I2SStandard:2;
	const uint16_t reserved0:1;
	volatile uint16_t shortFrameSync0_longFrameSync1:1;
	volatile uint16_t rw_I2SMode:2;
	volatile uint16_t enable_I2SPeripheral:1;
	volatile uint16_t enable_I2SMode:1;
	volatile uint16_t enable_AsynchronousStart:1;
	const uint16_t reserved1:3;
}SPI_I2S_CONFIG;
*/

typedef struct {
	volatile uint16_t rw_I2SLinearPrescaler:8;
	volatile uint16_t enable_OddPrescaler:1;
	volatile uint16_t enable_MasterClockOutput:1;
	const uint16_t reserved:6;
}SPI_I2S_PRESCALER;







struct _spi {
	SPI_CONTROL1 ControlReg1; // 0x00
	SPI_CONTROL2 ControlReg2; // 0x04
	SPI_STATUS StatusReg; // 0x08
	SPI_DATA DataReg; // 0x0C
	SPI_CRC_POLYNOMIAL CRCPolynomialReg; // 0x10
	SPI_RX_CRC RXCRCReg; // 0x14
	SPI_TX_CRC TXCRCReg; // 0x18
	SPI_I2S_CONFIG I2SConfigReg; // 0x1C
	SPI_I2S_PRESCALER I2SPrescalerReg; // 0x20
};



#endif
