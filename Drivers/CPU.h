#ifndef CPU_H
#define CPU_H


/**
 * @brief Clear the PRIMASK bit to ensure interrupts are enabled.
 *  Note: Not required in most cases unless you have explicitly disabled interrupts earlier
 * 
 */
void TurnOnInterrupts();

/**
 * @brief Sets the PRIMASK bit to disable interrupts.
 * 
 */
void TurnOffInterrupts();







#endif