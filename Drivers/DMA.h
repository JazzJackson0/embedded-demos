//STM32F407 Driver
#ifndef DMA_H_
#define DMA_H_
#include <stdint.h>
#include <stdbool.h>

//CLOCK
#define CLOCK 0x40023800
#define AHB1 0x30
#define ADDR_DMA_CLOCK ( (DMA_CLOCK*) ((CLOCK) + AHB1) )

//DMAx
typedef struct _dma DMAx;
#define DMA_BASE 0x40026000
#define ADDR_DMA1 ( (DMAx*) ((DMA_BASE) + 0x000) )
#define ADDR_DMA2 ( (DMAx*) ((DMA_BASE) + 0x400) )

#define SINGLE_TRANSFER 0x0
#define CIRCULAR 0x1

//DMA_STREAM_CONFIG Register
/*Data Sizes*/
#define BIT_8 0x00
#define  BIT_16 0x01
#define BIT_32 0x02
/*Priority Levels*/
#define LOW_P 0x00
#define MEDIUM_P 0x01
#define HIGH_P 0x02
#define VERY_HIGH_P 0x03
/*Burst Transfer Configurations*/
#define SINGLE_BURST 0x00
#define BEAT4_BURST 0x01
#define BEAT8_BURST 0x02
#define BEAT16_BURST 0x03
/*Channels*/
#define DMA_CH_0 0x00
#define DMA_CH_1 0x01
#define DMA_CH_2 0x02
#define DMA_CH_3 0x03
#define DMA_CH_4 0x04
#define DMA_CH_5 0x05
#define DMA_CH_6 0x06
#define DMA_CH_7 0x07

//DMA_STREAMx_FIFO_CONTROL Register
/*FIFO Thresholds*/
#define FIFO_1_4TH 0x00
#define FIFO_1_HALF 0x01
#define FIFO_3_4THS 0x02
#define FIFO_FULL 0x03

typedef enum _SrcDest E_SrcDest;
typedef struct _dmaconfig DMAConfig;


/*DMA Pins ---------------------------
		+ No Pins Needed
		------------------------------------*/


//DECLARATIONS
/**
 * @brief Initializ DMA
 * 
 * @param dmaNum DMA Number. (1 - 2)
 * @param streamNum 
 * @param cfg 
 * @return ** void 
 */
void DMA_Init(uint8_t dmaNum, uint8_t streamNum, DMAConfig cfg);

/**
 * @brief 
 * 
 * @param dmaNum 
 * @param streamNum 
 * @param burstSize 
 * @param fifo_thresh 
 */
void DMA_FIFOSetup(uint8_t dmaNum, uint8_t streamNum, uint8_t burstSize, uint8_t fifo_thresh);

/*Data Transfer Direction*/
enum _SrcDest {
	PERIPHERAL_TO_MEM = 0x0,
	MEM_TO_PERIPHERAL = 0x1,
	MEM_TO_MEM = 0x2
};

struct _dmaconfig {
	E_SrcDest src_dest;
	uint32_t src_address;
	uint32_t dest_address;
	uint8_t src_datasize;
	uint8_t dest_datasize;
	uint8_t channel;
	uint32_t numOfBlocks;
	uint8_t priorityLevel;
	uint8_t mode;
	bool peripheral_flowcontrol;
};

// Registers-------------------------------------------------------------------
typedef struct {
	const uint32_t reserved0:21;
	volatile uint32_t dma1_StartTick:1;
	volatile uint32_t dma2_StartTick:1;
	const uint32_t reserved1:9;
}DMA_CLOCK;

typedef struct {
	volatile uint32_t fifoErrorOnStream0:1;
	const uint32_t reserved0:1;
	volatile uint32_t directModeErrorOnStream0:1;
	volatile uint32_t transferErrorOnStream0:1;
	volatile uint32_t halfTransferEventOnStream0:1;
	volatile uint32_t transferCompleteOnStream0:1;

	volatile uint32_t fifoErrorOnStream1:1;
	const uint32_t reserved1:1;
	volatile uint32_t directModeErrorOnStream1:1;
	volatile uint32_t transferErrorOnStream1:1;
	volatile uint32_t halfTransferEventOnStream1:1;
	volatile uint32_t transferCompleteOnStream1:1;
	
	const uint32_t reserved2:4;
	
	volatile uint32_t fifoErrorOnStream2:1;
	const uint32_t reserved3:1;
	volatile uint32_t directModeErrorOnStream2:1;
	volatile uint32_t transferErrorOnStream2:1;
	volatile uint32_t halfTransferEventOnStream2:1;
	volatile uint32_t transferCompleteOnStream2:1;

	volatile uint32_t fifoErrorOnStream3:1;
	const uint32_t reserved4:1;
	volatile uint32_t directModeErrorOnStream3:1;
	volatile uint32_t transferErrorOnStream3:1;
	volatile uint32_t halfTransferEventOnStream3:1;
	volatile uint32_t transferCompleteOnStream3:1;
	
	const uint32_t reserved5:4;
}DMA_LOW_INTERRUPT_STATUS;


