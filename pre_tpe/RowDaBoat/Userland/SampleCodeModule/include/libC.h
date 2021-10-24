#ifndef _LIB_C_H_
#define _LIB_C_H_

#include <stdint.h>
#include <stdarg.h>

void putChar(char str);
char getChar();

void printf(const char *format, ...);
int scanf(const char *format, ...);
int strToInt(char *charValue);
int numToStr(char *str, int num);
int strcmp(char *s1, char *s2);
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);
int numToBase(uint64_t value, uint_least32_t base, uint64_t *buffer);
char *strcpy(char *destination, const char *source);

void parseHexa(char *buff, int dim);
void printBase(uint64_t value, uint_least32_t base);
#endif