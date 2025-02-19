//STM32F407 Driver
#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GPIO.h"

//CAN_ERRORSTATUS
/*Most recent error code*/
#define NO_ERROR 0x00
#define STUFF_ERROR 0x01
#define FORM_ERROR 0x02
#define ACK_ERROR 0x03
#define BIT_RECESSIVE_ERROR 0x04
#define BIT_DOMINANT_ERROR 0x05
#define CRC_ERROR 0x06
#define SETBY_SOFTWARE 0x07

//CLOCK
#define CLOCK 0x40023800
#define APB1 0x40
#define ADDR_CAN_CLOCK ( (CAN_CLOCK*) ((CLOCK) + APB1) )

//CANx
typedef struct _can CANx;
typedef struct _mailbox_filters MAIL_FILTERSx;
typedef union _filterBanks FILTER_BANKSx;
#define CAN_BASE 0x40006000
//
#define ADDR_CAN1 ( (CANx*) ((CAN_BASE) + 0x400) )
#define ADDR_CAN1_MAIL_FILTERS ( (MAIL_FILTERSx*) ((CAN_BASE) + (0x400 + 0x180)) )
#define ADDR_CAN1_FILTERBANKS ( (FILTER_BANKSx*) ((CAN_BASE) + (0x400 + 0x240) ) )
//
#define ADDR_CAN2 ( (CANx*) ((CAN_BASE) + 0x800) )
#define ADDR_CAN2_MAIL_FILTERS ( (MAIL_FILTERSx*) ((CAN_BASE) + (0x800 + 0x180)) )
#define ADDR_CAN2_FILTERBANKS ( (FILTER_BANKSx*) ((CAN_BASE) + (0x400 + 0x2B0) ) )

typedef enum _FilterSize E_FilterSize;
typedef enum _FilterMode E_FilterMode;
typedef union _Data Received_Data;
typedef struct _filter Filter;
typedef struct _InterruptManager CAN_InterruptManager;

/**
CAN Pins ---------------------------
		+ CAN1_TX: PA12, PB9, PD1, PH13 (AF9)
		+ CAN1_RX: PA11, PB8, PD0, PI9 (AF9)

		+ CAN2_TX: PB6, PB13 (AF9)
		+ CAN2_RX: PB5, PB12 (AF9)
		------------------------------------
**/

//DECLARATIONS
/**
 * @brief Set CAN Bit Rate
 * 			|||  1 Mbps Bit Rate Example:
 *				|||  Prescaler = 1
 *				|||  Num of Time Quanta = 16
 *					||| (a) Resync Jump Width = 1 (Always 1)
 *					||| (b) Seg 1 = 13
 *					||| (c) Seg 2 = 2
 *					||| (d) 1 + 13 + 2 = 16
 *				|||  Obtained from bittiming.can
 * 
 * @param canNum CAN Number (1 - 2)
 * @param baudRatePrescale BaudRate Prescaler
 * @param resyncJump Resync Jump Widtth
 * @param timeSeg1 Time Segment 1
 * @param timeSeg2 Time Segment 2
 * @return ** void 
 */
void CAN_SetBitTime(uint8_t canNum, uint8_t baudRatePrescale, uint8_t resyncJump, 
	uint8_t timeSeg1, uint8_t timeSeg2);
/**
 * @brief Set Up CAN Acceptance Filter
 * 
 * @param canNum CAN Number (1 - 2)
 * @param filterInfo Struct containing CAN Acceptance Filter Information
 * @return ** void 
 */
void CAN_SetAcceptanceFilter(uint8_t canNum, Filter *filterInfo);
/**
 * @brief Set Up CAN TX Mailbox
 * 
 * @param canNum CAN Number (1 - 2)
 * @param mailboxNum Mailbox Number (0 - 2)
 * @param standardID Mailbox Acceptance Filter ID
 * @param numOfBytes Mailbox Data Transmission Size (0 Bytes - 8 Bytes)
 * @return ** void 
 */
void CAN_SetTXMailbox(uint8_t canNum, uint8_t mailboxNum, uint64_t standardID, uint8_t numOfBytes);
/**
 * @brief Set Up CAN RX Mailbox
 * 
 * @param canNum CAN Number (1 - 2)
 * @param mailboxNum Mailbox Number (0 - 2)
 * @param standardID Mailbox Acceptance Filter ID
 * @param numOfBytes Mailbox Data Reception Size (0 Bytes - 8 Bytes)
 * @return ** void 
 */
void CAN_SetRXMailbox(uint8_t canNum, uint8_t mailboxNum, uint64_t standardID, uint8_t numOfBytes);
/**
 * @brief Initialize and Start CAN
 * 
 * @param canNum CAN Number (1 - 2)
 * @param port Port ID (A - I)
 * @param pinNums TX and RX Pin Numbers
 * @return ** void 
 */
