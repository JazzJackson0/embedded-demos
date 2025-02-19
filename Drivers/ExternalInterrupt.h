//STM32F407 Driver
#ifndef EXT_INTERRUPTS_H_
#define EXT_INTERRUPTS_H_
#include <stdint.h>
#include "NVIC.h"
#include "CPU.h"
#include "GPIO.h"

// Do Interrupts Even Need a Clock Source? There is Nothing in APB2
#define CLOCK 0x40023800
#define APB2 0x44
#define ADDR_SYSCFG_CLOCK ( (SYSCFG_CLOCK*) ((CLOCK) + APB2) )


// INTERRUPTS
typedef struct _exti EXTIx;
#define EXTI_BASE 0x40013C00
#define ADDR_EXTI ( (EXTIx*) (EXTI_BASE) )

typedef struct exti_cfg EXTI_CFG;
#define SYSCFG_BASE 0x40013800
#define EXTICR1 0x08
#define EXTICR2 0x0C
#define EXTICR3 0x10
#define EXTICR4 0x14
#define ADDRS_EXTICR1 ( (EXTI_CFG*) ((SYSCFG_BASE) + EXTICR1))
#define ADDRS_EXTICR2 ( (EXTI_CFG*) ((SYSCFG_BASE) + EXTICR2))
#define ADDRS_EXTICR3 ( (EXTI_CFG*) ((SYSCFG_BASE) + EXTICR3))
#define ADDRS_EXTICR4 ( (EXTI_CFG*) ((SYSCFG_BASE) + EXTICR4))

typedef enum _TriggerEdge E_TriggerEdge;
typedef enum _Type E_Type;

/*Interrupt Pins ---------------------------
		+ No Alternate Function Assignments Needed
			(Just use the Registers)
		------------------------------------*/


// DECLARATIONS
/**
 * @brief 
 * 
 * @param extiNum 
 * @param port 
 * @param interruptType 
 * @param triggerSelect 
 * @param priority [0 - 15] for Hardware Interrupts on M4 architecture
 */
void EXTIInit(uint8_t extiNum, char port, E_Type interruptType, E_TriggerEdge triggerSelect, uint8_t priority);

/**
 * @brief 
 * 
 * @param lineNumber 
 */
void ClearIRQ(uint8_t lineNumber);



//Enums----------------------------------------------------------------------
enum _TriggerEdge {
	RISING = 0, FALLING = 1, RISING_FALLING = 2
};


enum _Type {
	HARDWARE_INTERRUPT = 0, HARDWARE_EVENT = 1, SOFTWARE_INTERRUPT = 2
};


//Registers----------------------------------------------------------------------

typedef struct {	
	const uint32_t reserved1:14;
	volatile uint32_t sys_cfg_clk:1;
	const uint32_t reserved2:17;
}SYSCFG_CLOCK;


// See Reference Manual pg 383 for clarity on field names
typedef struct {
	volatile uint32_t unmask_EXTI0InterruptLine:1;
	volatile uint32_t unmask_EXTI1InterruptLine:1;
	volatile uint32_t unmask_EXTI2InterruptLine:1;
	volatile uint32_t unmask_EXTI3InterruptLine:1;
	volatile uint32_t unmask_EXTI4InterruptLine:1;
	volatile uint32_t unmask_EXTI5InterruptLine:1;
	volatile uint32_t unmask_EXTI6InterruptLine:1;
	volatile uint32_t unmask_EXTI7InterruptLine:1;
	volatile uint32_t unmask_EXTI8InterruptLine:1;
	volatile uint32_t unmask_EXTI9InterruptLine:1;
	volatile uint32_t unmask_EXTI10InterruptLine:1;
	volatile uint32_t unmask_EXTI11InterruptLine:1;
	volatile uint32_t unmask_EXTI12InterruptLine:1;
	volatile uint32_t unmask_EXTI13InterruptLine:1;
	volatile uint32_t unmask_EXTI14InterruptLine:1;
	volatile uint32_t unmask_EXTI15InterruptLine:1;
	volatile uint32_t unmask_PVDOutputInterruptLine:1;
	volatile uint32_t unmask_RTCAlarmInterruptLine:1;
	volatile uint32_t unmask_USB_OTG_FSWakeupInterruptLine:1;
	volatile uint32_t unmask_EthernetWakeupInterruptLine:1;
	volatile uint32_t unmask_USB_OTG_HSWakeupInterruptLine:1;
	volatile uint32_t unmask_RTCTamper_TimestampInterruptLine:1;
	volatile uint32_t unmask_RTCWakeupInterruptLine:1;
	const uint32_t reserved:9;
}INTERRUPT_MASK;


