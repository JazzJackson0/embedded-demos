#include "ExternalInterrupt.h"

typedef enum _ReadWrite {
	READ = 0, WRITE = 1
}E_ReadWrite;

//Static Prototypes---------------------------------------------
static void EXTI_PinInit(char port, uint8_t extiNumber);
static void setFallingTrigger(uint8_t lineNumber);
static void setRisingTrigger(uint8_t lineNumber);
static void unmaskInterruptLine(uint8_t lineNumber);
static void unmaskEventLine(uint8_t lineNumber);
static void enableSoftwareLine(uint8_t lineNumber);
static uint8_t triggerState(uint8_t lineNumber, E_ReadWrite rw);
static void Clock_Start(void);
static void Pin_SysCfg(EXTI_CFG *cfg, uint8_t extiNumber, char port);

//Global Variables------------------------------------------------
EXTIx *const EXTI = ADDR_EXTI;
EXTI_CFG *const CFG_EXTICR1 = ADDRS_EXTICR1;
EXTI_CFG *const CFG_EXTICR2 = ADDRS_EXTICR2;
EXTI_CFG *const CFG_EXTICR3 = ADDRS_EXTICR3;
EXTI_CFG *const CFG_EXTICR4 = ADDRS_EXTICR4;
SYSCFG_CLOCK *const SYSCFG_CLK = ADDR_SYSCFG_CLOCK;


void EXTIInit(uint8_t extiNum, char port, E_Type interruptType, E_TriggerEdge triggerSelect, uint8_t priority) {
    
    uint8_t vecTablePos[] = {6, 7, 8, 9, 10, 23, 23, 23, 23, 23, 40, 40, 40, 40, 40, 40}; // EXTI0 - EXTI15
    Clock_Start();
    E_ReadWrite write = WRITE;

    // Link GPIO pin to desired EXTI
    if (extiNum >= 0 && extiNum < 4) {
        EXTI_CFG *cfg = CFG_EXTICR1;
        Pin_SysCfg(cfg, extiNum, port);
    }
    else if (extiNum >= 4 && extiNum < 8) {
        EXTI_CFG *cfg = CFG_EXTICR2;
        Pin_SysCfg(cfg, extiNum, port);
        
    }
    else if (extiNum >= 8 && extiNum < 12) {
        EXTI_CFG *cfg = CFG_EXTICR3;
        Pin_SysCfg(cfg, extiNum, port);
    }
    else if (extiNum >= 12 && extiNum < 16) {
        EXTI_CFG *cfg = CFG_EXTICR4;
        Pin_SysCfg(cfg, extiNum, port);
    }

    // Software Interrupt
    if (interruptType == SOFTWARE_INTERRUPT) {
        unmaskInterruptLine(extiNum);
        unmaskEventLine(extiNum);
        enableSoftwareLine(extiNum);
    }

    // Hardware Interrupt
    else if (interruptType == HARDWARE_INTERRUPT) {

        //Trigger Selection
        if (triggerSelect == RISING) {
            setRisingTrigger(extiNum);
        }
        else if (triggerSelect == FALLING) {
            setFallingTrigger(extiNum);
        }
        else {
            setRisingTrigger(extiNum);
            setFallingTrigger(extiNum);
        }

        unmaskInterruptLine(extiNum);

        // Enable Interrupt & Set Priority
        NVICInterruptInit(vecTablePos[extiNum], priority, HARDWARE);
    }

    // Hardware Event
    else if (interruptType == HARDWARE_EVENT) {     

        //Trigger Selection
        if (triggerSelect == RISING) {
            setRisingTrigger(extiNum);
        }
        else if (triggerSelect == FALLING) {
            setFallingTrigger(extiNum);
        }

        else {
            setRisingTrigger(extiNum);
            setFallingTrigger(extiNum);
        }

        unmaskEventLine(extiNum);
    }

    // Configure desired GPIO pin as Input
    EXTI_PinInit(port, extiNum);
    // Clear Pending Flag to ignore any previous events
    triggerState(extiNum, write);
}

void ClearIRQ(uint8_t lineNumber) {
    E_ReadWrite write = WRITE;
    triggerState(lineNumber, write);
}