void CAN_Init_and_Start(uint8_t canNum, char port, uint8_t pinNums[]);
/**
 * @brief Transmit Data via CAN
 * 
 * @param canNum CAN Number (1 - 2)
 * @param mailboxNum Mailbox Number (0 - 2)
 * @param dataBuffer Data to transmit
 * @param numOfBytes Number of Bytes to Transmit
 * @return ** int8_t 
 */
int8_t CAN_Transmit(uint8_t canNum, uint8_t mailboxNum, uint8_t *dataBuffer, uint8_t numOfBytes);
/**
 * @brief Receive Data via CAN
 * 
 * @param canNum CAN Number (1 - 2)
 * @param mailboxNum Mailbox Number (0 - 2)
 * @param numOfBytes Number of Bytes to Receive
 * @return ** Received_Data* 
 */
Received_Data* CAN_Receive(uint8_t canNum, uint8_t mailboxNum, uint8_t numOfBytes);
/**
 * @brief Enable selected CAN interrupts
 * 
 * @param canNum CAN Number (1 - 2)
 * @param interrupt_manager 
 */
void CAN_EnableInterrupts(uint8_t canNum, CAN_InterruptManager interrupt_manager);

//Enums----------------------------------------------------------------------

//CAN_FILTER_SCALE
enum _FilterSize {
	_16BIT_CAN = 0, _32BIT_CAN = 1
};

//CAN_FILTER_MODE
enum _FilterMode {
	MASK_MODE = 0, LIST_MODE = 1
};

//Structs----------------------------------------------------------------------
//Filter

/**
 * @brief |||  filterNum: Filter 0 - Filter 27 |||  filterSize: 16-Bit or 32-Bit 
 * 		|||  filterMode: Mask Mode or List Mode |||  filterVal: Acceptance (Standard ID will be compared to this) 
 * 		|||  mailboxFIFOoNum: (What FIFO to filter for) FIFO 0 or FIFO 1 
 */
struct _filter{
	uint8_t filterNum; // Filter 0 - Filter 27
	E_FilterSize filterSize; // _16BIT_CAN or _32BIT_CAN 
	E_FilterMode filterType; // MASK_MODE or LIST_MODE
	uint32_t filterVal; // Acceptance Filter Identifier Value or Mask Value (Standard ID will be compared to this) 
	uint8_t mailboxFIFONum; // FIFO 0 or FIFO 1
};

//Byte Container
union _Data {
	struct {
		uint8_t byte0;
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
		uint8_t byte4;
		uint8_t byte5;
		uint8_t byte6;
		uint8_t byte7;
	};
	
	uint8_t dataIterator[8];
};

struct _InterruptManager{
	bool TransmitMailboxEmptyInterrupt_ON;
	bool FIFO0MessagePendingInterrupt_ON;
	bool FIFO0FullInterrupt_ON;
	bool FIFO0OverrunInterrupt_ON;
	bool FIFO1MessagePendingInterrupt_ON;
	bool FIFO1FullInterrupt_ON;
	bool FIFO1OverrunInterrupt_ON;
	bool ErrorWarningInterrupt_ON;
	bool ErrorPassiveInterrupt_ON;
	bool BusOffInterrupt_ON;
	bool LastErrorCodeInterrupt_ON;
	bool ErrorInterrupt_ON;
	bool WakeupInterrupt_ON;
	bool SleepInterrupt_ON;
};

// Registers-----------------------------------------------------------------


//Clock Register-------------------------------------------------------------
typedef struct {
	const uint32_t reserved0:25;
	volatile uint32_t can1_StartTick:1;
	volatile uint32_t can2_StartTick:1;
	const uint32_t reserved1:5;
}CAN_CLOCK;


//CONTROL & STATUS REGISTERS-----------------------------------------------
typedef struct {
	const uint32_t reserved1:32;
}CAN_RESERVED;

typedef struct {
	volatile uint32_t send_InitializeModeRequest:1;
	volatile uint32_t send_SleepModeRequest:1;
	volatile uint32_t txOrderIdentifier0_txOrderChronological1:1;
	volatile uint32_t enable_LockRXWhenFull:1;
	volatile uint32_t disable_AutoRetransmit:1;
	volatile uint32_t enable_AutoWakeUp:1;
	volatile uint32_t enable_AutoExitBusOffState:1;
	volatile uint32_t enable_TimeTriggeredCommMode:1;
	const uint32_t reserved0:7;
	volatile uint32_t resetMaster_thenSleep:1;
	volatile uint32_t enable_FreezeDuringDebug:1;
	const uint32_t reserved:15;
}CAN_MASTER_CONTROL;

