#include "DMA.h"

//Static Prototypes------------------------------------------------------
static DMAx* Get_DMA(uint8_t dmaNum);

//Global Variables-------------------------------------------------------
DMA_CLOCK *const DMAClock = ADDR_DMA_CLOCK;

//DMA
DMAx *const DMA1 = ADDR_DMA1;
DMAx *const DMA2 = ADDR_DMA2;


void DMA_Init(uint8_t dmaNum, uint8_t streamNum, DMAConfig cfg) {

	DMAx *const DMA = Get_DMA(dmaNum);
	if (dmaNum == 1) { DMAClock->dma1_StartTick = 1; }
	else { DMAClock->dma2_StartTick = 1; }

	switch (streamNum) {

		case 0 :	
			DMA->Stream0ConfigReg.enable_Stream = 0;
			DMA->Stream0ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream0PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream0Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream0ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream0ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
				DMA->Stream0ConfigReg.dmaAsFlowController0_peripheralAsFlowController1 = cfg.peripheral_flowcontrol;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream0PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream0Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream0ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream0ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream0Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream0Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream0ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}
			
			DMA->Stream0ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream0ConfigReg.enable_TransferErrorInterrupt = 1;
			DMA->LowInterruptFlagClearReg.clearTransferCompleteFlagOnStream0 = 1;
			DMA->LowInterruptFlagClearReg.clearTransferErrorFlagOnStream0 = 1;
			DMA->Stream0ConfigReg.enable_MemoryIncrementMode = 1;
			DMA->Stream0ConfigReg.select_Channel = cfg.channel;
			DMA->Stream0NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream0ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream0ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream0ConfigReg.enable_Stream = 1;
			break;
		case 1 :
			DMA->Stream1ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream1PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream1Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream1ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream1ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream1PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream1Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream1ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream1ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream1Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream1Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream1ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			DMA->Stream1ConfigReg.select_Channel = cfg.channel;
			DMA->Stream1NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream1ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream1ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream1ConfigReg.enable_Stream = 1;
			break;
		case 2 :
			DMA->Stream2ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream2PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream2Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream2ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream2ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream2PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream2Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream2ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream2ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream2Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream2Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream2ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			DMA->Stream2ConfigReg.select_Channel = cfg.channel;
			DMA->Stream2NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream2ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream2ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream2ConfigReg.enable_Stream = 1;
			break;
		case 3 :
			DMA->Stream3ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream3PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream3Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream3ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream3ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream3PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream3Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream3ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream3ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream3Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream3Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream3ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			DMA->Stream3ConfigReg.select_Channel = cfg.channel;
			DMA->Stream3NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream3ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream3ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream3ConfigReg.enable_Stream = 1;
			break;
		case 4 :
			DMA->Stream4ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream4PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream4Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream4ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream4ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream4PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream4Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream4ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream4ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream4Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream4Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream4ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			DMA->Stream4ConfigReg.select_Channel = cfg.channel;
			DMA->Stream4NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream4ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream4ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream4ConfigReg.enable_Stream = 1;
			break;
		case 5 :
			DMA->Stream5ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream5PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream5Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream5ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream5ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream5PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream5Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream5ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream5ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream5Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream5Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream5ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			DMA->Stream5ConfigReg.select_Channel = cfg.channel;
			DMA->Stream5NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream5ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream5ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream5ConfigReg.enable_Stream = 1;
			break;
		case 6 :
			DMA->Stream6ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream6PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream6Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream6ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream6ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream6PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream6Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream6ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream6ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream6Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream6Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream6ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			DMA->Stream6ConfigReg.select_Channel = cfg.channel;
			DMA->Stream6NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream6ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream6ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream6ConfigReg.enable_Stream = 1;
			break;
		case 7 :
			DMA->Stream7ConfigReg.rw_DataTransferDirection = cfg.src_dest;

			if (cfg.src_dest == PERIPHERAL_TO_MEM) {
				DMA->Stream7PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.src_address;
				DMA->Stream7Memory0AddressReg.rw_Memory0BaseAddress = cfg.dest_address;
				DMA->Stream7ConfigReg.rw_PeripheralDataSize = cfg.src_datasize;
				DMA->Stream7ConfigReg.rw_MemoryDataSize = cfg.dest_datasize;
			}

			else if (cfg.src_dest == MEM_TO_PERIPHERAL) {
				DMA->Stream7PeripheralAddrsReg.rw_PeripheralBaseAddress = cfg.dest_address;
				DMA->Stream7Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream7ConfigReg.rw_PeripheralDataSize = cfg.dest_datasize;
				DMA->Stream7ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			else if (cfg.src_dest == MEM_TO_MEM) {
				DMA->Stream7Memory0AddressReg.rw_Memory0BaseAddress = cfg.src_address;
				DMA->Stream7Memory1AddressReg.rw_Memory1BaseAddress = cfg.dest_address;
				DMA->Stream7ConfigReg.rw_MemoryDataSize = cfg.src_datasize;
			}

			DMA->Stream7ConfigReg.select_Channel = cfg.channel;
			DMA->Stream7NumOfDataReg.rw_NumOfDataItemsToTransfer = cfg.numOfBlocks;
			DMA->Stream7ConfigReg.rw_PriorityLevel = cfg.priorityLevel;
			DMA->Stream7ConfigReg.enable_CircularMode = cfg.mode;
			DMA->Stream7ConfigReg.enable_Stream = 1;
			break;
	}
}


