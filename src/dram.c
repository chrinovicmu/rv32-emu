#include "../includes/dram.h"

uint64_t dram_load_8(DRAM *dram, uint64_t addr)
{
    uint64_t base_offset = addr - DRAM_BASE;
    uint64_t value = 0; 
    value |= dram->mem[base_offset];

    return value;
}

uint64_t dram_load_16(DRAM *dram, uint64_t addr)
{
    uint64_t base_offset = addr - DRAM_BASE;

    uint8_t byte0 = dram->mem[base_offset]; 
    uint8_t byte1 = dram->mem[base_offset + 1]; 

    uint64_t value = 0; 
    value |= (uint64_t)byte0; 
    value |= (uint64_t)byte1 << 8; 

    return value; 

}

uint64_t dram_load_32(DRAM * dram, uint64_t addr)
{
    uint64_t base_offset = addr - DRAM_BASE; 

    uint8_t byte0 = dram->mem[base_offset];
    uint8_t byte1 = dram->mem[base_offset + 1];
    uint8_t byte2 = dram->mem[base_offset + 2]; 
    uint8_t byte3 = dram->mem[base_offset + 3]; 

    uint64_t value = 0; 
    value |= (uint64_t)byte0; 
    value |= (uint64_t)byte1 << 8; 
    value |= (uint64_t)byte2 << 16; 
    value |= (uint64_t)byte3 << 24; 

    return value; 
}

uint64_t dram_load_64(DRAM * dram, uint64_t addr)
{
    uint64_t base_offset = addr - DRAM_BASE; 

    uint8_t byte0 = dram->mem[base_offset]; 
    uint8_t byte1 = dram->mem[base_offset + 1]; 
    uint8_t byte2 = dram->mem[base_offset + 2]; 
    uint8_t byte3 = dram->mem[base_offset + 3]; 
    uint8_t byte4 = dram->mem[base_offset + 4]; 
    uint8_t byte5 = dram->mem[base_offset + 5]; 
    uint8_t byte6 = dram->mem[base_offset + 6]; 
    uint8_t byte7 = dram->mem[base_offset + 7];

    uint64_t value = 0; 

    value |= (uint64_t)byte0;
    value |= (uint64_t)byte1 << 8; 
    value |= (uint64_t)byte2 << 16; 
    value |= (uint64_t)byte3 << 24; 
    value |= (uint64_t)byte4 << 32; 
    value |= (uint64_t)byte5 << 40;
    value |= (uint64_t)byte6 << 48; 
    value |= (uint64_t)byte7 << 56; 

    return value;
}

void dram_store_8(DRAM * dram, uint64_t addr, uint64_t value)
{
    uint64_t base_offset = addr - DRAM_BASE; 
    dram->mem[base_offset] = (uint8_t)(value & 0xFF); 
}

void dram_store_16(DRAM * dram, uint64_t addr, uint64_t value)
{
    uint64_t base_offset = addr - DRAM_BASE; 

    dram->mem[base_offset] = (uint8_t) (value & 0xFF);
    dram->mem[base_offset + 1] = (uint8_t) ((value >> 8) & 0xFF); 
}

void dram_store_32(DRAM * dram, uint64_t addr, uint64_t value)
{
    uint64_t base_offset = addr - DRAM_BASE; 

    dram->mem[base_offset] = (uint8_t)(value & 0xFF); 
    dram->mem[base_offset + 1] = (uint8_t)((value >> 8)  & 0xFF); 
    dram->mem[base_offset + 2] = (uint8_t)((value >> 16) & 0xFF); 
    dram->mem[base_offset + 3] = (uint8_t)((value >> 24) & 0xFF); 
}
void dram_store_64(DRAM * dram, uint64_t addr, uint64_t value)
{
    uint64_t base_offset = addr = DRAM_BASE; 

    dram->mem[base_offset] = (uint8_t)(value & 0xFF); 
    dram->mem[base_offset + 1] = (uint8_t)((value >> 8)  & 0xFF);
    dram->mem[base_offset + 2] = (uint8_t)((value >> 16) & 0xFF); 
    dram->mem[base_offset + 3] = (uint8_t)((value >> 24) & 0xFF); 
    dram->mem[base_offset + 4] = (uint8_t)((value >> 32) & 0xFF); 
    dram->mem[base_offset + 5] = (uint8_t)((value >> 40) & 0xFF); 
    dram->mem[base_offset + 6] = (uint8_t)((value >> 48) & 0xFF); 
    dram->mem[base_offset + 7] = (uint8_t)((value >> 56) & 0xFF); 
}

uint64_t dram_load(DRAM * dram, uint64_t addr, uint64_t size)
{
    switch (size)
    {
        case 8:
            return dram_load_8(dram, addr);
            break; 
        case 16:
            return dram_load_16(dram, addr); 
            break; 
        case 32:
            return dram_load_32(dram, addr); 
            break; 
        case 64:
            return dram_load_64(dram, addr); 
    }
    return 1; 
}

void dram_store(DRAM * dram, uint64_t addr, uint64_t size, uint64_t value)
{
    switch (size)
    {

        case 8:
            dram_store_8(dram, addr, value); 
            break; 
        case 16:
            dram_store_16(dram, addr, value);
            break; 
        case 32:
            dram_store_32(dram, addr, value);
            break; 
        case 64:
            dram_store_64(dram, addr, value);
            break; 
    }

}