typedef struct {
	volatile uint32_t fifoErrorOnStream4:1;
	const uint32_t reserved0:1;
	volatile uint32_t directModeErrorOnStream4:1;
	volatile uint32_t transferErrorOnStream4:1;
	volatile uint32_t halfTransferEventOnStream4:1;
	volatile uint32_t transferCompleteOnStream4:1;

	volatile uint32_t fifoErrorOnStream5:1;
	const uint32_t reserved1:1;
	volatile uint32_t directModeErrorOnStream5:1;
	volatile uint32_t transferErrorOnStream5:1;
	volatile uint32_t halfTransferEventOnStream5:1;
	volatile uint32_t transferCompleteOnStream5:1;
	
	const uint32_t reserved2:4;
	
	volatile uint32_t fifoErrorOnStream6:1;
	const uint32_t reserved3:1;
	volatile uint32_t directModeErrorOnStream6:1;
	volatile uint32_t transferErrorOnStream6:1;
	volatile uint32_t halfTransferEventOnStream6:1;
	volatile uint32_t transferCompleteOnStream6:1;

	volatile uint32_t fifoErrorOnStream7:1;
	const uint32_t reserved4:1;
	volatile uint32_t directModeErrorOnStream7:1;
	volatile uint32_t transferErrorOnStream7:1;
	volatile uint32_t halfTransferEventOnStream7:1;
	volatile uint32_t transferCompleteOnStream7:1;
	
	const uint32_t reserved5:4;
}DMA_HIGH_INTERRUPT_STATUS;


typedef struct {
	volatile uint32_t clearFIFOFlagOnStream0:1;
	const uint32_t reserved0:1;
	volatile uint32_t clearDirectModeFlagOnStream0:1;
	volatile uint32_t clearTransferErrorFlagOnStream0:1;
	volatile uint32_t clearHalfTransferFlagOnStream0:1;
	volatile uint32_t clearTransferCompleteFlagOnStream0:1;

	volatile uint32_t clearFIFOFlagOnStream1:1;
	const uint32_t reserved1:1;
	volatile uint32_t clearDirectModeFlagOnStream1:1;
	volatile uint32_t clearTransferErrorFlagOnStream1:1;
	volatile uint32_t clearHalfTransferFlagOnStream1:1;
	volatile uint32_t clearTransferCompleteFlagOnStream1:1;
	
	const uint32_t reserved2:4;
	
	volatile uint32_t clearFIFOFlagOnStream2:1;
	const uint32_t reserved3:1;
	volatile uint32_t clearDirectModeFlagOnStream2:1;
	volatile uint32_t clearTransferErrorFlagOnStream2:1;
	volatile uint32_t clearHalfTransferFlagOnStream2:1;
	volatile uint32_t clearTransferCompleteFlagOnStream2:1;

	volatile uint32_t clearFIFOFlagOnStream3:1;
	const uint32_t reserved4:1;
	volatile uint32_t clearDirectModeFlagOnStream3:1;
	volatile uint32_t clearTransferErrorFlagOnStream3:1;
	volatile uint32_t clearHalfTransferFlagOnStream3:1;
	volatile uint32_t clearTransferCompleteFlagOnStream3:1;
	
	const uint32_t reserved5:4;
}DMA_LOW_INTERRUPT_FLAGCLEAR;


