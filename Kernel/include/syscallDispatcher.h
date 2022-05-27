#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stdint.h>
#include <syscalls.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <time.h>

#include <memoryManager.h>
#include <pipes.h>
#include <processManager.h>
#include <processManagerQueue.h>
#include <semaphores.h>
#include <syscallDispatcher.h>

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

#endif