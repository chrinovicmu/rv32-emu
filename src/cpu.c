#include <stdio.h>
#include "../includes/cpu.h"

void cpu_init(CPU *cpu)
{
    cpu->registers[0] = 0x00; 
    cpu->registers[2] = DRAM_BASE + DRAM_SIZE; 
    cpu->pc = DRAM_BASE; 
}

uint32_t cpu_fetch(CPU *cpu)
{
    uint32_t intruction = bus_load(&(cpu->bus), cpu->pc, 32);
}

uint64_t cpu_load(CPU *cpu, uint64_t addr, uint64_t size)
{
    return bus_load(&(cpu->bus), addr, size); 
}

void cput_store(CPU *cpu, uint64_t addr, uint64_t size, uint64_t value)
{
    bus_store(&(cpu->bus), addr, size, value); 
}

uint64_t rd(uint32_t intruction)
{
    return (intruction >> 7)& 0x1F; 
}
uint64_t rs1(uint32_t intruction)
{
    return (intruction >> 15) & 0x1F;
}
uint64_t rs2(uint32_t intruction)
{
    return (intruction >> 20) & 0x1F; 
}
uint64_t imm_I