typedef struct {
	volatile uint32_t clearFIFOFlagOnStream4:1;
	const uint32_t reserved0:1;
	volatile uint32_t clearDirectModeFlagOnStream4:1;
	volatile uint32_t clearTransferErrorFlagOnStream4:1;
	volatile uint32_t clearHalfTransferFlagOnStream4:1;
	volatile uint32_t clearTransferCompleteFlagOnStream4:1;

	volatile uint32_t clearFIFOFlagOnStream5:1;
	const uint32_t reserved1:1;
	volatile uint32_t clearDirectModeFlagOnStream5:1;
	volatile uint32_t clearTransferErrorFlagOnStream5:1;
	volatile uint32_t clearHalfTransferFlagOnStream5:1;
	volatile uint32_t clearTransferCompleteFlagOnStream5:1;
	
	const uint32_t reserved2:4;
	
	volatile uint32_t clearFIFOFlagOnStream6:1;
	const uint32_t reserved3:1;
	volatile uint32_t clearDirectModeFlagOnStream6:1;
	volatile uint32_t clearTransferErrorFlagOnStream6:1;
	volatile uint32_t clearHalfTransferFlagOnStream6:1;
	volatile uint32_t clearTransferCompleteFlagOnStream6:1;

	volatile uint32_t clearFIFOFlagOnStream7:1;
	const uint32_t reserved4:1;
	volatile uint32_t clearDirectModeFlagOnStream7:1;
	volatile uint32_t clearTransferErrorFlagOnStream7:1;
	volatile uint32_t clearHalfTransferFlagOnStream7:1;
	volatile uint32_t clearTransferCompleteFlagOnStream7:1;
	
	const uint32_t reserved5:4;
}DMA_HIGH_INTERRUPT_FLAGCLEAR;


typedef struct {
	volatile uint32_t enable_Stream:1;
	volatile uint32_t enable_DirectModeErrorInterrupt:1;
	volatile uint32_t enable_TransferErrorInterrupt:1;
	volatile uint32_t enable_HalfTransferInterrupt:1;
	volatile uint32_t enable_TransferCompleteFlag:1;
	volatile uint32_t dmaAsFlowController0_peripheralAsFlowController1:1;
	volatile uint32_t rw_DataTransferDirection:2;
	volatile uint32_t enable_CircularMode:1;
	volatile uint32_t enable_PeripheralIncrementMode:1;
	volatile uint32_t enable_MemoryIncrementMode:1;
	volatile uint32_t rw_PeripheralDataSize:2;
	volatile uint32_t rw_MemoryDataSize:2;
	volatile uint32_t enable_4BitAddressOffset:1;
	volatile uint32_t rw_PriorityLevel:2;
	volatile uint32_t enable_BufferSwitchAtEndOfTransfer:1;
	volatile uint32_t targetMem00_targetMem11:1;
	const uint32_t reserved0:1;
	volatile uint32_t rw_PeripheralBurstSize:2;
	volatile uint32_t rw_MemoryBurstSize:2;
	volatile uint32_t select_Channel:3;
	const uint32_t reserved:4;
}DMA_STREAMx_CONFIG;


typedef struct {
	volatile uint32_t rw_NumOfDataItemsToTransfer:16;
	const uint32_t reserved:16;
}DMA_STREAMx_NUMBEROF_DATA;


typedef struct {
	volatile uint32_t rw_PeripheralBaseAddress:32;
}DMA_STREAMx_PERIPHERAL_ADDRESS;


typedef struct {
	volatile uint32_t rw_Memory0BaseAddress:32;
}DMA_STREAMx_MEMORY0_ADDRESS;


typedef struct {
	volatile uint32_t rw_Memory1BaseAddress:32;
}DMA_STREAMx_MEMORY1_ADDRESS;


typedef struct {
	volatile uint32_t rw_FIFOThreshold:2;
	volatile uint32_t disable_DirectMode:1;
	volatile uint32_t read_FIFOStatus:3;
	const uint32_t reserved0:1;
	volatile uint32_t enable_FIFOErrorInterrupt:1;
	const uint32_t reserved1:24;
}DMA_STREAMx_FIFO_CONTROL;




struct _dma {
	DMA_LOW_INTERRUPT_STATUS LowInterruptStatusReg; //0x00
	DMA_HIGH_INTERRUPT_STATUS HighInterruptStatusReg; //0x04
	DMA_LOW_INTERRUPT_FLAGCLEAR LowInterruptFlagClearReg; //0x08
	DMA_HIGH_INTERRUPT_FLAGCLEAR HighInterruptFlagClearReg; //0x0C

