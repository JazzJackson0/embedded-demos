#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION                    1
#define configCPU_CLOCK_HZ                      ( 16000000UL )  // 16MHz System Clock
#define configTICK_RATE_HZ                      1000
#define configMAX_PRIORITIES                    10 // 0 - 9
#define configMINIMAL_STACK_SIZE                (128) // Minimum
#define configTOTAL_HEAP_SIZE                   (10 * 1024)
#define configMAX_TASK_NAME_LEN                 21
#define configUSE_16_BIT_TICKS                  0

/* Cortex-M specific definitions */

/**
 * @brief Preprocessor replaces vPortSVCHandler with SVCall_Handler 
 * 
 */
#define vPortSVCHandler     SVCall_Handler  

/**
 * @brief Preprocessor replaces xPortPendSVHandler with PendSV_Handler
 * 
 */
#define xPortPendSVHandler  PendSV_Handler

/**
 * @brief Preprocessor replaces xPortSysTickHandler with SysTick_Handler
 * 
 */
#define xPortSysTickHandler  SysTick_Handler

/**
 * @brief Defines the number of priority bits available in the NVIC.
 * 
 */
#define configPRIO_BITS                         4

/**
 * @brief Defines the LOWEST possible interrupt priority in your system.
 *         FreeRTOS runs its system tick and some critical internal functions at this priority.
 * 
 */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15

/**
 * @brief The NUMERICALLY highest priority an interrupt can have if it calls FreeRTOS API functions.
 *      FreeRTOS disables interrupts that are above this level when critical sections are executed.
 *      This prevents high-priority interrupts from interfering with the FreeRTOS scheduler.
 * 
 */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/**
 * @brief Defines the priority of FreeRTOS system interrupts (e.g., PendSV and SysTick).
 *          Same process as below but for storing the loest priority level.
 * 
 */
#define configKERNEL_INTERRUPT_PRIORITY         (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/**
 * @brief The hardware priority value actually stored in the NVIC register.
 *  Example: for M4 architecture, 5 needs to be shifted over 4 bits so it sits in the HIGHER section of the byte
 *          or else it would not be read. 
 *          So: 0000 0101 becomes 0101 0000
 *      
 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1

/* Hook functions */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          2

#endif /* FREERTOS_CONFIG_H */
