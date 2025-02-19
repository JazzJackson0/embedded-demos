#ifndef NVIC_H_
#define NVIC_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct nvic_generic NVIC_GENERIC; // Can represent ISER, ICER, ISPER, ICPR & IABR
// NVIC
// // Add (IPR## x 4) to the interrupt# number specified in the struct fields
typedef union nvic_set_priority SET_PRIORITY_X;

typedef struct _set_as_software SET_AS_SOFTWARE;
#define ADDR_STIR ((SET_AS_SOFTWARE*) 0xE00)

// Needed for SET_SOFTWARE_TRIGGER_X to work
typedef struct _config_ctrl CONFIG_CTRL;
#define ADDR_SCR ((CONFIG_CTRL*) 0x10)

typedef enum _NVICRegs  E_NVICRegs;
typedef enum _bit E_Bit;
typedef enum _interruptType E_InterruptType;


// DECLARATIONS-------------------------------------------------------------------------------------
/**
 * @brief The AUTOMATIC Process: 
 * After The Interrupt is Initialized by the user in the NVIC (i.e. NVICInterruptInit()),
 * When Trigger occurs on given EXTI line and NVIC sees the interrupt is NOT active (from the CHECK_ACTIVE register)
 * The NVIC will set the Interrupt as Pending
 * The Interrupt stays Pending until the processor enters the desired ISR, & Interrupt's state is moved from Pending to Active.
 * 
 * Write the code for the given Interrupt Handler (e.g. EXTI15_10_IRQHandler, USART2_IRQHandler) inside the 'startup.c' file
 * 
 * Important Document for NVIC Info: See 1-Datasheets/STM32/'STM32 M4 Programming Manual.pdf'
 */


/**
 * @brief Shows currently active interrupts (not pending ones). Useful for debugging ISR execution and nested interrupts.
 *          Set when the ISR starts executing.
 *          Remains active until the ISR completes
 * @param vecTablePos The Vector Table Index of your desired Interrupt
 * @return uint8_t uint8_t Returns 1 if Active, else 0
 */
uint8_t NVIC_InterruptIsActive(uint8_t vecTablePos);

/**
 * @brief Initialize the desired Interrupt
 * 
 * @param vecTablePos 
 * @param priority 
 * @param type 
 */
void NVICInterruptInit(uint8_t vecTablePos, uint8_t priority, E_InterruptType type);

/**
 * @brief 
 * 
 * @param vecTablePos 
 * @return uint8_t 
 */
uint8_t NVIC_InterruptIsPending(uint8_t vecTablePos);


//Enums----------------------------------------------------------------------
enum _NVICRegs {
	ENABLE = 0, DISABLE = 1, SET_PENDING = 2, CLEAR_PENDING = 3, CHECK_ACTIVE = 4
};

enum _bit {
    LOW_BIT = 0, HIGH_BIT = 1
};

enum _interruptType {
    HARDWARE = 0, SOFTWARE = 1
};


//Registers----------------------------------------------------------------------
// NVIC Registers------------------------------------------------------------
// Generic Register that can represent 5 different NVIC regs
/*
1. NVIC_ISER [Interrupt Set Enable Register]: Enable interrupts, and show which interrupts are enabled.
2. NVIC_ICER [Interrupt Clear Enable Register]: Disable interrupts, and show which interrupts are enabled.
3. NVIC_ISPR [Interrupt Set Pending Register]: Force interrupts into the pending state, and show which interrupts are pending
4. NVIC_ICPR [Interrupt Clear Pending Register]: Remove the pending state from interrupts, and show which interrupts are pending.
5. NVIC_IABR [Interrupt Active Bit Register]: Indicate which interrupts are active (Set when the ISR starts executing)
*/
struct __attribute__((__packed__)) nvic_generic { 
	volatile uint32_t interrupt0:1;
	volatile uint32_t interrupt1:1;
	volatile uint32_t interrupt2:1;
	volatile uint32_t interrupt3:1;
	volatile uint32_t interrupt4:1;
	volatile uint32_t interrupt5:1;
	volatile uint32_t interrupt6:1;
	volatile uint32_t interrupt7:1;
	volatile uint32_t interrupt8:1;
	volatile uint32_t interrupt9:1;
	volatile uint32_t interrupt10:1;
	volatile uint32_t interrupt11:1;
	volatile uint32_t interrupt12:1;
	volatile uint32_t interrupt13:1;
	volatile uint32_t interrupt14:1;
	volatile uint32_t interrupt15:1;
	volatile uint32_t interrupt16:1;
	volatile uint32_t interrupt17:1;
	volatile uint32_t interrupt18:1;
	volatile uint32_t interrupt19:1;
	volatile uint32_t interrupt20:1;
	volatile uint32_t interrupt21:1;
	volatile uint32_t interrupt22:1;
	volatile uint32_t interrupt23:1;
	volatile uint32_t interrupt24:1;
	volatile uint32_t interrupt25:1;
	volatile uint32_t interrupt26:1;
	volatile uint32_t interrupt27:1;
	volatile uint32_t interrupt28:1;
	volatile uint32_t interrupt29:1;
	volatile uint32_t interrupt30:1;
	volatile uint32_t interrupt31:1;
};



// Priority range 0-255
union nvic_set_priority {

	struct {
		volatile uint32_t interrupt0PriorityByte:8;
		volatile uint32_t interrupt1PriorityByte:8;
		volatile uint32_t interrupt2PriorityByte:8;
		volatile uint32_t interrupt3PriorityByte:8;
	};
	uint32_t full_register;
};


// Required privilege: When the USERSETMPEND bit in the SCR (i.e. CONFIG_CTRL) is set to 1, unprivileged software can access the STIR
struct _set_as_software {
	volatile uint32_t vecTablePos:8;
	const uint32_t reserved:23;
};

// CONFIG_CTRL Register (Needed for Software Interrupt)--------------------------------------------------------------------------------
struct _config_ctrl {
	const uint32_t threadModeEntranceMethod:1;
	volatile uint32_t enableSoftwareAccessToSTIR:1; // The only Bit that matters here
	const uint32_t reserved0:1;
	volatile uint32_t enableUnalignedAccessTraps:1;
	volatile uint32_t enableFaulting:1;
	const uint32_t reserved1:3;
	volatile uint32_t ignoreDatbusFaults:1;
	volatile uint32_t stackAlignConfig:1;
	const uint32_t reserved2:22;
};




#endif