void DMA_FIFOSetup(uint8_t dmaNum, uint8_t streamNum, uint8_t burstSize, uint8_t fifo_thresh) {

	DMAx *const DMA = Get_DMA(dmaNum);

	switch (streamNum) {

		case 0 :	
			DMA->Stream0ConfigReg.enable_Stream = 0;
			DMA->Stream0FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream0ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream0FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream0ConfigReg.enable_Stream = 1;
			break;
		case 1 :	
			DMA->Stream1ConfigReg.enable_Stream = 0;
			DMA->Stream1FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream1ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream1ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream1FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream1ConfigReg.enable_Stream = 1;
			break;
		case 2 :	
			DMA->Stream2ConfigReg.enable_Stream = 0;
			DMA->Stream2FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream2ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream2ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream2FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream2ConfigReg.enable_Stream = 1;
			break;
		case 3 :	
			DMA->Stream3ConfigReg.enable_Stream = 0;
			DMA->Stream3FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream3ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream3ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream3FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream3ConfigReg.enable_Stream = 1;
			break;
		case 4 :	
			DMA->Stream4ConfigReg.enable_Stream = 0;
			DMA->Stream4FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream4ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream4ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream4FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream4ConfigReg.enable_Stream = 1;
			break;
		case 5 :	
			DMA->Stream5ConfigReg.enable_Stream = 0;
			DMA->Stream5FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream5ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream5ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream5FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream5ConfigReg.enable_Stream = 1;
			break;
		case 6 :	
			DMA->Stream6ConfigReg.enable_Stream = 0;
			DMA->Stream6FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream6ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream6ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream6FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream6ConfigReg.enable_Stream = 1;
			break;
		case 7 :	
			DMA->Stream7ConfigReg.enable_Stream = 0;
			DMA->Stream7FIFOControlReg.disable_DirectMode = 1;
			DMA->Stream7ConfigReg.rw_MemoryBurstSize = burstSize;
			DMA->Stream7ConfigReg.enable_TransferCompleteFlag = 1;
			DMA->Stream7FIFOControlReg.rw_FIFOThreshold = fifo_thresh;
			DMA->Stream7ConfigReg.enable_Stream = 1;
			break;
	}
}


//Helper Functions------------------------------------------------------------------
static DMAx* Get_DMA(uint8_t dmaNum) {

	switch(dmaNum) {

		case 1:
			return DMA1;
		case 2:
			return DMA2;
		default:
			return ((void*)0);
	}
}