	DMA_STREAMx_CONFIG Stream0ConfigReg; //0x10
	DMA_STREAMx_NUMBEROF_DATA Stream0NumOfDataReg; //0x14
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream0PeripheralAddrsReg; //0x18
	DMA_STREAMx_MEMORY0_ADDRESS Stream0Memory0AddressReg; //0x1C
	DMA_STREAMx_MEMORY1_ADDRESS Stream0Memory1AddressReg; //0x20
	DMA_STREAMx_FIFO_CONTROL Stream0FIFOControlReg; //0x24

	DMA_STREAMx_CONFIG Stream1ConfigReg; //0x28
	DMA_STREAMx_NUMBEROF_DATA Stream1NumOfDataReg; //0x2C
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream1PeripheralAddrsReg; //0x30
	DMA_STREAMx_MEMORY0_ADDRESS Stream1Memory0AddressReg; //0x34
	DMA_STREAMx_MEMORY1_ADDRESS Stream1Memory1AddressReg; //0x38
	DMA_STREAMx_FIFO_CONTROL Stream1FIFOControlReg; //0x3C

	DMA_STREAMx_CONFIG Stream2ConfigReg; //0x40
	DMA_STREAMx_NUMBEROF_DATA Stream2NumOfDataReg; //0x44
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream2PeripheralAddrsReg; //0x48
	DMA_STREAMx_MEMORY0_ADDRESS Stream2Memory0AddressReg; //0x4C
	DMA_STREAMx_MEMORY1_ADDRESS Stream2Memory1AddressReg; //0x50
	DMA_STREAMx_FIFO_CONTROL Stream2FIFOControlReg; //0x54

	DMA_STREAMx_CONFIG Stream3ConfigReg; //0x58
	DMA_STREAMx_NUMBEROF_DATA Stream3NumOfDataReg; //0x5C
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream3PeripheralAddrsReg; //0x60
	DMA_STREAMx_MEMORY0_ADDRESS Stream3Memory0AddressReg; //0x64
	DMA_STREAMx_MEMORY1_ADDRESS Stream3Memory1AddressReg; //0x68
	DMA_STREAMx_FIFO_CONTROL Stream3FIFOControlReg; //0x6C

	DMA_STREAMx_CONFIG Stream4ConfigReg; //0x70
	DMA_STREAMx_NUMBEROF_DATA Stream4NumOfDataReg; //0x74
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream4PeripheralAddrsReg; //0x78
	DMA_STREAMx_MEMORY0_ADDRESS Stream4Memory0AddressReg; //0x7C
	DMA_STREAMx_MEMORY1_ADDRESS Stream4Memory1AddressReg; //0x80
	DMA_STREAMx_FIFO_CONTROL Stream4FIFOControlReg; //0x84

	DMA_STREAMx_CONFIG Stream5ConfigReg; //0x88
	DMA_STREAMx_NUMBEROF_DATA Stream5NumOfDataReg; //0x8C
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream5PeripheralAddrsReg; //0x90
	DMA_STREAMx_MEMORY0_ADDRESS Stream5Memory0AddressReg; //0x94
	DMA_STREAMx_MEMORY1_ADDRESS Stream5Memory1AddressReg; //0x98
	DMA_STREAMx_FIFO_CONTROL Stream5FIFOControlReg; //0x9C

	DMA_STREAMx_CONFIG Stream6ConfigReg; //0xA0
	DMA_STREAMx_NUMBEROF_DATA Stream6NumOfDataReg; //0xA4
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream6PeripheralAddrsReg; //0xA8
	DMA_STREAMx_MEMORY0_ADDRESS Stream6Memory0AddressReg; //0xAC
	DMA_STREAMx_MEMORY1_ADDRESS Stream6Memory1AddressReg; //0xB0
	DMA_STREAMx_FIFO_CONTROL Stream6FIFOControlReg; //0xB4
	
	DMA_STREAMx_CONFIG Stream7ConfigReg; //0xB8
	DMA_STREAMx_NUMBEROF_DATA Stream7NumOfDataReg; //0xBC
	DMA_STREAMx_PERIPHERAL_ADDRESS Stream7PeripheralAddrsReg; //0xC0
	DMA_STREAMx_MEMORY0_ADDRESS Stream7Memory0AddressReg; //0xC4
	DMA_STREAMx_MEMORY1_ADDRESS Stream7Memory1AddressReg; //0xC8
	DMA_STREAMx_FIFO_CONTROL Stream7FIFOControlReg; //0xCC
};


#endif
