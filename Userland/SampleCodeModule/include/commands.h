#ifndef COMMANDS_H
#define COMMANDS_H

#include <shell.h>
#include <stdint.h>
#include <libc.h>
#include <syscalls.h>
#include <RTCID.h>
#include <games.h>

void help(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void getCurrentDayTime(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void getInfoReg(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void divZero(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void opCode(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void clear(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void exit(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void getMem(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
void _opcodeExp(void);
// void changeColour(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE], int bg);
void games(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);
#endif