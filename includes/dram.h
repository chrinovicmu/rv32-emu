#ifndef DRAM_H 
#define DRAM_H 

#include <stdint.h>

#define DRAM_SIZE 1024 * 1024 * 1  /*1mb*/ 
#define DRAM_BASE 0x80000000

struct DRAM{
    uint64_t    mem[DRAM_SIZE]; 
};
typedef struct DRAM DRAM; 



#endif 