typedef struct {
	volatile uint32_t initializeModeRequestAccepted:1;
	volatile uint32_t sleepModeRequestAccepted:1;
	volatile uint32_t errorDetected:1;
	volatile uint32_t wakeUpDetected:1;
	volatile uint32_t inSleepMode:1;
	const uint32_t reserved0:3;
	volatile uint32_t inTransmitMode:1;
	volatile uint32_t inReceiveMode:1;
	volatile uint32_t rxVal_LastSamplePoint:1;
	volatile uint32_t rxSignal:1;
	const uint32_t reserved:20;
}CAN_MASTER_SATUS;

typedef struct {
	volatile uint32_t mailbox0_RequestCompleted:1;
	volatile uint32_t mailbox0_TransmitSuccess:1;
	volatile uint32_t mailbox0_ArbitrationLost:1;
	volatile uint32_t mailbox0_TransmitError:1;
	const uint32_t reserved0:3;
	volatile uint32_t send_Mailbox0TransmitAbortRequest:1;
	volatile uint32_t mailbox1_RequestCompleted:1;
	volatile uint32_t mailbox1_TransmitSuccess:1;
	volatile uint32_t mailbox1_ArbitrationLost:1;
	volatile uint32_t mailbox1_TransmitError:1;
	const uint32_t reserved1:3;
	volatile uint32_t send_Mailbox1TransmitAbortRequest:1;
	volatile uint32_t mailbox2_RequestCompleted:1;
	volatile uint32_t mailbox2_TransmitSuccess:1;
	volatile uint32_t mailbox2_ArbitrationLost:1;
	volatile uint32_t mailbox2_TransmitError:1;
	const uint32_t reserved2:3;
	volatile uint32_t send_Mailbox2TransmitAbortRequest:1;
	volatile uint32_t freeMailbox:2;
	volatile uint32_t mailbox0_NoTransmitRequestPending:1;
	volatile uint32_t mailbox1_NoTransmitRequestPending:1;
	volatile uint32_t mailbox2_NoTransmitRequestPending:1;
	volatile uint32_t mailbox0_HasLowestPriority:1;
	volatile uint32_t mailbox1_HasLowestPriority:1;
	volatile uint32_t mailbox2_HasLowestPriority:1;
}CAN_TRANSMIT_STATUS;

typedef struct {
	volatile uint32_t numOfMessagesWaitingInFIFO0:2;
	const uint32_t reserved0:1;
	volatile uint32_t messageFIFO0_Full:1;
	volatile uint32_t messageFIFO0_Overrun:1;
	volatile uint32_t release_FIFO0_OutputMailbox:1;
	const uint32_t reserved1:26;
}CAN_RECEIVE_FIFO0;

typedef struct {
	volatile uint32_t numOfMessagesWaitingInFIFO1:2;
	const uint32_t reserved0:1;
	volatile uint32_t messageFIFO1_Full:1;
	volatile uint32_t messageFIFO1_Overrun:1;
	volatile uint32_t release_FIFO1_OutputMailbox:1;
	const uint32_t reserved1:26;
}CAN_RECEIVE_FIFO1;

typedef struct {
	volatile uint32_t enable_TransmitMailboxEmptyInterrupt:1;
	volatile uint32_t enable_FIFO0MessagePendingInterrupt:1;
	volatile uint32_t enable_FIFO0FullInterrupt:1;
	volatile uint32_t enable_FIFO0OverrunInterrupt:1;
	volatile uint32_t enable_FIFO1MessagePendingInterrupt:1;
	volatile uint32_t enable_FIFO1FullInterrupt:1;
	volatile uint32_t enable_FIFO1OverrunInterrupt:1;
	const uint32_t reserved0:1;
	volatile uint32_t enable_ErrorWarningInterrupt:1;
	volatile uint32_t enable_ErrorPassiveInterrupt:1;
	volatile uint32_t enable_BusOffInterrupt:1;
	volatile uint32_t enable_LastErrorCodeInterrupt:1;
	const uint32_t reserved1:3;
	volatile uint32_t enable_ErrorInterrupt:1;
	volatile uint32_t enable_WakeupInterrupt:1;
	volatile uint32_t enable_SleepInterrupt:1;
	const uint32_t reserved2:14;
}CAN_INTERRUPTS;

typedef struct {
	volatile uint32_t errorWarning:1;
	volatile uint32_t ErrorPassive:1;
	volatile uint32_t busOff:1;
	const uint32_t reserved0:1;
	volatile uint32_t mostRecentErrorCode:3;
	const uint32_t reserved1:9;
	volatile uint32_t numOfTransmitErrors:8;
	volatile uint32_t numOfReceiveErrors:8;
}CAN_ERRORSTATUS;

