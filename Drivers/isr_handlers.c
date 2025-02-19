#include "isr_handlers.h"


void HardFault_Handler(void) {
    uint32_t *hardfault_stat_reg = HARDFAULT_STAT_REG;
    uint32_t bus_fault_on_vec_table = (*hardfault_stat_reg) & (1 << 1);
    uint32_t forced_fault = (*hardfault_stat_reg) & (1 << 30);
    bool bus_fault_triggered = bus_fault_on_vec_table == 0 ? false : true;
    bool forced_fault_triggered = forced_fault == 0 ? false : true;
    while(1);
}

void MemManage_Handler(void) {
    uint32_t *shcsr_reg = SHCSR;
    uint32_t fault_state = (*shcsr_reg) & (1 << 13);
    bool fault_triggered = fault_state == 0 ? false : true;
    while(1);
}

void BusFault_Handler(void) {
    uint32_t *shcsr_reg = SHCSR;
    uint32_t fault_state = (*shcsr_reg) & (1 << 14);
    bool fault_triggered = fault_state == 0 ? false : true;
    while(1);
}

void UsageFault_Handler(void) {
    uint32_t *shcsr_reg = SHCSR;
    uint32_t fault_state = (*shcsr_reg) & (12 << 3);
    bool fault_triggered = fault_state == 0 ? false : true;
    while(1);
}




