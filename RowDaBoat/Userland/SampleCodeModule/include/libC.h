#ifndef _LIB_C_H_
#define _LIB_C_H_

#include <stdint.h>
#include <stdarg.h>
#include <utils.h>
#include <syscalls.h>
#include <colors.h>

#define BUFF_LEN 100

void putChar(char c);
char getChar();

void printf(char *str, ...);
int scanf(char *str, ...);

#endif