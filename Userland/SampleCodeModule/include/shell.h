#ifndef SHELL_H
#define SHELL_H

<<<<<<< HEAD
#define USER_SIZE 25
#define BUFFER_SIZE 1000
#define MAX_ARGUMENTS 5
#define COMMAND_COUNT 36
#define TEST_COMMAND_COUNT 5
#define TEST_COMMAND_START (COMMAND_COUNT - TEST_COMMAND_COUNT) - 2

void startShell(int argc, char **argv);
void printUser();

typedef struct t_command {
  void (*commandFn)(int, char **);
  char *name;
  char *description;
} t_command;

typedef struct t_shell {
  char userName[USER_SIZE];
  t_command commands[COMMAND_COUNT];
=======
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
#define COMMAND_COUNT 36
#define TEST_COMMAND_COUNT 5
#define TEST_COMMAND_START (COMMAND_COUNT - TEST_COMMAND_COUNT) - 2

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
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
} t_shell;
#endif