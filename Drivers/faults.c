#include "faults.h"

void enable_faults(void) {
    enable_busfault();
    enable_memmanagefault();
    enable_usagefault();
}

void enable_usagefault(void) {
    uint32_t *shcsr_reg = SHCSR_REG;
    (*shcsr_reg) |= (1 << 18);
}

void enable_busfault(void) {
    uint32_t *shcsr_reg = SHCSR_REG;
    (*shcsr_reg) |= (1 << 17);
}

void enable_memmanagefault(void) {
    uint32_t *shcsr_reg = SHCSR_REG;
    (*shcsr_reg) |= (1 << 16);
}

