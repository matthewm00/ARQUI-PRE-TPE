#ifndef SYS_CALL_DISPATCHER
#define SYS_CALL_DISPATCHER

#include <stdint.h>
#include <naiveConsole.h>
#include <lib.h>
#include <interrupts.h>
#include <keyboard.h>
#include <registers.h>

// #define RAX 0 // syscall_id
// #define RDI 1 // buffer
// #define RSI 2 // length
// #define RDX 3 // backgroundColor
// #define R10 4 //  fontColor
// #define R8 5
// #define R9 6
// #define REGISTERS 7

typedef enum
{
    READ = 0,
    RTC_TIME = 1,
    WRITE = 3,
    GETCHAR = 4,
    CLEAR = 5,
    RUN = 7,
    EXIT = 8,
    INFOREG = 9,
    PRINTMEM = 10
} syscallID;

void read(uint64_t *buff, uint64_t length);
void write(uint64_t *buff, uint64_t length, t_color fontColor, t_color background_color);

extern void exit(void);
// void sysCallDispatcher(uint64_t *r[REGISTERS]);
uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
#endif