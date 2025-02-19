#include "NVIC.h"

//Static Prototypes---------------------------------------------
static void AlterInterruptSettings(NVIC_GENERIC *generic, uint8_t offset, uint8_t vecTablePos, E_Bit bit);
static uint8_t ReadInterruptSettings(NVIC_GENERIC *generic, uint8_t offset, uint8_t vecTablePos, E_Bit bit);
static void EditInterrupt(uint8_t vecTablePos, E_NVICRegs regType);
static uint8_t ReadInterrupt(uint8_t vecTablePos, E_NVICRegs regType);
static void SetInterruptPriority(uint8_t vecTablePos, uint8_t priority);

//Global Variables------------------------------------------------
NVIC_GENERIC* addresses[5][8] = {
    {(NVIC_GENERIC*)0xE000E100, (NVIC_GENERIC*)0xE000E104, (NVIC_GENERIC*)0xE000E108, (NVIC_GENERIC*)0xE000E10C, // Row 0: ISER0 - ISER7
        (NVIC_GENERIC*)0xE000E110, (NVIC_GENERIC*)0xE000E114, (NVIC_GENERIC*)0xE000E118, (NVIC_GENERIC*)0xE000E11C},

    {(NVIC_GENERIC*)0xE000E180, (NVIC_GENERIC*)0xE000E184, (NVIC_GENERIC*)0xE000E188, (NVIC_GENERIC*)0xE000E18C, // Row 1: ICER0 - ICER7
        (NVIC_GENERIC*)0xE000E190, (NVIC_GENERIC*)0xE000E194, (NVIC_GENERIC*)0xE000E198, (NVIC_GENERIC*)0xE000E19C}, 

    {(NVIC_GENERIC*)0xE000E200, (NVIC_GENERIC*)0xE000E204, (NVIC_GENERIC*)0xE000E208, (NVIC_GENERIC*)0xE000E20C, // Row 2: ISPR0 - ISPR7
        (NVIC_GENERIC*)0xE000E210, (NVIC_GENERIC*)0xE000E214, (NVIC_GENERIC*)0xE000E218, (NVIC_GENERIC*)0xE000E21C}, 

    {(NVIC_GENERIC*)0xE000E280, (NVIC_GENERIC*)0xE000E284, (NVIC_GENERIC*)0xE000E288, (NVIC_GENERIC*)0xE000E28C, // Row 3: ICPR0 - ICPR7
        (NVIC_GENERIC*)0xE000E290, (NVIC_GENERIC*)0xE000E294, (NVIC_GENERIC*)0xE000E298, (NVIC_GENERIC*)0xE000E29C}, 

    {(NVIC_GENERIC*)0xE000E300, (NVIC_GENERIC*)0xE000E304, (NVIC_GENERIC*)0xE000E308, (NVIC_GENERIC*)0xE000E30C, // Row 4: IABR0 - IABR7
        (NVIC_GENERIC*)0xE000E310, (NVIC_GENERIC*)0xE000E314, (NVIC_GENERIC*)0xE000E318, (NVIC_GENERIC*)0xE000E31C}}; 

