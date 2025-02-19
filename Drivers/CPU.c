#include "CPU.h"


void TurnOnInterrupts() {
    // See 1-Datasheets/STM32/'STM32 M4 Programming Manual.pdf' for more info
    // __asm volatile ("cpsie i");
    __asm volatile ("cpsie i" : : : "memory");
}

void TurnOffInterrupts() {
    // See 1-Datasheets/STM32/'STM32 M4 Programming Manual.pdf' for more info
    // __asm volatile ("cpsid i");
    __asm volatile ("cpsid i" : : : "memory");
}