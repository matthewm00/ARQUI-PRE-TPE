#ifndef SHELL_H
#define SHELL_H

#include <libc.h>
#include <commands.h>
#include <stdint.h>
#include <userSyscalls.h>
#include <testUtil.h>
#include <memoryTest.h>
#include <processTest.h>
#include <priorityTest.h>
#include <semaphoreTest.h>

#define USERLAND_INIT_PID 1
#define BUFFER_SIZE 100
#define MAX_ARGUMENTS 5
#define USER_SIZE 25
#define COMMAND_COUNT 29
#define TEST_COMMAND_COUNT 5
#define TEST_COMMAND_START 22

void initialize(int argc, char **argv);
void shellExecute();
void printUser();
void _setStack();

typedef struct t_command
{
  void (*commandFn)(int, char **);
  char *name;
  char *description;
} t_command;

typedef struct t_shell
{
  char userName[USER_SIZE];
  t_command commands[COMMAND_COUNT];
} t_shell;
#endif