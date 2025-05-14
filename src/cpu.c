#include <stdio.h>
#include "../includes/cpu.h"
#include "../includes/opcodes.h"


#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[31m"
#define ANSI_RESET   "\x1b[0m"

void print_opperation(const char *s)
{
    printf("%s%s%s\n", ANSI_BLUE, s, ANSI_RESET);
}
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


void exec_ADDI(CPU* cpu, int32_t inst)
{
    uint32_t imm = imm_I(inst); 
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst) + (uint64_t)imm];
    print_opperation("addI\n")
}

void exec_SLLI(CPU *cpu, uint32_t inst)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1[inst]] << shamt(inst);
    print_opperation("slli\n")
}

void exec_SRAI(CPU *cpu, uint32_t inst)
{
    uint64_t imm = imm_I(int32_t); 
    cpu
}
void exec_SLTI(CPU *cpu, uint32_t inst)
{
    uint64_t imm = imm_I(inst);
    cpu->regs[rd(inst)] = (cpu->regs[rs1(inst)] < (int64_t) imm)?1:0;
    print_op("slti\n");
}

void SLTIU(CPU * cpu, uint32_t inst)
{
    uint64_t imm = imm_I(inst); 
    cpu->regs[rd(inst)] = (cpu->regs[rs1(inst)] < (int64_t)imm)?1:0' '
}


void exec_XORI(CPU* cpu, uint32_t inst)
{
    uint64_t imm = imm_I(inst);
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] ^ imm;
    print_op("xori\n");
}

void exec_SRLI(CPU* cpu, uint32_t inst)
{
    uint64_t imm = imm_I(inst);
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] >> imm;
    print_op("srli\n");
}

void exec_SRAI(CPU* cpu, uint32_t inst) 
{
    uint64_t imm = imm_I(inst);
    cpu->regs[rd(inst)] = (int32_t)cpu->regs[rs1(inst)] >> imm;
    print_op("srai\n");
}

void exec_ORI(CPU* cpu, uint32_t inst)
{
    uint64_t imm = imm_I(inst);
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] | imm;
    print_op("ori\n");
}

void exec_ANDI(CPU* cpu, uint32_t inst)
{
    uint64_t imm = imm_I(inst);
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] & imm;
    print_op("andi\n");
}

void exec_ADD(CPU* cpu, uint32_t inst) 
{
    cpu->regs[rd(inst)] =
        (uint64_t) ((int64_t)cpu->regs[rs1(inst)] + (int64_t)cpu->regs[rs2(inst)]);
    print_op("add\n");
}

void exec_SUB(CPU* cpu, uint32_t inst) 
{
    cpu->regs[rd(inst)] =
        (uint64_t) ((int64_t)cpu->regs[rs1(inst)] - (int64_t)cpu->regs[rs2(inst)]);
    print_op("sub\n");
}

void exec_SLL(CPU* cpu, uint32_t inst)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] << (int64_t)cpu->regs[rs2(inst)];
    print_op("sll\n");
}

void exec_SLT(CPU* cpu, uint32_t inst)
{
    cpu->regs[rd(inst)] = (cpu->regs[rs1(inst)] < (int64_t) cpu->regs[rs2(inst)])?1:0;
    print_op("slt\n");
}

void exec_SLTU(CPU* cpu, uint32_t inst) 
{
    cpu->regs[rd(inst)] = (cpu->regs[rs1(inst)] < cpu->regs[rs2(inst)])?1:0;
    print_op("slti\n");
}

void exec_XOR(CPU* cpu, uint32_t inst)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] ^ cpu->regs[rs2(inst)];
    print_op("xor\n");
}

void exec_SRL(CPU* cpu, uint32_t inst) 
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] >> cpu->regs[rs2(inst)];
    print_op("srl\n");
}

void exec_SRA(CPU* cpu, uint32_t inst)
{
    cpu->regs[rd(inst)] = (int32_t)cpu->regs[rs1(inst)] >> 
        (int64_t) cpu->regs[rs2(inst)];
    print_op("sra\n");
}

void exec_OR(CPU* cpu, uint32_t inst) 
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] | cpu->regs[rs2(inst)];
    print_op("or\n");
}

void exec_AND(CPU* cpu, uint32_t inst)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] & cpu->regs[rs2(inst)];
    print_op("and\n");
}


void exec_LB(CPU* cpu, uint32_t inst)
{
    // load 1 byte to rd from address in rs1
    uint64_t imm = imm_I(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu->regs[rd(inst)] = (int64_t)(int8_t) cpu_load(cpu, addr, 8);
    print_op("lb\n");
}
void exec_LH(CPU* cpu, uint32_t inst)
{

    // load 2 byte to rd from address in rs1
    uint64_t imm = imm_I(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu->regs[rd(inst)] = (int64_t)(int16_t) cpu_load(cpu, addr, 16);
    print_op("lh\n");
}

void exec_LW(CPU* cpu, uint32_t inst)
{

    // load 4 byte to rd from address in rs1
    uint64_t imm = imm_I(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu->regs[rd(inst)] = (int64_t)(int32_t) cpu_load(cpu, addr, 32);
    print_op("lw\n");
}

void exec_LD(CPU* cpu, uint32_t inst)
{
    // load 8 byte to rd from address in rs1
    uint64_t imm = imm_I(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu->regs[rd(inst)] = (int64_t) cpu_load(cpu, addr, 64);
    print_op("ld\n");
}

void exec_LBU(CPU* cpu, uint32_t inst) 
{
    // load unsigned 1 byte to rd from address in rs1
    uint64_t imm = imm_I(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu->regs[rd(inst)] = cpu_load(cpu, addr, 8);
    print_op("lbu\n");
}
void exec_LHU(CPU* cpu, uint32_t inst)
{
    // load unsigned 2 byte to rd from address in rs1
    uint64_t imm = imm_I(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu->regs[rd(inst)] = cpu_load(cpu, addr, 16);
    print_op("lhu\n");
}
void exec_LWU(CPU* cpu, uint32_t inst)
{
    // load unsigned 2 byte to rd from address in rs1
    uint64_t imm = imm_I(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu->regs[rd(inst)] = cpu_load(cpu, addr, 32);
    print_op("lwu\n");
}
void exec_SB(CPU* cpu, uint32_t inst)
{
    uint64_t imm = imm_S(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu_store(cpu, addr, 8, cpu->regs[rs2(inst)]);
    print_op("sb\n");
}
void exec_SH(CPU* cpu, uint32_t inst) 
{
    uint64_t imm = imm_S(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu_store(cpu, addr, 16, cpu->regs[rs2(inst)]);
    print_op("sh\n");
}
void exec_SW(CPU* cpu, uint32_t inst) {

    uint64_t imm = imm_S(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu_store(cpu, addr, 32, cpu->regs[rs2(inst)]);
    print_op("sw\n");
}
void exec_SD(CPU* cpu, uint32_t inst) 
{
    uint64_t imm = imm_S(inst);
    uint64_t addr = cpu->regs[rs1(inst)] + (int64_t) imm;

    cpu_store(cpu, addr, 64, cpu->regs[rs2(inst)]);
    print_op("sd\n");
}

int cpu_execute(CPU *cpu, uint32_t inst)
{
    int opcode = inst & 0x7F; 
    int func3 = (inst >> 12) & 0x7; 
    int func7 = (inst >> 25) & 0x7F; 

    cpu->reg[0] = 0; 

}