typedef struct {
	volatile uint32_t unmask_EXTI0EventLine:1;
	volatile uint32_t unmask_EXTI1EventLine:1;
	volatile uint32_t unmask_EXTI2EventLine:1;
	volatile uint32_t unmask_EXTI3EventLine:1;
	volatile uint32_t unmask_EXTI4EventLine:1;
	volatile uint32_t unmask_EXTI5EventLine:1;
	volatile uint32_t unmask_EXTI6EventLine:1;
	volatile uint32_t unmask_EXTI7EventLine:1;
	volatile uint32_t unmask_EXTI8EventLine:1;
	volatile uint32_t unmask_EXTI9EventLine:1;
	volatile uint32_t unmask_EXTI10EventLine:1;
	volatile uint32_t unmask_EXTI11EventLine:1;
	volatile uint32_t unmask_EXTI12EventLine:1;
	volatile uint32_t unmask_EXTI13EventLine:1;
	volatile uint32_t unmask_EXTI14EventLine:1;
	volatile uint32_t unmask_EXTI15EventLine:1;
	volatile uint32_t unmask_PVDOutputEventLine:1;
	volatile uint32_t unmask_RTCAlarmEventLine:1;
	volatile uint32_t unmask_USB_OTG_FSWakeupEventLine:1;
	volatile uint32_t unmask_EthernetWakeupEventLine:1;
	volatile uint32_t unmask_USB_OTG_HSWakeupEventLine:1;
	volatile uint32_t unmask_RTCTamper_TimestampEventLine:1;
	volatile uint32_t unmask_RTCWakeupEventLine:1;
	const uint32_t reserved:9;
}INTERRUPT_EVENTMASK;


typedef struct {
	volatile uint32_t enable_EXTI0InputLine:1;
	volatile uint32_t enable_EXTI1InputLine:1;
	volatile uint32_t enable_EXTI2InputLine:1;
	volatile uint32_t enable_EXTI3InputLine:1;
	volatile uint32_t enable_EXTI4InputLine:1;
	volatile uint32_t enable_EXTI5InputLine:1;
	volatile uint32_t enable_EXTI6InputLine:1;
	volatile uint32_t enable_EXTI7InputLine:1;
	volatile uint32_t enable_EXTI8InputLine:1;
	volatile uint32_t enable_EXTI9InputLine:1;
	volatile uint32_t enable_EXTI10InputLine:1;
	volatile uint32_t enable_EXTI11InputLine:1;
	volatile uint32_t enable_EXTI12InputLine:1;
	volatile uint32_t enable_EXTI13InputLine:1;
	volatile uint32_t enable_EXTI14InputLine:1;
	volatile uint32_t enable_EXTI15InputLine:1;
	volatile uint32_t enable_PVDOutputInputLine:1;
	volatile uint32_t enable_RTCAlarmInputLine:1;
	volatile uint32_t enable_USB_OTG_FSWakeupInputLine:1;
	volatile uint32_t enable_EthernetWakeupInputLine:1;
	volatile uint32_t enable_USB_OTG_HSWakeupInputLine:1;
	volatile uint32_t enable_RTCTamper_TimestampInputLine:1;
	volatile uint32_t enable_RTCWakeupInputLine:1;
	const uint32_t reserved:9;
}INTERRUPT_TRIGGER_SELECTION; // Rising & Falling regs are different for STM32F446

/*
	[ALTERNATIVE] For STM32F446, Falling Trigger Selection Register has 2 reserved sections
typedef struct {
	volatile uint32_t enable_FallingTriggerInputLine0:1;
	volatile uint32_t enable_FallingTriggerInputLine1:1;
	volatile uint32_t enable_FallingTriggerInputLine2:1;
	volatile uint32_t enable_FallingTriggerInputLine3:1;
	volatile uint32_t enable_FallingTriggerInputLine4:1;
	volatile uint32_t enable_FallingTriggerInputLine5:1;
	volatile uint32_t enable_FallingTriggerInputLine6:1;
	volatile uint32_t enable_FallingTriggerInputLine7:1;
	volatile uint32_t enable_FallingTriggerInputLine8:1;
	volatile uint32_t enable_FallingTriggerInputLine9:1;
	volatile uint32_t enable_FallingTriggerInputLine10:1;
	volatile uint32_t enable_FallingTriggerInputLine11:1;
	volatile uint32_t enable_FallingTriggerInputLine12:1;
	volatile uint32_t enable_FallingTriggerInputLine13:1;
	volatile uint32_t enable_FallingTriggerInputLine14:1;
	volatile uint32_t enable_FallingTriggerInputLine15:1;
	volatile uint32_t enable_FallingTriggerInputLine16:1;
	volatile uint32_t enable_FallingTriggerInputLine17:1;
	volatile uint32_t enable_FallingTriggerInputLine18:1;
	const uint32_t reserved0:1;
	volatile uint32_t enable_FallingTriggerInputLine20:1;
	volatile uint32_t enable_FallingTriggerInputLine21:1;
	volatile uint32_t enable_FallingTriggerInputLine22:1;
	const uint32_t reserved1:9;
}INTERRUPT_FALLING_TRIGGER_SELECTION;
 */

