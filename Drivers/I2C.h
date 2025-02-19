//STM32F407 Driver
#ifndef I2C_H_
#define I2C_H_
#include <stdint.h>
#include <stdio.h>
#include "GPIO.h"

//CLOCK
#define CLOCK 0x40023800
#define APB1 0x40
#define ADDR_I2C_CLOCK ( (I2C_CLOCK*) ((CLOCK) + APB1) )

//I2Cx
typedef struct _i2c I2Cx;
#define I2C_BASE 0x40005000
#define ADDR_I2C1 ( (I2Cx*) ((I2C_BASE) + 0x400) )
#define ADDR_I2C2 ( (I2Cx*) ((I2C_BASE) + 0x800) )
#define ADDR_I2C3 ( (I2Cx*) ((I2C_BASE) + 0xC00) )


//I2C_CONTROL1
/*SMBus Type*/
#define SMBUS_DEVICE 0x00
#define SMBUS_HOST 0x01

typedef enum _ReadWrite E_ReadWrite;

/**
I2C Pins ---------------------------------
		+ I2C1_SCL: PB6, PB8 (AF4)
		+ I2C1_SDA: PB7, PB9 (AF4)
		+ I2C1_SMBA PB5 (AF4)
		
		+ I2C2_SCL: PB10, PF1, PH4 (AF4)
		+ I2C2_SDA: PB11, PF0, PH5 (AF4)
		+ I2C2_SMBA PB12, PF2 (AF4)
		
		+ I2C3_SCL: PA8, PH7 (AF4)
		+ I2C3_SCL: PC9, PH8 (AF4)
		------------------------------------
**/

//DECLARATIONS
/**
 * @brief Initialize I2C
 * 			|||  Clock Control Clock Value Calculation Example:
 *				|||  (1) SCL FREQ GOAL: 100KHz = 10,000 ns(p)
 *					|||  (1a) Peripheral Clock Frequency: 8MHz = 125 ns(p)
 *					|||  (1b) [Clock Value * 125 ns(p) = 10,000 ns(p)]
 *					|||  (1c) Clock Value = 10,000 / 125 ns(p)
 *					|||  (1d) Clock Value = 80 (i.e. 0x50)
 * 
 * @param i2cNumber I2C Number (1 - 3)
 * @param apbClockFreqMHz APB Clock Frequency in MHz (Ex: 8 for 8MHz Clock)
 * @param desiredI2CFrequencykHz Desired I2C Frequency in KHz (Ex: 100 for 100KHz SCLK)
 * @return ** void 
 */
void I2C_Init(uint8_t i2cNumber, uint8_t apbClockFreqMHz, uint8_t desiredI2CFrequencykHz);
/**
 * @brief Start I2C as Master and start communication.
 * 
 * @param i2cNumber I2C Number (1 - 3)
 * @param slaveAddress Address of the Slave Device the host desires to communicate with.
 * @param readWrite READ_BIT or WRITE_BIT
 * @return ** uint8_t 
 */
uint8_t I2C_StartMaster_SendAddress(uint8_t i2cNumber, uint8_t slaveAddress, E_ReadWrite readWrite);
/**
 * @brief Receive data via I2C
 * 
 * @param i2cNumber I2C Number (1 - 3)
 * @return ** uint8_t Received data
 */
uint8_t I2C_Receive(uint8_t i2cNumber);
/**
 * @brief Transmit data via I2C
 * 
 * @param i2cNumber I2C Number (1 - 3)
 * @param data Data to transmit
 * @return ** uint8_t 
 */
uint8_t I2C_Transmit(uint8_t i2cNumber, uint8_t data);
/**
 * @brief Send 'Stop Condition' to end current transmission.
 * 
 * @param i2cNumber I2C Number (1 - 3)
 * @return ** void 
 */
void I2C_Stop(uint8_t i2cNumber);

//Enums----------------------------------------------------------------------
enum _ReadWrite {
	WRITE_BIT = 0, READ_BIT = 1
};

//Registers------------------------------------------------------------------
typedef struct {
	const uint32_t reserved0:21;
	volatile uint32_t i2c1_StartTick:1;
	volatile uint32_t i2c2_StartTick:1;
	volatile uint32_t i2c3_StartTick:1;
	const uint32_t reserved1:8;
}I2C_CLOCK;


