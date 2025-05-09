
#ifndef CPU_H 
#define CPU_H 

#include "bus.h"
#include <cstdint>
#include <stdint.h>

struct CPU{
    uint64_t registers[32]; 
    uint64_t pc;
    struct BUS bus; 
}; 
typedef struct CPU CPU;

void  cpu_init(CPU *cpu); 
uint32_t cpu_fetch(CPU *cpu);
int cpu_execute(CPU *cpu, uint32_t instruction); 
void dump_registers(CPU *cpu); 

#endif // !CPU_H 

