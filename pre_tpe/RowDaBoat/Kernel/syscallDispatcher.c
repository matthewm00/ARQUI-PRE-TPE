#include <stdint.h>
#include <naiveConsole.h>
#include <lib.h>
#include <interrupts.h>

typedef uint64_t (*FunSyscall)(uint64_t, uint64_t, uint64_t); // puntero a funcion

uint64_t read(unsigned int fd, const char *buff, unsigned int count);
uint64_t write(unsigned int fd, const char *buff, unsigned int count);

static FunSyscall sysCalls[255] = {(FunSyscall)&read, (FunSyscall)&write};

// otra opcion usar un switch para las distintas syscalls

// read

// write

// resto...

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx)
{
    FunSyscall syscall = sysCalls[rcx];
    if (syscall != 0)
    {
        return syscall(rdi, rsi, rdx);
    }
    return 0;
}