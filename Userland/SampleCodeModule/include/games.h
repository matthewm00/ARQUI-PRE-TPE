#ifndef GAMES_H
#define GAMES_H

#include <stdint.h>
#include <libc.h>
#include <syscalls.h>
#include <RTCID.h>

void startGames();
void hangman(char c);
void sudoku(char c);
void printTime();
void stopWatch();
void updateSecondsStopwatch();
#endif