typedef struct {
	volatile uint32_t enable_SoftwareInterruptLine0:1;
	volatile uint32_t enable_SoftwareInterruptLine1:1;
	volatile uint32_t enable_SoftwareInterruptLine2:1;
	volatile uint32_t enable_SoftwareInterruptLine3:1;
	volatile uint32_t enable_SoftwareInterruptLine4:1;
	volatile uint32_t enable_SoftwareInterruptLine5:1;
	volatile uint32_t enable_SoftwareInterruptLine6:1;
	volatile uint32_t enable_SoftwareInterruptLine7:1;
	volatile uint32_t enable_SoftwareInterruptLine8:1;
	volatile uint32_t enable_SoftwareInterruptLine9:1;
	volatile uint32_t enable_SoftwareInterruptLine10:1;
	volatile uint32_t enable_SoftwareInterruptLine11:1;
	volatile uint32_t enable_SoftwareInterruptLine12:1;
	volatile uint32_t enable_SoftwareInterruptLine13:1;
	volatile uint32_t enable_SoftwareInterruptLine14:1;
	volatile uint32_t enable_SoftwareInterruptLine15:1;
	volatile uint32_t enable_SoftwareInterruptLine16:1;
	volatile uint32_t enable_SoftwareInterruptLine17:1;
	volatile uint32_t enable_SoftwareInterruptLine18:1;
	volatile uint32_t enable_SoftwareInterruptLine19:1;
	volatile uint32_t enable_SoftwareInterruptLine20:1;
	volatile uint32_t enable_SoftwareInterruptLine21:1;
	volatile uint32_t enable_SoftwareInterruptLine22:1;
	const uint32_t reserved:9;
}SOFTWARE_INTERRUPT_EVENT;


typedef struct {
	volatile uint32_t triggerOccurredEXTI0:1;
	volatile uint32_t triggerOccurredEXTI1:1;
	volatile uint32_t triggerOccurredEXTI2:1;
	volatile uint32_t triggerOccurredEXTI3:1;
	volatile uint32_t triggerOccurredEXTI4:1;
	volatile uint32_t triggerOccurredEXTI5:1;
	volatile uint32_t triggerOccurredEXTI6:1;
	volatile uint32_t triggerOccurredEXTI7:1;
	volatile uint32_t triggerOccurredEXTI8:1;
	volatile uint32_t triggerOccurredEXTI9:1;
	volatile uint32_t triggerOccurredEXTI10:1;
	volatile uint32_t triggerOccurredEXTI11:1;
	volatile uint32_t triggerOccurredEXTI12:1;
	volatile uint32_t triggerOccurredEXTI13:1;
	volatile uint32_t triggerOccurredEXTI14:1;
	volatile uint32_t triggerOccurredEXTI15:1;
	volatile uint32_t triggerOccurredPVDOutput:1;
	volatile uint32_t triggerOccurredRTCAlarm:1;
	volatile uint32_t triggerOccurredUSB_OTG_FSWakeup:1;
	volatile uint32_t triggerOccurredEthernetWakeup:1;
	volatile uint32_t triggerOccurredUSB_OTG_HSWakeup:1;
	volatile uint32_t triggerOccurredRTCTamper_Timestamp:1;
	volatile uint32_t triggerOccurredRTCWakeup:1;
	const uint32_t reserved:9;
}PENDING;



// SYSCFG Registers----------------------------------------------------------------
struct exti_cfg {
	volatile uint32_t extiPortAndPin_0:4;
	volatile uint32_t extiPortAndPin_1:4;
	volatile uint32_t extiPortAndPin_2:4;
	volatile uint32_t extiPortAndPin_3:4;
	const uint32_t reserved:16;
};






struct _exti { // 0x40013C00
	INTERRUPT_MASK MaskReg; // 0x00
	INTERRUPT_EVENTMASK EventMaskReg; // 0x04
	INTERRUPT_TRIGGER_SELECTION RisingTrigSelectReg; // 0x08
	INTERRUPT_TRIGGER_SELECTION FallingTrigSelectReg; // 0x0C
	SOFTWARE_INTERRUPT_EVENT SoftwareInterruptEventReg; // 0x10
	PENDING PendingReg; // 0x14
};

#endif