SET_PRIORITY_X* priority_addresses[60] ={ // IPR0 - IPR59 (4 Interrupts per Register)
(SET_PRIORITY_X*)0xE000E400, (SET_PRIORITY_X*)0xE000E404, (SET_PRIORITY_X*)0xE000E408, (SET_PRIORITY_X*)0xE000E40C, (SET_PRIORITY_X*)0xE000E410, 
(SET_PRIORITY_X*)0xE000E414, (SET_PRIORITY_X*)0xE000E418, (SET_PRIORITY_X*)0xE000E41C, (SET_PRIORITY_X*)0xE000E420, (SET_PRIORITY_X*)0xE000E424, 
(SET_PRIORITY_X*)0xE000E428, (SET_PRIORITY_X*)0xE000E42C, (SET_PRIORITY_X*)0xE000E430, (SET_PRIORITY_X*)0xE000E434, (SET_PRIORITY_X*)0xE000E438,
(SET_PRIORITY_X*)0xE000E43C, (SET_PRIORITY_X*)0xE000E440, (SET_PRIORITY_X*)0xE000E444, (SET_PRIORITY_X*)0xE000E448, (SET_PRIORITY_X*)0xE000E44C, 
(SET_PRIORITY_X*)0xE000E450, (SET_PRIORITY_X*)0xE000E454, (SET_PRIORITY_X*)0xE000E458, (SET_PRIORITY_X*)0xE000E45C, (SET_PRIORITY_X*)0xE000E460, 
(SET_PRIORITY_X*)0xE000E464, (SET_PRIORITY_X*)0xE000E468, (SET_PRIORITY_X*)0xE000E46C, (SET_PRIORITY_X*)0xE000E470, (SET_PRIORITY_X*)0xE000E474,
(SET_PRIORITY_X*)0xE000E478, (SET_PRIORITY_X*)0xE000E47C, (SET_PRIORITY_X*)0xE000E480, (SET_PRIORITY_X*)0xE000E484, (SET_PRIORITY_X*)0xE000E488, 
(SET_PRIORITY_X*)0xE000E48C, (SET_PRIORITY_X*)0xE000E490, (SET_PRIORITY_X*)0xE000E494, (SET_PRIORITY_X*)0xE000E498, (SET_PRIORITY_X*)0xE000E49C, 
(SET_PRIORITY_X*)0xE000E4A0, (SET_PRIORITY_X*)0xE000E4A4, (SET_PRIORITY_X*)0xE000E4A8, (SET_PRIORITY_X*)0xE000E4AC, (SET_PRIORITY_X*)0xE000E4B0,
(SET_PRIORITY_X*)0xE000E4B4, (SET_PRIORITY_X*)0xE000E4B8, (SET_PRIORITY_X*)0xE000E4BC, (SET_PRIORITY_X*)0xE000E4C0, (SET_PRIORITY_X*)0xE000E4C4, 
(SET_PRIORITY_X*)0xE000E4C8, (SET_PRIORITY_X*)0xE000E4CC, (SET_PRIORITY_X*)0xE000E4D0, (SET_PRIORITY_X*)0xE000E4D4, (SET_PRIORITY_X*)0xE000E4D8, 
(SET_PRIORITY_X*)0xE000E4DC, (SET_PRIORITY_X*)0xE000E4E0, (SET_PRIORITY_X*)0xE000E4E4, (SET_PRIORITY_X*)0xE000E4E8, (SET_PRIORITY_X*)0xE000E4EC};

// Set-Software-Trigger Register
SET_AS_SOFTWARE *const SOFTWARE_SET = ADDR_STIR;
CONFIG_CTRL *const CONFIG_CONTROL = ADDR_SCR;

/**
 * @brief The AUTOMATIC Process: 
 * After The Interrupt is Initialized by the user in the NVIC (i.e. NVICInterruptInit()),
 * When Trigger occurs on given EXTI line and NVIC sees the interrupt is NOT active (from the CHECK_ACTIVE register)
 * The NVIC will set the Interrupt as Pending
 * The Interrupt stays Pending until the processor enters the desired ISR, & Interrupt's state is moved from Pending to Active.
 * 
 * Write the code for the given Interrupt Handler (e.g. EXTI15_10_IRQHandler, USART2_IRQHandler)
 * 
 * Important Document for NVIC Info: See 1-Datasheets/STM32/'STM32 M4 Programming Manual.pdf'
 */
//------------------------------------------------------------------------------------------


uint8_t NVIC_InterruptIsActive(uint8_t vecTablePos) {
    return ReadInterrupt(vecTablePos, CHECK_ACTIVE);
}

void NVICInterruptInit(uint8_t vecTablePos, uint8_t priority, E_InterruptType type) {

    if (type == SOFTWARE) {
        CONFIG_CONTROL->enableSoftwareAccessToSTIR = 1;
        SOFTWARE_SET->vecTablePos = vecTablePos;
    }
    
    EditInterrupt(vecTablePos, ENABLE); // Enable Interrupt
    SetInterruptPriority(vecTablePos, priority); 
    TurnOnInterrupts();
    EditInterrupt(vecTablePos, CLEAR_PENDING); // To ignore any previous events 
}

uint8_t NVIC_InterruptIsPending(uint8_t vecTablePos) {
    return ReadInterrupt(vecTablePos, CLEAR_PENDING);
}


// Helpers---------------------------------------------------------------------------------------
/**
 * @brief Handles writing functions for the 5 main Interrupt Registers
 * 
 * @param generic One of the register address
 * @param offset 
 * @param vecTablePos The interrupt's position on the vector table
 * @param bit bit to be written to the given register
 * @return uint8_t 
 */
