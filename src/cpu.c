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
    uint32_t inst = bus_load(&(cpu->bus), cpu->pc, 32);
}

uint64_t cpu_load(CPU *cpu, uint64_t addr, uint64_t size)
{
    return bus_load(&(cpu->bus), addr, size); 
}

void cput_store(CPU *cpu, uint64_t addr, uint64_t size, uint64_t value)
{
    bus_store(&(cpu->bus), addr, size, value); 
}

uint64_t rd(uint32_t inst)
{
    return (inst >> 7)& 0x1F; 
}

uint64_t rs1(uint32_t inst)
{
    return (inst >> 15) & 0x1F;
}

uint64_t rs2(uint32_t inst)
{
    return (inst >> 20) & 0x1F; 
}

uint64_t imm_I(uint32_t inst)
{
    return ((int64_t)(int32_t)(inst & 0xFFF00000) >> 20); 
}

uint64_t imm_S(uint32_t inst)
{
    int32_t imm_11_5 = (int32_t)(inst & 0xFE000000) >> 20; 
    int32_t imm_4_0 = (int32_t)(inst >> 7) & 0x1F; 

    int32_t imm = (imm_11_5 << 5) | imm_4_0; 

    return (int64_t)(int32_t)(imm << 20) >> 20;
};

uint64_t imm_B(uint32_t inst)
{
    int32_t imm_12 = (inst >> 31) & 0x1; 
    int32_t imm_11 = (inst >> 7) & 0x1; 
    int32_t imm_10_5 = (inst >> 25) & 0x3F; 
    int32_t imm_4_1 = (inst >> 8) & 0xF; 

    int32_t imm = (imm_12 << 12) |
                  (imm_11 << 11) | 
                  (imm_10_5 << 5)|
                  (imm_4_1) << 1); 

    return (int64_t)((int32_t)(imm << 19) >> 19); 
}

uint64_t imm_U(uint32_t inst)
{
    return (uint64_t)(int32_t)(inst & 0xFFFFF000); 
}

uint64_t imm_J(uint32_t inst)
{
    int32_t imm_20    = (inst >> 31) & 0x1;
    int32_t imm_10_1  = (inst >> 21) & 0x3FF;
    int32_t imm_11    = (inst >> 20) & 0x1;
    int32_t imm_19_12 = (inst >> 12) & 0xFF;

    int32_t imm = (imm_20 << 20) |
                  (imm_19_12 << 12) |
                  (imm_11 << 11) |
                  (imm_10_1 << 1);

    return (int64_t)((int32_t)(imm << 11) >> 11);
}
uint32_t shamt(uint32_t inst)
{
    return (int32_t)(imm_I(inst) & 0x1F); 
}




