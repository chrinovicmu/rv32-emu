#ifndef BUS_H 
#define BUS_H  

#include "dram.h"

struct BUS{
    struct DRAM dram; 
}; 

typedef struct BUS BUS;

uint64_t bus_load(BUS * bus, uint64_t addr, uint64_t size); 
void bus_store(BUS * bus, uint64_t addr, uint64_t size, uint64_t value); 

#endif // !BUS_H 


