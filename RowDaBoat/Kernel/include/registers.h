#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <stdint.h>
#define REGISTERS 19

void saveRegisters(uint64_t *stackFrame);
void saveRegistersASM();
uint64_t *getRegisters();
#endif