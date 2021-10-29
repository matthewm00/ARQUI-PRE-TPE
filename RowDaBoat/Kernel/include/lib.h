#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <syscallDispatcher.h>

void *memset(void *destination, int32_t character, uint64_t length);
void *memcpy(void *destination, const void *source, uint64_t length);

char *cpuVendor(char *result);

int numToStr(char *str, int num);
int BCDtoInt(uint64_t number);

#endif