// Helpers-------------------------------------------------------------------------------------------------------
static void EXTI_PinInit(char port, uint8_t extiNumber) {

    if (extiNumber >= 0 && extiNumber < 16) {

        switch(port) {
            case 'A':
                Pin_Init('A', extiNumber, IN);
                break;
            case 'B':
                Pin_Init('B', extiNumber, IN);
                break;
            case 'C':
                Pin_Init('C', extiNumber, IN);
                break;
            case 'D':
                Pin_Init('D', extiNumber, IN);
                break;
            case 'E':
                Pin_Init('E', extiNumber, IN);
                break;
            case 'F':
                Pin_Init('F', extiNumber, IN);
                break;
            case 'G':
                Pin_Init('G', extiNumber, IN);
                break;
            case 'H':
                Pin_Init('H', extiNumber, IN);
                break;
            case 'I':
                Pin_Init('I', extiNumber, IN);
                break;
            default:
                break;
        }
    }
}


static void setFallingTrigger(uint8_t lineNumber) {

    switch (lineNumber) {
        case 0:
            EXTI->FallingTrigSelectReg.enable_EXTI0InputLine = 1;
            break;
        case 1:
            EXTI->FallingTrigSelectReg.enable_EXTI1InputLine = 1;
            break;
        case 2:
            EXTI->FallingTrigSelectReg.enable_EXTI2InputLine = 1;
            break;
        case 3:
            EXTI->FallingTrigSelectReg.enable_EXTI3InputLine = 1;
            break;
        case 4:
            EXTI->FallingTrigSelectReg.enable_EXTI4InputLine = 1;
            break;
        case 5:
            EXTI->FallingTrigSelectReg.enable_EXTI5InputLine = 1;
            break;
        case 6:
            EXTI->FallingTrigSelectReg.enable_EXTI6InputLine = 1;
            break;
        case 7:
            EXTI->FallingTrigSelectReg.enable_EXTI7InputLine = 1;
            break;
        case 8:
            EXTI->FallingTrigSelectReg.enable_EXTI8InputLine = 1;
            break;
        case 9:
            EXTI->FallingTrigSelectReg.enable_EXTI9InputLine = 1;
            break;
        case 10:
            EXTI->FallingTrigSelectReg.enable_EXTI10InputLine = 1;
            break;
        case 11:
            EXTI->FallingTrigSelectReg.enable_EXTI11InputLine = 1;
            break;
        case 12:
            EXTI->FallingTrigSelectReg.enable_EXTI12InputLine = 1;
            break;
        case 13:
            EXTI->FallingTrigSelectReg.enable_EXTI13InputLine = 1;
            break;
        case 14:
            EXTI->FallingTrigSelectReg.enable_EXTI14InputLine = 1;
            break;
        case 15:
            EXTI->FallingTrigSelectReg.enable_EXTI15InputLine = 1;
            break;
        case 16:
            EXTI->FallingTrigSelectReg.enable_PVDOutputInputLine = 1;
            break;
        case 17:
            EXTI->FallingTrigSelectReg.enable_RTCAlarmInputLine = 1;
            break;
        case 18:
            EXTI->FallingTrigSelectReg.enable_USB_OTG_FSWakeupInputLine = 1;
            break;
        case 19:
            EXTI->FallingTrigSelectReg.enable_EthernetWakeupInputLine = 1;
            break;
        case 20:
            EXTI->FallingTrigSelectReg.enable_USB_OTG_HSWakeupInputLine = 1;
            break;
        case 21:
            EXTI->FallingTrigSelectReg.enable_RTCTamper_TimestampInputLine = 1;
            break;
        case 22:
            EXTI->FallingTrigSelectReg.enable_RTCWakeupInputLine = 1;
            break;
    }
}


