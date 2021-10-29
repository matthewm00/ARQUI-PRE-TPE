#ifndef SYS_CALL_DISPATCHER
#define SYS_CALL_DISPATCHER

#include <stdint.h>
#include <naiveConsole.h>
#include <lib.h>
#include <interrupts.h>
#include <keyboard.h>

#define RAX 0 // syscall_id
#define RDI 1 // buffer
#define RSI 2 // length
#define RDX 3 // backgroundColor
#define R10 4 //  fontColor
#define R8 5
#define R9 6
#define REGISTERS 7

void read(uint64_t *buff, uint64_t length);
void write(uint64_t *buff, uint64_t length, uint64_t fontColor, uint64_t background_color);

void sysCallDispatcher(uint64_t *r[REGISTERS]);

#endif