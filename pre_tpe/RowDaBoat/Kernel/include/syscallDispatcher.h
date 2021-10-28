#ifndef SYS_CALL_DISPATCHER
#define SYS_CALL_DISPATCHER

#include <stdint.h>
#include <naiveConsole.h>
#include <lib.h>
#include <interrupts.h>
#include <keyboard.h>
#include <shell.h>
#define RAX 0
#define RDI 1
#define RSI 2
#define RDX 3
#define RCX 4
#define R8 5
#define R9 6
#define REGISTERS 7

void read(uint64_t *buff, uint64_t length);
void write(uint64_t *buff, uint64_t length, uint64_t fontColor, uint64_t background_color);

uint64_t sysCallDispatcher(uint64_t *r[REGISTERS]);

#endif