static void AlterInterruptSettings(NVIC_GENERIC *generic, uint8_t offset, uint8_t vecTablePos, E_Bit bit) {


    switch (vecTablePos - offset) {
        case 0:
            generic->interrupt0 = bit;
            break;
        case 1:
            generic->interrupt1 = bit;
            break;
        case 2:
            generic->interrupt2 = bit;
            break;
        case 3:
            generic->interrupt3 = bit;
            break;
        case 4:
            generic->interrupt4 = bit;
            break;
        case 5:
            generic->interrupt5 = bit;
            break;
        case 6:
            generic->interrupt6 = bit;
            break;
        case 7:
            generic->interrupt7 = bit;
            break;
        case 8:
            generic->interrupt8 = bit;
            break;
        case 9:
            generic->interrupt9 = bit;
            break;
        case 10:
            generic->interrupt10 = bit;
            break;
        case 11:
            generic->interrupt11 = bit;
            break;
        case 12:
            generic->interrupt12 = bit;
            break;
        case 13:
            generic->interrupt13 = bit;
            break;
        case 14:
            generic->interrupt14 = bit;
            break;
        case 15:
            generic->interrupt15 = bit;
            break;
        case 16:
            generic->interrupt16 = bit;
            break;
        case 17:
            generic->interrupt17 = bit;
            break;
        case 18:
            generic->interrupt18 = bit;
            break;
        case 19:
            generic->interrupt19 = bit;
            break;
        case 20:
            generic->interrupt20 = bit;
            break;
        case 21:
            generic->interrupt21 = bit;
            break;
        case 22:
            generic->interrupt22 = bit;
            break;
        case 23:
            generic->interrupt23 = bit;
            break;
        case 24:
            generic->interrupt24 = bit;
            break;
        case 25:
            generic->interrupt25 = bit;
            break;
        case 26:
            generic->interrupt26 = bit;
            break;
        case 27:
            generic->interrupt27 = bit;
            break;
        case 28:
            generic->interrupt28 = bit;
            break;
        case 29:
            generic->interrupt29 = bit;
            break;
        case 30:
            generic->interrupt30 = bit;
            break;
        case 31:
            generic->interrupt31 = bit; 
            break; 
        default:
            break;
    }
}


/**
 * @brief Handles reading functions for the 5 main Interrupt Registers
 * 
 * @param generic One of the register address
 * @param offset 
 * @param vecTablePos The interrupt's position on the vector table
 * @param bit bit to be written to the given register
 * @return uint8_t 
 */
static uint8_t ReadInterruptSettings(NVIC_GENERIC *generic, uint8_t offset, uint8_t vecTablePos, E_Bit bit) {


    switch (vecTablePos - offset) {
        case 0:
            return generic->interrupt0;
        case 1:
            return generic->interrupt1;
        case 2:
            return generic->interrupt2;
        case 3:
            return generic->interrupt3;
        case 4:
            return generic->interrupt4;
        case 5:
            return generic->interrupt5;
        case 6:
            return generic->interrupt6;
        case 7:
            return generic->interrupt7;
        case 8:
            return generic->interrupt8;
        case 9:
            return generic->interrupt9;
        case 10:
            return generic->interrupt10;
        case 11:
            return generic->interrupt11;
        case 12:
            return generic->interrupt12;
        case 13:
            return generic->interrupt13;
        case 14:
            return generic->interrupt14;
        case 15:
            return generic->interrupt15;
        case 16:
            return generic->interrupt16;
        case 17:
            return generic->interrupt17;
        case 18:
            return generic->interrupt18;
        case 19:
            return generic->interrupt19;
        case 20:
            return generic->interrupt20;
        case 21:
            return generic->interrupt21;
        case 22:
            return generic->interrupt22;
        case 23:
            return generic->interrupt23;
        case 24:
            return generic->interrupt24;
        case 25:
            return generic->interrupt25;
        case 26:
            return generic->interrupt26;
        case 27:
            return generic->interrupt27;
        case 28:
            return generic->interrupt28;
        case 29:
            return generic->interrupt29;
        case 30:
            return generic->interrupt30;
        case 31:
            return generic->interrupt31;   
        default:
            break;
    }
}