static void setRisingTrigger(uint8_t lineNumber) {

    switch (lineNumber) {
        case 0:
            EXTI->RisingTrigSelectReg.enable_EXTI0InputLine = 1;
            break;
        case 1:
            EXTI->RisingTrigSelectReg.enable_EXTI1InputLine = 1;
            break;
        case 2:
            EXTI->RisingTrigSelectReg.enable_EXTI2InputLine = 1;
            break;
        case 3:
            EXTI->RisingTrigSelectReg.enable_EXTI3InputLine = 1;
            break;
        case 4:
            EXTI->RisingTrigSelectReg.enable_EXTI4InputLine = 1;
            break;
        case 5:
            EXTI->RisingTrigSelectReg.enable_EXTI5InputLine = 1;
            break;
        case 6:
            EXTI->RisingTrigSelectReg.enable_EXTI6InputLine = 1;
            break;
        case 7:
            EXTI->RisingTrigSelectReg.enable_EXTI7InputLine = 1;
            break;
        case 8:
            EXTI->RisingTrigSelectReg.enable_EXTI8InputLine = 1;
            break;
        case 9:
            EXTI->RisingTrigSelectReg.enable_EXTI9InputLine = 1;
            break;
        case 10:
            EXTI->RisingTrigSelectReg.enable_EXTI10InputLine = 1;
            break;
        case 11:
            EXTI->RisingTrigSelectReg.enable_EXTI11InputLine = 1;
            break;
        case 12:
            EXTI->RisingTrigSelectReg.enable_EXTI12InputLine = 1;
            break;
        case 13:
            EXTI->RisingTrigSelectReg.enable_EXTI13InputLine = 1;
            break;
        case 14:
            EXTI->RisingTrigSelectReg.enable_EXTI14InputLine = 1;
            break;
        case 15:
            EXTI->RisingTrigSelectReg.enable_EXTI15InputLine = 1;
            break;
        case 16:
            EXTI->RisingTrigSelectReg.enable_PVDOutputInputLine = 1;
            break;
        case 17:
            EXTI->RisingTrigSelectReg.enable_RTCAlarmInputLine = 1;
            break;
        case 18:
            EXTI->RisingTrigSelectReg.enable_USB_OTG_FSWakeupInputLine = 1;
            break;
        case 19:
            EXTI->RisingTrigSelectReg.enable_EthernetWakeupInputLine = 1;
            break;
        case 20:
            EXTI->RisingTrigSelectReg.enable_USB_OTG_HSWakeupInputLine = 1;
            break;
        case 21:
            EXTI->RisingTrigSelectReg.enable_RTCTamper_TimestampInputLine = 1;
            break;
        case 22:
            EXTI->RisingTrigSelectReg.enable_RTCWakeupInputLine = 1;
            break;
    }
}


static void unmaskInterruptLine(uint8_t lineNumber) {

    switch (lineNumber) {
        case 0:
            EXTI->MaskReg.unmask_EXTI0InterruptLine = 1;
            break;
        case 1:
            EXTI->MaskReg.unmask_EXTI1InterruptLine = 1;
            break;
        case 2:
            EXTI->MaskReg.unmask_EXTI2InterruptLine = 1;
            break;
        case 3:
            EXTI->MaskReg.unmask_EXTI3InterruptLine = 1;
            break;
        case 4:
            EXTI->MaskReg.unmask_EXTI4InterruptLine = 1;
            break;
        case 5:
            EXTI->MaskReg.unmask_EXTI5InterruptLine = 1;
            break;
        case 6:
            EXTI->MaskReg.unmask_EXTI6InterruptLine = 1;
            break;
        case 7:
            EXTI->MaskReg.unmask_EXTI7InterruptLine = 1;
            break;
        case 8:
            EXTI->MaskReg.unmask_EXTI8InterruptLine = 1;
            break;
        case 9:
            EXTI->MaskReg.unmask_EXTI9InterruptLine = 1;
            break;
        case 10:
            EXTI->MaskReg.unmask_EXTI10InterruptLine = 1;
            break;
        case 11:
            EXTI->MaskReg.unmask_EXTI11InterruptLine = 1;
            break;
        case 12:
            EXTI->MaskReg.unmask_EXTI12InterruptLine = 1;
            break;
        case 13:
            EXTI->MaskReg.unmask_EXTI13InterruptLine = 1;
            break;
        case 14:
            EXTI->MaskReg.unmask_EXTI14InterruptLine = 1;
            break;
        case 15:
            EXTI->MaskReg.unmask_EXTI15InterruptLine = 1;
            break;
        case 16:
            EXTI->MaskReg.unmask_PVDOutputInterruptLine = 1;
            break;
        case 17:
            EXTI->MaskReg.unmask_RTCAlarmInterruptLine = 1;
            break;
        case 18:
            EXTI->MaskReg.unmask_USB_OTG_FSWakeupInterruptLine = 1;
            break;
        case 19:
            EXTI->MaskReg.unmask_EthernetWakeupInterruptLine = 1;
            break;
        case 20:
            EXTI->MaskReg.unmask_USB_OTG_HSWakeupInterruptLine = 1;
            break;
        case 21:
            EXTI->MaskReg.unmask_RTCTamper_TimestampInterruptLine = 1;
            break;
        case 22:
            EXTI->MaskReg.unmask_RTCWakeupInterruptLine = 1;
            break;
    }
}