typedef struct {
	volatile uint32_t rw_BaudRatePrescaler:10;
	const uint32_t reserved0:6;
	volatile uint32_t rw_TimeSegment1:4; //No Macros available
	volatile uint32_t rw_TimeSegment2:3; //No Macros available
	const uint32_t reserved1:1;
	volatile uint32_t rw_ReSyncJumpWidth:2; //No Macros available
	const uint32_t reserved2:4;
	volatile uint32_t enable_LoopbackMode:1;
	volatile uint32_t enable_SilentMode:1;
}CAN_BITTIMING;


//MAILBOX REGISTERS-------------------------------------------------------
typedef union {
	
	struct {
		volatile uint32_t request_TransmissionFromMailbox:1;
		volatile uint32_t enable_RemoteFrame:1;
		volatile uint32_t enable_ExtendedIdentifier:1;
		volatile uint32_t rw_ExtendedIdentifier:26;
		const uint32_t reserved:3;
	}ExtendedIdentifier;

	struct {
		volatile uint32_t request_TransmissionFromMailbox:1;
		volatile uint32_t enable_RemoteFrame:1;
		const uint32_t reserved:19;
		volatile uint32_t rw_StandardIdentifier:11;
	}StandardIdentifier;

}CAN_TX_MAILBOX_IDENTIFIER;

typedef struct {
	volatile uint32_t rw_DataLen_InBytes:4; //0 to 8 Bytes
	const uint32_t reserved0:4;
	volatile uint32_t transmit_GlobalTime:1;
	const uint32_t reserved1:7;
	volatile uint32_t rw_MessageTimeStamp:16;
}CAN_TX_MAILBOX_DATALENCNTRL_TIMESTAMP; // Alternate (446) Version below

/** ALTERNATIVE FOR STM32F446
typedef struct {
	volatile uint32_t rw_DataLen_InBytes:4;
	const uint32_t reserved:12;
	volatile uint32_t rw_MessageTimeStamp:16;
}CAN_TX_MAILBOX_DATALENCNTRL_TIMESTAMP;
**/

typedef union {
	struct {
		volatile uint32_t rw_DataByte0:8;
		volatile uint32_t rw_DataByte1:8;
		volatile uint32_t rw_DataByte2:8;
		volatile uint32_t rw_DataByte3:8;
	};
	volatile uint32_t data;
	// uint8_t dataIterator[4];
}CAN_TX_MAILBOX_DATALOW;

typedef union {
	struct {
		volatile uint32_t rw_DataByte4:8;
		volatile uint32_t rw_DataByte5:8;
		volatile uint32_t rw_DataByte6:8;
		volatile uint32_t rw_DataByte7:8;
	};
	volatile uint32_t data;
	// uint8_t dataIterator[4];

}CAN_TX_MAILBOX_DATAHIGH;

typedef struct {
	struct {
		const uint32_t reserved0:1;
		volatile uint32_t enable_RemoteFrame:1;
		volatile uint32_t enable_ExtendedIdentifier:1;
		volatile uint32_t read_ExtendedIdentifier:26;
		const uint32_t reserved1:3;
	}ExtendedIdentifier;

	struct {
		const uint32_t reserved0:1;
		volatile uint32_t enable_RemoteFrame:1;
		const uint32_t reserved1:19;
		volatile uint32_t read_StandardIdentifier:11;
	}StandardIdentifier;
}CAN_RX_MAILBOX_IDENTIFIER;

typedef struct {
	volatile uint32_t read_DataLen_InBytes:4;
	const uint32_t reserved0:4;
	volatile uint32_t read_IdentifierFilterMatchIndex:8;
	volatile uint32_t read_MessageTimeStamp:16;
}CAN_RX_MAILBOX_DATALENCNTRL_TIMESTAMP;

typedef union {
	struct {
		volatile uint32_t read_DataByte0:8;
		volatile uint32_t read_DataByte1:8;
		volatile uint32_t read_DataByte2:8;
		volatile uint32_t read_DataByte3:8;
	};

	uint8_t dataIterator[4];
	
}CAN_RX_MAILBOX_DATALOW;

typedef union {
	struct {
		volatile uint32_t read_DataByte4:8;
		volatile uint32_t read_DataByte5:8;
		volatile uint32_t read_DataByte6:8;
		volatile uint32_t read_DataByte7:8;
	};

	uint8_t dataIterator[4];
	
}CAN_RX_MAILBOX_DATAHIGH;



