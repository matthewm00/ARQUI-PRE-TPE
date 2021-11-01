#include <registers.h>
static uint64_t registers [REGISTERS];

// SORTED REGISTERS
// GS,FS,R15,R14,R13,R12,R11,R10,R9,R8,RSI,RDI,RBP,RDX,RCX,RBX,RAX,RIP
void saveRegisters(uint64_t *stackFrame)
{
    for (int i = 0; i < REGISTERS; i++)
    {
        registers[i] = stackFrame[i];
    }
}

uint64_t * getRegisters(){
    return registers;
}