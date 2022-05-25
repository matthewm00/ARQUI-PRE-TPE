#ifndef COMMANDS_H
#define COMMANDS_H

#include <shell.h>
#include <stdint.h>
#include <libc.h>
#include <syscalls.h>
#include <RTCID.h>
#include <games.h>

#define REGISTER_AMOUNT 19

void help(int argc, char **argv);
void getCurrentDayTime(int argc, char **argv);
void getInfoReg(int argc, char **argv);
void divZero(int argc, char **argv);
void opCode(int argc, char **argv);
void clear(int argc, char **argv);
void exit(int argc, char **argv);
void getMem(int argc, char **argv);
void _opcodeExp(void);
void _divZeroExp(void);
// void changeColour(int argc, char **argv, int bg);
void games(int argc, char **argv);

int checkArgCount(int argc, int argsAllowed);
void callMemStatus(int argc, char **argv);
void callSemStatus(int argc, char **argv);
void callProcessStatus(int argc, char **argv);
void callKillProcess(int argc, char **argv);
void callSetPriority(int argc, char **argv);
void callBlockProcess(int argc, char **argv);
void callUnblockProcess(int argc, char **argv);

void cat(int argc, char **argv);
void loop(int argc, char **argv);
void callPipeStatus(int argc, char **argv);
void filter(int argc, char **argv);
void wc(int argc, char **argv);

#endif