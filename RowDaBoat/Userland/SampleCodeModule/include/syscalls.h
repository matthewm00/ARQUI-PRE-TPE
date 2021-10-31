#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

#include <stdint.h>

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

// extern void syscall(uint64_t syscallId, ...);
// extern void syscall(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);
uint64_t syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

#endif