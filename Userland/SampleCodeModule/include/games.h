#ifndef GAMES_H
#define GAMES_H

#include <stdint.h>
#include <libc.h>
#include <syscalls.h>
#include <RTCID.h>
#include <sudoku.h>
#include <hangman.h>
#include <stopWatch.h>

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define WIDTH 1024
#define HEIGHT 768

int startGames();
void printTime();
void stopWatch();
void updateSecondsStopwatch();
void initStopWatch();

void changeCursorState(int state);
void setCursor(uint64_t x, uint64_t y);
#endif