//FILTER REGISTERS--------------------------------------------------------
typedef struct {
	volatile uint32_t filterActive0_filterReadyToInitialize1:1;
	const uint32_t reserved0:7;
	volatile uint32_t set_CAN2StartBank:6;
	const uint32_t reserved1:18;
}CAN_FILTER_MASTER;

typedef struct {
	volatile uint32_t filter0IDMaskMode0_filter0IDListMode1:1;
	volatile uint32_t filter1IDMaskMode0_filter1IDListMode1:1;
	volatile uint32_t filter2IDMaskMode0_filter2IDListMode1:1;
	volatile uint32_t filter3IDMaskMode0_filter3IDListMode1:1;
	volatile uint32_t filter4IDMaskMode0_filter4IDListMode1:1;
	volatile uint32_t filter5IDMaskMode0_filter5IDListMode1:1;
	volatile uint32_t filter6IDMaskMode0_filter6IDListMode1:1;
	volatile uint32_t filter7IDMaskMode0_filter7IDListMode1:1;
	volatile uint32_t filter8IDMaskMode0_filter8IDListMode1:1;
	volatile uint32_t filter9IDMaskMode0_filter9IDListMode1:1;
	volatile uint32_t filter10IDMaskMode0_filter10IDListMode1:1;
	volatile uint32_t filter11IDMaskMode0_filter11IDListMode1:1;
	volatile uint32_t filter12IDMaskMode0_filter12IDListMode1:1;
	volatile uint32_t filter13IDMaskMode0_filter13IDListMode1:1;
	volatile uint32_t filter14IDMaskMode0_filter14IDListMode1:1;
	volatile uint32_t filter15IDMaskMode0_filter15IDListMode1:1;
	volatile uint32_t filter16IDMaskMode0_filter16IDListMode1:1;
	volatile uint32_t filter17IDMaskMode0_filter17IDListMode1:1;
	volatile uint32_t filter18IDMaskMode0_filter18IDListMode1:1;
	volatile uint32_t filter19IDMaskMode0_filter19IDListMode1:1;
	volatile uint32_t filter20IDMaskMode0_filter20IDListMode1:1;
	volatile uint32_t filter21IDMaskMode0_filter21IDListMode1:1;
	volatile uint32_t filter22IDMaskMode0_filter22IDListMode1:1;
	volatile uint32_t filter23IDMaskMode0_filter23IDListMode1:1;
	volatile uint32_t filter24IDMaskMode0_filter24IDListMode1:1;
	volatile uint32_t filter25IDMaskMode0_filter25IDListMode1:1;
	volatile uint32_t filter26IDMaskMode0_filter26IDListMode1:1;
	volatile uint32_t filter27IDMaskMode0_filter27IDListMode1:1;
	const uint32_t reserved:4;
}CAN_FILTER_MODE;

typedef struct {
	volatile uint32_t filter0Size16B0_filter0Size32B1:1;
	volatile uint32_t filter1Size16B0_filter1Size32B1:1;
	volatile uint32_t filter2Size16B0_filter2Size32B1:1;
	volatile uint32_t filter3Size16B0_filter3Size32B1:1;
	volatile uint32_t filter4Size16B0_filter4Size32B1:1;
	volatile uint32_t filter5Size16B0_filter5Size32B1:1;
	volatile uint32_t filter6Size16B0_filter6Size32B1:1;
	volatile uint32_t filter7Size16B0_filter7Size32B1:1;
	volatile uint32_t filter8Size16B0_filter8Size32B1:1;
	volatile uint32_t filter9Size16B0_filter9Size32B1:1;
	volatile uint32_t filter10Size16B0_filter10Size32B1:1;
	volatile uint32_t filter11Size16B0_filter11Size32B1:1;
	volatile uint32_t filter12Size16B0_filter12Size32B1:1;
	volatile uint32_t filter13Size16B0_filter13Size32B1:1;
	volatile uint32_t filter14Size16B0_filter14Size32B1:1;
	volatile uint32_t filter15Size16B0_filter15Size32B1:1;
	volatile uint32_t filter16Size16B0_filter16Size32B1:1;
	volatile uint32_t filter17Size16B0_filter17Size32B1:1;
	volatile uint32_t filter18Size16B0_filter18Size32B1:1;
	volatile uint32_t filter19Size16B0_filter19Size32B1:1;
	volatile uint32_t filter20Size16B0_filter20Size32B1:1;
	volatile uint32_t filter21Size16B0_filter21Size32B1:1;
	volatile uint32_t filter22Size16B0_filter22Size32B1:1;
	volatile uint32_t filter23Size16B0_filter23Size32B1:1;
	volatile uint32_t filter24Size16B0_filter24Size32B1:1;
	volatile uint32_t filter25Size16B0_filter25Size32B1:1;
	volatile uint32_t filter26Size16B0_filter26Size32B1:1;
	volatile uint32_t filter27Size16B0_filter27Size32B1:1;
	const uint32_t reserved:4;
}CAN_FILTER_SCALE;