static void unmaskEventLine(uint8_t lineNumber) {

    switch (lineNumber) {
        case 0:
            EXTI->EventMaskReg.unmask_EXTI0EventLine = 1;
            break;
        case 1:
            EXTI->EventMaskReg.unmask_EXTI1EventLine = 1;
            break;
        case 2:
            EXTI->EventMaskReg.unmask_EXTI2EventLine = 1;
            break;
        case 3:
            EXTI->EventMaskReg.unmask_EXTI3EventLine = 1;
            break;
        case 4:
            EXTI->EventMaskReg.unmask_EXTI4EventLine = 1;
            break;
        case 5:
            EXTI->EventMaskReg.unmask_EXTI5EventLine = 1;
            break;
        case 6:
            EXTI->EventMaskReg.unmask_EXTI6EventLine = 1;
            break;
        case 7:
            EXTI->EventMaskReg.unmask_EXTI7EventLine = 1;
            break;
        case 8:
            EXTI->EventMaskReg.unmask_EXTI8EventLine = 1;
            break;
        case 9:
            EXTI->EventMaskReg.unmask_EXTI9EventLine = 1;
            break;
        case 10:
            EXTI->EventMaskReg.unmask_EXTI10EventLine = 1;
            break;
        case 11:
            EXTI->EventMaskReg.unmask_EXTI11EventLine = 1;
            break;
        case 12:
            EXTI->EventMaskReg.unmask_EXTI12EventLine = 1;
            break;
        case 13:
            EXTI->EventMaskReg.unmask_EXTI13EventLine = 1;
            break;
        case 14:
            EXTI->EventMaskReg.unmask_EXTI14EventLine = 1;
            break;
        case 15:
            EXTI->EventMaskReg.unmask_EXTI15EventLine = 1;
            break;
        case 16:
            EXTI->EventMaskReg.unmask_PVDOutputEventLine = 1;
            break;
        case 17:
            EXTI->EventMaskReg.unmask_RTCAlarmEventLine = 1;
            break;
        case 18:
            EXTI->EventMaskReg.unmask_USB_OTG_FSWakeupEventLine = 1;
            break;
        case 19:
            EXTI->EventMaskReg.unmask_EthernetWakeupEventLine = 1;
            break;
        case 20:
            EXTI->EventMaskReg.unmask_USB_OTG_HSWakeupEventLine = 1;
            break;
        case 21:
            EXTI->EventMaskReg.unmask_RTCTamper_TimestampEventLine = 1;
            break;
        case 22:
            EXTI->EventMaskReg.unmask_RTCWakeupEventLine = 1;
            break;
    }
}


static void enableSoftwareLine(uint8_t lineNumber) {

    switch (lineNumber) {
        case 0:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine0 = 1;
            break;
        case 1:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine1 = 1;
            break;
        case 2:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine2 = 1;
            break;
        case 3:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine3 = 1;
            break;
        case 4:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine4 = 1;
            break;
        case 5:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine5 = 1;
            break;
        case 6:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine6 = 1;
            break;
        case 7:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine7 = 1;
            break;
        case 8:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine8 = 1;
            break;
        case 9:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine9 = 1;
            break;
        case 10:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine10 = 1;
            break;
        case 11:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine11 = 1;
            break;
        case 12:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine12 = 1;
            break;
        case 13:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine13 = 1;
            break;
        case 14:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine14 = 1;
            break;
        case 15:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine15 = 1;
            break;
        case 16:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine16 = 1;
            break;
        case 17:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine17 = 1;
            break;
        case 18:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine18 = 1;
            break;
        case 19:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine10 = 1;
            break;
        case 20:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine20 = 1;
            break;
        case 21:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine21 = 1;
            break;
        case 22:
            EXTI->SoftwareInterruptEventReg.enable_SoftwareInterruptLine22 = 1;
            break;
    }
}