typedef struct {

	volatile uint16_t enable_I2C:1;
	volatile uint16_t i2cMode0_SMBusMode1:1;
	const uint16_t reserved0:1;
	volatile uint16_t rw_SMBusType:1;
	volatile uint16_t enable_AddressResolutionProtocol:1;
	volatile uint16_t enable_PacketErrorCheck:1;
	volatile uint16_t enable_GeneralCall:1;
	volatile uint16_t disable_ClockStetchSlave:1;
	volatile uint16_t enable_StartGeneration:1;
	volatile uint16_t enable_StopGeneration:1;
	volatile uint16_t enable_ACK:1;
	volatile uint16_t currentACKPEC0_nextACKPEC1:1;
	volatile uint16_t enable_PECTransfer:1;
	volatile uint16_t enable_SMBusAlert:1;
	const uint16_t reserved1:1;
	volatile uint16_t reset_I2C:1;
}I2C_CONTROL1;


typedef struct {
	volatile uint16_t rw_APBClockFrequency:6;
	const uint16_t reserved0:2;
	volatile uint16_t enable_ErrorInterrupt:1;
	volatile uint16_t enable_EventInterrupt:1;
	volatile uint16_t enable_BufferInterrupt:1;
	volatile uint16_t enable_DMARequests:1;
	volatile uint16_t enable_DMALastTransfer:1;
	const uint16_t reserved1:3;
}I2C_CONTROL2;


typedef union {
	struct {
		volatile uint16_t rw_address10:10;
		const uint16_t reserved0:5;
		volatile uint16_t addrss7Bit0_addrss10Bit1:1;
	}Address10;
	
	struct {
		const uint16_t reserved0:1;
		volatile uint16_t rw_address7:7;
		const uint16_t reserved1:7;
		volatile uint16_t addrss7Bit0_addrss10Bit1:1;
	}Address7;
}I2C_OWNADDRESS1;


typedef struct {
	volatile uint16_t enable_DualAddressing:1;
	volatile uint16_t rw_InterfaceAddress:7;
	const uint16_t reserved:8;
}I2C_OWNADDRESS2;


typedef struct {
	volatile uint16_t rw_Data:8;
	const uint16_t reserved:8;
}I2C_DATA;

typedef struct {
	volatile uint16_t masterStartBitSet:1;
	volatile uint16_t addressSentOrMatched:1;
	volatile uint16_t byteTransferFinished:1;
	volatile uint16_t master10BitHeaderSent:1;
	volatile uint16_t slaveStopConditionDetected:1;
	const uint16_t reserved0:1;
	volatile uint16_t dataReadyToRead:1;
	volatile uint16_t transferRegisterOpen:1;
	volatile uint16_t busError:1;
	volatile uint16_t masterArbitrationLost:1;
	volatile uint16_t ackFailure:1;
	volatile uint16_t overrunUnderrun:1;
	volatile uint16_t receiverPECError:1;
	const uint16_t reserved1:1;
	volatile uint16_t TimeoutTLowError:1;
	volatile uint16_t smBusAlert:1;
}I2C_STATUS1;


typedef struct {
	volatile uint16_t masterMode1_slaveMode0:1;
	volatile uint16_t busBusy:1;
	volatile uint16_t transmitter1_receiver0:1;
	const uint16_t reserved:1;
	volatile uint16_t generalCallAddressReceived:1;
	volatile uint16_t smBusDefaultAddressReceived:1;
	volatile uint16_t smBusHostAddressReceived:1;
	volatile uint16_t addrssMatchOwn2nd1_addrssMatchOwn1st0:1;
	volatile uint16_t set_PacketErrorCheckValue:8;
}I2C_STATUS2;

typedef struct {
	volatile uint16_t rw_ClockValue:12;
	const uint16_t reserved:2;
	volatile uint16_t rw_FMDutyCycle:1;
	volatile uint16_t smMode0_fmMode1:1;
}I2C_CLOCKCONTROL;

typedef struct {
	volatile uint16_t rw_MaxRiseTime:6;
	const uint16_t reserved:10;
}I2C_RISETIME;

typedef struct {
	volatile uint16_t rw_DigitalNoiseFilterValue:4;
	volatile uint16_t disable_AnalogNoiseFilter:1;
	const uint16_t reserved:11;
}I2C_NOISEFILTER;




struct _i2c {
	I2C_CONTROL1 ControlReg1; //0x00
	I2C_CONTROL2 ControlReg2; //0x04
	I2C_OWNADDRESS1 OwnAddressReg1; //0x08
	I2C_OWNADDRESS2 OwnAddressReg2; //0x0C
	I2C_DATA DataReg; //0x10
	I2C_STATUS1 StatusReg1; //0x14
	I2C_STATUS2 StatusReg2; //0x18
	I2C_CLOCKCONTROL ClockControlReg; //0x1C
	I2C_RISETIME RiseTimeReg; //0x20
	I2C_NOISEFILTER NoiseFilterReg; //0x24
};


#endif