typedef struct {
	volatile uint32_t filter0ToFIFO0_filter0ToFIFO1:1;
	volatile uint32_t filter1ToFIFO0_filter1ToFIFO1:1;
	volatile uint32_t filter2ToFIFO0_filter2ToFIFO1:1;
	volatile uint32_t filter3ToFIFO0_filter3ToFIFO1:1;
	volatile uint32_t filter4ToFIFO0_filter4ToFIFO1:1;
	volatile uint32_t filter5ToFIFO0_filter5ToFIFO1:1;
	volatile uint32_t filter6ToFIFO0_filter6ToFIFO1:1;
	volatile uint32_t filter7ToFIFO0_filter7ToFIFO1:1;
	volatile uint32_t filter8ToFIFO0_filter8ToFIFO1:1;
	volatile uint32_t filter9ToFIFO0_filter9ToFIFO1:1;
	volatile uint32_t filter10ToFIFO0_filter10ToFIFO1:1;
	volatile uint32_t filter11ToFIFO0_filter11ToFIFO1:1;
	volatile uint32_t filter12ToFIFO0_filter12ToFIFO1:1;
	volatile uint32_t filter13ToFIFO0_filter13ToFIFO1:1;
	volatile uint32_t filter14ToFIFO0_filter14ToFIFO1:1;
	volatile uint32_t filter15ToFIFO0_filter15ToFIFO1:1;
	volatile uint32_t filter16ToFIFO0_filter16ToFIFO1:1;
	volatile uint32_t filter17ToFIFO0_filter17ToFIFO1:1;
	volatile uint32_t filter18ToFIFO0_filter18ToFIFO1:1;
	volatile uint32_t filter19ToFIFO0_filter19ToFIFO1:1;
	volatile uint32_t filter20ToFIFO0_filter20ToFIFO1:1;
	volatile uint32_t filter21ToFIFO0_filter21ToFIFO1:1;
	volatile uint32_t filter22ToFIFO0_filter22ToFIFO1:1;
	volatile uint32_t filter23ToFIFO0_filter23ToFIFO1:1;
	volatile uint32_t filter24ToFIFO0_filter24ToFIFO1:1;
	volatile uint32_t filter25ToFIFO0_filter25ToFIFO1:1;
	volatile uint32_t filter26ToFIFO0_filter26ToFIFO1:1;
	volatile uint32_t filter27ToFIFO0_filter27ToFIFO1:1;
	const uint32_t reserved:4;
}CAN_FILTER_FIFO_ASSIGNMENT;

typedef struct {
	volatile uint32_t enable_Filter0:1;
	volatile uint32_t enable_Filter1:1;
	volatile uint32_t enable_Filter2:1;
	volatile uint32_t enable_Filter3:1;
	volatile uint32_t enable_Filter4:1;
	volatile uint32_t enable_Filter5:1;
	volatile uint32_t enable_Filter6:1;
	volatile uint32_t enable_Filter7:1;
	volatile uint32_t enable_Filter8:1;
	volatile uint32_t enable_Filter9:1;
	volatile uint32_t enable_Filter10:1;
	volatile uint32_t enable_Filter11:1;
	volatile uint32_t enable_Filter12:1;
	volatile uint32_t enable_Filter13:1;
	volatile uint32_t enable_Filter14:1;
	volatile uint32_t enable_Filter15:1;
	volatile uint32_t enable_Filter16:1;
	volatile uint32_t enable_Filter17:1;
	volatile uint32_t enable_Filter18:1;
	volatile uint32_t enable_Filter19:1;
	volatile uint32_t enable_Filter20:1;
	volatile uint32_t enable_Filter21:1;
	volatile uint32_t enable_Filter22:1;
	volatile uint32_t enable_Filter23:1;
	volatile uint32_t enable_Filter24:1;
	volatile uint32_t enable_Filter25:1;
	volatile uint32_t enable_Filter26:1;
	volatile uint32_t enable_Filter27:1;
	const uint32_t reserved:4;
}CAN_FILTER_ACTIVATION;

