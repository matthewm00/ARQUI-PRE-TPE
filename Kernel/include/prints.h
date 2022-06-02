#ifndef PRINTS_H
#define PRINTS_H

#include <colors.h>
#include <stdint.h>
#include <stdarg.h>

void printIntDec(uint64_t num);
void printIntHex(uint64_t num);
void printIntBin(uint64_t num);
int strlen(char *str);
void printLine();
// void strcpy(char dest[], const char source[]);
void strcpy(char *str1, char *str2);
uint64_t uintToBase(uint64_t value, char *buffer, uint32_t base);
int printf(char const *fmt, ...);
void putChar(char c);
char *intToStr(int value, char *buffer, int base);
#endif