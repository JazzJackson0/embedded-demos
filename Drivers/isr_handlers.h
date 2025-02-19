#ifndef ISR_HANDLERS_H
#define ISR_HANDLERS_H
#include <stdint.h>
#include <stdbool.h>

#define SHCSR (uint32_t*) 0xE000ED24 // System Handler Control and State Register
#define HARDFAULT_STAT_REG (uint32_t*) 0xE000ED2C
#define MEM_MANAGE_FAULT_ADDR_REG (uint32_t*) 0xE000ED34 // Address of location that generated MemManage fault
#define BUS_FAULT_ADDR_REG (uint32_t*) 0xE000ED38 // Address of location that generated Bus fault





#endif