typedef union {
	struct {
		volatile uint32_t bit0_IdentiferORMask:1;
		volatile uint32_t bit1_IdentiferORMask:1;
		volatile uint32_t bit2_IdentiferORMask:1;
		volatile uint32_t bit3_IdentiferORMask:1;
		volatile uint32_t bit4_IdentiferORMask:1;
		volatile uint32_t bit5_IdentiferORMask:1;
		volatile uint32_t bit6_IdentiferORMask:1;
		volatile uint32_t bit7_IdentiferORMask:1;
		volatile uint32_t bit8_IdentiferORMask:1;
		volatile uint32_t bit9_IdentiferORMask:1;
		volatile uint32_t bit10_IdentiferORMask:1;
		volatile uint32_t bit11_IdentiferORMask:1;
		volatile uint32_t bit12_IdentiferORMask:1;
		volatile uint32_t bit13_IdentiferORMask:1;
		volatile uint32_t bit14_IdentiferORMask:1;
		volatile uint32_t bit15_IdentiferORMask:1;
		volatile uint32_t bit16_IdentiferORMask:1;
		volatile uint32_t bit17_IdentiferORMask:1;
		volatile uint32_t bit18_IdentiferORMask:1;
		volatile uint32_t bit19_IdentiferORMask:1;
		volatile uint32_t bit20_IdentiferORMask:1;
		volatile uint32_t bit21_IdentiferORMask:1;
		volatile uint32_t bit22_IdentiferORMask:1;
		volatile uint32_t bit23_IdentiferORMask:1;
		volatile uint32_t bit24_IdentiferORMask:1;
		volatile uint32_t bit25_IdentiferORMask:1;
		volatile uint32_t bit26_IdentiferORMask:1;
		volatile uint32_t bit27_IdentiferORMask:1;
		volatile uint32_t bit28_IdentiferORMask:1;
		volatile uint32_t bit29_IdentiferORMask:1;
		volatile uint32_t bit30_IdentiferORMask:1;
		volatile uint32_t bit31_IdentiferORMask:1;
		volatile uint32_t bit32_IdentiferORMask:1;
	};

	uint32_t IdentiferORMask;
	
}CAN_FILTERBANKi_REGISTERx;





struct _can {
	CAN_MASTER_CONTROL MasterControlReg; // 0x00
	CAN_MASTER_SATUS MasterStatusReg; // 0x04
	CAN_TRANSMIT_STATUS TransmitStatReg; // 0x08
	CAN_RECEIVE_FIFO0 RXFIFO0Reg; // 0x0C
	CAN_RECEIVE_FIFO1 RXFIFO1Reg; // 0x10
	CAN_INTERRUPTS InterruptsReg; // 0x14
	CAN_ERRORSTATUS ErrorStatusReg; // 0x18
	CAN_BITTIMING BitTimingReg; // 0x1C
};


struct _mailbox_filters {
	CAN_TX_MAILBOX_IDENTIFIER TXMailBox0IDReg; //0x180
	CAN_TX_MAILBOX_DATALENCNTRL_TIMESTAMP TXMailBox0DataLenCtrlTimeStampReg; //0x184
	CAN_TX_MAILBOX_DATALOW TXMailBox0DataLowReg; //0x188
	CAN_TX_MAILBOX_DATAHIGH TXMailBox0DataHighReg; //0x18C

	CAN_TX_MAILBOX_IDENTIFIER TXMailBox1IDReg; //0x190
	CAN_TX_MAILBOX_DATALENCNTRL_TIMESTAMP TXMailBox1DataLenCtrlTimeStampReg; //0x194
	CAN_TX_MAILBOX_DATALOW TXMailBox1DataLowReg; //0x198
	CAN_TX_MAILBOX_DATAHIGH TXMailBox1DataHighReg; //0x19C

	CAN_TX_MAILBOX_IDENTIFIER TXMailBox2IDReg; //0x1A0
	CAN_TX_MAILBOX_DATALENCNTRL_TIMESTAMP TXMailBox2DataLenCtrlTimeStampReg; //0x1A4
	CAN_TX_MAILBOX_DATALOW TXMailBox2DataLowReg; //0x1A8
	CAN_TX_MAILBOX_DATAHIGH TXMailBox2DataHighReg; //0x1AC
	
	CAN_RX_MAILBOX_IDENTIFIER RXMailBox0IDReg; //0x1B0
	CAN_RX_MAILBOX_DATALENCNTRL_TIMESTAMP RXMailBox0DataLenCtrlTimeStampReg; //0x1B4
	CAN_RX_MAILBOX_DATALOW RXMailBox0DataLowReg; //0x1B8
	CAN_RX_MAILBOX_DATAHIGH RXMailBox0DataHighReg; //0x1BC