static void EditInterrupt(uint8_t vecTablePos, E_NVICRegs regType) {
    
    // Default: ENABLE (ISER) Register
    int row = 0; 

    // DISABLE (ICER) Register
    if (regType == DISABLE) {
        row = 1;
    }

    // SET PENDING (ISPR) Register
    else if (regType == SET_PENDING) {
        row = 2;
    }

    // CLEAR PENDING (ICPR) Register
    else if (regType == CLEAR_PENDING) {
        row = 3;
    }

    // CHECK ACTIVE (IABR) Register
    else if (regType == CHECK_ACTIVE) {
        return; // This function is for writing not reading
    }

    /** NOTE: PLUS_x: Means -> Vec Table Position = (Bit Index in the Register + x) 
     * Bit Index in the Register = (Vec Table Position - x) */ 

    if (vecTablePos >= 0 && vecTablePos < 32) {
        NVIC_GENERIC *const PLUS_0 = addresses[row][0]; 
        AlterInterruptSettings(PLUS_0, 0, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 32 && vecTablePos < 64) {
        NVIC_GENERIC *const PLUS_32 = addresses[row][1];
        AlterInterruptSettings(PLUS_32, 32, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 64 && vecTablePos < 96) {
        NVIC_GENERIC *const PLUS_64 = addresses[row][2];
        AlterInterruptSettings(PLUS_64, 64, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 96 && vecTablePos < 128) {
        NVIC_GENERIC *const PLUS_96 = addresses[row][3];
        AlterInterruptSettings(PLUS_96, 96, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 128 && vecTablePos < 160) {
        NVIC_GENERIC *const PLUS_128 = addresses[row][4];
        AlterInterruptSettings(PLUS_128, 128, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 160 && vecTablePos < 192) {
        NVIC_GENERIC *const PLUS_160 = addresses[row][5];
        AlterInterruptSettings(PLUS_160, 160, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 192 && vecTablePos < 224) {
        NVIC_GENERIC *const PLUS_192 = addresses[row][6];
        AlterInterruptSettings(PLUS_192, 192, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 224 && vecTablePos < 256) {
        NVIC_GENERIC *const PLUS_224 = addresses[row][7];
        AlterInterruptSettings(PLUS_224, 224, vecTablePos, HIGH_BIT);
    }
}


static uint8_t ReadInterrupt(uint8_t vecTablePos, E_NVICRegs regType) {
    
    // Default: ENABLE (ISER) Register
    int row = 0; 

    // DISABLE (ICER) Register
    if (regType == DISABLE) {
        row = 1;
    }

    // SET PENDING (ISPR) Register
    else if (regType == SET_PENDING) {
        row = 2;
    }

    // CLEAR PENDING (ICPR) Register
    else if (regType == CLEAR_PENDING) {
        row = 3;
    }

    // CHECK ACTIVE (IABR) Register
    else if (regType == CHECK_ACTIVE) {
        row = 4;
    }

    /** NOTE: PLUS_x: Means -> Vec Table Position = (Bit Index in the Register + x) 
     * Bit Index in the Register = (Vec Table Position - x) */ 

    if (vecTablePos >= 0 && vecTablePos < 32) {
        NVIC_GENERIC *const PLUS_0 = addresses[row][0]; 
        return ReadInterruptSettings(PLUS_0, 0, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 32 && vecTablePos < 64) {
        NVIC_GENERIC *const PLUS_32 = addresses[row][1];
        return ReadInterruptSettings(PLUS_32, 32, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 64 && vecTablePos < 96) {
        NVIC_GENERIC *const PLUS_64 = addresses[row][2];
        return ReadInterruptSettings(PLUS_64, 64, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 96 && vecTablePos < 128) {
        NVIC_GENERIC *const PLUS_96 = addresses[row][3];
        return ReadInterruptSettings(PLUS_96, 96, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 128 && vecTablePos < 160) {
        NVIC_GENERIC *const PLUS_128 = addresses[row][4];
        return ReadInterruptSettings(PLUS_128, 128, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 160 && vecTablePos < 192) {
        NVIC_GENERIC *const PLUS_160 = addresses[row][5];
        return ReadInterruptSettings(PLUS_160, 160, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 192 && vecTablePos < 224) {
        NVIC_GENERIC *const PLUS_192 = addresses[row][6];
        return ReadInterruptSettings(PLUS_192, 192, vecTablePos, HIGH_BIT);
    }
        
    else if (vecTablePos >= 224 && vecTablePos < 256) {
        NVIC_GENERIC *const PLUS_224 = addresses[row][7];
        return ReadInterruptSettings(PLUS_224, 224, vecTablePos, HIGH_BIT);
    }
        
    return -1;
}


/**
 * @brief IMPORTANT: Even though NVIC_IPRx is an 8-bit field per interrupt, for Cortex M4 the hardware only SET and READ the upper 4 bits.
 *                  Most Cortex-M4 MCUs have 4 priority bits, meaning priority values range from 0 to 15 (not 0 to 255).
 *                  NVIC priority values in the datasheet may use the full 8-bit range (0-255) 
 *                  for software configuration purposes, but the hardware only implements 4 bits.
 * 
 * @param vecTablePos 
 * @param priority 
 */
static void SetInterruptPriority(uint8_t vecTablePos, uint8_t priority) {
    
    /** Obtain corect Priority Register 
        59 Priority Registers
        4 Interrupts per Priority Register
    **/
    SET_PRIORITY_X * priorityReg = priority_addresses[(vecTablePos / 4)];

    switch((vecTablePos % 4)) {
        case 0:
            priorityReg->interrupt0PriorityByte = (priority << 4);
            break;
        case 1:
            priorityReg->interrupt1PriorityByte = (priority << 4);
            break;
        case 2:
            break;
            priorityReg->interrupt2PriorityByte = (priority << 4);
        case 3:
            priorityReg->interrupt3PriorityByte = (priority << 4);
            break;
    }
}




