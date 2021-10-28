#ifndef _LIB_C_H_
#define _LIB_C_H_

#include <stdint.h>
#include <stdarg.h>
#include <utils.h>

void putChar(char str);
char getChar();

void printf(const char *format, ...);
int scanf(const char *format, ...);

#endif