	CAN_RX_MAILBOX_IDENTIFIER RXMailBox1IDReg; //0x1C0
	CAN_RX_MAILBOX_DATALENCNTRL_TIMESTAMP RXMailBox1DataLenCtrlTimeStampReg; //0x1C4
	CAN_RX_MAILBOX_DATALOW RXMailBox1DataLowReg; //0x1C8
	CAN_RX_MAILBOX_DATAHIGH RXMailBox1DataHighReg; //0x1CC
	CAN_RESERVED reserved0; // 0x1D0
	CAN_RESERVED reserved1; // 0x1D4
	CAN_RESERVED reserved2; // 0x1D8
	CAN_RESERVED reserved3; // 0x1DC
	CAN_RESERVED reserved4; // 0x1E0
	CAN_RESERVED reserved5; // 0x1E4
	CAN_RESERVED reserved6; // 0x1E8
	CAN_RESERVED reserved7; // 0x1EC
	CAN_RESERVED reserved8; // 0x1F0
	CAN_RESERVED reserved9; // 0x1F4
	CAN_RESERVED reserved10; // 0x1F8
	CAN_RESERVED reserved11; // 0x1FC
	CAN_FILTER_MASTER FilterMasterReg; // 0x200
	CAN_FILTER_MODE FilterModeReg; // 0x204
	CAN_RESERVED reserved12; // 0x208
	CAN_FILTER_SCALE FilterScaleReg; // 0x20C
	CAN_RESERVED reserved13; // 0x210
	CAN_FILTER_FIFO_ASSIGNMENT FilterFIFOAssignReg; // 0x214
	CAN_RESERVED reserved14; // 0x218
	CAN_FILTER_ACTIVATION FilterActivationReg; // 0x21C
	CAN_RESERVED reserved15; // 0x220
	CAN_RESERVED reserved16; // 0x224
	CAN_RESERVED reserved17; // 0x228
	CAN_RESERVED reserved18; // 0x22C
	CAN_RESERVED reserved19; // 0x230
	CAN_RESERVED reserved20; // 0x234
	CAN_RESERVED reserved21; // 0x238
	CAN_RESERVED reserved22; // 0x23C
};

union _filterBanks {
	struct  {
		CAN_FILTERBANKi_REGISTERx FilterBank0; // Reg1: 0x240 (CAN 1) | Reg2: 0x2B0 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank1; // Reg1: 00x244 (CAN 1) | Reg2: 0x2B4 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank2; // Reg1: 00x248 (CAN 1) | Reg2: 0x2B8 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank3; // Reg1: 00x24C (CAN 1) | Reg2: 0x2BC (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank4; // Reg1: 00x250 (CAN 1) | Reg2: 0x2C0 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank5; // Reg1: 00x254 (CAN 1) | Reg2: 0x2C4 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank6; // Reg1: 00x258 (CAN 1) | Reg2: 0x2C8 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank7; // Reg1: 00x25C (CAN 1) | Reg2: 0x2CC (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank8; // Reg1: 00x260 (CAN 1) | Reg2: 0x2D0 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank9; // Reg1: 00x264 (CAN 1) | Reg2: 0x2D4 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank10; // Reg1: 00x268 (CAN 1) | Reg2: 0x2D8 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank11; // Reg1: 00x26C (CAN 1) | Reg2: 0x2DC (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank12; // Reg1: 00x270 (CAN 1) | Reg2: 0x2E0 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank13; // Reg1: 00x274 (CAN 1) | Reg2: 0x2E4 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank14; // Reg1: 00x278 (CAN 1) | Reg2: 0x2E8 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank15; // Reg1: 00x27C (CAN 1) | Reg2: 0x2EC (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank16; // Reg1: 00x280 (CAN 1) | Reg2: 0x2F0 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank17; // Reg1: 00x284 (CAN 1) | Reg2: 0x2F4 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank18; // Reg1: 00x288 (CAN 1) | Reg2: 0x2F8 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank19; // Reg1: 00x28C (CAN 1) | Reg2: 0x2FC (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank20; // Reg1: 00x290 (CAN 1) | Reg2: 0x300 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank21; // Reg1: 00x294 (CAN 1) | Reg2: 0x304 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank22; // Reg1: 00x298 (CAN 1) | Reg2: 0x308 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank23; // Reg1: 00x29C (CAN 1) | Reg2: 0x30C (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank24; // Reg1: 00x2A0 (CAN 1) | Reg2: 0x310 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank25; // Reg1: 00x2A4 (CAN 1) | Reg2: 0x314 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank26; // Reg1: 00x2A8 (CAN 1) | Reg2: 0x318 (CAN 2)
		CAN_FILTERBANKi_REGISTERx FilterBank27; // Reg1: 00x2AC (CAN 1) | Reg2: 0x31C (CAN 2)
	};

	CAN_FILTERBANKi_REGISTERx Banks[28];
};


#endif
