#ifndef FAULTS_H
#define FAULTS_H
#include <stdint.h>

#define SHCSR_REG (uint32_t*) 0xE000ED24 // System Handler Control and State Register

void enable_faults(void);
void enable_usagefault(void);
void enable_busfault(void);
void enable_memmanagefault(void);

#endif