/**
 * @brief Interrupt pending register bit set to 1 by hardware if interrupt/event occurred (bit is readable)
 * Clear bit by writing 1 (writing 0 has no effect)
 * Interrupt handler must write 1 to this bit to clear the pending state
 * NOTE: Writing a 1 to one of these bits will clear the pending state of the interrupt (to cancel the IRQn request)
 * 
 * @param lineNumber The line to read or write to
 * @param rw Indicates whether you want to read the line or write to it.
 */
static uint8_t triggerState(uint8_t lineNumber, E_ReadWrite rw) {

    switch (lineNumber) {
        case 0:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI0;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI0 = 1;
        case 1:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI1;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI1 = 1;
            break;
        case 2:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI2;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI2 = 1;
            break;
        case 3:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI3;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI3 = 1;
            break;
        case 4:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI4;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI4 = 1;
            break;
        case 5:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI5;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI5 = 1;
            break;
        case 6:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI6;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI6 = 1;
            break;
        case 7:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI7;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI7 = 1;
            break;
        case 8:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI8;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI8 = 1;
            break;
        case 9:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI9;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI9 = 1;
            break;
        case 10:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI10;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI10 = 1;
            break;
        case 11:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI11;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI11 = 1;
            break;
        case 12:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI12;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI12 = 1;
            break;
        case 13:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI13;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI13 = 1;
            break;
        case 14:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI14;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI14 = 1;
            break;
        case 15:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEXTI15;
            else 
                return EXTI->PendingReg.triggerOccurredEXTI15 = 1;
            break;
        case 16:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredPVDOutput;
            else 
                return EXTI->PendingReg.triggerOccurredPVDOutput = 1;
            break;
        case 17:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredRTCAlarm;
            else 
                return EXTI->PendingReg.triggerOccurredRTCAlarm = 1;
            break;
        case 18:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredUSB_OTG_FSWakeup;
            else 
                return EXTI->PendingReg.triggerOccurredUSB_OTG_FSWakeup = 1;
            break;
        case 19:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredEthernetWakeup;
            else 
                return EXTI->PendingReg.triggerOccurredEthernetWakeup = 1;
            break;
        case 20:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredUSB_OTG_HSWakeup;
            else 
                return EXTI->PendingReg.triggerOccurredUSB_OTG_HSWakeup = 1;
            break;
        case 21:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredRTCTamper_Timestamp;
            else 
                return EXTI->PendingReg.triggerOccurredRTCTamper_Timestamp = 1;
            break;
        case 22:
            if (rw == READ)
                return EXTI->PendingReg.triggerOccurredRTCWakeup;
            else 
                return EXTI->PendingReg.triggerOccurredRTCWakeup = 1;
            break;
    }
}


static void Clock_Start(void) {

    SYSCFG_CLK->sys_cfg_clk = 1;
}



static void Pin_SysCfg(EXTI_CFG *cfg, uint8_t extiNumber, char port) { 
    
    // ascii char: ['A' - 'I'] --> asci decimal: ['65' - '73']
    switch ((extiNumber % 4)) {
        case 0:
            cfg->extiPortAndPin_0 = 0;
            cfg->extiPortAndPin_0 = (port % 'A'); // port % A (i.e. port % 65) = the correct byte value for the port (0 -> A, ... 8 -> I)
            break;
        case 1:
            cfg->extiPortAndPin_1 = 0;
            cfg->extiPortAndPin_1 = (port % 'A');
            break;
        case 2:
            cfg->extiPortAndPin_2 = 0;
            cfg->extiPortAndPin_2 = (port % 'A');
            break;
        case 3:
            cfg->extiPortAndPin_3 = 0;
            cfg->extiPortAndPin_3 = (port % 'A');
            break;
        default:
            break;
    }
}




