#include <registers.h>
static uint64_t registers[REGISTERS];

// SORTED REGISTERS
// GS,FS,R15,R14,R13,R12,R11,R10,R9,R8,RSI,RDI,RBP,RDX,RCX,RBX,RAX,RIP
void getRegisterState(uint64_t *buff)
{
    for (int i = 0; i < REGISTERS; i++)
    {
        buff[i] = registers[i];
    }
}