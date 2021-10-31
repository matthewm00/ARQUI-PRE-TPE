#ifndef SHELL_H
#define SHELL_H

#define USER_SIZE 25
#define BUFFER_SIZE 100
#define MAX_ARGUMENTS 3

#include <libC.h>
#include <stdint.h>
#include <commands.h>
#include <utils.h>

void initialize();
void getCommandAndRun();
void printUser();
#endif