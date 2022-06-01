#ifndef SHELL_H
#define SHELL_H

#include <libc.h>
#include <commands.h>
#include <stdint.h>
#include <userSyscalls.h>
#include <test_mm.h>
#include <test_priority.h>
#include <test_processes.h>
#include <test_sync.h>

#define USERLAND_INIT_PID 1
#define BUFFER_SIZE 100
#define MAX_ARGUMENTS 5
#define FOREGROUNG 1
#define BACKGROUND 0

void initialize(int argc, char **argv);
void shellExecute();
void _setStack();

#endif