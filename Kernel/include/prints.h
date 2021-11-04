#ifndef PRINTS_H
#define PRINTS_H

#include <colors.h>
#include <stdint.h>

void printIntDec(uint64_t num);
void printIntHex(uint64_t num);
void printIntBin(uint64_t num);
void printLine();
uint64_t uintToBase(uint64_t value, char *buffer, uint32_t base);
#endif